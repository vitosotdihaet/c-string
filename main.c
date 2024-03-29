#include <stdio.h>
#include <inttypes.h>

#define _STRING_IMPLEMENTATION
#include "string.h"


int main() {
    string s1;
    string_init(&s1);
    string s2;
    string_init(&s2);

    string_push_char(&s2, 'h');
    string_push_char(&s2, 'i');
    string_push_char(&s2, 'a');

    printf("s2 after pushing h, i and a: %s\n", s2.values);

    string_push_char(&s1, 'a');
    printf("s1 after pushing a: %s\n", s1.values);

    string_push_string(&s1, s2);
    printf("s1 after pushing s2 to it: %s\n", s1.values);

    string_copy(&s2, s1);
    printf("s2 after copying s1: %s\n", s2.values);

    printf("Input any string to s1: ");
    string_read(&s1, stdin);
    printf("s1 after reading: %s. It's length is %"PRIu32"\n", s1.values, string_len(s1));

    string_set(&s2, s1);
    printf("s2 after setting it to s1: %s\n", s2.values);

    string_push_str(&s1, "hello!");
    printf("s1 after pushing \"hello!\" to it: %s\n", s1.values);

    string_push_string(&s2, s1);
    printf("s2 after pushing s1 to it: %s\n", s2.values);

    if (string_contains(s2, 'a')) {
        printf("s2 contains 'a'! It's index is %"PRIi64"!\n", string_find(s2, 'a'));
    } else {
        printf("s2 doesn't contain 'a' :(\n");
    }

    printf("Char in s2 at index = 0 is %c\n", string_at(s2, 0));

    string_free(s1);
    string_free(s2);

    return 0;
}
