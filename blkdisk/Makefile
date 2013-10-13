
obj-m :=rd.o

#KDIR:= /lib/modules/$(shell uname -r)
KDIR:=/home/cl/Project/linux/linux-3.9.6
all:
	make -C $(KDIR) M=$(PWD) modules 
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers *.order



