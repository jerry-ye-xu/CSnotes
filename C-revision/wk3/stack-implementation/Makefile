FLAGS := -std=c99 -Wall -pedantic -g
VALGRIND_FLAGS :=  --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: run_test run_vg_test

run_test: test_stack
	./$<

vg_test: test_stack
	valgrind $(VALGRIND_FLAGS) ./$<

test_stack: stack.o tests.o
	gcc $(FLAGS) -o $@ $^

stack.o: stack.c stack.h
	gcc $(FLAGS) -c $<

tests.o: tests.c
	gcc $(FLAGS) -c $<
