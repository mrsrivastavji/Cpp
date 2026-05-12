#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

// Database credentials
const string HOST = "tcp://127.0.0.1:3306";
const string USER = "root";
const string PASS = "your_password";
const string DB   = "bankdb";

// Connect to DB
sql::Connection* connectDB() {
    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
    sql::Connection* con = driver->connect(HOST, USER, PASS);
    con->setSchema(DB);
    return con;
}

// Get account
bool verifyAccount(string accNo, int &pin, double &balance) {
    try {
        sql::Connection* con = connectDB();

        sql::PreparedStatement* ps =
            con->prepareStatement("SELECT * FROM accounts WHERE accountNumber=?");

        ps->setString(1, accNo);

        sql::ResultSet* rs = ps->executeQuery();

        if (rs->next()) {
            int dbPin = rs->getInt("pin");

            cout << "Enter PIN: ";
            cin >> pin;

            if (pin != dbPin) {
                cout << "Incorrect PIN!" << endl;
                return false;
            }

            balance = rs->getDouble("balance");

            delete rs;
            delete ps;
            delete con;

            return true;
        } else {
            cout << "Account not found!" << endl;
        }

    } catch (exception &e) {
        cout << "DB Error: " << e.what() << endl;
    }

    return false;
}

// Create account
void createAccount() {
    string accNo, name;
    double amount;
    int pin;

    cout << "Enter Account Number: ";
    cin >> accNo;

    cout << "Enter Holder Name: ";
    cin >> name;

    cout << "Enter Initial Deposit: ";
    cin >> amount;

    cout << "Set 4-digit PIN: ";
    cin >> pin;

    try {
        sql::Connection* con = connectDB();

        sql::PreparedStatement* ps =
            con->prepareStatement("INSERT INTO accounts VALUES (?,?,?,?)");

        ps->setString(1, accNo);
        ps->setString(2, name);
        ps->setDouble(3, amount);
        ps->setInt(4, pin);

        ps->executeUpdate();

        cout << "Account created successfully!" << endl;

        delete ps;
        delete con;

    } catch (exception &e) {
        cout << "DB Error: " << e.what() << endl;
    }
}

// Deposit
void depositMoney() {
    string accNo;
    int pin;
    double balance;

    cout << "Enter Account Number: ";
    cin >> accNo;

    if (!verifyAccount(accNo, pin, balance)) return;

    double amt;
    cout << "Enter amount to deposit: ";
    cin >> amt;

    if (amt <= 0) {
        cout << "Invalid amount!" << endl;
        return;
    }

    double newBal = balance + amt;

    try {
        sql::Connection* con = connectDB();

        sql::PreparedStatement* ps =
            con->prepareStatement("UPDATE accounts SET balance=? WHERE accountNumber=?");

        ps->setDouble(1, newBal);
        ps->setString(2, accNo);

        ps->executeUpdate();

        cout << "₹" << amt << " deposited successfully." << endl;

        delete ps;
        delete con;

    } catch (exception &e) {
        cout << "DB Error: " << e.what() << endl;
    }
}

// Withdraw
void withdrawMoney() {
    string accNo;
    int pin;
    double balance;

    cout << "Enter Account Number: ";
    cin >> accNo;

    if (!verifyAccount(accNo, pin, balance)) return;

    double amt;
    cout << "Enter amount to withdraw: ";
    cin >> amt;

    if (amt <= 0 || amt > balance) {
        cout << "Invalid or insufficient balance!" << endl;
        return;
    }

    double newBal = balance - amt;

    try {
        sql::Connection* con = connectDB();

        sql::PreparedStatement* ps =
            con->prepareStatement("UPDATE accounts SET balance=? WHERE accountNumber=?");

        ps->setDouble(1, newBal);
        ps->setString(2, accNo);

        ps->executeUpdate();

        cout << "₹" << amt << " withdrawn successfully." << endl;

        delete ps;
        delete con;

    } catch (exception &e) {
        cout << "DB Error: " << e.what() << endl;
    }
}

// View balance
void viewBalance() {
    string accNo;
    int pin;
    double balance;

    cout << "Enter Account Number: ";
    cin >> accNo;

    if (!verifyAccount(accNo, pin, balance)) return;

    cout << "Current balance: ₹" << balance << endl;
}

// Main
int main() {

    while (true) {
        cout << "\n==== BANK SYSTEM ====" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. View Balance" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: viewBalance(); break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}