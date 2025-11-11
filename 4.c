4.Implement bubble sort and selection sort to reorder product prices for items of a store.



#include <stdio.h>

int main() {
    int n, i, j, temp, min;
    float prices[50];

    printf("Enter number of products: ");
    scanf("%d", &n);

    printf("Enter product prices:\n");
    for(i = 0; i < n; i++)
        scanf("%f", &prices[i]);

    printf("\n(a) Bubble Sort:\n");
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(prices[j] > prices[j + 1]) {
                temp = prices[j];
                prices[j] = prices[j + 1];
                prices[j + 1] = temp;
            }
        }
    }
    printf("Prices in ascending order:\n");
    for(i = 0; i < n; i++)
        printf("%.2f ", prices[i]);

    printf("\n\n(b) Selection Sort:\n");
    printf("Enter product prices again:\n");
    for(i = 0; i < n; i++)
        scanf("%f", &prices[i]);

    for(i = 0; i < n - 1; i++) {
        min = i;
        for(j = i + 1; j < n; j++) {
            if(prices[j] < prices[min])
                min = j;
        }
        if(min != i) {
            temp = prices[i];
            prices[i] = prices[min];
            prices[min] = temp;
        }
    }
    printf("Prices in ascending order:\n");
    for(i = 0; i < n; i++)
        printf("%.2f ", prices[i]);

    return 0;
}
