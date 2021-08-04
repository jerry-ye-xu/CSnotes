### Function Pointers

Function pointers are, as you might have already guessed, pointers that point to a function.

All you really need to know here is how the syntax works, and why you might need them.

```c
#include <stdio.h>

int print_marks(int effort){
    printf("Please input a number from 1 to 10, indicating how much effort you have put into this subject this semester.\n");
    
    int effort;
    scanf("%d", &effort);
    
    if(effort <= 0){
        printf("You're pretty screwed.\n");
        return 0;
    }
    else if(effort <= 5){
        printf("Try harder.\n");
    } else if (effort <= 10){
        printf("Keep trying.\n");
    } else {
        printf("Too much effort.\n");
    }
    return effort;
}

int main(){
    
    int (*function_ptr)(int);
    function_ptr = print_marks;
    
    function_ptr(5); // `effort` is parameter.
    
}
```

The syntax for function pointers is quite straight forward. You create a pointer to a function, specifying a return type and the parameters as you would normally for a function.

The simply assign the address of the function to the function pointer.

### Harder example of Function Pointer

Let’s look at an example where function pointers are put to good use.

```c
#include <stdio.h>

/* simple exponential, assumes n > 0 */
int n_power(int n, int power){
    for(int i = 1; i < power; i++){
        n *= n;
    }
    printf("n is %d\n", n);
    return n;
}

/* Increment for loops by n steps */
int n_increment(int i, int increment){
    return (i + increment);
}

/* cumulative sum of a sequence of numbers from start to finish, to the power of `power` and incrementing `increment` at a time */
int cum_sum(int (*n_power_ptr)(), int (*up)(), int start, int finish, int power, int increment){
    int total = 0;
    for(int i = start; i < finish; i = (*up)(i, increment)){
		printf("i is %d\n", i);
        total += (*n_power_ptr)(i, power);
    }
	return total;
}

int main(){
    int power, increment, start, finish;
    int (*n_power_ptr)(int, int) = n_power;
    int (*n_increment_ptr)(int, int) = n_increment;
    
    printf("Please input power, increment, start, finish in the format:\n<power> <increment> <start> <finish>\n");
    scanf("%d %d %d %d", &power, &increment, &start, &finish);
    
    int total = cum_sum(n_power_ptr, n_increment_ptr, start, finish, power, increment);
	printf("the total is %d\n", total);
}

```

<http://www-ee.eng.hawaii.edu/~tep/EE160/Book/chap14/section2.1.3.html>

^ you can check out the details here. 

Basically the idea is that you can have function pointers as parameters to be used inside a function. By passing the relevant parameters, you can execute a single function with more flexibility than using multiple if statements or whatnot in a single function.

Also, you are able to write more modular code and the overall codebase will be more clean and readable. 

<https://www.quora.com/Whats-the-use-of-a-function-pointer>

They are also used for callback functions, which is basically when a different pathways of functions are possible given an output of one function.

`Callback` == defined as when a function is not explicitly called by the programmer. 

<https://stackoverflow.com/questions/6807376/call-back-routine>

