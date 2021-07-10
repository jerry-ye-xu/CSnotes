### Const Declarations

```c
const char greetings[] = "Hello Charles the 4th!\n";

greetings[3] = "x"; // Cannot change the char values!

char* const confessions[] = "Yu Pyn is cute.\n";

confessions = "Hello!"; // Cannot change address that the ptr points to!
```

What's the difference between the 2 lines?

`const char` == `char` values must be constant

`char* const` word == the `char*` word must be constant. In other words, the address that char* points to must be constant.  

However, you need to be careful as if you are pointing to an area of memory that is writable, you can cast it back to a non `const` type and write over it.

```c
char letters[] = {'y', 'p', 'c'};
const char *ptr = (char*) letters;

char *ptr2 = (char*)ptr; // re-cast const char to char
ptr2[0] = 'j';
```

### Enums, Structs and Unions

```c
enum day{
  Sun, Mon, Tues, Wed, Thurs, Fri, Sat
};

// Sun == 0, Mon == 1, etc.
// automatically assigns words to integer and increments
// Can perform operations like Sun++;

enum states{
  happy = 0,
  gloomy = 1,
  so_so = 2,
  
  elated = 0; // you can have repeated int values. 
}

int main(){
  
  enum states Jerry = elated;
  printf("%d\n", Jerry); // output is 1
}
```

```c
struct person{
  char* name; // either we use `char name[15]` or malloc.
  int age;
  float height;
  float weight;
};

int main(){
  struct person Jerry;
  
  char n[5] = "Jerry";
	
  Jerry.name = n; // to be safe
  Jerry.age = 15;
  
  printf("Jerry's name is %s\n", Jerry.name); 
  printf("Jerry's age is %d\n", Jerry.age);
}
```

__Unions__

Unions save memory space by only allowing one of its variables to be initialised at a time.

The memory allocated is shared by all members i.e. the total memory used by the memory is the size of the largest type, whereas for structs it is the sum of its individual variables. 

```c
union num_types{
  
  int x;
  float y;
  double z;
};

int main(){
  
  union num_types num;
  num.x = 3;
  num.y = 6.0;
  num.z = 9.0;
  
  // only z is in use right now.
  
  union num_types num2 = {3, 6.0, 9.0};
  // only x is in use at this time right now
  // i.e. only the FIRST variable is initialised
}
```

Something a little bit more complicated?

```c
enum media_type{
  book, film, radio
};

struct catalog{
  char* title;
  enum media_type media;
  
  // create a union to store either book/film info
  union media_info{
    struct book{
      char* author;
      char* ISBN;
    };
    struct film{
      char* director;
      char* producer;
    };
  };
  
};

int main(){
  struct catalog Bosch;
  Bosch.media_info.book.author = "Jerry";
  
  // How would you access the information?
      // Using the enum media_type of course!
      
  switch(Bosch.media){
    case book:
      printf("author is %s\n", Bosch.media_info.book.author);
      break;
    case film:
      printf("director is %s\n", Bosch.media_info.film.director);
      break;
    default:
      printf("Media type does not exist!\n");
  }
}
```

