$(EXEC): $(MAZE).o $(QUEUE).o $(POINT).o
	gcc  -Wall -g -o $(EXEC) $(MAZE).o $(QUEUE).o $(POINT).o

.PHONY: run_test

run_test: test_stack
	./test_stack

test_stack: stack.o tests.o
	gcc -Wall -pedantic -g -o test_stack stack.o tests.o

stack.o: stack.h stack.c
	gcc -ansi -Wall -g -c stack.c

tests.o: tests.c
	gcc -ansi -Wall -g -c tests.c