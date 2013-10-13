
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define TITLE_LEN 32
#define BOOK_NUM 10

typedef struct{
	char title[TITLE_LEN];
	int  id;
} Book;

int main(int argc, char** argv) // map a normal file as shared mem:
{
	char * shm_file = "shm";
	int fd,i;
	Book *b_map;
	char title[TITLE_LEN];

	fd=open(shm_file,O_CREAT|O_RDWR); // flag si important

	b_map = (Book*) mmap( NULL,sizeof(Book)*BOOK_NUM,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0 );
	close( fd );

	printf ("%u\n",b_map);
	for(i=0; i<BOOK_NUM; i++)
	{
		printf("title = %s id = %d\n",(b_map+i)->title,(b_map+i)->id);
	}
	printf(" print over \n ");
	sleep(10);
	munmap( b_map, sizeof(Book)*BOOK_NUM );
	printf( "umap ok \n" );
}

