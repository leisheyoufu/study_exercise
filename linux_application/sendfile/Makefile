#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJS = cp_sendfile.o


BIN =  cp_sendfile

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

