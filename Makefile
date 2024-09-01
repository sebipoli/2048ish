EXEC = 2048
CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBS = -lncurses

$(EXEC): 2048.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

build: $(EXEC)

clean:
	rm -f $(EXEC)

run: $(EXEC)
	./$(EXEC)
