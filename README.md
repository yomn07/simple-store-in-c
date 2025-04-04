# Simple Online Store in C

This project is a simple command-line based online store application written in **C**. It provides two user roles: **Administrator** and **Customer**. The system allows administrators to manage products and stock, while customers can create accounts, browse products, and make orders.

## Features:
### **Administrator:**
- Add, update, and delete products in the catalog.
- Modify product details such as price, stock, and name.

### **Customer:**
- Register a new account with personal details.
- View and browse available products.
- Place orders for selected products.
- View order history.

## Core Data Structures:
- **Product:** Contains information about the product's reference, name, price, and stock.
- **Client:** Stores customer details including contact information, date of birth, and order history.
- **Order:** Each order contains a description of the products purchased.

## Key Functions:
- **Create Account:** Allows new customers to register with personal details.
- **Product Catalog Management:** Admin can add or update product details, modify stock, and delete products.
- **Order Placement:** Customers can add products to their cart and place an order. The system ensures stock availability and updates the catalog accordingly.

## Technologies Used:
- **C Programming Language**
- **Basic File Handling** (for managing data during program execution)
- **Memory Management** (using dynamic memory allocation)

## How to Run:
1. Clone this repository:
   ```bash
   git clone https://github.com/YOUR-USERNAME/simple-store-in-c.git
