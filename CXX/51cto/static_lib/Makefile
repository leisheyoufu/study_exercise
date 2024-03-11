compile_type = release

CC = gcc
AR = ar
RANLIB = ranlib 

CCFLAGS = -Wall -Wextra -Wshadow -Wconversion -std=c99 -pedantic -O2 -g
ifeq ($(compile_type), release)
CCFLAGS =
endif


SRCS=$(wildcard src/*.c)
SRCS+=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
INCLUDES=$(wildcard include/*.h)
LIBS=$(wildcard lib/*.a)
DLLS=$(wildcard bin/*.so)

$(OBJS): $(INCLUDES)

libmath.so: $(OBJS)
	$(CC) -shared -fPIC $(CCFLAGS) $(SRCS) -o $@
	mkdir -p bin
	mv $@ bin/
	make clean

mathTest.o: $(INCLUDES)

mathTest: mathTest.o $(DLLS)
	$(CC) $(CCFLAGS) -o $@ $^
	make clean


# libmath.a: $(OBJS)
#     $(AR) rcu $@ $^
#     $(RANLIB) $@
#     make clean

# mathTest.o: $(INCLUDES)

# mathTest: mathTest.o $(LIBS)
#     $(CC) $(CCFLAGS) -o $@ $^
#     make clean


clean:
	rm -rf $(OBJS)

reinstall:
	@echo "Please comming soon.";