MAZE := maze
QUEUE := queue
POINT := point

Q_EXEC := test_queue
EXEC := maze_exe

.PHONY: all clean qt mz

qt: $(Q_EXEC)
	./$(Q_EXEC)

mz: $(EXEC)
	./$(EXEC) $@

$(EXEC): $(MAZE).o $(QUEUE).o $(POINT).o
	gcc  -Wall -g -o $(EXEC) $(MAZE).o $(QUEUE).o $(POINT).o

$(Q_EXEC): $(QUEUE).o $(POINT).o $(Q_EXEC).o
	gcc  -Wall -g -o $(Q_EXEC) $(QUEUE).o $(POINT).o $(Q_EXEC).o

$(MAZE).o: $(MAZE).c $(MAZE).h
	gcc -ansi -Wall -g -c $(MAZE).c

$(Q_EXEC).o: $(Q_EXEC).c
	gcc -ansi -Wall -g -c $(Q_EXEC).c

$(QUEUE).o: $(QUEUE).c $(QUEUE).h
	gcc -ansi -Wall -g -c $(QUEUE).c

$(POINT).o: $(POINT).c $(POINT).h
	gcc -ansi -Wall -g -c $(POINT).c


clean:
	rm $(EXEC); \
	 rm $(Q_EXEC); \
	 rm *.o;