### Pipes

We use pipes that hold file descriptors to allow communication with child and parent processes.

You check out a pretty good video [here](https://www.youtube.com/watch?v=FcUlMsVX7aE&t=11s).

File descriptors have integer representations:

0 == stdin
1 == stdout
2 == stderr

There's also other methods like mmps but we'll focus on pipes for now as a means of communication.

We have 

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(){
    
    pid_t childPID;
    
    /* Create 2 int arrays to hold file descriptors for the parent to write to the child and vice versa. */
    int p_to_c[2];
    int c_to_p[2];
    /* p_to_c -> parent writes to child */
    /* descriptor[0] is the read end, 
        descriptor[1] is the write end. */
    
    
    /* Create the pipes before forking so the parent and child have access to the same pipes */
    int pipe_check1 = pipe(p_to_c);
    if(pipe_check1 < 0){
        perror("Pipe cannot be created.\n");
    }
    int pipe_check2 = pipe(c_to_p);
    if(pipe_check2 < 0){
        perror("Pipe cannot be created.\n");
    }
    
    /* Create the child process */
    childPID = fork();
    
    if(childPID < 0){
        perror("Error creating forks.\n");
    } else if (childPID == 0){
        
        // close the write end of the pipe 
        close(p_to_c[1]);
        
        // sleep(2);
        printf("Writing a message for the parent.\n");
        char message[70] = "The child process writes a message for parent process.";
        write(c_to_p[1], message, sizeof(char)*70);
    } else {
        
        // close the write end of the pipe
        close(c_to_p[1]);
        
        
        /* The pipe will block until it reads */
        char message[70];
        read(c_to_p[0], message, sizeof(message));
        
        printf("The message received from child is: %s\n", message);
    }
    
    printf("Program now exiting.\n");
    return 0;
}
```

This example is also nice, with time stuff in it:

```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main(){
	
	int pipefd[2];
	
	int p_check = pipe(pipefd[2]);
	if(p_check < 0){
		perror("Pipe cannot be created.");
	}
	
	int childPID = fork();
	
	if(childPID < 0){
		perror("Error creating forks");
	}
	
	if(childPID == 0){
		close(pipefd[0]);
		
		time_t current_time = time(NULL);
		puts("Child: yes I do!");
		int buf[100];
		write(pipefd[1], &current_time, sizeof(current_time));
		close(pipefd[1]);
	} else {
		close(pipefd[0]);
		
		time_t current_time_parent;
		puts("Parent: Do you know what time it is?");
		
		read(pipefd[0], &current_time_parent, sizeof(current_time_parent));
		
		char* current_time_string = ctime(current_time_parent);
		printf("Parent: The time is %s, thanks!", current_time_parent);
	}
}
```

