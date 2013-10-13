#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJS = pv_test.o


BIN =  pv_test

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

