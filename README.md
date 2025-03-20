# Billing System

## Overview

This is a simple billing system in C that allows users to:

- Generate bills for customers.
- View the available stock of products.
- Update stock quantities.

The system reads product stock from a file (`stock.txt`) and updates it based on purchases. It also calculates GST at a fixed rate of 3%.

## Features

- **Generate Bill:**

  - Enter customer details.
  - Add multiple products to the bill.
  - Check product availability in stock.
  - Calculate total amount with GST.
  - Save bill details in `bill.txt`.

- **View Stock:**

  - Display all available products with price and quantity.
  - Read stock details from `stock.txt`.

- **Update Stock:**

  - Modify product quantities.
  - Save updated stock to `stock.txt`.

## Files

- `customer.h` - Header file for customer-related operations.
- `bill.h` - Header file for billing operations.
- `stock.txt` - Stores product names, prices, and quantities.
- `bill.txt` - Stores generated bills.
- `billing_system.c` - Main source code.

## Compilation & Execution

To compile the program, use:

Run the executable:

## Usage

1. Run the program.
2. Choose an option:
   - Generate a new bill.
   - View stock.
   - Update stock.
3. Follow on-screen instructions.

## Notes

- Ensure `stock.txt` exists before running the program.
- Bills are stored in `bill.txt` and overwritten on each new transaction.

## Future Enhancements

- Save multiple bills without overwriting.
- Implement a database instead of text files.
- Improve user interface with a GUI.

## Author

Sarayu Ventrapati

