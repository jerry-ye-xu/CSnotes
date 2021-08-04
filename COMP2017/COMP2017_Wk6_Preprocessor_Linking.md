![IMAGE](http://nerdyelectronics.com/wp-content/uploads/2017/07/GCC_CompilationProcess.png)

What happens when you want to compile many programs and link them together?

```sh
gcc -c program.c # creates program.o file

gcc program.o new_file.c -o link_them # links both and creates a "link_them" file that holds both.

# if you update code just recompile the single program and then compile the whole thing again (here is where you might need Make files)

gcc -c program.c # updated
gcc program.o new_file.c -o link_them
```

### Preprocessor

The preprocessor — it handles everything that starts with `#`, e.g. `#include` -- which includes code from another file to be used.

It is useful for externs, typedef and struct definitions. 

#### Externs

Extern basically increases the scope of variables declared in a .c file.

For functions, this doesn't matter as every function is implicitly declared as an `extern` anyway. This basically means that other files that are linked to this file can use that function. 

```c
extern void some_function(int x);

// If you wanted to restrict the function to be used within this file only. Then use the static keyword. 

static void some_function(int x);
```

For variables, it becomes much more important when you're considering the linkage of several files together. 

If you declare a variable as `extern` then you are asking the compiler to defer the definition of the variable until the linkage stage. More importantly, it doesn't allocate any memory (instantiate) the variable and the type and value of the variable are sourced from the linked files.

```c
#include "otherfile.h"

extern int num_from_other_file;

int main(){
    
    printf("extern int is %d\n", num_from_other_file);
}
```

```c
int num_from_other_file = 10; 

// say this is in "otherfile.h"
```

For variables shared across compilation units, you should declare them in a header file with the `extern` keyword, then define them in a single source file, without the `extern` keyword. 

The single source file should be the one sharing the header file's name, for best practice.

#### Defining MACROS & VARIABLES

You can define MACROs and variables like this:

```c
#define BYTE 4;
#define min(a, b) ((a<b)?(a):(b))
```

I think I'll leave you to figure line 2 out.

Just kidding.

A macro is basically a function that's processed during the preprocessing stage (actually it's a little more complicated than that).

In the above example, it's basically saying define `min(a, b)` as if (?) `a < b` then `a` else `b`.

Here's something tricky:

```c
#define min(a, b) ( ((a++) < b)?(a++):(b) )
```

What's going on here?

### Conditional Inclusion

You can define things in the command line, and this has the same effect as using

```c
#define WAM 60
```

```c
#include <stdio.h>
#define WAM 55

int main(){
    printf("my WAM is %d\n", WAM);
    printf("his WAM is %d\n", HISWAM);
    return 0;
}   
```

```sh
gcc -D HISWAM=90 program.c
```

\#ifdef -- tests if symbol is defined
\#ifndef -- tests if symbol is NOT defined
\#if -- if-statements for different conditions of a variable e.g. 
\#else
\#elif

```c
#include "other.h"

int main(){
#if WAM > 90
    printf("What a beast!\n");
#else if WAM > 50
    printf("Not good enough\n");
#else
    printf("I think you failed lots of subjects...\n")
}
```

\#undef -- undefines the variable set by the command line. 
\#endif -- ends the `#` statements

You also have set symbols such as

`__LINE__`
`__FILE__`

Which basically helps with debugging and other things.

e.g.

```c
#ifdef EBUG#define DEBUG(m) // macro (without the function)    printf("debug: %s at line %d in file %s\n"􀀁,(m), __LINE__, __FILE__);#else#define DEBUG(m) /* null statement */#endif
```



