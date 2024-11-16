CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -Werror

SRCS = error.c no-comment.c
OBJS = $(SRCS:.c=.o)
TARGET = no-comment

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
