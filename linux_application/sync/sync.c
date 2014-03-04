#include "header.h"

struct hash_tag hash_table[HASH_TABLE_SIZE];

int get_file_stat(char *filename,struct chunk_descriptor *chunk_desc)
{
    int fd;
    struct stat st;
    if(chunk_desc == NULL) {
        return;
    }
    fd = open(filename,O_RDONLY|O_CREAT);
    if(fd == -1) {
        CL_ERR_PRINT("failed to open fd\n");
        return -1;
    }
    if (fstat(fd,&st) != 0) {
        CL_ERR_PRINT("fstat %s : %s\n",filename,strerror(errno));
        close(fd);
        return -1;
    }
    if (!S_ISREG(st.st_mode)) {
        CL_ERR_PRINT("%s : not a regular file\n",filename);
        close(fd);
        return -1;
    }
    if (st.st_size > 0) {
        chunk_desc->buf = map_file(fd,st.st_size);
        if (!chunk_desc->buf) return -1;
    } else {
        chunk_desc->buf = NULL;
    }
    chunk_desc->total = st.st_size;
    chunk_desc->chunk_count = st.st_size/CHUNK_SIZE;
    if(chunk_desc->chunk_count %CHUNK_SIZE !=0) {
        chunk_desc->chunk_count++;
    }
    chunk_desc->chunk = (struct chunk_buffer *)malloc(sizeof(struct chunk_buffer)*chunk_desc->chunk_count);
    get_chunk_descriptor(chunk_desc);
    //print_stat(chunk_desc);
    //unmap_file(chunk_desc->buf,st.st_size);
    return 0;
}

void get_chunk_descriptor(struct chunk_descriptor *chunk_desc)
{
    int i;
    struct chunk_buffer *chunk;
    if(chunk_desc == NULL || chunk_desc->chunk == NULL) {
        return;
    }
    off_t reminder = chunk_desc->total;
    for(i=0; i<chunk_desc->chunk_count; i++) {
        chunk = &(chunk_desc->chunk[i]);
        chunk->chunk_desc = (struct chunk_descriptor *)chunk_desc;
        chunk->offset = i*CHUNK_SIZE;
        chunk->len = MIN(reminder,CHUNK_SIZE);
        chunk->adler_sum = adler32(chunk_desc->buf+chunk->offset,chunk->len);
        MD5(chunk_desc->buf+chunk->offset,chunk->len,chunk->md5_sum);
        reminder -= CHUNK_SIZE;
    }
}

void init_hash_table()
{
    int i;
    for(i=0; i<HASH_TABLE_SIZE; i++) {
        hash_table[i].chunk = NULL;
        hash_table[i].next = NULL;
    }
}
/* 将整个文件分块的hash值放入hash table 加速查找，hash table 采用链hash */

void build_hash_table(struct chunk_descriptor *chunk_desc)
{
    int i,count;
    uint32 checksum;
    struct chunk_buffer *chunk_buf;
    struct hash_tag *h_tag,*next_tag;
    if(chunk_desc == NULL || chunk_desc->chunk == NULL) {
        return;
    }
    init_hash_table();
    count = chunk_desc->chunk_count;
    for( i=0; i<count; i++) {
        chunk_buf = &(chunk_desc->chunk[i]);
        checksum = chunk_buf->adler_sum;
        if(hash_table[HASH_KEY(checksum)].chunk == NULL) {
            hash_table[HASH_KEY(checksum)].chunk = chunk_buf;
        } else {
            int found;
            found = 0;
            h_tag = &hash_table[HASH_KEY(checksum)];
            next_tag = h_tag;
            do {
                if(h_tag->chunk->adler_sum ==checksum ) {
                    found = 1;
                    break;
                }
                h_tag = next_tag;
                next_tag =h_tag->next;
            } while(next_tag !=NULL);
            if(!found) {
                next_tag = (struct hash_tag*)malloc(sizeof(struct hash_tag));
                next_tag->chunk =chunk_buf;
                next_tag->next = NULL;
                h_tag ->next = next_tag;
            }
        }
    }
}


struct hash_tag* search_hash_table(uint32 checksum)
{
    struct hash_tag *h_tag;
    if( (h_tag = &hash_table[HASH_KEY(checksum)])
        && h_tag->chunk!=NULL) {
        while(h_tag!=NULL && h_tag->chunk !=NULL) {
            if(h_tag->chunk->adler_sum == checksum) {
                return h_tag;
            }
            h_tag = h_tag->next;
        }
    }
    return NULL;
}

int generate_modify_descriptor(char *filename,struct chunk_modify_descriptor *chunk_modify_desc,struct chunk_descriptor *chunk_desc)
{
    int fd;
    struct stat st;
    char *buf;
    if(chunk_modify_desc == NULL) {
        return;
    }
    fd = open(filename,O_RDONLY|O_CREAT);
    if(fd == -1) {
        CL_ERR_PRINT("failed to open fd\n");
        return -1;
    }
    if (fstat(fd,&st) != 0) {
        CL_ERR_PRINT("fstat %s : %s\n",filename,strerror(errno));
        close(fd);
        return -1;
    }
    if (!S_ISREG(st.st_mode)) {
        CL_ERR_PRINT("%s : not a regular file\n",filename);
        close(fd);
        return -1;
    }
    if (st.st_size > 0) {
        buf = map_file(fd,st.st_size);
        if (!buf) return -1;
    } else {
        return -1;
    }
    generate_modify_buf(buf,st.st_size,chunk_modify_desc,chunk_desc);
    return 0;
}

