#include <stdlib.h>
#include <stdio.h>

#include "fat.h"

void *new_fat_pointer(size_t header_size, size_t data_size) {
    void **fat_pointer = malloc(2 * FIELD_SIZE);
    fat_pointer[HEADER_INDEX] = calloc(1, header_size);
    fat_pointer[DATA_INDEX] = calloc(1, data_size);

    return fat_pointer[DATA_INDEX];
}

void free_fat_pointer(void *data_ptr) {
    void **fat_pointer = data_ptr - FIELD_SIZE;

    free(fat_pointer[HEADER_INDEX]);
    free(fat_pointer[DATA_INDEX]);
    free(fat_pointer);
}

void *get_header_helper(void *data_ptr) {
    return data_ptr - FIELD_SIZE;
}
