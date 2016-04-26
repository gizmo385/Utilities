#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fat.h"

struct list_t {
    void *data;

    struct list_t *next;
};

struct list_header {
    size_t len;
    struct list_t *head;
    struct list_t *tail;
};

struct list_t *new_list(void) {
    struct list_t *list = fat_pointer(struct list_header, struct list_t);

    // Fill out header
    struct list_header *header = get_header(list);
    header->len = 0;
    header->head = NULL;
    header->tail = NULL;

    list->data = NULL;
    list->next = NULL;

    return list;
}

void prepend_item(struct list_t *list, void *data) {
    if(!list) {
        fprintf(stderr, "Error: list is NULL\n");
        return;
    }

    if(list->data) {
        struct list_t *new_entry = calloc(1, sizeof(struct list_t));
        if(!new_entry) {
            fprintf(stderr, "Error: Couldn't malloc new entry\n");
            return;
        }
        new_entry->data = list->data;
        new_entry->next = list->next;

        list->data = data;
        list->next = new_entry;
    } else {
        list->data = data;
    }

    struct list_header *header = get_header(list);
    header->len += 1;
}

void append_item(struct list_t *list, void *data) {
    
}


int main(void) {
    struct list_t *list = new_list();
    struct list_header *header = get_header(list);

    printf("There are %ld elements in the list\n", header->len);

    // Prepend some items
    for(int i = 0; i < 5; i++) {
        int *i2 = malloc(sizeof(int));
        *i2 = i;

        printf("Atempting to prepend %d (at %p)\n", *i2, i2);
        prepend_item(list, i2);

        printf("\tList now has %ld items\n", header->len);
    }

    // Walk the list
    struct list_t *current = list;
    while(current) {
        int *i = current->data;

        printf("Item in list: %d @ %p\n", *i, i);

        current = current->next;
    }

    return 0;
}
