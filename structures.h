#ifndef STRUCTURES_H
#define STRUCTURES_H

// Define structure for a bill
struct Bill {
    int number;
    float totalAmount;
    // You can add more fields as needed
};

// Define structure for a customer
struct Customer {
    char name[100];
    char contact[100];
};

#endif /* STRUCTURES_H */
