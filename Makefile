CC = gcc
CFLAGS = -g -O3 -Wall

BIN = doom

$(BIN): doomsday.c
	$(CC) $(CFLAGS) $^ -o $(BIN)

.PHONY: clean
clean:
	rm $(BIN)
