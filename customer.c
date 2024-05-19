#include <stdio.h>
#include "structures.h"

// Function to input customer details and write to file
void inputCustomerDetails(struct Customer *customer) {
    printf("Enter customer details:\n");
    printf("Name: ");
    scanf("%s", customer->name);
    printf("Contact: ");
    scanf("%s", customer->contact);

    // Write customer details to file
    FILE *file = fopen("customer_details.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "Customer Details:\n");
    fprintf(file, "Name: %s\n", customer->name);
    fprintf(file, "Contact: %s\n", customer->contact);
    fclose(file);
}

