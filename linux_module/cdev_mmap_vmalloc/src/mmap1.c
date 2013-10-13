
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


#define PAGE_SIZE 4096

int main(int argc, char** argv) // map a normal file as shared mem:
{
	char * shm_file = "/dev/vir_cdev0";
	int fd,i;
	char *b_map;	
	char temp[] = "mmap_test1 by cl";

	
	fd=open(shm_file,O_CREAT|O_RDWR|O_TRUNC);

	//lseek(fd,sizeof(Book)*BOOK_NUM-1,SEEK_SET);
//	write(fd,"",1); // must write something

	b_map = (char*) mmap( NULL,PAGE_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0 );
	close( fd );
	printf("the address of b_map is %u\n",b_map);

	strncpy(b_map,temp,strlen(temp));
		printf(" initialize over \n ");
	printf("this is kernel string %s \n",b_map);

	sleep(30);
	munmap( b_map,PAGE_SIZE );
	printf( "umap ok \n" );
}

