FLAGS := -std=c99 -Wall -pedantic -g
VALGRIND_FLAGS :=  --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: all clean

alpha: merge-sort.o
	./$< fruits.txt -a -alpha
	echo ""
	./$< fruits.txt -d -alpha

num: merge-sort.o
	./$< numbers.txt -a -num
	echo ""
	./$< numbers.txt -d -num


merge-sort.o: merge-sort.c
	gcc $(FLAGS) -o $@ $<