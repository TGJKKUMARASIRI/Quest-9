#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

using namespace std;

class User
{
public:
    char Password[128];
    char Username[128];

    // function to ask user to enter the username and password
    void GetUserInfo()
    {
        cout << "Enter Username: ";
        cin >> Username;

        cout << "Enter Password: ";
        char ch;
        int i = 0;
        while ((ch = _getch()) != '\r') // Read characters until Enter is pressed
        {
            if (ch == '\b') // Check for backspace character
            {
                if (i > 0)
                {
                    --i;
                    cout << "\b \b"; // Move the cursor back, overwrite the character with a space, and move the cursor back again
                }
            }
            else
            {
                Password[i++] = ch;
                _putch('*'); // Display asterisks instead of the actual characters
            }
        }
        Password[i] = '\0'; // Null-terminate the password string
        cout << endl;
    };
};

class SavingsAccounts
{
public:
    string AccountNumber;
    string CustomerName;
    string PhoneNumber;
    double amount;
    double AnualInterestRate;

    //function to money withdraw when the amount is given
    void Withdraw(int amount)
    {
        if (amount > this->amount)
        {
            cout << "Insufficient balance" << endl;
        }
        else
        {
            this->amount -= amount;
        }
    }

    void Deposit(int amount)
    {
        this->amount += amount;
    }
};

class CurrentAccounts
{
public:
    string AccountNumber;
    string CustomerName;
    string PhoneNumber;
    double amount;
    double AnualInterestRate;
    double OverdraftLimit;
    double OverdraftAmount;

    //function to money withdraw when the amount is given
    void Withdraw(int amount)
    {
        if (amount > this->amount)
        {
            if (amount > this->amount + this->OverdraftLimit)
            {
                cout << "Insufficient balance" << endl;
            }
            else
            {
                this->OverdraftAmount = amount - this->amount;
                this->amount = 0;
            }
        }
        else
        {
            this->amount -= amount;
        }
    }

    void Deposit(int amount)
    {
        if (this->OverdraftAmount > 0)
        {
            if (amount > this->OverdraftAmount)
            {
                this->amount += amount - this->OverdraftAmount;
                this->OverdraftAmount = 0;
            }
            else
            {
                this->OverdraftAmount -= amount;
            }
        }
        else
        {
            this->amount += amount;
        }
    }
};

class Customer : public User
{
public:
    Customer *NextCustomer;
    SavingsAccounts *HeadSavingsAccounts;
    CurrentAccounts *HeadCurrentAccounts;
    char Username[128];
    char name[128];
    char phone[128];

    // function to display the customer menu
    void DisplayCustomerMenu()
    {
        cout << "1. View Transactions" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. View the Personal Information" << endl;
    }

    //function to view the personal information
    void ViewPersonalInfo()
    {
        cout << "Name: " << name << endl;
        cout << "Phone number: " << phone << endl;
    }
};

class Employee : public User
{
public:
    Employee *NextEmployee;
    char Bufffer[128];

    // function to add a new customer to the customer linked list when the head is given
    void AddCustomer(Customer *HeadCustomer, int ID)
    {
        Customer *CurrentCustomer;
        CurrentCustomer = HeadCustomer;
        while (CurrentCustomer->NextCustomer != NULL)
        {
            CurrentCustomer = CurrentCustomer->NextCustomer;
        }
        CurrentCustomer->NextCustomer = new Customer;
        CurrentCustomer = CurrentCustomer->NextCustomer;
        sprintf(CurrentCustomer->Username, "customer%03d", ID + 1);
        CurrentCustomer->NextCustomer = NULL;
    }

    // function to display employee menu
    void DisplayEmployeeMenu()
    {
        cout << "1. Add a new customer" << endl;
        cout << "2. Create saving or current account" << endl;
        cout << "3. Close the customer\'s account" << endl;
        cout << "4. Deposit the money to an account" << endl;
        cout << "5. Withdraw the money from an account" << endl;
        cout << "6. view transactions of an account" << endl;
    }
};

class Admin : public User
{
public:
    // function to add a new employee to the employee linked list when the head is given
    void AddEmployee(Employee *HeadEmployee, int ID)
    {
        Employee *CurrentEmployee;
        CurrentEmployee = HeadEmployee;
        while (CurrentEmployee->NextEmployee != NULL)
        {
            CurrentEmployee = CurrentEmployee->NextEmployee;
        }
        CurrentEmployee->NextEmployee = new Employee;
        CurrentEmployee = CurrentEmployee->NextEmployee;
        sprintf(CurrentEmployee->Bufffer, "employee%03d", ID + 1);
        CurrentEmployee->NextEmployee = NULL;
    }
};

class App
{
public:
    User *user;
    Employee *HeadEmployee;
    Customer *HeadCustomer;
    Admin *admin;
    int ID;

