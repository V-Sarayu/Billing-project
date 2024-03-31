#include <stdio.h>

// Function to input customer details and write to file
void inputCustomerDetails() {
    char customerName[100]; // Adjust as needed
    char customerContact[100]; // Adjust as needed

    // Input customer details
    printf("Enter customer details:\n");
    printf("Name: ");
    scanf("%s", customerName);
    printf("Contact: ");
    scanf("%s", customerContact);

    // Write customer details to file
    FILE *file = fopen("customer_details.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "Customer Details:\n");
    fprintf(file, "Name: %s\n", customerName);
    fprintf(file, "Contact: %s\n", customerContact);
    fclose(file);
}
