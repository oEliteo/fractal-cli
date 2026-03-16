CC = gcc

CFLAGS = -Iinclude -Wall -Wextra
SRCS = $(wildcard src/*.c)

all: src/main.c src/canvas.c
	$(CC) $(CFLAGS) $(SRCS) -o bin/fractal-cli

clean:
	rm -f bin/fractal-cli

