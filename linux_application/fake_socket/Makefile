#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJ1 = fake_socket.o ip_gen.o tcp_gen.o
#OBJ2 = signal_2.o

BIN1=  fake_socket
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

