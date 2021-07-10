### Pointers

Pointers are variables in C that hold the address of another variable. E.g.

```c
#include <stdio.h>

int number;

scanf(%d, &number);

// In the case above we store the std input value into the address reserved by the declaration of int number.

int* int_ptr;
int x = 5;

int_ptr = &x;
```

Here’s a link to some good C pointer questions:

<https://www.geeksforgeeks.org/c-language-2-gq/pointers-gq/>

```c
// Wk3 tute Q7

*p = p[0];

*(p+10) = p[10];

&r[20] = (r+20);

&(g[0]) = g;

&*p = &p[0]; // BE VERY CAREFUL!!!

p++ = (p+1); // tautology.... the correct solution is &(p[1]);

(&(r[5])[5]) = r+5+5
```

What about double pointers? 

You can interpret something like this in many different ways:

```c
int **data;

// You can interpret this in many different ways!

int **data; // pointer to pointer
int *data[]; // array of int* (int pointers);
int *data[]; // pointer to an array of ints;
int data[][]; 
```

What happens if you:

```c
int array[] = {1, 2, 3}

printf("%d\n", array[-1]);
```

<https://cs.stackexchange.com/questions/10837/why-do-negative-array-indices-make-sense>

#### Copying arrays

```c
int main() {    int original_array[10];  int copied_array[10];  // int *copied_array; doesn't work either. It simply points to address of the original_array.   for (int i = 0; i < 10; i++) {  original_array[i] = i * i;  }  copied_array = original_array;}
```

What’s wrong with the Line 8?

Well… you can’t assign one array to another, it gives a compilation error. 

Arrays are an immutable pointer to a location in memory. 

<http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Pointers.html>

“because the array name is constant, you can't assign to it"

---

### Hexadecimal Representation

0x001 = 1

0x00A = 10

0x00F = 15

0x010 = 16

0x020 = 32

0x100 = 256

0xF01 = 3841

This should be enough for you to understand what it is yes?

---

### Byte size of Primitive Types

```c
int x; // 2 for 32 bit || 4 for 64 bit
short x; // 2 bytes
long x; // 4 bytes
float x; // 4 bytes

double x; // 8 bytes
long double x; // 10 bytes

char x; // 1 byte
unsigned char x; // 1 byte

int* ptr; // 2 for 16 bit || 8 for 64 bit (x64 Intel processors are most recent)

uint32_t x; // 32 bits (4 bytes) regardless of where you run it.
```

[https://www.tutorialspoint.com/cprogramming/c\_data\_types.htm](https://www.tutorialspoint.com/cprogramming/c_data_types.htm)

---

### Unsafe Functions

<https://stackoverflow.com/questions/26558197/unsafe-c-functions-and-the-replacement>

e.g. gets() is unsafe because it doesn’t perform bound checking on the size of the input.

```c
int main(){
  
  char sentence[100];
  printf("Please input a sentence.\n");
  gets(sentence);
}
```

If you input a sentence longer than 100 characters, get() will not check this for you.

See above link for more examples.