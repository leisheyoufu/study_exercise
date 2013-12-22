#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJ1 = test.o

BIN1=  test

LIB = dlsym.so
LIB_OBJ = dlsym.o

CFLAGS += -g -ldl


all:$(BIN1) 
	

lib: $(LIB)
%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN1):$(OBJ1)
	$(CC) $(CFLAGS) -o $(BIN1) $(OBJ1) ./$(LIB)
$(LIB):$(LIB_OBJ)
	$(CC) -O -fpic -shared -lc -o $(LIB) $(LIB_OBJ)

clean:
	rm $(OBJ1) $(BIN1) $(LIB) $(LIB_OBJ)

clean_lib:
	rm $(LIB) $(LIB_OBJ)
