#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJS = input.o
BIN =  input

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

