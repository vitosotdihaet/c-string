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
<<<<<<< HEAD
    string_read(&s1);
    printf("s1 after reading: %s. It's length is %"PRIu32"\n", s1.values, string_len(s1));
=======
    string_read(&s1, stdin);
    printf("s1 after reading: %s. It's length is %d\n", s1.values, string_len(s1));
>>>>>>> 5fef2b9e7f06f4f61ca5853394fb784676dd7c18

    string_set(&s2, s1);
    printf("s2 after setting it to s1: %s\n", s2.values);

    string_push_str(&s1, "hello!");
    printf("s1 after pushing \"hello!\" to it: %s\n", s1.values);

    string_push_string(&s2, s1);
    printf("s2 after pushing s1 to it: %s\n", s2.values);

    if (string_contains(s2, 'a')) {
<<<<<<< HEAD
        printf("s2 contains 'a'! It's index is %"PRIi64"!\n", string_index(s2, 'a'));
=======
        printf("s2 contains 'a'! It's index is %ld!\n", string_index(s2, 'a'));
>>>>>>> 5fef2b9e7f06f4f61ca5853394fb784676dd7c18
    } else {
        printf("s2 doesn't contain 'a' :(\n");
    }

    printf("Char in s2 at index = 0 is %c\n", string_at(s2, 0));

    return 0;
}
