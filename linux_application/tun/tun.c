#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/ioctl.h>  
#include <linux/if.h>
#include <netinet/in.h> 
#include <fcntl.h>    
#include <sys/socket.h>
#include <linux/if_tun.h>
#include <assert.h>

#define BUFFER_SIZE 4096
int tun_creat(char *dev,int flags)  
{  
	struct ifreq ifr;  
	int fd,err;  
	assert(dev != NULL);  
	if((fd = open ("/dev/net/tun",O_RDWR))<0) //you can replace it to tun to create tun device.  
		return fd;  
	memset(&ifr,0,sizeof (ifr));  
	ifr.ifr_flags|=flags;  
	if(*dev != '\0')  
		strncpy(ifr.ifr_name,dev,IFNAMSIZ);  
	if((err = ioctl(fd,TUNSETIFF,(void *)&ifr))<0)    // ioctl, the ifr doesn't have the name ,so the system will assign a name
	{  
		close (fd);  
		return err;  
	}  
	strcpy(dev,ifr.ifr_name);  
	return fd;  
}  


int main()
{
	int tun,ret;
	char tun_name[IFNAMSIZ];
	unsigned char buf[BUFFER_SIZE];
	tun_name[0] = '\0';

	tun = tun_creat(tun_name,IFF_TUN|IFF_NO_PI);

	if(tun < 0)
	{
		perror("tun_create");
		return 1;
	}

	printf("tun name is %s\n",tun_name);

	while (1) {  
		unsigned char ip[4];  

		ret = read(tun, buf, sizeof(buf));  
		if (ret < 0)  
			break;  
		memcpy(ip, &buf[12], 4);  
		memcpy(&buf[12], &buf[16], 4);  
		memcpy(&buf[16], ip, 4);  
		buf[20] = 0;  
		*((unsigned short*)&buf[22]) += 8;  
		printf("read %d bytes\n", ret);  
		ret = write(tun, buf, ret);  
		printf("write %d bytes\n", ret);  
	}  

	return 0;
}


