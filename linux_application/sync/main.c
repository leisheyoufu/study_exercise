#include "header.h"
int verbose;

void init_chunk_modify_descriptor(struct chunk_modify_descriptor *chunk_modify_desc)
{
    chunk_modify_desc->chunk_list= NULL;
    chunk_modify_desc->modify = 0;
}

int main( int argc, char **argv )
{
    if(argc < 3) {
        CL_INFO_PRINT("at least two argument!\n");
    }
    /* ************
    filename1  wait sync
    filename2  dest
    **************/
    char *filename1,*filename2;
    int fd1,fd2;
    char * buf;
    uint32 checksum1;
    struct stat st;
    struct chunk_descriptor *chunk_desc;
    struct chunk_modify_descriptor chunk_modify_desc;
    filename1 = argv[1];
    filename2 = argv[2];
    chunk_desc = malloc(sizeof(struct chunk_descriptor));
    if(!chunk_desc) {
        CL_ERR_PRINT("out memory");
        return -1;
    }
    if(get_file_stat(filename1,chunk_desc)!=0) {
        return -1;
    }
    build_hash_table(chunk_desc);
    init_chunk_modify_descriptor(&chunk_modify_desc);
    generate_modify_descriptor(filename2,&chunk_modify_desc,chunk_desc);
    // print_hash_stat();
     // print_chunk_modify(&chunk_modify_desc);
    sync_file(filename1,&chunk_modify_desc);
    cleanup_modify_list(&chunk_modify_desc);
    cleanup_hash_list();

    free(chunk_desc->chunk);
    free(chunk_desc);
    return 0;
}
