#include <stdio.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

int main() {
    int c;
    int tag_flag;

    while ((c = getchar()) != EOF) {
        if (c == '<')
            tag_flag = TRUE;
        else if (c == '>')
            tag_flag = FALSE;
        if (!tag_flag)
            putchar(c);
    }
    return 0;
}