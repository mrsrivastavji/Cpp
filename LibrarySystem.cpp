#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// ---------------------------------------------------
// Book Class
// ---------------------------------------------------
class Book {
private:
    string id;
    string title;
    string author;

public:
    // Constructor
    Book(string id, string title, string author) {
        this->id = id;
        this->title = title;
        this->author = author;
    }

    // Getters
    string getId() const {
        return id;
    }

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    // Display Book
    void display() const {
        cout << "ID: " << id
             << " | Title: " << title
             << " | Author: " << author
             << endl;
    }
};

// ---------------------------------------------------
// Library Management System
// ---------------------------------------------------
class LibrarySystem {
private:
    vector<Book> books;

    // Convert string to lowercase
    string toLower(string str) {

        transform(str.begin(), str.end(), str.begin(), ::tolower);

        return str;
    }

public:

    // Add Book
    void addBook() {

        string id, title, author;

        cout << "Enter Book ID: ";
        getline(cin, id);

        // Check duplicate ID
        for (const auto &b : books) {
            if (toLower(b.getId()) == toLower(id)) {
                cout << "Book ID already exists!" << endl;
                return;
            }
        }

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Book Author: ";
        getline(cin, author);

        // Validation
        if (id.empty() || title.empty() || author.empty()) {
            cout << "Fields cannot be empty!" << endl;
            return;
        }

        books.push_back(Book(id, title, author));

        cout << "Book added successfully!" << endl;
    }

    // Remove Book
    void removeBook() {

        string id;

        cout << "Enter Book ID to remove: ";
        getline(cin, id);

        for (auto it = books.begin(); it != books.end(); ++it) {

            if (toLower(it->getId()) == toLower(id)) {

                books.erase(it);

                cout << "Book removed successfully!" << endl;

                return;
            }
        }

        cout << "Book not found!" << endl;
    }

    // Search Book
    void searchBook() {

        string keyword;

        cout << "Enter keyword (ID/Title/Author): ";
        getline(cin, keyword);

        keyword = toLower(keyword);

        bool found = false;

        for (const auto &b : books) {

            if (toLower(b.getId()).find(keyword) != string::npos ||
                toLower(b.getTitle()).find(keyword) != string::npos ||
                toLower(b.getAuthor()).find(keyword) != string::npos) {

                b.display();

                found = true;
            }
        }

        if (!found) {
            cout << "No matching book found!" << endl;
        }
    }

    // View All Books
    void viewBooks() {

        if (books.empty()) {
            cout << "No books in the library!" << endl;
            return;
        }

        cout << "\n---- Book List ----" << endl;

        for (const auto &b : books) {
            b.display();
        }
    }

    // Menu System
    void showMenu() {

        int choice;

        while (true) {

            cout << "\n===== Library Management System =====" << endl;

            cout << "1. Add Book" << endl;
            cout << "2. Remove Book" << endl;
            cout << "3. Search Book" << endl;
            cout << "4. View All Books" << endl;
            cout << "5. Exit" << endl;

            cout << "Enter your choice: ";

            // Input Validation
            while (!(cin >> choice)) {

                cout << "Invalid input! Please enter a number: ";

                cin.clear();

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {

                case 1:
                    addBook();
                    break;

                case 2:
                    removeBook();
                    break;

                case 3:
                    searchBook();
                    break;

                case 4:
                    viewBooks();
                    break;

                case 5:
                    cout << "Exiting the system... Goodbye!" << endl;
                    return;

                default:
                    cout << "Invalid choice! Try again." << endl;
            }
        }
    }
};

// ---------------------------------------------------
// Main Function
// ---------------------------------------------------
int main() {

    LibrarySystem library;

    library.showMenu();

    return 0;
}