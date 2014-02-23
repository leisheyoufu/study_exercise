#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJ1 = rdir_srp.o rdir_sif.o rpc_dir_svc.o
OBJ2 = rdir.o rdir_cif.o rpc_dir_clnt.o

BIN1=  rdird
BIN2 = rdir

all:$(BIN1) $(BIN2)
CFLAGS += -lnsl
%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN1):$(OBJ1)
	$(CC) $(CFLAGS) -o $(BIN1) $(OBJ1)
$(BIN2):$(OBJ2)
	$(CC) $(CFLAGS) -o $(BIN2) $(OBJ2)
clean:
	rm $(OBJ1) $(BIN1) $(OBJ2) $(BIN2)

