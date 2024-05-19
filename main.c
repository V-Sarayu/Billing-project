#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "customer.h"
#include "bill.h"

// Function to view stock
void viewStock() {
    // Read stock from file and print it
    FILE *file = fopen("stock.txt", "r");
    if (file == NULL) {
        printf("Error opening stock file.\n");
        return;
    }
    printf("Stock Details:\n");
    printf("---------------------------------\n");
    printf("| %-20s | %-8s | %-8s |\n", "Product Name", "Price", "Quantity");
    printf("---------------------------------\n");
    char productName[100];
    float productPrice;
    int productQuantity;
    while (fscanf(file, "%s %f %d", productName, &productPrice, &productQuantity) != EOF) {
        printf("| %-20s | %-8.2f | %-8d |\n", productName, productPrice, productQuantity);
    }
    printf("---------------------------------\n");
    fclose(file);
}

// Function to update stock
void updateStock() {
    // Read existing stock from file
    FILE *file = fopen("stock.txt", "r");
    if (file == NULL) {
        printf("Error opening stock file.\n");
        return;
    }
    // Store stock data in arrays
    char productNames[100][100]; 
    float productPrices[100]; 
    int productQuantities[100]; 
    int numProducts = 0;
    while (fscanf(file, "%s %f %d", productNames[numProducts], &productPrices[numProducts], &productQuantities[numProducts]) != EOF) {
        numProducts++;
    }
    fclose(file);

    // Update stock
    int choice, quantity;
    printf("Select product to update:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("%d. %s\n", i + 1, productNames[i]);
    }
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > numProducts) {
        printf("Invalid choice.\n");
        return;
    }
    printf("Enter new quantity: ");
    scanf("%d", &quantity);
    productQuantities[choice - 1] = quantity;

    // Write updated stock to file
    file = fopen("stock.txt", "w");
    if (file == NULL) {
        printf("Error opening stock file.\n");
        return;
    }
    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "%s %.2f %d\n", productNames[i], productPrices[i], productQuantities[i]);
    }
    fclose(file);

    printf("Stock updated successfully.\n");
}

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
            //inputCustomerDetails();
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
