#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJ1 = epoll.o
OBJ2 = client.o

BIN1=  epoll
BIN2 = client

all:$(BIN1) $(BIN2)
CFLAGS += -lpthread -g
%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN1):$(OBJ1)
	$(CC) $(CFLAGS) -o $(BIN1) $(OBJ1)
$(BIN2):$(OBJ2)
	$(CC) $(CFLAGS) -o $(BIN2) $(OBJ2)
clean:
	rm $(OBJ1) $(BIN1) $(OBJ2) $(BIN2)

