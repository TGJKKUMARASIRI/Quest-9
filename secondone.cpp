//21_ENG_008-A.M.N.K.Gayasan
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

using namespace std;

class User {
public:
    char Password[128];
    char Username[128];

    void GetUserInfo();
};
void User::GetUserInfo() {
    std::cout << "Enter Username: ";
    std::cin >> Username;

    std::cout << "Enter Password: ";
    char ch;
    int i = 0;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (i > 0) {
                --i;
                std::cout << "\b \b";
            }
        } else {
            Password[i++] = ch;
            _putch('*');
        }
    }
    Password[i] = '\0';
    std::cout << std::endl;
}

class SavingsAccounts {
public:
    string AccountNumber;
    string CustomerName;
    string PhoneNumber;
    double amount;
    double AnnualInterestRate;

    void Withdraw(int amount);
    void Deposit(int amount);
};

class CurrentAccounts {
public:
    string AccountNumber;
    string CustomerName;
    string PhoneNumber;
    double amount;
    double AnnualInterestRate;
    double OverdraftLimit;
    double OverdraftAmount;

    void Withdraw(int amount);
    void Deposit(int amount);
};

class Customer : public User {
public:
    Customer* NextCustomer;
    char Username[128];
    char name[128];
    char phone[128];
    SavingsAccounts* savingsAccount;
    CurrentAccounts* currentAccount;

    
    
    void DisplayCustomerMenu() {
        cout << "Customer Menu:" << endl;
        cout << "1. View Personal Information" << endl;
        cout << "2. Display Transaction Information" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Transfer Funds" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                ViewPersonalInfo();
                break;
            case 2:
                DisplayTransactionInformation();
                break;
            case 3:
                DepositMoney();
                break;
            case 4:
                WithdrawMoney();
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
  

    }

    void ViewPersonalInfo() {
        ifstream personalInfoFile("PersonalInfo.txt");
        if (personalInfoFile.is_open()) {
            string line;
            while (getline(personalInfoFile, line)) {
                cout << line << endl;
            }
            personalInfoFile.close();
        } else {
            cerr << "Unable to open file" << endl;
        }
    }
    
    void DisplayTransactionInformation() {
        ifstream transactionFile("TransactionInfo.txt");
        if (transactionFile.is_open()) {
            string line;
            cout << "Transaction Information:" << endl;
            cout << "Recent Transactions:" << endl;
            int count = 1;
            while (getline(transactionFile, line)) {
                cout << count << ". " << line << endl;
                count++;
            }
            transactionFile.close();
        } else {
            cerr << "Unable to open file" << endl;
        }
    }
      void DepositMoney() {
    double amount;
    cout << "Enter the amount to deposit: ";
    cin >> amount;
    cout << "Successfully deposited $" << amount << endl;
}

void WithdrawMoney() {
    double amount;
    cout << "Enter the amount to withdraw: ";
    cin >> amount;
    cout << "Successfully withdrew $" << amount << endl;
}

};

class Employee : public User {
public:
    Employee* NextEmployee;
    char Bufffer[128];

    void AddCustomer(Customer* HeadCustomer, int ID);
    void DisplayEmployeeMenu();
};

void Employee::DisplayEmployeeMenu() {
    cout << "Employee Menu:" << endl;
    cout << "1. Add a new customer" << endl;
    cout << "2. Create saving or current account" << endl;
    cout << "3. Close the customer's account" << endl;
    cout << "4. Deposit money to an account" << endl;
    cout << "5. Withdraw money from an account" << endl;
    cout << "6. View transactions of an account" << endl;

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
        	cout<<"enough"<<endl;
           // AddCustomer(HeadCustomer, ID);
            break;
        // Inside the switch statement of Employee::DisplayEmployeeMenu()
case 2: {
    string accountType;
    cout << "Create a new account (Savings/Current): ";
    cin >> accountType;

    if (accountType == "Savings") {
        
        SavingsAccounts* newSavingsAccount = new SavingsAccounts;
       
    } else if (accountType == "Current") {
        
        CurrentAccounts* newCurrentAccount = new CurrentAccounts;
        
    } else {
        cout << "Invalid account type" << endl;
    }
    break;
}

       
case 3: {
    string accountNumber;
    cout << "Enter the account number to close: ";
    cin >> accountNumber;

    
    break;
}

        
case 4: {
    string accountNumber;
    double amount;
    cout << "Enter the account number to deposit money into: ";
    cin >> accountNumber;

    cout << "Enter the amount to deposit: ";
    cin >> amount;

    
    break;
}

        // Inside the switch statement of Employee::DisplayEmployeeMenu()
case 5: {
    string accountNumber;
    double amount;
    cout << "Enter the account number to withdraw money from: ";
    cin >> accountNumber;

    cout << "Enter the amount to withdraw: ";
    cin >> amount;

    
    break;
}

       
case 6: {
    string accountNumber;
    cout << "Enter the account number to view transactions: ";
    cin >> accountNumber;

    
    break;
}

        default:
            cout << "Invalid choice" << endl;
            break;
    }
}


class Admin : public User {
public:
    void AddEmployee(Employee* HeadEmployee, int ID);
};

class App {
public:
    User* user;
    Employee* HeadEmployee;
    Customer* HeadCustomer;
    Admin* admin;
    int ID;

