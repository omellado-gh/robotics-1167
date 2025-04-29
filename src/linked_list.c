#include <linked_list.h>
#include <objects.h>

#include <stdio.h>
#include <stdlib.h>

linked_list_t* create_linked_list() {
    linked_list_t* list = (linked_list_t*)malloc(sizeof(linked_list_t));
    if (list == NULL) exit(1);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

node_t* create_node(void *data) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) exit(1);
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void append(linked_list_t *l, void *data) {
    if (l == NULL) return;

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

void **get_array(linked_list_t *list) {
    void **array = (void **)malloc(sizeof(void *) * list->size);

    node_t *current = list->head;

    size_t i = 0;
    while (current != NULL) {
        array[i] = current->data;
        i++;
        current = current->next;
    }

    return array;
}

void destroy_node(node_t *node) {
    if (node == NULL) return;
    if (node->data != NULL) {
        destroy_cube((cube_t *)node->data);
    }

    free(node);
}

void delete_at(linked_list_t* l, size_t position) {
    if (l == NULL) return;
    if (position >= l->size) return;

    node_t *current = l->head;
    size_t i = 0;
    while (current != NULL || i != position) {
        i++;
        current = current->next;
    }

    if (current == NULL) return;

    node_t *del_node = current;
    node_t *prev_node = current->prev;
    node_t *next_node = current->next;

    prev_node->next = next_node;
    next_node->prev = prev_node;

    destroy_node(del_node);
}

void destroy_linked_list(linked_list_t *list) {
    if (list == NULL) return;

    node_t* current = list->head;
    while (current != NULL) {
        node_t* del_node = current;
        current = del_node->next;
        destroy_node(del_node);
    }

    free(list);
}