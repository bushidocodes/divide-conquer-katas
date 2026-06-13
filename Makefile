CC     = gcc
CFLAGS = -std=c2x -Wall -Wextra -pedantic

TARGETS = 1 2 3 4 5
TESTS   = 1test 2test 3test 4test 5test

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

1test: 1.c 1_test.c
	$(CC) $(CFLAGS) -DTEST_BUILD -o $@ $^

2test: 2.c 2_test.c
	$(CC) $(CFLAGS) -DTEST_BUILD -o $@ $^

3test: 3.c 3_test.c
	$(CC) $(CFLAGS) -DTEST_BUILD -o $@ $^

4test: 4.c 4_test.c
	$(CC) $(CFLAGS) -DTEST_BUILD -o $@ $^

5test: 5.c 5_test.c
	$(CC) $(CFLAGS) -DTEST_BUILD -o $@ $^

test: $(TESTS)
	./1test
	./2test
	./3test
	./4test
	./5test

run5: 5
	./5 < 5.txt

clean:
	$(RM) $(TARGETS) $(TESTS)

.PHONY: all clean run5 test
