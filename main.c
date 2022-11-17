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

    printf("s2 after pushing h, i and a: %s\n", s2.values);

    push_char(&s1, 'a');
    printf("s1 after pushing a: %s\n", s1.values);

    push_string(&s1, s2);
    printf("s1 after pushing s2 to it: %s\n", s1.values);

    copy_string(&s2, s1);
    printf("s2 after copying s1: %s\n", s2.values);

    printf("Input any string: ");
    read_string(&s1);
    printf("s1 after reading: %s\n", s1.values);

    set_string(&s2, s1);
    printf("s2 after setting it to s1: %s\n", s2.values);

    push_chars(&s1, "hello!");
    printf("s1 after pushing \"hello!\" to it: %s\n", s1.values);

    push_string(&s2, s1);
    printf("s2 after pushing s1 to it: %s\n", s2.values);

    return 0;
}
