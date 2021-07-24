
.PHONY: run

run: test_time.out
	time  ./test_time.out bitmap-example.txt 8 16 1 2
	time  ./test_time.out bitmap-example.txt 8 16 2 4
	time  ./test_time.out bitmap-example.txt 8 16 4 8

run-large: test_time.out
	time  ./test_time.out bitmap-example-large.txt 16 32 1 2 \
	time  ./test_time.out bitmap-example-large.txt 16 32 2 4 \
	time  ./test_time.out bitmap-example-large.txt 16 32 4 8 \
	time  ./test_time.out bitmap-example-large.txt 16 32 8 16 \

test_time.out: test_time.c
	gcc -ansi -Wall -pedantic -o test_time.out test_time.c

    # printf("file_path: %s\n", file_path);
    # printf("nrows: %lu\n", nrows);
    # printf("ncols: %lu\n", ncols);
    # printf("nrows_resized: %lu\n", nrows_resized);
    # printf("ncols_resized: %lu\n", ncols_resized);

    # printf("ORIGINAL:\n");
    # print_bitmap(original_bitmap, nrows, ncols);
    # printf("\nRESIZE:\n");
    # print_bitmap(resized_bitmap, nrows_resized, ncols_resized);