void generate_modify_buf(char *buf,off_t len,struct chunk_modify_descriptor *chunk_modify_desc,struct chunk_descriptor *chunk_desc)
{
    off_t cur;
    uint32 adler_sum;
    char md5_sum[MD5_SUM_LEN];
    int block_len;
    struct hash_tag *h_tag;
    struct chunk_buffer_list *curr_chunk,*next_chunk;
    int match;
    cur = 0;
    while(cur < len && cur<chunk_desc->total) {
        if(chunk_modify_desc->chunk_list == NULL) {
            chunk_modify_desc->chunk_list = (struct chunk_buffer_list *)malloc(sizeof(struct chunk_buffer_list));
            if(chunk_modify_desc->chunk_list == NULL) {
                CL_ERR_PRINT("out of memory\n");
                return ;
            }
            curr_chunk = chunk_modify_desc->chunk_list;
            next_chunk = curr_chunk;
        } else {
            next_chunk = (struct chunk_buffer_list *)malloc(sizeof(struct chunk_buffer_list));
        }
        match = 0;
        block_len = MIN(len-cur,CHUNK_SIZE);
        block_len = MIN(chunk_desc->total-cur,block_len);
        adler_sum = adler32(buf+cur,block_len);
        if( (h_tag = search_hash_table(adler_sum)) != NULL) {
            MD5(buf+cur,block_len,md5_sum);
            if( strncmp(h_tag->chunk->md5_sum,md5_sum,MD5_SUM_LEN) == 0) {
                strncpy(next_chunk->buf,buf+cur,block_len);
                next_chunk->buf[block_len] = '\0';
                next_chunk->size = block_len;
                cur+=block_len;
                match = 1;
                // 比较了hash table 的值后，还要考虑当前块的位置偏移才能判断文件是否更改
                if(h_tag->chunk->offset != cur) {
                    chunk_modify_desc->modify = 1;
                }
            }
        }
        if(!match) {
           // strncpy(next_chunk->buf,buf+cur,1);
            strncpy(next_chunk->buf,chunk_desc->buf+cur,1);
            next_chunk->size = 1;
            next_chunk->buf[1] = '\0';
            cur++;
            chunk_modify_desc->modify = 1;
        }
        curr_chunk->next = next_chunk;
        curr_chunk = next_chunk;
    }
    while(cur <chunk_desc->total) {
        block_len = MIN(chunk_desc->total-cur,CHUNK_SIZE);
        printf("block len = %d\n",block_len);
        next_chunk = (struct chunk_buffer_list *)malloc(sizeof(struct chunk_buffer_list));
        strncpy(next_chunk->buf,chunk_desc->buf+cur,block_len);
        next_chunk->buf[block_len] = '\0';
        next_chunk->size = block_len;
        cur+=block_len;
        chunk_modify_desc->modify = 1;
        curr_chunk->next = next_chunk;
        curr_chunk = next_chunk;
    }
}

void sync_file(char *filename,struct chunk_modify_descriptor *chunk_modify_desc)
{
    int fd;
    struct chunk_buffer_list *curr_chunk;
    fd = open(filename,O_RDWR|O_CREAT);
    if(fd == -1) {
        CL_ERR_PRINT("failed to open fd\n");
        return ;
    }
    curr_chunk = chunk_modify_desc->chunk_list;
    while(curr_chunk != NULL && curr_chunk->buf !=NULL) {
        write_buf(fd,curr_chunk->buf,curr_chunk->size);
        curr_chunk = curr_chunk->next;
    }
    close(fd);
}


void cleanup_hash_list()
{
    int i;
    struct hash_tag *h_tag,*next_tag;
    for(i=0; i<HASH_TABLE_SIZE; i++) {
        h_tag = hash_table[i].next;
        while(h_tag != NULL) {
            next_tag = h_tag->next;
            free(h_tag);
            h_tag = next_tag;
        }
    }
}

void cleanup_modify_list(struct chunk_modify_descriptor *chunk_modify_desc)
{
    struct chunk_buffer_list *curr_chunk,*next_chunk;
    curr_chunk = chunk_modify_desc->chunk_list;
    while(curr_chunk != NULL) {
        next_chunk = curr_chunk->next;
        free(curr_chunk);
        curr_chunk = next_chunk;
    }
}

void print_stat(struct chunk_descriptor *chunk_desc)
{
    int i,j;
    char buf[33] = {'\0'},tmp[3] = {'\0'};
    struct chunk_buffer *chunk;
    if(chunk_desc == NULL) {
        return ;
    }
    printf("chunk count = %d\n",chunk_desc->chunk_count);
    for(i=0; i<chunk_desc->chunk_count; i++) {
        chunk = &(chunk_desc->chunk[i]);
        printf("chunk count = %d len = %u\n",i,chunk->len);
        printf("adler_count = %d sum = %u\n",i,chunk->adler_sum);
        for (j = 0; j < 16; j++) {
            sprintf(tmp,"%2.2x",(char)chunk->md5_sum[j]);
            strcat(buf,tmp);
        }
        printf("md5 %s\n",buf);
    }
}

void print_hash_stat()
{
    int i;
    struct hash_tag *h_tag;
    for(i=0; i<HASH_TABLE_SIZE; i++) {
        h_tag = &hash_table[i];
        if(h_tag->chunk!=NULL) {
            do {
                printf(" %u --> ",h_tag->chunk->adler_sum);
                h_tag = h_tag->next;
            } while(h_tag !=NULL);
            printf("\n");
        }
    }
}

void print_chunk_modify(struct chunk_modify_descriptor *chunk_modify_desc)
{
    struct chunk_buffer_list *curr_chunk;
    curr_chunk = chunk_modify_desc->chunk_list;
    while(curr_chunk != NULL && curr_chunk->buf !=NULL) {
        printf("size = %d\n",curr_chunk->size);
        printf("%s",curr_chunk->buf);
        curr_chunk = curr_chunk->next;
    }
}




