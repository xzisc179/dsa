1.Write a program in C to display the following patterns:
a. Right-angle triangle with a number
b. Diamond shape with numbers


#include <stdio.h>

int main() {
    int n, i, j, space;
    printf("Enter number of rows: ");
    scanf("%d", &n);

    printf("\n(a) Right-angle triangle with numbers:\n");
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }

    printf("\n(b) Diamond shape with numbers:\n");
    for(i = 1; i <= n; i++) {
        for(space = i; space < n; space++)
            printf(" ");
        for(j = 1; j <= i; j++)
            printf("%d", j);
        for(j = i - 1; j >= 1; j--)
            printf("%d", j);
        printf("\n");
    }

    for(i = n - 1; i >= 1; i--) {
        for(space = n; space > i; space--)
            printf(" ");
        for(j = 1; j <= i; j++)
            printf("%d", j);
        for(j = i - 1; j >= 1; j--)
            printf("%d", j);
        printf("\n");
    }

    return 0;
}
