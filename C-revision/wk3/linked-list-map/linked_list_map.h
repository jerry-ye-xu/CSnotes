struct LinkedListMap {
    struct Node* head;
    size_t size;
};

struct Node {
    void* key;
    void* value;
    struct Node* next;
};

struct LinkedListMap* create_linked_list_map(
    int (*cmp)(void* void*),
    void (*key_del)(void*),
    void (*val_del)(void*)
);

void llm_put(struct LinkedListMap* llm, void* key, void* value);
void llm_get(struct LinkedListMap* llm, void* key);
void llm_remove(struct LinkedListMap* llm, void* key);
size_t llm_size(struct LinkedListMap* llm);
void llm_destroy(struct LinkedListMap* llm);