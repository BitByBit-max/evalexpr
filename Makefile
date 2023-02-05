CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror -pedantic -Wvla -g
LDFLAGS=-fsanitize=address
SRCNOMAIN=src/token_queue.c src/lexing.c src/token_stack.c src/torpn.c src/evaluation.c
SRC=src/evalexpr.c $(SRCNOMAIN)
OBJ=${SRC:.c=.o}
TEST=tests/lexing_tests.c tests/evaluation_tests.c tests/torpn_tests.c
TESTOBJ=${TEST:.c=.o}

all: evalexpr

evalexpr: $(OBJ)
	$(CC) -o evalexpr $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS)

check: $(TEST) $(SRCNOMAIN)
	$(CC) $(CFLAGS) -lcriterion $^ -o testsuite $(LDFLAGS)
	./testsuite

functest: evalexpr
	./tests/func_tests.sh
	./tests/func_tests_rpn.sh

clean:
	$(RM) evalexpr $(OBJ) $(TESTOBJ) testsuite
