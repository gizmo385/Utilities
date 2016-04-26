#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fat.h"

struct string_t_header {
    size_t len;
};

struct string_t {
    char *s;
};

struct string_t *new_string(char *str, size_t length) {
    struct string_t *new_str = fat_pointer(struct string_t_header, struct string_t);
    new_str->s = str;

    struct string_t_header *header = get_header(new_str);
    header->len = length;

    return new_str;
}

size_t string_t_len(struct string_t *str) {
    struct string_t_header *header = get_header(str);
    return header->len;
}

int main(void) {
    struct string_t *s = new_string("Hello", strlen("Hello"));

    printf("%s has length %zu\n", s->s, string_t_len(s));
    printf("Header size is %zu\n", get_header_size(s));
    printf("Data size is %zu\n", get_data_size(s));
    return 0;
}
