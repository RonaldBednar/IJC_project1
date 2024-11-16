#include <stdio.h>

// This is a single-line comment
int main() {
    printf("Hello, world!\n"); // This is a single-line comment after code

    /* This is a block comment */ printf("This code contains block comment inside code\n");

    printf("/* This is not a block comment */\n");

    printf("// This is not a line comment\n");

    printf("This line contains // a comment in code\n");

    char *str = "This is a string /* with a block comment */ inside";
    printf("%s\n", str);

    char ch = '\''; // This line contains a character literal inside code

    /*
        This is a multi-line
        comment
    */
    printf("This is code inside a multi-line comment\n");

    // This is a single-line comment with a backslash at the end \
    printf("This line continues after the backslash\n");

    return 0;
}
