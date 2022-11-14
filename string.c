#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.h"

//? Maybe deprecated, but those are for error handling
#define UNDEFINED 0
#define SUCCESS 1
#define ERROR -1

// How big initial memory is
const uint64_t INIT_CAPACITY = 2;
// How big relative to previous allocated memory new memory should be
const uint64_t EXTENDED_CAPACITY = 2;

// Memory-related macros 
#define new(a, n) (a*)calloc(n, sizeof(a) * n)
#define reallocate(ptr, a, n) (a*)realloc(ptr, sizeof(a) * n)

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

// Initialize string with default capacity
int init_string(string* s) {
    int result = UNDEFINED;
    s->memory_size = INIT_CAPACITY;
    s->values = new(char, INIT_CAPACITY);
    s->last_element = 0;
    return result;
}

// Sets all struct's parameters to zero
int free_string(string* s) {
    s->values = new(char, 0);
    s->last_element = 0;
    s->memory_size = 0;
    return SUCCESS;
}

// Reallocates memory
int string_resize(string* s, uint64_t capacity) {
    s->values = reallocate(s->values, char, capacity);
    return SUCCESS;
}

// Copies s2 to s1 (taking minimal memory size): s1='aboba', s2='bobr' -> s1='bobr '
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

// Pushes a char to string 
int push_char(string* s, char value) {
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

// Pushes whole string2 to string1
int push_string(string* s1, string s2) {
    int result = UNDEFINED;
    for (uint64_t i = 0; i < s2.last_element; ++i) {
        result = push_char(s1, s2.values[i]);
        if (result != SUCCESS) { return result; }
    }
    return SUCCESS;
}

// Pushes native C string to string
int push_chars(string* s, char values[]) {
    int result = UNDEFINED;
    uint64_t l = strlen(values);
    for (uint64_t i = 0; i < l; ++i) {
        result = push_char(s, values[i]);
        if (result != SUCCESS) { return result; }
    }
    return SUCCESS;
}

// Fully changes parameters of s1 to s2
int set_string(string* s1, string s2) {
    *s1 = s2;
    return SUCCESS;
}

// Reads string char by char returning 1 if EOF
int read_string(string* s) {
    char c = ' ';
    int end = 0;

    while (1) {
        c = getchar();
        if (c == ' ' || c == ',' || c == '\t' || c == '\n') {
            break;
        } else if ((int) c == EOF) {
            end = 1;
            break;
        }
        push_char(s, c);
    }

    return end;
}
