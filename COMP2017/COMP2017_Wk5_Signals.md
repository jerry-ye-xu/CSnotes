### Signals Overview

Sometimes things in the system can occur, and maybe the system will just stop the program when it happens. Like when you ctrl-C the system will have a default signal handler that simply stops the program.   

You the programmer however, need more control over the program to deal with error handling perhaps, or maybe you just want to program to proceed in different ways when things happen.

Either way, signals can you help do that.

Some possible signals that you might have to handle are:

SIGINT = interrupt
SIGKILL = kill
SIGBART = abort
SEGSEV = segmentation 
SIGUSR = user signal
SIGSTOP = stop 

All signals can be caught and handled by the user except SIGKILL and SIGSTOP which cannot be ignored, caught or blocked. 

Each signal has its own integer representation e.g. SIGKILL is 9.

So in the command line you can:

```sh
ps -A # to see all your processes
kill -9 pid # kill the process by specifying its pid
```

### Signal handling in C

You can set signal handlers with `signal()` or `sigaction()` but `signal()` is considered to be deprecated. However, we're going to use `signal()` anyway.

Let's look at an example.

```c
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h> // for sleep()

volatile int signal_caught = 0;

/* Create a signal handler that will perform an action when the SIGINT is received. */
void sig_handler(int sig_val){
    
    signal_caught = 1;
}

int main(){
   
	void (*f_ptr)(int) = sig_handler; // you can use a func_ptr as well.
    // have the signal id and the function 
    signal(SIGINT, f_ptr);
    while(!signal_caught){
        sleep(10);
    }
    printf("Signal caught.\n Program terminating.\n");
    return 0;
}
```

If you're interested you can find information about the volatile keyword here: https://barrgroup.com/Embedded-Systems/How-To/C-Volatile-Keyword

### Errno

When running code, errors are reported using a global variable `errno` which is short for error number. 

When something goes wrong, errno will return an integer value that represents the corresponding error that has occurred. 

In order to obtain a human readable version of the error code, you can use `strerror()` (or `strerror_r` which is supposedly thread-safe) or `perror()`.

```c
#include <errno.h>
#include <stdio.h>

int main(){
    
    FILE *fp = open("non_existent_file.txt", "r");
    printf("errno is %d\n", errno);
    // perror("Error!\n"); // this will also print a message corresponding to the error. 
    return 0;
}    
```

#### Important!

Errno is determined by the immediately previous function call. It will be overwritten if another mistake was generated with a new function call. Hence you should save that value immediately to avoid it being lost. 





