#include <stdio.h>
#include <stdbool.h>

// Define the structure for a node in the linked list
typedef struct Node {
    void *data;
    struct Node* next;
    struct Node* prev;
} node_t;


typedef struct LinkedList {
    node_t *head;
    node_t *tail;
    size_t size;
} linked_list_t;


extern linked_list_t* create_linked_list();
extern void append(linked_list_t *l, void *data);
extern void **get_array(linked_list_t *list);
// extern void insert_at(linked_list_t *l, void *data, size_t position);
extern void delete_at(linked_list_t* l, size_t position);
extern void destroy_linked_list(linked_list_t* l);