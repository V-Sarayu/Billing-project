#include <stdio.h>

// Function to generate a unique bill number
int generateBillNumber() {
    static int billNumber = 0;
    return ++billNumber;
}

// Function to create a file with bill details
void createBillFile(float total) {
    char filename[50];
    int billNumber = generateBillNumber();
    sprintf(filename, "bill_%d.txt", billNumber);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating bill file.\n");
        return;
    }

    fprintf(file, "Bill Number: %d\n", billNumber);
    fprintf(file, "\nTotal amount (including GST): %.2f\n", total);

    fclose(file);
}
