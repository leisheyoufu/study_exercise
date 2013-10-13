#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJS = tun.o
BIN =  tun

all:$(BIN)
CFLAGS += -lpthread -g
%.o:%.c %.h
	echo $(OBJS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):$(OBJS)
	echo $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)
clean:
	rm $(OBJS) $(BIN)

