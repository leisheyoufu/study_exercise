#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJ1 = pci_scan.o names.o

BIN1=  pci_scan


all:$(BIN1) 
	


%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN1):$(OBJ1)
	$(CC) $(CFLAGS) -o $(BIN1) $(OBJ1) 

clean:
	rm $(OBJ1) $(BIN1) 

