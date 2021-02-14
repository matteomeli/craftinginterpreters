EXEC     = $(shell basename $$(pwd))
CC       = gcc

CFLAGS   = -std=gnu11 -O3 -Wall -Wextra -Wpedantic -Wstrict-aliasing

SRC      = $(wildcard src/*.c)
OBJ      = $(SRC:.c=.o)

.PHONY: all clean

all: $(EXEC)

${EXEC}: $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf src/*.o
	@rm -rf $(EXEC)
