#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

// just to use with dynamic memory
linked_list_t* create_linked_list() {
    linked_list_t* list = (linked_list_t*)malloc(sizeof(linked_list_t));
    if (list == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Function to create a new node
node_t* create_node(void *data) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void append(linked_list_t *l, void *data) {
    // l is a list
    if (l == NULL) {
        printf("List is NULL\n");
        return;
    }
    node_t* new_node = create_node(data);
    l->size++;
    if (l->head == NULL) {
        l->head = new_node;
        l->tail = new_node;
        return;
    }

    l->tail->next = new_node;
    new_node->prev = l->tail;
    l->tail = new_node;
}

// Function to insert a node at position
void insert_at(linked_list_t *l, void *data, size_t position) {
    if (l == NULL) {
        printf("List is NULL\n");
        return;
    }
    node_t* new_node = create_node(data);
    l->size++;
    if (l->head == NULL) {
        l->head = new_node;
        l->tail = new_node;
        return;
    }
    if (position == 0) {
        new_node->next = l->head;
        l->head->prev = new_node;
        l->head = new_node;
        return;
    }
    if (position == l->size - 1) {
        l->tail->next = new_node;
        new_node->prev = l->tail;
        l->tail = new_node;
        return;
    }
    if (position == l->size) {
        append(l, data);
        return;
    }

    node_t* current = l->head;
    // to know if head is more closer to the position
    // than tail
    if (position <= l->size / 2) {
        for (size_t i = 0; i != position; i++)
            current = current->next;
    } else {
        for (size_t i = l->size - 1; i != position; i--)
            current = current->prev;
    }
    // current is the node at position
    node_t *prev_node = current->prev;

    prev_node->next = new_node;
    new_node->prev = prev_node;
    current->prev = new_node;
    new_node->next = current;
}

void destroy_node(node_t *node) {
    if (node == NULL) return;
    if (node->data != NULL) free(node->data);
    free(node);
}

// Function to delete a node by value
void delete_at(linked_list_t* l, size_t position) {
    if (l == NULL) {
        printf("List is NULL\n");
        return;
    }
    if (position >= l->size) {
        printf("Position out of bounds\n");
        return;
    }
    node_t *current = l->head;
    size_t i = 0;
    while (current != NULL || i != position) {
        i++;
        current = current->next;
    }

    if (current == NULL) {
        printf("Position out of bounds\n");
        return;
    }

    node_t *del_node = current;
    node_t *prev_node = current->prev;
    node_t *next_node = current->next;

    prev_node->next = next_node;
    next_node->prev = prev_node;

    destroy_node(del_node);
}

// Function to free and destroy the entire linked list
void destroy_linked_list(linked_list_t *list) {
    if (list == NULL) {
        return;
    }

    node_t* current = list->head;
    while (current != NULL) {
        node_t* del_node = current;
        current = del_node->next;
        destroy_node(del_node);
    }

    free(list);
}