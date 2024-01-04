#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <algorithm> // Added for transform function

using namespace std;

class User
{
public:
    char Password[128];
    char Username[128];

    void GetUserInfo()
    {
        cout << "Enter Username: ";
        cin >> Username;

        cout << "Enter Password: ";
        char ch;
        int i = 0;
        while ((ch = _getch()) != '\r')
        {
            if (ch == '\b')
            {
                if (i > 0)
                {
                    --i;
                    cout << "\b \b";
                }
            }
            else
            {
                Password[i++] = ch;
                _putch('*');
            }
        }
        Password[i] = '\0';
        cout << endl;
    }
};

class Customer : public User
{
public:
    // ... (Your existing code for Customer class)

    void DisplayTransactionInformation()
    {
        // ... (Your existing code for DisplayTransactionInformation function)
    }
};

class Employee : public User
{
public:
    // ... (Your existing code for Employee class)

    void DisplayEmployeeMenu()
    {
        // ... (Your existing code for DisplayEmployeeMenu function)
    }
};

class App
{
public:
    User *user;
    Employee *HeadEmployee;
    Customer *HeadCustomer;
    int ID;

    void UserAuthentication()
    {
        char choice;
        string username(user->Username);
        if (username == "administrator")
        {
            // Handle administrator actions
            cout << "Administrator actions" << endl;
        }
        else if (username.compare(0, 8, "employee") == 0)
        {
            ID = GettingTheID(username);
            GoToEmployee();
        }
        else if (username.compare(0, 8, "customer") == 0)
        {
            ID = GettingTheID(username);
            GoToCustomer();
        }
        else
        {
            cout << "Access denied" << endl;
        }
    }

    void GoToCustomer()
    {
        Customer *CurrentCustomer;
        CurrentCustomer = HeadCustomer;
        while (CurrentCustomer->NextCustomer != NULL)
        {
            int customerId = GettingTheID(CurrentCustomer->Username);
            if (ID == customerId)
            {
                cout << "Welcome!" << endl;
                char choice;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case '1':
                    cout << "View Transactions" << endl;
                    CurrentCustomer->DisplayTransactionInformation();
                    break;
                case '2':
                    cout << "Deposit" << endl;
                    break;
                case '3':
                    cout << "Withdraw" << endl;
                    break;
                case '4':
                    CurrentCustomer->ViewPersonalInfo();
                    break;
                default:
                    cout << "Invalid Input" << endl;
                    break;
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

    void GoToEmployee()
    {
        Employee *CurrentEmployee;
        CurrentEmployee = HeadEmployee;
        while (CurrentEmployee->NextEmployee != NULL)
        {
            int employeeId = GettingTheID(CurrentEmployee->Username);
            if (ID == employeeId)
            {
                cout << "Welcome!" << endl;
                CurrentEmployee->DisplayEmployeeMenu();
                char choice;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case '1':
                    cout << "Add a new customer" << endl;
                    break;
                case '2':
                    cout << "Create saving or current account" << endl;
                    break;
                case '3':
                    cout << "Close the customer\'s account" << endl;
                    break;
                case '4':
                    cout << "Deposit the money to an account" << endl;
                    break;
                case '5':
                    cout << "Withdraw the money from an account" << endl;
                    break;
                case '6':
                    cout << "View transactions of an account" << endl;
                    break;
                default:
                    cout << "Invalid Input" << endl;
                    break;
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

    void CheckPassword()
    {
        string enteredPassword(user->Password);
        string storedPassword = "Password@1234";

        // Convert both passwords to lowercase for case-insensitive comparison
        transform(enteredPassword.begin(), enteredPassword.end(), enteredPassword.begin(), ::tolower);
        transform(storedPassword.begin(), storedPassword.end(), storedPassword.begin(), ::tolower);

        if (enteredPassword == storedPassword)
        {
            UserAuthentication();
        }
        else
        {
            cout << "Access denied" << endl;
        }
    }
};

int main()
{
    App myApp;
    myApp.CheckPassword();

    return 0;
}

