CC     = gcc
CFLAGS = -std=c2x -Wall -Wextra -pedantic

TARGETS = 1 2 3 4 5

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

2test: 2.c 2_test.c
	$(CC) $(CFLAGS) -DTEST_BUILD -o $@ $^

test: 2test
	./2test

run5: 5
	./5 < 5.txt

clean:
	$(RM) $(TARGETS) 2test

.PHONY: all clean run5 test
