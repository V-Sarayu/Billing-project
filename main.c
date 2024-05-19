#include <stdio.h>
#include <stdlib.h>
#include "customer.h"
#include "bill.h"

int main() {
    int choice;
    printf("Welcome to the Grocery Store!\n");
    printf("1. Create Bill\n");
    printf("2. View Stock\n");
    printf("3. Update Stock\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            generateBill();
            break;
        case 2:
            viewStock();
            break;
        case 3:
            updateStock();
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
