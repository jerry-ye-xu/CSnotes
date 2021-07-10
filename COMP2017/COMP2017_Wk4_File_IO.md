### Overview of FIle IO

There are 3 main points with FILE IO that you need to understand. We leave the other details in part 4. 

1) Read & Write
2) Locating the pointer of the file (calculating length etc.)
3) Breaking up strings or binary files into bytes and characters
4) Other details

##### 1) Read & Write

For each file opened, you need a file descriptor that describes the state of the file e.g. opened, closed, position etc. 

You have:

fopen(), fclose(), fseek(), ftell(), rewind(),

fwrite(), fprintf(), fputs(), fputc(), 
fread(), fscanf(), fgets(), fgetc(),

strtok(), strtol(), 

**Reading & Writing Text**

We are going to use the txt file input below:

Line31onlyworkswithnospacesokay 50 100 150 250 y
x This entire line should have been read except for This at the beginning
You will have to break it up with strtok if you want each individual word

```c
#include <stdio.h>

void main(int argc, char** argv){
    
    // ---------------------------------
    // --- READ AND WRITE TEXT FILES ---
    // ---------------------------------
    
    // ---------------------- READ ----------------------

    // Error checking
    if(argc < 2){
        perror("No file has been provided!\n");
    }
    
    FILE* read_file = fopen(argv[1], "r");
    // NOTE: "rb" is necessary for reading binary files!
    if(read_file == NULL){
        perror("File cannot be opened.\n");
    }
	
	printf("begin reading\n");
    
    // You can extract files by specifying the exact format.
    int array[4];
    int check_scan = fscanf(read_file, "%*s %d %d %d %d", &array[0], &array[1], &array[2], &array[3] );
    if(check_scan != 4){ perror("fscanf did not read in 4 integers\n"); };
    
    printf("fscanf\n");
    
    char char_buff;
    char_buff = fgetc(read_file); // the space is read here.
	printf("the char is %c\n", char_buff);
    // Error handling: You can check the EOF and use ferror to distinguish whether fgetc() has reached EOF due to an error or it having already reached the end.
    // You have to be careful here as fgetc() doesn't automatically jump to the next line.
	// Hence that is why I added an extra 'y' character.
	if(ferror(read_file) != 0){
        perror("EOF is returned due to an error!\n");
    }
	
    char_buff = fgetc(read_file); // this will read the y 
	// printf("the char is %c\n", char_buff); 
	char_buff = fgetc(read_file); // this reads the "\n";
	// printf("the char is %c\n", char_buff); 
    // char_buff = fgetc(read_file); // this line reads the 'x' on line 2;

  
    char line_2[255];
    fgets(line_2, 255, (FILE*)read_file);
    
    char line_3[255];
    fgets(line_3, 255, (FILE*)read_file);
    
    printf("the character is %c\nline 2 is %s\nline 3 is %s\n", char_buff, line_2, line_3); // note that stream ptr when increments stays put for further reading.
    
    rewind(read_file);
	
	printf("read the whole file\n");

    // ---------------------- READ WHOLE FILE ----------------------
	
	printf("read the whole file\n");

    char line_all[255];
    
    while(fgets(line_all, 255, read_file) != NULL){
        printf("%s\n", line_all);
    }
    
    // preserves only the last line. 
    // printf("the first line is %s\n", line_all);

    fclose(read_file);
    
    // ---------------------- WRITE ----------------------
    
    FILE* write_file = fwrite("participant_data.txt", "w");
    
    
    
    // -----------------------------------
    // --- READ AND WRITE BINARY FILES ---
    // -----------------------------------  
    
    // ---------------------- READ ----------------------
   
    FILE* read_file = fopen(argv[1], "rb");
    // NOTE: "rb" is necessary for reading binary files!
    if(read_file == NULL){
        perror("File cannot be opened.\n");
    };
    
    // stream, offset, whence = SEEK_SET, SEEK_CUR, SEEK_END
    // Apparently will fail on files larger than 4GB
    fseek(read_file, 0, SEEK_END);
    // find out length of file
    unsigned int file_len = ftell(read_file);
    // rewind to the beginning
    rewind(read_file);
    
    // create buffer, ensure that you null terminate the string afterwards if that is indeed what you are reading. 
    char buffer[file_len];
    
    // read everything in using fread.
    fread(buffer, sizeof(int), file_len, read_file);
    
    return 0;
}
```

<https://www.geeksforgeeks.org/scanf-and-fscanf-in-c-simple-yet-poweful/>

[https://www.tutorialspoint.com/cprogramming/c\_file\_io.htm](https://www.tutorialspoint.com/cprogramming/c_file_io.htm)

<https://stackoverflow.com/questions/5431941/why-is-while-feof-file-always-wrong>

How do you read the entire file and not line by line?

### strtok, strtol 



