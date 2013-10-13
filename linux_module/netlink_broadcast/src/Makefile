#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJS = netlink_broadcast.o


BIN = netlink_broadcast

all:$(BIN)

%.o:%.c %.h
	echo $(OBJS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):$(OBJS)
	echo $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)


