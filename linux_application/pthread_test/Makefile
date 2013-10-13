#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJS = pthread.o


BIN =  pthread

all:$(BIN)
CFLAGS += -lpthread
%.o:%.c %.h
	echo $(OBJS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):$(OBJS)
	echo $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)
clean:
	rm $(OBJS) $(BIN)

