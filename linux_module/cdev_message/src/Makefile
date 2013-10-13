#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJS = cdev_message_tool.o


BIN =  cdev_message_tool

all:$(BIN)
CFLAGS += -lpthread
%.o:%.c %.h
	echo $(OBJS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):$(OBJS)
	echo $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)
cdev_pthread:cdev_pthread.o
	$(CC) $(CFLAGS) -o $@ $<
cdev_pthread.o:cdev_pthread.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm $(OBJS) $(BIN)

