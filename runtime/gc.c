#include "gc.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

void _mark_ptr(void ** ptr) {
    uint32_t * int_ptr = (uint32_t *) ptr;
    *int_ptr |= (uint32_t) 1;
}

void _unmark_ptr(void ** ptr) {
    uint32_t * int_ptr = (uint32_t *) ptr;
    *int_ptr &= ~ (uint32_t) 1;
}

bool _is_marked(void ** ptr) {
    uint32_t * int_ptr = (uint32_t *) ptr;
    return *int_ptr & (uint32_t) 1;
}

void _assert_marked(void ** ptr) {
    assert(_is_marked(ptr));
}

struct count_ptr {
    long count;
    char * data;
};

struct count_ptr * _make_count_ptr(char * raw) {
    struct count_ptr * res = (struct count_ptr *) malloc(sizeof(struct count_ptr));
    res->count = 1;
    res->data = raw; 
    _mark_ptr((void **) &res);
    return res;
}

char * _get_as_string(const struct count_ptr * ptr) {
    _assert_marked((void **) &ptr);
    _unmark_ptr((void **) &ptr);
    return ptr->data;
}

int32_t * _get_as_array32(const struct count_ptr * ptr) {
    _assert_marked((void **) &ptr);
    _unmark_ptr((void **) &ptr);
    return (int32_t *) ptr->data;
}

void _increase_count(struct count_ptr * ptr) {
    if (!_is_marked((void **) &ptr)) {
        return;
    }
    _unmark_ptr((void **) &ptr);
    ptr->count++;
}

void _decrease_count(struct count_ptr * ptr) {
    if (!_is_marked((void **) &ptr)) {
        return;
    }
    _unmark_ptr((void **) &ptr);
    if (ptr == NULL)
        return;
    if (--ptr->count == 0) {
        free(ptr->data);
        free(ptr);
    }
}
