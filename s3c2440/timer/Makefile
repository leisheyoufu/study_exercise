CFLAGS := -nostdlib
objs := head.o init.o serial.o main.o timer.o

timer.bin: $(objs)
	arm-linux-ld -Ttimer.lds -o timer_elf $^
	arm-linux-objcopy -O binary -S timer_elf $@
	arm-linux-objdump -D -m arm timer_elf > timer.dis
	
%.o:%.c
	arm-linux-gcc $(CFLAGS) -Wall -O2 -c -o $@ $<

%.o:%.S
	arm-linux-gcc $(CFLAGS) -Wall -O2 -c -o $@ $<

clean:
	rm -f timer.bin timer_elf timer.dis *.o		
	
