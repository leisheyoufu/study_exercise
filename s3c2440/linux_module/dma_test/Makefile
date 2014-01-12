ifneq ($(KERNELRELEASE),)
obj-m :=dma_copy.o

else
#KDIR:= /lib/modules/$(shell uname -r)
KDIR:= /home/cl/Project/s3c2440/linux-3.9.6

#KDIR:= /usr/include/build
all:
	make -C $(KDIR) M=$(PWD) modules 
clean:
	rm -f *.ko *.o *.mod.o *.mod.c .symvers

endif


