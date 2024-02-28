// An STB-style library for string
// 
// use
//
// #define _STRING_IMPLEMENTATION
//
// before including the header file to turn on the implementation

#ifndef _STRING_H
#define _STRING_H

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct string {
    char *values;
    uint32_t last_element;
    uint32_t memory_size;
} string;


// Initialize string with default capacity
int string_init(string* s);

// Adds memory
int string_resize(string* s, uint32_t capacity);

// Adds a char to string, adding more memory if needed 
int string_push_char(string* s, char value);

// Pushes native C string to the custom string
int string_push_str(string* s, char values[]);

// Pushes whole s2 to s1
int string_push_string(string* s1, string s2);

// Copies s2 to s1 (taking minimal memory size) -> s1='aboba', s2='bobr' -> s1='bobr '
int string_copy(string* s1, string s2);

// Fully changes parameters of s1 to s2
int string_set(string* s1, string s2);

// Reads string char by char returning EOF if EOF
int string_read(string* s, FILE* stream);

// Returns index of char if present, else -1
int64_t string_find(string s1, char c);

// Returns 1 if char is present else 0
int string_contains(string s1, char c);

// Returns length of a string
uint32_t string_len(string s);

// Returns element at ith position if it exists, else EOF
int string_at(string s, uint32_t i);

// Free the buffer, set all fields to 0
void string_free(string s);


#ifdef _STRING_IMPLEMENTATION
//? Maybe deprecated, but those are for error handling
#define STRING_UNDEFINED 0
#define STRING_SUCCESS 1
#define STRING_ERROR -1

// How big initial memory is
const uint32_t STRING_INIT_CAPACITY = 2;
// How big relative to previous allocated memory new memory should be
const uint32_t STRING_EXTENDED_CAPACITY_FACTOR = 2;

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

int string_init(string* s) {
    int result = STRING_UNDEFINED;

    s->memory_size = STRING_INIT_CAPACITY;
    s->values = (char*) calloc(STRING_INIT_CAPACITY, sizeof(char));
    s->last_element = 0;

    return result;
}

int string_resize(string* s, uint32_t capacity) {
    s->memory_size *= capacity;
    char *new_ptr = (char*) realloc(s->values, sizeof(char) * s->memory_size);

    if (new_ptr == NULL) return STRING_ERROR;
    s->values = new_ptr;

    return STRING_SUCCESS;
}

int string_push_char(string* s, char value) {
    int result = STRING_UNDEFINED;

    if (s->last_element < s->memory_size - 1) {
        result = STRING_SUCCESS;
    } else {
        result = string_resize(s, STRING_EXTENDED_CAPACITY_FACTOR);
    }

    s->values[s->last_element] = value;
    s->values[s->last_element + 1] = '\0';
    s->last_element++;

    return result;
}

int string_push_str(string* s, char values[]) {
    int result = STRING_UNDEFINED;

    uint32_t l = strlen(values);
    for (uint32_t i = 0; i < l; ++i) {
        result = string_push_char(s, values[i]);
        if (result != STRING_SUCCESS) return result;
    }

    return result;
}

int string_push_string(string* s1, string s2) {
    int result = STRING_UNDEFINED;

    result = string_push_str(s1, s2.values);

    return result;
}

int string_copy(string* s1, string s2) {
    int result = STRING_UNDEFINED;

    uint32_t minimal = min(s1->last_element, s2.last_element);
    for (uint32_t i = 0; i < s1->last_element; ++i) {
        if (i < minimal) {
            s1->values[i] = s2.values[i];
        } else {
            s1->values[i] = ' ';
        }
    }
    s1->last_element = minimal;

    return result;
}

int string_set(string* s1, string s2) {
    int result = STRING_UNDEFINED;

    string_free(*s1);
    result = string_init(s1);
    result = string_push_string(s1, s2);

    return result;
}

int string_read(string* s, FILE* stream) {
    string_free(*s);
    string_init(s);

    int c = 0;
    int end = 0;

    while (1) {
        c = fgetc(stream);
        char ch = (char) c;

        if (c == EOF) {
            end = EOF;
            break;
        } else if (ch == ' ' || ch == '\t' || ch == '\n') {
            break;
        }

        string_push_char(s, ch);
    }

    return end;
}

int64_t string_find(string s, char c) {
    for (int64_t i = 0; i < s.last_element; ++i) {
        if (s.values[i] == c) {
            return i;
        }
    }

    return -1;
}

int string_contains(string s, char c) {
    for (uint32_t i = 0; i < s.last_element; ++i) {
        if (s.values[i] == c) {
            return 1;
        }
    }

    return 0;
}

uint32_t string_len(string s) {
    return s.last_element;
}

int string_at(string s, uint32_t i) {
    if (i <= s.last_element) {
        return s.values[i];
    } else {
        return EOF;
    }
}

void string_free(string s) {
    if (s.values != NULL) free(s.values);
    s.values = NULL;
    s.last_element = 0;
    s.memory_size = 0;
}

#endif // _STRING_IMPLEMENTATION

#endif // _STRING_H
