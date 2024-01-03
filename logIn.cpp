#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class User {
public:
    std::string username;
    std::string password;

    User(const std::string& username, const std::string& password)
        : username(username), password(password) {}

    virtual ~User() = default;  // Add a virtual destructor
    virtual void dummyFunction() {}  // Add a virtual function

    // Add other common functionalities if needed
};

class Customer : public User {
public:
    Customer(const std::string& username, const std::string& password)
        : User(username, password) {}

    // Add customer-specific functionalities
    void viewTransactions() {
        std::cout << "Viewing transactions...\n";
    }
};

class Employee : public User {
public:
    Employee(const std::string& username, const std::string& password)
        : User(username, password) {}

    // Add employee-specific functionalities
    void addCustomer() {
        std::cout << "Adding a new customer...\n";
    }
};

class Administrator : public User {
public:
    Administrator(const std::string& username, const std::string& password)
        : User(username, password) {}

    // Add administrator-specific functionalities
    void increaseDate() {
        std::cout << "Increasing the date...\n";
    }
};

// Function to read user details from a file
void readUserDetailsFromFile(const std::string& fileName, std::unordered_map<std::string, User*>& users) {
    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string username, password;
        while (file >> username >> password) {
            // Extract user type from the username
            size_t userTypeLength = username.find_first_of("0123456789");
            if (userTypeLength != std::string::npos) {
                std::string userType = username.substr(0, userTypeLength);
                if (userType == "customer") {
                    users[username] = new Customer(username, password);
                } else if (userType == "employee") {
                    users[username] = new Employee(username, password);
                } else if (userType == "admin") {
                    users[username] = new Administrator(username, password);
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Error opening file: " << fileName << std::endl;
    }
}

int main() {
    std::unordered_map<std::string, User*> users;

    // Read user details from files
    readUserDetailsFromFile("customers.txt", users);
    readUserDetailsFromFile("employees.txt", users);
    readUserDetailsFromFile("admins.txt", users);

    // User login
    std::string enteredUsername, enteredPassword;
    std::cout << "Enter username: ";
    std::cin >> enteredUsername;
    std::cout << "Enter password: ";
    std::cin >> enteredPassword;

    // Authenticate user
    auto it = users.find(enteredUsername);
    if (it != users.end() && it->second->password == enteredPassword) {
        std::cout << "Login successful. Welcome, " << enteredUsername << "!\n";

        // Determine user type and perform actions
        if (dynamic_cast<Customer*>(it->second)) {
            // Customer
            Customer* customer = dynamic_cast<Customer*>(it->second);
            customer->viewTransactions();
            // Add other customer-specific actions
        } else if (dynamic_cast<Employee*>(it->second)) {
            // Employee
            Employee* employee = dynamic_cast<Employee*>(it->second);
            employee->addCustomer();
            // Add other employee-specific actions
        } else if (dynamic_cast<Administrator*>(it->second)) {
            // Administrator
            Administrator* admin = dynamic_cast<Administrator*>(it->second);
            admin->increaseDate();
            // Add other administrator-specific actions
        } else {
            std::cout << "Unknown user type.\n";
        }

    } else {
        std::cout << "Login failed. Invalid username or password.\n";
    }

    // Clean up memory
    for (auto& pair : users) {
        delete pair.second;
    }

    return 0;
}
