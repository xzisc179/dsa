3. Write a program that locates a specific name in a list of contact names using binary search technique.




#include <stdio.h>
#include <string.h>

int main() {
    char names[10][50], key[50];
    int n, i, low, high, mid, found = 0;

    printf("Enter number of contacts: ");
    scanf("%d", &n);

    printf("Enter contact names in alphabetical order:\n");
    for(i = 0; i < n; i++)
        scanf("%s", names[i]);

    printf("Enter name to search: ");
    scanf("%s", key);

    low = 0;
    high = n - 1;

    while(low <= high) {
        mid = (low + high) / 2;
        if(strcmp(names[mid], key) == 0) {
            found = 1;
            break;
        }
        else if(strcmp(names[mid], key) < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    if(found)
        printf("Name '%s' found at position %d.\n", key, mid + 1);
    else
        printf("Name '%s' not found in the list.\n", key);

    return 0;
}
