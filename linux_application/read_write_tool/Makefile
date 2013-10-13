#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJS1 = block_read.o
OBJS2 = block_write.o

OBJS3 = byte_read.o
OBJS4 = poll.o
BIN1 =  block_read
BIN2 = block_write
BIN3 = byte_read
BIN4 = poll
all:$(BIN1) $(BIN2) $(BIN3) $(BIN4)
CFLAGS += -lpthread -g
%.o:%.c %.h
	echo $(OBJS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN1):$(OBJS1)
	$(CC) $(CFLAGS) -o $(BIN1) $(OBJS1)
$(BIN2):$(OBJS2)
	$(CC) $(CFLAGS) -o $(BIN2) $(OBJS2)
$(BIN3) : $(OBJS3)
	$(CC) $(CFLAGS) -o $(BIN3) $(OBJS3)
$(BIN4) : $(OBJS4)
	$(CC) $(CFLAGS) -o $(BIN4) $(OBJS4)
cdev_pthread:cdev_pthread.o
	$(CC) $(CFLAGS) -o $@ $<
cdev_pthread.o:cdev_pthread.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm $(OBJS1) $(BIN1)

