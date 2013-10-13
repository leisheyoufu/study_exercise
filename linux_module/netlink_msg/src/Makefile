#SRC = ./*.c
#OBJS = $(patsubst %.c,%.o,$(SRC))
OBJS = netlink_date.o


BIN = netlink_date

all:$(BIN)

%.o:%.c %.h
	echo $(OBJS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):$(OBJS)
	echo $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)


