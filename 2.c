2.Write a program in C to display the following patterns:
a. Pyramid with an asterisk
b. Pyramid using the alphabet


#include <stdio.h>

int main() {
    int n, i, j, space;
    char ch;

    printf("Enter number of rows: ");
    scanf("%d", &n);

    printf("\n(a) Pyramid with an asterisk:\n");
    for(i = 1; i <= n; i++) {
        for(space = i; space < n; space++)
            printf(" ");
        for(j = 1; j <= (2 * i - 1); j++)
            printf("*");
        printf("\n");
    }

    printf("\n(b) Pyramid using the alphabet:\n");
    for(i = 1; i <= n; i++) {
        ch = 'A';
        for(space = i; space < n; space++)
            printf(" ");
        for(j = 1; j <= (2 * i - 1); j++) {
            printf("%c", ch);
            if(j < i) ch++;
            else ch--;
        }
        printf("\n");
    }

    return 0;
}
