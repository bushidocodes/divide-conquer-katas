CC     = gcc
CFLAGS = -std=c2x -Wall -Wextra -pedantic

TARGETS = 1 2 3 4 5

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

run5: 5
	./5 < 5.txt

clean:
	$(RM) $(TARGETS)

.PHONY: all clean run5
