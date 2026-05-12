#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// ----------------------------------------------------
// Student Class
// ----------------------------------------------------
class Student {
private:
    int id;
    string name;
    int age;
    string course;

public:

    // Constructor
    Student(int id, string name, int age, string course) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->course = course;
    }

    // Getters
    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    string getCourse() const {
        return course;
    }

    // Setters
    void setName(string name) {
        this->name = name;
    }

    void setAge(int age) {
        this->age = age;
    }

    void setCourse(string course) {
        this->course = course;
    }

    // Display Student
    void display() const {

        cout << "ID: " << id
             << ", Name: " << name
             << ", Age: " << age
             << ", Course: " << course
             << endl;
    }
};

// ----------------------------------------------------
// Student Management System Class
// ----------------------------------------------------
class StudentManagementSystem {
private:

    vector<Student> students;

public:

    // Add Student
    void addStudent() {

        int id, age;
        string name, course;

        cout << "Enter ID: ";
        cin >> id;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Course: ";
        getline(cin, course);

        students.push_back(Student(id, name, age, course));

        cout << "Student added successfully!" << endl;
    }

    // View All Students
    void viewStudents() {

        if (students.empty()) {

            cout << "No students found!" << endl;

            return;
        }

        cout << "\n=== Student List ===" << endl;

        for (const auto &s : students) {
            s.display();
        }
    }

    // Search Student
    void searchStudent() {

        int id;

        cout << "Enter Student ID: ";
        cin >> id;

        for (const auto &s : students) {

            if (s.getId() == id) {

                cout << "Student Found:" << endl;

                s.display();

                return;
            }
        }

        cout << "Student not found!" << endl;
    }

    // Update Student
    void updateStudent() {

        int id;

        cout << "Enter Student ID to Update: ";
        cin >> id;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (auto &s : students) {

            if (s.getId() == id) {

                string name, course;
                int age;

                cout << "Enter new Name: ";
                getline(cin, name);

                cout << "Enter new Age: ";
                cin >> age;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter new Course: ";
                getline(cin, course);

                s.setName(name);
                s.setAge(age);
                s.setCourse(course);

                cout << "Student updated successfully!" << endl;

                return;
            }
        }

        cout << "Student not found!" << endl;
    }

    // Delete Student
    void deleteStudent() {

        int id;

        cout << "Enter Student ID to Delete: ";
        cin >> id;

        for (auto it = students.begin(); it != students.end(); ++it) {

            if (it->getId() == id) {

                students.erase(it);

                cout << "Student removed successfully!" << endl;

                return;
            }
        }

        cout << "Student not found!" << endl;
    }

    // Menu System
    void showMenu() {

        int choice;

        while (true) {

            cout << "\n===== Student Management System =====" << endl;

            cout << "1. Add Student" << endl;
            cout << "2. View All Students" << endl;
            cout << "3. Search Student by ID" << endl;
            cout << "4. Update Student" << endl;
            cout << "5. Delete Student" << endl;
            cout << "6. Exit" << endl;

            cout << "Enter your choice: ";

            cin >> choice;

            switch (choice) {

                case 1:
                    addStudent();
                    break;

                case 2:
                    viewStudents();
                    break;

                case 3:
                    searchStudent();
                    break;

                case 4:
                    updateStudent();
                    break;

                case 5:
                    deleteStudent();
                    break;

                case 6:
                    cout << "Exiting... Thank you!" << endl;
                    return;

                default:
                    cout << "Invalid choice! Try again." << endl;
            }
        }
    }
};

// ----------------------------------------------------
// Main Function
// ----------------------------------------------------
int main() {

    StudentManagementSystem sms;

    sms.showMenu();

    return 0;
}