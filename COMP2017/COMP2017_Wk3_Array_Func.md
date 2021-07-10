### Bitwise Operations

The Wikipedia guide is a great read.

[https://en.wikipedia.org/wiki/Bitwise\_operations\_in\_C](https://en.wikipedia.org/wiki/Bitwise_operations_in_C)

ADD: Return 1 IFF both bit values are 1

OR: Return 1 if any bit value is 1

XOR: Return 1 if bit values are different to each other

NOT: Return the compliment

`\<\<` & `\>\>`: Bitshifting, see below

```c
void showbits(int n){
    
    
}

int main(){
    
    a = 3; // 00000011
    b = 8; // 00001000
    
    a ^= b;
    
    printf("a is %d\n"); // output is 11 == 00001011;
    
    int c = a << 3; // 00011000;
    
    printf("c is %d\n");
}
```

##### Bitmasking (unfinished)

```c
int main(){
    char* value = "hello";
    
    unsigned char value = !!((1 << n) & target);   
}
```

### Copying Arrays

```c
#include <string.h> 
#include <stdio.h>
// for memcpy

void print_int_array(int* array, const size_t len){
  
  for(int i = 0; i < len; i++){
    printf("array[%d] is %d\n", i, array[i]);
  }
}

void copy_int_array(int* array, int* array_ptr, const size_t len){
  
  for(int i = 0; i < len; i++){
    (array_ptr[i]) = array[i];
  }
}

int main(){
  
  // memcpy(b, a, sizeof(int) * 5); // dest, source, size
  
  int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int array_copy[10];
  int *array_ptr;
  array_ptr = &array_copy[0];
  
  copy_int_array(array, array_ptr, 10);
  
  print_int_array(array_copy, 10);
}
```

##### Shifting array memory

```c
#include <string.h>

void shift_array(int* array, const size_t len_total, const size_t shift){
  
  int* temp[len_total];
  int shift_mod = shift % len_total; // 5 - 3;
  
  memcpy( (array+shift_mod), array, sizeof(int)*(len_total - shift_mod) );
}

int main(){
  
  int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  
  shift_array(array, 10, 3);
  
  print_int_array(array, 10);
  
  // output is {1, 2, 3, 1, 2, 3, 4, 5, 6, 7};
}
```

##### Memmove and memset

Memmove uses a buffer in memory that copies from the original source location to the buffer, then from the buffer to the destination. But otherwise the arguments to the function are the same as memcpy.

**Memmove is safer when copying overlapping memory!**

Memset takes an integer argument and converts it to an unsigned char before allocating this value to each byte in a block of memory starting at the address specified by ‘destination’ and continuing for ‘n_bytes’.

```c
  #include <stdio.h>
  #include <string.h>
  
  int main(){
  
    int a = 2;
    int b[] = {5, 5, 5, 5, 5};
    int c = 3;
    
    // we want to change a to 3 and b to 2;
    
    memset(b, 2, sizeof(int)*3);
    print_int_array(b, 5); // does NOT output {2, 2, 2, 5, 5}!!
    
    // this is because memset copies characters NOT integers.... 
  }
```

[https://www.tutorialspoint.com/c\_standard\_library/c\_function\_memset.htm](https://www.tutorialspoint.com/c_standard_library/c_function_memset.htm)

[https://www.tutorialspoint.com/c\_standard\_library/c\_function\_memmove.htm](https://www.tutorialspoint.com/c_standard_library/c_function_memmove.htm)

