CC=gcc
CFLAGS = -Iinclude -Wall -Wextra
TARGET = out/tests

LIB_SRCS = $(wildcard src/*.c)
LIB_OBJS = $(LIB_SRCS:.c=.o)

TESTS_SRCS = $(wildcard tests/*.c)
TESTS_OBJS = $(TESTS_SRCS:.c=.o)

all: ($TARGET)

$(TARGET): $(TESTS_OBJS) $(LIB_OBJS)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf out/ *.o $(LIB_OBJS) $(TESTS_OBJS) $(TARGET)

.PHONY: all clean