    // function to get the customer information from the file while creating a customer linked list
    void GetCustomerInfo()
    {
        char Buffer[128];
        ifstream CustomerInfo("Customer.txt");
        Customer *CurrentCustomer;
        HeadCustomer = new Customer;
        CurrentCustomer = HeadCustomer;
        while (CustomerInfo.eof() == false)
        {
            CustomerInfo.getline(CurrentCustomer->Username, 128);
            CustomerInfo.getline(CurrentCustomer->name, 128);
            CustomerInfo.getline(CurrentCustomer->phone, 128);
            CurrentCustomer->NextCustomer = new Customer;
            CurrentCustomer = CurrentCustomer->NextCustomer;
        }
    }

    // function to display the customer information
    void DisplayCustomerInfo()
    {
        Customer *CurrentCustomer;
        CurrentCustomer = HeadCustomer;
        while (CurrentCustomer->NextCustomer != NULL)
        {
            cout << CurrentCustomer->Username << endl;
            cout << CurrentCustomer->name << endl;
            cout << CurrentCustomer->phone << endl;
            CurrentCustomer = CurrentCustomer->NextCustomer;
        }
    }

    // function to get the employee information from the file while creating a employee linked list
    void GetEmployeeInfo()
    {
        ifstream EmployeeInfo("Employee.txt");
        Employee *CurrentEmployee;
        HeadEmployee = new Employee;
        CurrentEmployee = HeadEmployee;
        while (EmployeeInfo.eof() == false)
        {
            EmployeeInfo.getline(CurrentEmployee->Bufffer, 128);
            CurrentEmployee->NextEmployee = new Employee;
            CurrentEmployee = CurrentEmployee->NextEmployee;
        }
    }

    // function to display the employee information
    void DisplayEmployeeInfo()
    {
        Employee *CurrentEmployee;
        CurrentEmployee = HeadEmployee;
        while (CurrentEmployee->NextEmployee != NULL)
        {
            cout << CurrentEmployee->Bufffer << endl;
            CurrentEmployee = CurrentEmployee->NextEmployee;
        }
    }

    int GettingTheID(string &Username)
    {
        string lastThreeChars = Username.substr(std::max(0, static_cast<int>(Username.length()) - 3));
        stringstream ss(lastThreeChars);
        int resultInteger;

        if (ss >> resultInteger)
        {
            return resultInteger;
        }

        return -1;
    }

    void UserAuthontication()
    {
        char choice;
        string username(user->Username);
        if (username == "administrator")
        {
        }
        else if (username.compare(0, 8, "employee") == 0)
        {
            ID = GettingTheID(username);
            GoToEmployee();
        }
        else if (username.compare(0, 8, "customer") == 0)
        {
            ID = GettingTheID(username);
            // cout << ID << endl; //comment
            GoToCustomer();
        }
        else
        {
            cout << "Access denied" << endl;
        }
    }

    // function to going to a specific customer
    void GoToCustomer()
    {
        Customer *CurrentCustomer;
        CurrentCustomer = HeadCustomer;
        while (CurrentCustomer->NextCustomer != NULL)
        {
            string Id(CurrentCustomer->Username);
            if (ID == GettingTheID(Id))
            {
                cout << "Welcome!" << endl;
                CurrentCustomer->DisplayCustomerMenu();
                char choice;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case '1':
                {
                    cout << "View Transactions" << endl;
                    break;
                }
                case '2':
                {
                    cout << "Deposit" << endl;
                    break;
                }
                case '3':
                {
                    cout << "Withdraw" << endl;
                    break;
                }
                case '4':
                {
                    CurrentCustomer->ViewPersonalInfo();
                    break;
                }
                default:
                {
                    cout << "Invalid Input" << endl;
                    break;
                }
                }
                break;
            }
            CurrentCustomer = CurrentCustomer->NextCustomer;
            if (CurrentCustomer->NextCustomer == NULL)
            {
                cout << "Access denied" << endl;
            }
        }
    }

    // function to going to a specific employee
    void GoToEmployee()
    {
        Employee *CurrentEmployee;
        CurrentEmployee = HeadEmployee;
        while (CurrentEmployee->NextEmployee != NULL)
        {
            string Id(CurrentEmployee->Bufffer);
            if (ID == GettingTheID(Id))
            {
                cout << "Welcome!" << endl;
                CurrentEmployee->DisplayEmployeeMenu();
                char choice;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case '1':
                {
                    cout << "Add a new customer" << endl;
                    break;
                }
                case '2':
                {
                    cout << "Create saving or current account" << endl;
                    break;
                }
                case '3':
                {
                    cout << "Close the customer\'s account" << endl;
                    break;
                }
                case '4':
                {
                    cout << "Deposit the money to an account" << endl;
                    break;
                }
                case '5':
                {
                    cout << "Withdraw the money from an account" << endl;
                    break;
                }
                case '6':
                {
                    cout << "view transactions of an account" << endl;
                    break;
                }
                default:
                {
                    cout << "Invalid Input" << endl;
                    break;
                }
                }
                break;
            }
            CurrentEmployee = CurrentEmployee->NextEmployee;
            if (CurrentEmployee->NextEmployee == NULL)
            {
                cout << "Access denied" << endl;
            }
        }
    }

    // function to check the passward
    void CheckPassword()
    {
        string password(user->Password);
        if (password == "Password@1234") // Compare the strings
        {
            UserAuthontication();
        }
        else
        {
            cout << "Access denied" << endl;
        }
    }
};
