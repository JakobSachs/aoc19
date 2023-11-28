CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -0g
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
EXES := $(SRCS:.c=)

.PHONY: all clean

all: $(EXES)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(EXES)

