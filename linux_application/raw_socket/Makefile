#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJ1 = raw_socket.o
#OBJ2 = signal_2.o

BIN1=  raw_socket
#BIN2 = signal_2

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

