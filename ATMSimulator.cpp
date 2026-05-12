#include <iostream>
using namespace std;

class Account {
private:
    double balance;
    int pin;

public:
    // Constructor
    Account(double balance, int pin) {
        this->balance = balance;
        this->pin = pin;
    }

    // Verify PIN
    bool verifyPin(int enteredPin) {
        return this->pin == enteredPin;
    }

    // Get Balance
    double getBalance() {
        return balance;
    }

    // Deposit Money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    // Withdraw Money
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

class ATM {
private:
    Account& account;
    bool sessionActive;

public:
    // Constructor
    ATM(Account& account) : account(account) {
        sessionActive = false;
    }

    // Start ATM Session
    void startSession() {

        int enteredPin;

        cout << "Enter PIN: ";
        cin >> enteredPin;

        if (account.verifyPin(enteredPin)) {
            cout << "Login successful!" << endl;
            sessionActive = true;
            showMenu();
        } else {
            cout << "Incorrect PIN. Session terminated." << endl;
        }
    }

    // ATM Menu
    void showMenu() {

        while (sessionActive) {

            cout << "\n--- ATM MENU ---" << endl;
            cout << "1. Check Balance" << endl;
            cout << "2. Deposit Money" << endl;
            cout << "3. Withdraw Money" << endl;
            cout << "4. Exit" << endl;

            int choice;

            cout << "Choose an option: ";
            cin >> choice;

            switch (choice) {

            case 1:
                cout << "Your balance: ₹" << account.getBalance() << endl;
                break;

            case 2: {
                double depAmt;

                cout << "Enter deposit amount: ";
                cin >> depAmt;

                account.deposit(depAmt);

                cout << "Amount deposited successfully." << endl;
                break;
            }

            case 3: {
                double wAmt;

                cout << "Enter withdrawal amount: ";
                cin >> wAmt;

                if (account.withdraw(wAmt)) {
                    cout << "Withdrawal successful." << endl;
                } else {
                    cout << "Insufficient balance." << endl;
                }

                break;
            }

            case 4:
                cout << "Exiting session..." << endl;
                sessionActive = false;
                break;

            default:
                cout << "Invalid choice." << endl;
            }
        }
    }
};

int main() {

    // Create Account
    Account userAccount(5000.0, 1234);

    // Create ATM
    ATM atm(userAccount);

    // Start ATM Session
    atm.startSession();

    return 0;
}