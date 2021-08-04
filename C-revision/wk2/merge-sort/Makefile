FLAGS := -std=c99 -Wall -pedantic -g
VALGRIND_FLAGS :=  --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: all clean

alpha: merge-sort.o
	./$< fruits.txt -a -alph
	./$< fruits.txt -a -alph

num: merge-sort.o
	./$< numbers.txt -a -num
	./$< numbers.txt -d -num


merge-sort.o: merge-sort.c
	gcc $(FLAGS) -o $@ $<