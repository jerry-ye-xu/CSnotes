FLAGS := -std=c99 -Wall -pedantic -g
VALGRIND_FLAGS :=  --leak-check=full --show-leak-kinds=all --track-origins=yes

MAZE := maze
QUEUE := queue
POINT := point

Q_EXEC := test_queue
EXEC := maze_exe

.PHONY: all clean qt mz

qt: $(Q_EXEC)
	./$<

vg: $(Q_EXEC)
	valgrind $(VALGRIND_FLAGS) ./$<

mz: $(EXEC)
	./$< $@


$(EXEC): $(MAZE).o $(QUEUE).o $(POINT).o
	gcc  $(FLAGS) -o $@ $^

$(Q_EXEC): $(QUEUE).o $(POINT).o $(Q_EXEC).o
	gcc  $(FLAGS) -o $@ $^

$(MAZE).o: $(MAZE).c $(MAZE).h
	gcc $(FLAGS) -c $<

$(Q_EXEC).o: $(Q_EXEC).c
	gcc $(FLAGS) -c $<

$(QUEUE).o: $(QUEUE).c $(QUEUE).h
	gcc $(FLAGS) -c $<

$(POINT).o: $(POINT).c $(POINT).h
	gcc $(FLAGS) -c $<


clean:
	rm $(EXEC); \
	 rm $(Q_EXEC); \
	 rm *.o;