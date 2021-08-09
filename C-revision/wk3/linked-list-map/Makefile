FLAGS := -std=c99 -Wall -pedantic -g
VALGRIND_FLAGS :=  --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: all clean

td: test_dll
	./$<

test_dll: test_dll.o double_linked_list.o
	gcc $(FLAGS) -o $@ $^

test_dll.o: test_dll.c
	gcc $(FLAGS) -c $<

double_linked_list.o: double_linked_list.c double_linked_list.h
	gcc $(FLAGS) -c $^