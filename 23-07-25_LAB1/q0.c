#include <stdio.h>

// WAP in C to swap two variables using function and pointer
void swap(int *ptr1, int *ptr2) {
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

int main() {
    int num1, num2;

    printf("Enter the value of num1 and num2: ");
    scanf("%d %d", &num1, &num2);

    printf("\nBefore swapping: %d and %d\n", num1, num2);

    swap(&num1, &num2);

    printf("After swapping: %d and %d\n", num1, num2);

    return 0;
}
