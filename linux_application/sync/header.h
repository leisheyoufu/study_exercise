#ifndef _HEADER_H_
#define _HEADER_H_

#include <sys/types.h>
#include<stdio.h>
#include<openssl/md5.h>
#include<string.h>
#include <sys/stat.h>
#include <unistd.h>
# include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>

typedef unsigned int uint32;



#define CL_DEBUG
#define CL_INFO
#define CL_ERROR

#ifdef CL_DEBUG
	#define CL_DBG_PRINT(fmt,args...) fprintf(stdout,"CL debug: %s  %d  "fmt,__FILE__,__LINE__,##args)
#else
	#define CL_DBG_PRINT(fmt,args...)
#endif

#ifdef CL_INFO
	#define CL_INFO_PRINT(fmt,args...) fprintf(stdout,"CL info: %s  %d  "fmt,__FILE__,__LINE__,##args)
#else
	#define CL_INFO_PRINT(fmt,args...)
#endif

#ifdef CL_ERROR
	#define CL_ERR_PRINT(fmt,args...) fprintf(stdout,"CL err: %s  %d  "fmt,__FILE__,__LINE__,##args)
#else
	#define CL_ERR_PRINT(fmt,args...)
#endif

#include "util.h"
#include "lib.h"


#include "byteorder.h"


#include "sync.h"

#endif // _HEADER_H_
