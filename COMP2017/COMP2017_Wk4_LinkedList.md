```c
struct node{
    
    int value;
    struct node* next_node;
};

/*
	list_init
	Creates a new list by creating and head node
	:: int value :: The value to be stored in the head node
	Returns a pointer to the newly created node
 */
struct node* list_initialise(int value){
    struct node *head = malloc(sizeof(struct node));
    
    head->value = value;
    head->next = NULL;
    return head;
} 

/*
	list_add
	Adds a node containing a specified value to an existing list
	:: int value :: The value to be stored in the new node
	Does not return anything
 */
void add_node(struct node *head, int value){
    
    struct node* curr_node;
    
    // loop until you get to the last node. 
    for(curr_node=linkedlist; curr_node->next != NULL; curr_node = curr_node->next){ };
    
    curr_node->next = list_initialise(value);
}

/*
	list_next
	Returns a pointer to the next node in the list
	:: const struct node* n :: The node
	Returns a pointer to the next node
 */
struct node* next(const struct node *node){
    
    return node->next;
}

/*
    list_print
    Prints all values stored in the list
    :: struct node* head:: The first node of the linked list
    Does not return anything

 */
 void print_linkedlist(struct node* head){
     
    struct node *curr_node;
    
    for(curr_node=head; curr_node->next != NULL; curr_node = curr_node->next){
        
        printf("curr_node->value is %d\n", curr_node->value);
        
    }
	// Print the last value.
    printf("curr_node->value is %d\n", curr_node->value);
 }

/*
	list_free
	Frees all existing nodes in a list
	:: struct node* n :: The pointer to the head node of the list
	Does not return anything
 */
 void free_list(struct node *head){
     if(head == NULL){
         return;
     }
     
     free_list(head->next);
     free(node);
 }
 
 int main(){
	
	struct node* linked_list = list_init(5);
	
	list_add(linked_list, 3);
	list_add(linked_list, 4);
	list_add(linked_list, 6);
	list_add(linked_list, 7);
	
	print_linkedlist(linked_list);
	
	list_free(linked_list);
	
	// print_linkedlist(linked_list);
}

// gcc -o ll linked_list.c -fsanitize=address

```

