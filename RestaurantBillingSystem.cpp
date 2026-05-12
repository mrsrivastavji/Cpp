#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// -----------------------------------------------------
// Menu Item Class
// -----------------------------------------------------
class MenuItem {
private:
    string name;
    double price;

public:
    // Constructor
    MenuItem(string name, double price) {
        this->name = name;
        this->price = price;
    }

    // Getters
    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    // Display Item
    void display() const {
        cout << name << " - Rs. " << fixed << setprecision(2)
             << price << endl;
    }
};

// -----------------------------------------------------
// Order Item Class
// -----------------------------------------------------
class OrderItem {
private:
    MenuItem item;
    int quantity;

public:
    // Constructor
    OrderItem(MenuItem item, int quantity)
        : item(item), quantity(quantity) {}

    double getTotal() const {
        return item.getPrice() * quantity;
    }

    string getName() const {
        return item.getName();
    }

    int getQuantity() const {
        return quantity;
    }

    double getPrice() const {
        return item.getPrice();
    }
};

// -----------------------------------------------------
// Restaurant Billing System Class
// -----------------------------------------------------
class RestaurantBillingSystem {
private:

    vector<MenuItem> menu;
    vector<OrderItem> cart;

    const double GST = 0.05;

public:

    // Constructor
    RestaurantBillingSystem() {

        menu.push_back(MenuItem("Pizza", 250));
        menu.push_back(MenuItem("Burger", 120));
        menu.push_back(MenuItem("Pasta", 180));
    }

    // View Menu
    void viewMenu() {

        cout << "\n----- MENU -----" << endl;

        for (int i = 0; i < menu.size(); i++) {

            cout << i + 1 << ". ";

            menu[i].display();
        }
    }

    // Add Menu Item
    void addMenuItem() {

        string name;
        double price;

        cin.ignore();

        cout << "Enter item name: ";
        getline(cin, name);

        cout << "Enter item price: ";
        cin >> price;

        menu.push_back(MenuItem(name, price));

        cout << "Item added successfully!" << endl;
    }

    // Remove Menu Item
    void removeMenuItem() {

        viewMenu();

        cout << "Enter item number to remove: ";

        int index;
        cin >> index;

        if (index > 0 && index <= menu.size()) {

            menu.erase(menu.begin() + (index - 1));

            cout << "Item removed!" << endl;

        } else {

            cout << "Invalid item number!" << endl;
        }
    }

    // Take Order
    void takeOrder() {

        viewMenu();

        cout << "Enter item number: ";

        int index;
        cin >> index;

        if (index < 1 || index > menu.size()) {

            cout << "Invalid item!" << endl;

            return;
        }

        cout << "Enter quantity: ";

        int qty;
        cin >> qty;

        cart.push_back(OrderItem(menu[index - 1], qty));

        cout << "Item added to cart!" << endl;
    }

    // Generate Bill
    void generateBill() {

        if (cart.empty()) {

            cout << "No items ordered!" << endl;

            return;
        }

        cout << "\n========== BILL RECEIPT ==========" << endl;

        double subtotal = 0;

        for (const auto &oi : cart) {

            cout << left
                 << setw(15) << oi.getName()
                 << " Qty: " << setw(3) << oi.getQuantity()
                 << " Price: " << setw(8) << fixed << setprecision(2)
                 << oi.getPrice()
                 << " Total: " << oi.getTotal()
                 << endl;

            subtotal += oi.getTotal();
        }

        double gstAmount = subtotal * GST;

        double grandTotal = subtotal + gstAmount;

        cout << "-----------------------------------" << endl;

        cout << "Subtotal: Rs "
             << fixed << setprecision(2)
             << subtotal << endl;

        cout << "GST (5%): Rs "
             << gstAmount << endl;

        cout << "Grand Total: Rs "
             << grandTotal << endl;

        cout << "===================================" << endl;

        // Clear cart after bill generation
        cart.clear();
    }

    // Main Menu
    void showMenu() {

        int choice;

        do {

            cout << "\n===== RESTAURANT BILLING SYSTEM =====" << endl;

            cout << "1. View Menu" << endl;
            cout << "2. Add Menu Item" << endl;
            cout << "3. Remove Menu Item" << endl;
            cout << "4. Take Order" << endl;
            cout << "5. Generate Bill" << endl;
            cout << "6. Exit" << endl;

            cout << "Enter choice: ";

            cin >> choice;

            switch (choice) {

                case 1:
                    viewMenu();
                    break;

                case 2:
                    addMenuItem();
                    break;

                case 3:
                    removeMenuItem();
                    break;

                case 4:
                    takeOrder();
                    break;

                case 5:
                    generateBill();
                    break;

                case 6:
                    cout << "Thank you!" << endl;
                    break;

                default:
                    cout << "Invalid choice!" << endl;
            }

        } while (choice != 6);
    }
};

// -----------------------------------------------------
// Main Function
// -----------------------------------------------------
int main() {

    RestaurantBillingSystem system;

    system.showMenu();

    return 0;
}