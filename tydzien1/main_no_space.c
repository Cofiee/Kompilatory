#include <stdio.h>
#include <string.h>

int main() {
    int c;

    while ((c = getchar()) != EOF) {
        if (!isspace(c)) 
            putchar(c);
    }
    return 0;
}