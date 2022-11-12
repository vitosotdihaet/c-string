#ifdef STRING_H

#define STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

//? Maybe deprecated, but those are for error handling 
#define UNDEFINED 0
#define SUCCESS 1
#define ERROR -1

// How big initial memory is
const uint64_t INIT_CAPACITY = 2;
// How big relative to previous allocated memory new memory should be
const uint64_t EXTENDED_CAPACITY = 2;

// Memory-related macros 
#define new(a, n) (a*)calloc(sizeof(a), sizeof(a) * n)
#define reallocate(ptr, a, n) (a*)realloc(ptr, sizeof(a))

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

struct string {
    char *values;
    uint64_t last_element;
    uint64_t memory_size;
};

#define string struct string

// Initialize string with default capacity
int init_string(string* s) {
    int result = UNDEFINED;
    s->memory_size = INIT_CAPACITY;
    s->values = new(char, INIT_CAPACITY);
    s->last_element = 0;
    return result;
}

// Initialize string with set capacity
int init_string_with_set_capacity(string* s, uint64_t capacity) {
    int result = UNDEFINED;
    s->memory_size = capacity;
    s->values = new(char, capacity);
    s->last_element = 0;
    return result;
}

// Sets all struct's parameters to zero
int free_string(string* s) {
    int result = UNDEFINED;
    s->values = new(char, 0);
    s->last_element = 0;
    s->memory_size = 0;
    return SUCCESS;
}

// Adds memory
int string_resize(string* s, uint64_t capacity) {
    int result = UNDEFINED;
    s->values = reallocate(s->values, char, capacity);
    return SUCCESS;
}

// Adds a char to string, adding more memory if needed 
int add_char(string* s, char value) {
    int result = UNDEFINED;
    if (s->last_element < s->memory_size) {
        result = SUCCESS;
    } else {
        result = string_resize(s, 2);
    }
    s->values[s->last_element] = value;
    s->last_element++;
    return result;
}

// Copies s2 to s1 (taking minimal memory size) -> s1='aboba', s2='bobr' -> s1='bobr'
int copy_string(string* s1, string s2) {
    int result = UNDEFINED;
    uint64_t minimal = min(s1->last_element, s2.last_element);
    for (uint64_t i = 0; i < s1->last_element; ++i) {
        if (i < minimal) {
            s1->values[i] = s2.values[i];
        } else {
            s1->values[i] = ' ';
        }
    }
    s1->last_element = minimal;
    return result;
}

// Pushes whole s2 to s1
int push_string(string* s1, string s2) {
    int result = UNDEFINED;
    for (uint64_t i = 0; i < s2.last_element; ++i) {
        add_char(s1, s2.values[i]);
    }
}

// Fully changes parameters of s1 to s2
int set_string(string* s1, string s2) {
    int result = UNDEFINED;
    *s1 = s2;
    return SUCCESS;
}

int main() {
    string s;
    string a;

    init_string(&s);
    init_string(&a);

    add_char(&s, 'h');

    printf("s after add_char: %s\n", s.values);

    add_char(&a, 'b');
    add_char(&a, 'e');
    add_char(&a, 'b');

    printf("a after add_char: %s\n", a.values);

    copy_string(&s, a);

    printf("s after copy: %s\n", s.values);

    push_string(&s, a);

    printf("s after pushing a: %s\n", s.values);

    add_char(&s, '!');

    printf("s after add_char: %s\n", s.values);

    set_string(&a, s);

    printf("a after setting to s: %s\n", a.values);

    return 0;
}

#endif