void cast_to_change_size() {
    /*
        Pointer arithmetic is dependent on the data type in
        to which it points.

        Hence casting a ptr to (char*) will recalibrate the
        ptr size from 4 (ints) to 1 (chars).
    */

    int arr[] = {10, 20, 30, 40, 50, 60};
    int *ptr1 = arr;
    int *ptr2 = arr + 5;
    printf("Number of elements between two pointer are: %d.", 
                                (ptr2 - ptr1));
    printf("Number of bytes between two pointers are: %d",  
                              (char*)ptr2 - (char*) ptr1);
    return 0;
}

int main() { 
    cast_to_change_size();
    return 0; 
}