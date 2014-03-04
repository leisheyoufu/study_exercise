#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJ1 = main.o lib.o util.o sync.o
BIN1=  sync

all:$(BIN1)
CFLAGS += -lcrypto -g
%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN1):$(OBJ1)
	$(CC) $(CFLAGS) -o $(BIN1) $(OBJ1)

clean:
	rm $(OBJ1) $(BIN1)

