#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "structures.h"

float calculateGST(float amount) {
    return 0.04 * amount; // Assuming GST rate is 4%
}

int generateBillNumber() {
    static int billNumber = 0;
    return ++billNumber;
}

// Function to create a file with bill details and update inventory
void generateBill() {
    // Declare variables
    char productName[100];
    int productQuantity;
    float totalAmount = 0;
    struct Bill bill;
    struct Customer customer;

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

    // Open stock file for reading and writing
    FILE *stockFile = fopen("stock.txt", "r+");
    if (stockFile == NULL) {
        printf("Error opening stock file for update.\n");
        fclose(billFile);
        return;
    }

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

        // Search for the product in stock file
        char name[100];
        float price;
        int quantity;
        long int pos;
        while (fscanf(stockFile, "%s %f %d", name, &price, &quantity) != EOF) {
            if (strcmp(productName, name) == 0) {
                // Update quantity in stock
                pos = ftell(stockFile);
                quantity -= productQuantity;
                fseek(stockFile, pos, SEEK_SET);
                fprintf(stockFile, "%s %.2f %d\n", name, price, quantity);
                break;
            }
        }
        fseek(stockFile, 0, SEEK_SET);

        // Calculate total amount for this product
        float productTotal = price * productQuantity;

        // Add product details to bill file
        fprintf(billFile, "Product Details:\n");
        fprintf(billFile, "Name: %s\n", productName);
        fprintf(billFile, "Price: %.2f\n", price);
        fprintf(billFile, "Quantity: %d\n", productQuantity);
        fprintf(billFile, "Total for this product: %.2f\n", productTotal);

        // Add product total to overall total
        totalAmount += productTotal;
    }

    // Calculate GST amount
    float gstAmount = calculateGST(totalAmount);

    //Print bill number
    printf("Your bill number is: %d \n",bill.number);

    // Display GST amount
    fprintf(billFile, "GST (4%%): %.2f\n", gstAmount);
    printf("The gst is: %.2f \n",gstAmount);

    // Add GST to total amount
    totalAmount += gstAmount;

    // Write total amount to bill file
    fprintf(billFile, "Total Amount (Including GST): %.2f\n", totalAmount);

    // Print total amount
    printf("Total Amount (Including GST): %.2f\n", totalAmount);


    // Close files
    fclose(stockFile);
    fclose(billFile);

    printf("Bill generated successfully.\n");
}

