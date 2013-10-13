
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
	char temp[PAGE_SIZE];
	
	fd=open(shm_file,O_CREAT|O_RDWR);

	//lseek(fd,sizeof(Book)*BOOK_NUM-1,SEEK_SET);
	//write(fd,"",1); // must write something

//	fseek(fd,0,0);
	b_map = (char*) mmap( NULL,PAGE_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0 );
	close( fd );

	printf("After mmap 1 Initialized \n ");
	printf("the address of b_map is %u\n",b_map);
	
	
	strcpy(temp,b_map);
	printf("the kernal address is %s\n",temp);
	sleep(30);
	munmap( b_map,PAGE_SIZE );
	printf( "umap ok \n" );
}

