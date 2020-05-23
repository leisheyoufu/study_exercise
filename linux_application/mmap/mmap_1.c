
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define TITLE_LEN 32
#define BOOK_NUM 10

typedef struct {
    char title[TITLE_LEN];
    int  id;
} Book;

int main(int argc, char** argv) // map a normal file as shared mem:
{
    char * shm_file = "shm";
    int fd,i;
    Book *b_map;
    char title[TITLE_LEN];

    printf("ddd\n");
    fd=open(shm_file,O_CREAT|O_RDWR|O_TRUNC);

    //lseek(fd,sizeof(Book)*BOOK_NUM-1,SEEK_SET);
    write(fd,"",1); // must write something

    b_map = (Book*) mmap( NULL,sizeof(Book)*BOOK_NUM,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0 );
    close( fd );
    printf("the address of b_map is %u\n",b_map);

    for(i=0; i<BOOK_NUM; i++) {
        sprintf(title,"BOOK_%d",i);
        memcpy( (b_map+i)->title, title,strlen(title) );

        printf("%s\n",(b_map+i)->title);
        ( *(b_map+i) ).id = i;
    }
    printf(" initialize over \n ");
    sleep(10);
    munmap( b_map, sizeof(Book)*BOOK_NUM );
    printf( "umap ok \n" );
}

