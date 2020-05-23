#ifndef _DIFF_H_
#define _DIFF_H_
#include "header.h"


struct chunk_buffer {
    void * chunk_desc;
    off_t offset;			/* offset in file of this chunk */
    int len;			/* length of chunk of file */
    int i;			/* index of this chunk */
    uint32 adler_sum;
    char md5_sum[MD5_SUM_LEN];
};
struct chunk_descriptor {
    off_t total;
    int chunk_count;
    struct chunk_buffer *chunk;
    char *buf;
};

struct chunk_buffer_list {
    int size;
    char buf[CHUNK_SIZE+1];
    struct chunk_buffer_list *next;
};

struct chunk_modify_descriptor {
    int modify;
    struct chunk_buffer_list *chunk_list;
};

struct hash_tag {
    struct chunk_buffer *chunk;
    struct hash_tag *next;
};

#define HASH_TABLE_SIZE (1<<16)
#define HASH_KEY(v) ((v)%HASH_TABLE_SIZE)

extern struct hash_tag hash_table[HASH_TABLE_SIZE];

int get_file_stat(char *filename,struct chunk_descriptor *chunk_desc);
void get_chunk_descriptor(struct chunk_descriptor *chunk_desc);
void init_hash_table();
void build_hash_table(struct chunk_descriptor *chunk_desc);
struct hash_tag* search_hash_table(uint32 checksum);
int generate_modify_descriptor(char *filename,struct chunk_modify_descriptor *chunk_modify_desc,struct chunk_descriptor *chunk_desc);
void generate_modify_buf(char *buf,off_t len,struct chunk_modify_descriptor *chunk_modify_desc,struct chunk_descriptor *chunk_desc);

// free
void cleanup_hash_list();
void cleanup_modify_list(struct chunk_modify_descriptor *chunk_modify_desc);

// debug
void print_hash_stat();
void print_stat(struct chunk_descriptor *chunk_desc);
void print_chunk_modify(struct chunk_modify_descriptor *chunk_modify_desc);

#endif // _DIFF_H_