    void GetCustomerInfo();
    void DisplayCustomerInfo();
    void GetEmployeeInfo();
    void DisplayEmployeeInfo();
    int GettingTheID(string& Username);
    void UserAuthontication();
    void GoToCustomer();
    void GoToEmployee();
    void CheckPassword();
//     App() {
//        HeadCustomer = nullptr; 
//    }
};
void App::GetCustomerInfo() {
    std::ifstream CustomerInfo("Customer.txt");
    if (!CustomerInfo) {
        cerr << "Unable to open Customer.txt" << endl;
        return;
    }

    HeadCustomer = NULL; // Initialize the HeadCustomer pointer to NULL
    Customer* CurrentCustomer = NULL; // Initialize the CurrentCustomer pointer to NULL

    while (!CustomerInfo.eof()) {
        Customer* newCustomer = new Customer;
        CustomerInfo.getline(newCustomer->Username, 128);
        CustomerInfo.getline(newCustomer->name, 128);
        CustomerInfo.getline(newCustomer->phone, 128);
        newCustomer->NextCustomer = NULL; // Ensure the NextCustomer pointer is NULL

        if (HeadCustomer == NULL) {
            HeadCustomer = newCustomer;
            CurrentCustomer = newCustomer;
        } else {
            CurrentCustomer->NextCustomer = newCustomer;
            CurrentCustomer = CurrentCustomer->NextCustomer;
        }
    }
    CustomerInfo.close();
}



void App::DisplayCustomerInfo() {
    Customer *CurrentCustomer = HeadCustomer;
    while (CurrentCustomer->NextCustomer != NULL) {
        cout << CurrentCustomer->Username << endl;
        cout << CurrentCustomer->name << endl;
        cout << CurrentCustomer->phone << endl;
        CurrentCustomer = CurrentCustomer->NextCustomer;
    }
}

void App::GetEmployeeInfo() {
    ifstream EmployeeInfo("Employee.txt");
    Employee *CurrentEmployee = HeadEmployee;
    while (!EmployeeInfo.eof()) {
        EmployeeInfo.getline(CurrentEmployee->Bufffer, 128);
        CurrentEmployee->NextEmployee = new Employee;
        CurrentEmployee = CurrentEmployee->NextEmployee;
    }
    EmployeeInfo.close();
}

void App::DisplayEmployeeInfo() {
    Employee *CurrentEmployee = HeadEmployee;
    while (CurrentEmployee->NextEmployee != NULL) {
        cout << CurrentEmployee->Bufffer << endl;
        CurrentEmployee = CurrentEmployee->NextEmployee;
    }
}

int App::GettingTheID(string &Username) {
    string lastThreeChars = Username.substr(std::max(0, static_cast<int>(Username.length()) - 3));
    stringstream ss(lastThreeChars);
    int resultInteger;

    if (ss >> resultInteger) {
        return resultInteger;
    }

    return -1;
}

void App::UserAuthontication() {
    string password(user->Password);
    if (password == "Password@1234") {
        // Authentication logic
    } else {
        cout << "Access denied" << endl;
    }
}

void App::GoToCustomer() {
    Customer *CurrentCustomer = HeadCustomer;
    int targetID; // ID of the customer to navigate to
    cout << "Enter the customer ID: ";
    cin >> targetID;

    while (CurrentCustomer->NextCustomer != NULL) {
        string Id(CurrentCustomer->Username);
        if (targetID == GettingTheID(Id)) {
            cout << "Welcome!" << endl;
            char choice;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case '1': {
                    cout << "View Transactions" << endl;
                    CurrentCustomer->DisplayTransactionInformation();
                    break;
                }
                case '2': {
                    cout << "Deposit" << endl;
                    break;
                }
                case '3': {
                    cout << "Withdraw" << endl;
                    break;
                }
                case '4': {
                    CurrentCustomer->ViewPersonalInfo();
                    break;
                }
                default: {
                    cout << "Invalid Input" << endl;
                    break;
                }
            }
            break;
        }
        CurrentCustomer = CurrentCustomer->NextCustomer;

        if (CurrentCustomer->NextCustomer == NULL) {
            cout << "Access denied" << endl; // Customer not found
        }
    }
}


void App::GoToEmployee() {
    Employee *CurrentEmployee = HeadEmployee;
    int targetID; // ID of the employee to navigate to
    cout << "Enter the employee ID: ";
    cin >> targetID;

    while (CurrentEmployee->NextEmployee != NULL) {
        string Id(CurrentEmployee->Bufffer);
        if (targetID == GettingTheID(Id)) {
            cout << "Welcome!" << endl;
            CurrentEmployee->DisplayEmployeeMenu();
            char choice;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case '1': {
                    cout << "Add a new customer" << endl;
                    break;
                }
                case '2': {
                    cout << "Create saving or current account" << endl;
                    break;
                }
                case '3': {
                    cout << "Close the customer\'s account" << endl;
                    break;
                }
                case '4': {
                    cout << "Deposit the money to an account" << endl;
                    break;
                }
                case '5': {
                    cout << "Withdraw the money from an account" << endl;
                    break;
                }
                case '6': {
                    cout << "view transactions of an account" << endl;
                    break;
                }
                default: {
                    cout << "Invalid Input" << endl;
                    break;
                }
            }
            break;
        }
        CurrentEmployee = CurrentEmployee->NextEmployee;

        if (CurrentEmployee->NextEmployee == NULL) {
            cout << "Access denied" << endl; // Employee not found
        }
    }
}

void App::CheckPassword() {
    string password(user->Password);
    if (password == "Password@1234") {
        UserAuthontication();
    } else {
        cout << "Access denied" << endl;
    }
}


int main() {
    App* app = new App;

    // Fetching customer and employee information from files
    app->GetCustomerInfo();
    app->GetEmployeeInfo();

    // Getting user information
    app->user = new User;
    app->user->GetUserInfo();

    // Authenticating user
    app->CheckPassword();

    // Deleting dynamically allocated memory
    delete app->user;
    delete app;
    
    return 0;
}


