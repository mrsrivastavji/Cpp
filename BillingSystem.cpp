#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <limits>

using namespace std;

// -----------------------------------------------------
// Model Class : Represents an Item
// -----------------------------------------------------
class Item {
private:
    int id;
    string name;
    double price;
    int stock;

public:
    // Constructor
    Item(int id, string name, double price, int stock) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->stock = stock;
    }

    // Getters
    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getStock() const {
        return stock;
    }

    // Setters
    void setPrice(double price) {
        this->price = price;
    }

    void setStock(int stock) {
        this->stock = stock;
    }

    // Display Item
    void display() const {
        cout << left
             << setw(10) << id
             << setw(20) << name
             << setw(10) << fixed << setprecision(2) << price
             << setw(10) << stock
             << endl;
    }
};

// -----------------------------------------------------
// Inventory Manager Class
// -----------------------------------------------------
class InventoryManager {
private:
    vector<Item> items;

    // Search item by ID
    Item* searchItem(int id) {
        for (auto &item : items) {
            if (item.getId() == id) {
                return &item;
            }
        }
        return nullptr;
    }

    // Integer input validation
    int getIntInput() {
        int value;

        while (!(cin >> value)) {
            cout << "Invalid input! Enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }

    // Double input validation
    double getDoubleInput() {
        double value;

        while (!(cin >> value)) {
            cout << "Invalid input! Enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }

public:

    // Add Item
    void addItem() {

        int id, stock;
        double price;
        string name;

        cout << "Enter Item ID: ";
        id = getIntInput();

        cout << "Enter Item Name: ";
        getline(cin, name);

        cout << "Enter Price: ";
        price = getDoubleInput();

        cout << "Enter Stock Quantity: ";
        stock = getIntInput();

        items.push_back(Item(id, name, price, stock));

        cout << "Item added successfully!" << endl;
    }

    // Update Item
    void updateItem() {

        cout << "Enter Item ID to update: ";
        int id = getIntInput();

        Item* item = searchItem(id);

        if (item == nullptr) {
            cout << "Item not found!" << endl;
            return;
        }

        cout << "1. Update Price" << endl;
        cout << "2. Update Stock" << endl;
        cout << "Choose an option: ";

        int choice = getIntInput();

        switch (choice) {

            case 1: {
                cout << "Enter new price: ";
                double newPrice = getDoubleInput();

                item->setPrice(newPrice);

                cout << "Price updated successfully!" << endl;
                break;
            }

            case 2: {
                cout << "Enter new stock quantity: ";
                int newStock = getIntInput();

                item->setStock(newStock);

                cout << "Stock updated successfully!" << endl;
                break;
            }

            default:
                cout << "Invalid option!" << endl;
        }
    }

    // View Inventory
    void viewInventory() {

        if (items.empty()) {
            cout << "No items in inventory." << endl;
            return;
        }

        cout << "\n---------------- INVENTORY ----------------" << endl;

        cout << left
             << setw(10) << "ID"
             << setw(20) << "NAME"
             << setw(10) << "PRICE"
             << setw(10) << "STOCK"
             << endl;

        cout << "-------------------------------------------" << endl;

        for (const auto &item : items) {
            item.display();
        }

        cout << "-------------------------------------------" << endl;
    }

    // Generate Bill
    void generateBill() {

        unordered_map<int, int> cart;

        while (true) {

            cout << "Enter Item ID to purchase (0 to finish): ";

            int id = getIntInput();

            if (id == 0)
                break;

            Item* item = searchItem(id);

            if (item == nullptr) {
                cout << "Item not found!" << endl;
                continue;
            }

            cout << "Enter quantity: ";
            int qty = getIntInput();

            if (qty > item->getStock()) {
                cout << "Not enough stock!" << endl;
                continue;
            }

            cart[id] += qty;

            item->setStock(item->getStock() - qty);

            cout << "Item added to cart!" << endl;
        }

        if (cart.empty()) {
            cout << "No items purchased." << endl;
            return;
        }

        cout << "\n---------------------- BILL ----------------------" << endl;

        cout << left
             << setw(20) << "ITEM"
             << setw(10) << "QTY"
             << setw(10) << "PRICE"
             << setw(10) << "TOTAL"
             << endl;

        cout << "--------------------------------------------------" << endl;

        double grandTotal = 0;

        for (auto &entry : cart) {

            int id = entry.first;
            int qty = entry.second;

            Item* item = searchItem(id);

            if (item != nullptr) {

                double price = item->getPrice();
                double total = qty * price;

                grandTotal += total;

                cout << left
                     << setw(20) << item->getName()
                     << setw(10) << qty
                     << setw(10) << fixed << setprecision(2) << price
                     << setw(10) << total
                     << endl;
            }
        }

        double tax = grandTotal * 0.18;
        double finalTotal = grandTotal + tax;

        cout << "--------------------------------------------------" << endl;

        cout << "Subtotal: " << fixed << setprecision(2)
             << grandTotal << endl;

        cout << "GST (18%): " << tax << endl;

        cout << "Final Total: " << finalTotal << endl;

        cout << "--------------------------------------------------" << endl;

        cout << "Thank you for shopping!" << endl;
    }

    // Menu System
    void showMenu() {

        while (true) {

            cout << "\n====== BILLING & INVENTORY SYSTEM ======" << endl;

            cout << "1. Add Item" << endl;
            cout << "2. Update Item" << endl;
            cout << "3. View Inventory" << endl;
            cout << "4. Generate Bill" << endl;
            cout << "5. Exit" << endl;

            cout << "Enter choice: ";

            int choice = getIntInput();

            switch (choice) {

                case 1:
                    addItem();
                    break;

                case 2:
                    updateItem();
                    break;

                case 3:
                    viewInventory();
                    break;

                case 4:
                    generateBill();
                    break;

                case 5:
                    cout << "Exiting system..." << endl;
                    return;

                default:
                    cout << "Invalid choice! Try again." << endl;
            }
        }
    }
};

// -----------------------------------------------------
// Main Function
// -----------------------------------------------------
int main() {

    InventoryManager manager;

    manager.showMenu();

    return 0;
}