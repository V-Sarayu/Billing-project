#ifndef CUSTOMER_H
#define CUSTOMER_H

struct Customer {
    char name[100];
    char contact[100];
};

void inputCustomerDetails(struct Customer *customer);

#endif /* CUSTOMER_H */

