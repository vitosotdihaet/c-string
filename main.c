#include <stdio.h>
#include "string.h"

int main() {
    string s1;
    init_string(&s1);
    string s2;
    init_string(&s2);

    push_char(&s2, 'h');
    push_char(&s2, 'i');
    push_char(&s2, 'a');

    printf("s2 after adding h and i: %s\n", s2.values);

    push_char(&s1, 'a');
    printf("s1 after adding a: %s\n", s1.values);

    push_string(&s1, s2);
    printf("s1 after pushing s2: %s\n", s1.values);

    copy_string(&s2, s1);
    printf("s2 after copying s1: %s\n", s2.values);

    free_string(&s1);
    printf("s1 after freeing: %s\n", s1.values);

    return 0;
}