#ifndef _FAT_H
#define _FAT_H

#include <stdlib.h>

/* Offsets for certain fields from the pointer returned to the user */
#define HEADER_INDEX 0
#define DATA_INDEX 1
#define FIELD_SIZE sizeof(void *)

/* Creating a fat pointer */
#define fat_pointer(header_type, data_type) \
{\
    (data_type *) new_fat_pointer(sizeof(header_type), sizeof(data_type)) \
}

/**
 *            Fat Pointer Structure
 *  --------------------------------------
 * |      header       |        data      |
 * | size of a pointer | size of a pointer|
 *  --------------------------------------
 * ^                   ^
 * |                   |
 * |        Pointer returned from fat_pointer
 * |
 * Start of fat_pointer_t
 *
 */
extern void *new_fat_pointer(size_t header_size, size_t data_size);

/* Retrieving the header from a fat pointer */
#define get_header(data_ptr) \
{\
    (get_header_helper((data_ptr))) \
}

extern void free_fat_pointer(void *data_ptr);


/* Assistance functions */
extern void *get_header_helper(void *data_ptr);

#endif
