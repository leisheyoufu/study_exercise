CC ?= gcc
AR ?= ar  # 用来创建和维护静态库文件, 可直接将需要增加的.o 文件简单的追加到静态库的末尾;
RANLIB ?= ranlib  # 更新静态库中的符号索引表;

CCFLAGS ?= -Wall -Wextra -Wshadow -Wconversion -std=c99 -pedantic -O2 -g

# wildcard: 用来 匹配文件
# OBJS=$(SRCS:%.c=%.o): 含义为将 SRCS中的所有.c文件替换为同名的.o文件, 并赋值给OBJS
SRCS=$(wildcard indicators/*.c)
SRCS+=$(wildcard utils/*.c)
OBJS=$(SRCS:%.c=%.o)
AMAL=$(SRCS:%.c=%.ca)

.SUFFIXES: .c .o .h .ca

all: libindicators.a sample example1 example2 fuzzer smoke smoke_amal benchmark cli

indicators.h: build.tcl templates/indicators.h templates/indicators.c templates/candles.h templates/candles.c

# 创建静态库的过程.
libindicators.a: indicators.h candles.h indicators.c candles.c $(OBJS)
    $(CC) -c $(CCFLAGS) indicators.c -o indicators.o
    $(CC) -c $(CCFLAGS) candles.c -o candles.o
    $(AR) rcu $@ $^ indicators.o candles.o
    $(RANLIB) $@

# -lm 表示引用了math的库，libm


# 自动变量
# 假设您编写一个编译‘.c’文件生成‘.o’文件的规则：您怎样编写命令‘CC’，使它能够操作正确的文件名？您当然不能将文件名直接写进命令中，因为每次使用隐含规则操作的文件名都不一样。

# 您应该使用make的另一个特点，自动变量。这些变量在规则每次执行时都基于目标和依赖产生新值。例如您可以使用变量‘$@’代替目标文件名，变量‘$<’代替依赖文件名。

# 下面是自动变量列表：

# $@

# 规则的目标文件名。如果目标是一个档案成员，则变量‘$@’ 档案文件的文件名。对于有多个目标的格式规则（参阅格式规则简介），变量‘$@’是那个导致规则命令运行的目标文件名。

# $%

# 当目标是档案成员时，该变量是目标成员名，参阅使用make更新档案文件。例如，如果目标是‘foo.a(bar.o)'，则‘$%'的值是‘bar.o'，‘$@'的值是‘foo.a'。如果目标不是档案成员，则‘$%'是空值。

# $<

# 第一个依赖的文件名。如果目标更新命令来源于隐含规则，该变量的值是隐含规则添加的第一个依赖。参阅使用隐含规则。

# $?

# 所有比目标‘新’的依赖名，名字之间用空格隔开。对于为档案成员的依赖，只能使用已命名的成员。参阅使用make更新档案文件。

# $^

# 所有依赖的名字，名字之间用空格隔开。对于为档案成员的依赖，只能使用已命名的成员。参阅使用make更新档案文件。对同一个目标来说，一个文件只能作为一个依赖，不管该文件的文件名在依赖列表中出现多少次。所以，如果在依赖列表中，同一个文件名出现多次，变量‘$^’的值仍然仅包含该文件名一次。

# $+

# 该变量象‘$^'，但是，超过一次列出的依赖将按照它们在makefile文件中出现的次序复制。这主要的用途是对于在按照特定顺序重复库文件名很有意义的地方使用连接命令。

# $*
# 和隐含规则匹配的stem(径)，参阅格式匹配。如果一个目标为‘dir/a.foo.b'，目标格式规则为：‘a.%.b' ，则stem为‘dir/foo'。在构建相关文件名时stem 十分有用。在静态格式规则中，stem是匹配目标格式中字符‘%’的文件名中那一部分。在一个没有stem具体规则中；变量‘$*' 不能以该方法设置。如果目标名以一种推荐的后缀结尾（参阅过时的后缀规则），变量‘$*'设置为目标去掉该后缀后的部分。例如，如果目标名是‘foo.c'，则变量‘$*' 设置为‘foo', 因为‘.c' 是一个后缀。GNU make 处理这样奇怪的事情是为了和其它版本的make兼容。在隐含规则和静态格式规则以外，您应该尽量避免使用变量‘$*'。在具体规则中如果目标名不以推荐的后缀结尾，则变量‘$*’在该规则中设置为空值。
smoke: smoke.o libindicators.a
    $(CC) $(CCFLAGS) -o $@ $^ -lm
    ./$@

smoke_amal: smoke.o tiamalgamation.o
    $(CC) $(CCFLAGS) -o $@ $^ -lm
    ./$@

example1: example1.o libindicators.a
    $(CC) $(CCFLAGS) -o $@ $^ -lm

example2: example2.o libindicators.a
    $(CC) $(CCFLAGS) -o $@ $^ -lm

fuzzer: fuzzer.o libindicators.a
    $(CC) $(CCFLAGS) -o $@ $^ -lm

sample: sample.o libindicators.a
    $(CC) $(CCFLAGS) -o $@ $^ -lm

cli: cli.o libindicators.a
    $(CC) $(CCFLAGS) -o $@ $^ -lm

#Benchmark and further testing.
benchmark: benchmark.o libindicators.a
    $(CC) $(CCFLAGS) -o $@ $^ -lm

#Optional benchmark program. Requires TA-Lib.
benchmark_talib: benchmark.c libindicators.a
    $(CC) $(CCFLAGS) -o $@ $^ -DTA_LIB -lta_lib -lm

#This will build all of Tulip Indicators into one .c file.
#This is recommended to be used with other bindings for ease of build.
tiamalgamation.c: $(AMAL) indicators.ca indicators.h candles.ca candles.h

$(OBJS): indicators.h candles.h

smoke.o: indicators.h candles.h

example1.o: indicators.h

example2.o: indicators.h

fuzzer.o: indicators.h candles.h

sample.o: indicators.h candles.h

cli.o: indicators.h candles.h

benchmark.o: indicators.h candles.h

$(AMAL): indicators.h candles.h

.c.o:
    $(CC) -c $(CCFLAGS) $< -o $@

# -E: 同名的环境变量将覆盖目标指定的变量定义;
# -P: 输出Makefille被执行的过程信息;
# -D: 等价于在头文件中定义宏;
.c.ca:
    $(CC) -E -P $(CCFLAGS) $< -o $@ -D TI_SKIP_SYSTEM_HEADERS -D __TI_INDICATORS_H__ -D __TC_CANDLES_H__ -D __BUFFER_H__ -D __LOCALBUFFER_H__ -D __MINMAX_H__

clean:
    rm -f *.a
    rm -f *.exe
    rm -f *.o
    rm -f indicators/*.o
    rm -f utils/*.o
    rm -f *.ca
    rm -f indicators/*.ca
    rm -f utils/*.ca

veryclean:
    rm -f *.a
    rm -f *.exe
    rm -f *.o
    rm -f indicators/*.o
    rm -f utils/*.o
    rm -f *.ca
    rm -f indicators/*.ca
    rm -f utils/*.ca
    rm -f indicators.h
    rm -f indicators.c
    rm -f candles.h
    rm -f candles.c
    rm -f tiamalgamation.c
    rm -f -r docs

	## reference: https://blog.51cto.com/u_9527606/6094249