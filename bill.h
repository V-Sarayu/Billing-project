#ifndef BILL_H
#define BILL_H

#define MAX_PRODUCTS 100

struct Bill {
    int number;
    // Add any other bill-related fields here as needed
};

typedef struct {
    char name[100];
    float price;
    int quantity;
} StockItem;

void generateBill();
void viewStock();
void updateStock();

#endif /* BILL_H */
