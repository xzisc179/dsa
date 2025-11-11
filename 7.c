7.Write a program to convert a Decimal number to a Binary number using a stack.




#include <stdio.h>
#define MAX 64

int stack[MAX];
int top = -1;

void push(int v) {
    if (top < MAX - 1) stack[++top] = v;
}

int pop() {
    if (top >= 0) return stack[top--];
    return -1;
}

int isEmpty() {
    return top == -1;
}

int main() {
    unsigned int n;
    printf("Enter a decimal number: ");
    if (scanf("%u", &n) != 1) return 0;

    if (n == 0) {
        printf("Binary: 0\n");
        return 0;
    }

    while (n > 0) {
        push(n % 2);
        n /= 2;
    }

    printf("Binary: ");
    while (!isEmpty()) {
        printf("%d", pop());
    }
    printf("\n");
    return 0;
}
