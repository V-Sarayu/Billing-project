#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "bill.h"

float calculateGST(float amount) {
    return 0.03 * amount; // Assuming GST rate is 3%
}

int generateBillNumber() {
    static int billNumber = 0;
    return ++billNumber;
}

void generateBill() {
    // Declare variables
    char productName[100];
    int productQuantity;
    float totalAmount = 0;
    struct Bill bill;
    struct Customer customer;
    StockItem stock[MAX_PRODUCTS];
    int stockCount = 0;
    int i, found;

    // Input customer details
    inputCustomerDetails(&customer);

    // Open bill file for writing
    FILE *billFile = fopen("bill.txt", "w");
    if (billFile == NULL) {
        printf("Error creating bill file.\n");
        return;
    }

    // Generate bill number
    bill.number = generateBillNumber();
    fprintf(billFile, "Bill Number: %d\n", bill.number);

    // Open stock file for reading
    FILE *stockFile = fopen("stock.txt", "r");
    if (stockFile == NULL) {
        printf("Error opening stock file.\n");
        fclose(billFile);
        return;
    }

    // Read stock file into memory
    while (fscanf(stockFile, "%s %f %d", stock[stockCount].name, &stock[stockCount].price, &stock[stockCount].quantity) == 3) {
        stockCount++;
    }
    fclose(stockFile);

    // Input product details repeatedly until user is done
    while (1) {
        // Get product details
        printf("Enter product name (type 'done' to finish): ");
        scanf("%s", productName);
        if (strcmp(productName, "done") == 0) {
            break;
        }
        printf("Quantity: ");
        scanf("%d", &productQuantity);

        // Search for the product in stock array
        found = 0;
        for (i = 0; i < stockCount; i++) {
            if (strcmp(stock[i].name, productName) == 0) {
                found = 1;
                if (stock[i].quantity >= productQuantity) {
                    stock[i].quantity -= productQuantity;
                    // Calculate total amount for this product
                    float productTotal = stock[i].price * productQuantity;

                    // Add product details to bill file
                    fprintf(billFile, "Product Details:\n");
                    fprintf(billFile, "Name: %s\n", productName);
                    fprintf(billFile, "Price: %.2f\n", stock[i].price);
                    fprintf(billFile, "Quantity: %d\n", productQuantity);
                    fprintf(billFile, "Total for this product: %.2f\n", productTotal);

                    // Add product total to overall total
                    totalAmount += productTotal;
                } else {
                    printf("Not enough stock for %s. Available: %d\n", productName, stock[i].quantity);
                }
                break;
            }
        }
        if (!found) {
            printf("Product not found: %s\n", productName);
        }
    }

    // Calculate GST amount
    float gstAmount = calculateGST(totalAmount);

    // Print bill number
    printf("Your bill number is: %d \n", bill.number);

    // Display GST amount
    fprintf(billFile, "GST (3%%): %.2f\n", gstAmount);
    printf("The GST is: %.2f \n", gstAmount);

    // Add GST to total amount
    totalAmount += gstAmount;

    // Write total amount to bill file
    fprintf(billFile, "Total Amount (Including GST): %.2f\n", totalAmount);

    // Print total amount
    printf("Total Amount (Including GST): %.2f\n", totalAmount);

    // Open stock file for writing to update quantities
    stockFile = fopen("stock.txt", "w");
    if (stockFile == NULL) {
        printf("Error opening stock file for update.\n");
        fclose(billFile);
        return;
    }

    // Write updated stock back to file
    for (i = 0; i < stockCount; i++) {
        fprintf(stockFile, "%s %.2f %d\n", stock[i].name, stock[i].price, stock[i].quantity);
    }
    fclose(stockFile);

    // Close bill file
    fclose(billFile);

    printf("Bill generated successfully.\n");
}

void viewStock() {
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

void updateStock() {
    FILE *file = fopen("stock.txt", "r");
    if (file == NULL) {
        printf("Error opening stock file.\n");
        return;
    }
    char productNames[100][100]; 
    float productPrices[100]; 
    int productQuantities[100]; 
    int numProducts = 0;
    while (fscanf(file, "%s %f %d", productNames[numProducts], &productPrices[numProducts], &productQuantities[numProducts]) != EOF) {
        numProducts++;
    }
    fclose(file);

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
