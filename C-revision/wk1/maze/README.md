

```bash
gcc -ansi -Wall -pedantic -g -c maze.c
gcc -ansi -Wall -pedantic -g -c queue.c
gcc -ansi -Wall -pedantic -g -c point.c

gcc  -Wall -pedantic -g -o queue_test queue.o point.o
gcc  -Wall -pedantic -g -o maze_exe maze.o queue.o point.o
```