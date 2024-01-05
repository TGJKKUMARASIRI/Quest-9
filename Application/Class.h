// T.G.J.K. Kumarasiri 21/ENG/147

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

    // function to money withdraw when the amount is given
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

    // function to money withdraw when the amount is given
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
    char Username[128];
    char name[128];
    char phone[128];
    SavingsAccounts *savingsAccount;
    CurrentAccounts *currentAccount;

    // function to display the customer menu
    void DisplayCustomerMenu()
    {
        cout << "1. View Transactions" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. View the Personal Information" << endl;
        cout << "5. exit" << endl;
    }

    // function to view the personal information
    void ViewPersonalInfo()
    {
        cout << "Name: " << name << endl;
        cout << "Phone number: " << phone << endl;
    }

    // function to get the account information from a file that has the username as it's name
    // void GetAccountInfo()
    // {
    //     cout << "In the function" << endl; //comment
    //     string username(Username);
    //     username += ".txt";
    //     cout << "Name: " << username << endl; //comment
    //     ifstream AccountInfo(username);
    //     cout << "Hi" << endl; //comment
    //     if (!AccountInfo.is_open())
    //     {
    //         cerr << "Error opening file" << endl;
    //         return;
    //     }
    //     cout << "Opened the file" << endl; //comment
    //     char Buffer[128];
    //     AccountInfo.getline(Buffer, 128);
    //     cout << Buffer << endl; //comment
    //     string AccType = Buffer;
    //     if (stoi(AccType) == 0)
    //     {
    //         savingsAccount = new SavingsAccounts;
    //         AccountInfo.getline(Buffer, 128);
    //         cout << Buffer << endl; //comment
    //         savingsAccount->AnualInterestRate = stod(Buffer);
    //         // should reed the last line of the file to get the ammount
    //         while (AccountInfo.eof() == false)
    //         {
    //             AccountInfo.getline(Buffer, 128);
    //             cout << Buffer << endl; //comment
    //         }
    //         string Amount = Buffer;
    //         savingsAccount->amount = stod(Amount);
    //     }
    //     else
    //     {
    //     }
    //     AccountInfo.close();
    // }

    // function to display the user account information
    void DisplayTransactionInformation()
    {
        string username(Username);
        username += ".txt";
        ifstream AccountInfo(username);
        char Buffer[128];
        AccountInfo.getline(Buffer, 128);
        AccountInfo.getline(Buffer, 128);
        while (AccountInfo.eof() == false)
        {
            AccountInfo.getline(Buffer, 128);
            cout << Buffer << endl;
        }
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
        cout << "7. exit" << endl;
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

    // function to display admin menu
    void DisplayAdminMenu()
    {
        cout << "1. Add a new employee" << endl;
        cout << "2. Increase day by one day" << endl;
        cout << "3. Set new annual savings interest" << endl;
        cout << "4. Set a new overdraft charge" << endl;
        cout << "5. exit" << endl;
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
        char choice = '0';
        string username(user->Username);
        if (username == "administrator")
        {
            Admin *admin = new Admin;

            while (choice != '5')
            {
                // display the admin menu
                admin->DisplayAdminMenu();
                cout << "Enter your choice: ";
                cin >> choice;

                // switch case to admin menu
                switch (choice)
                {
                case '1':
                {
                    cout << "New Employee added" << endl;
                    // travel to the last emplyee in the linked list
                    Employee *currentEmployee = HeadEmployee;
                    while (currentEmployee->NextEmployee != NULL)
                    {
                        currentEmployee = currentEmployee->NextEmployee;
                    }
                    string user = currentEmployee->Username;
                    admin->AddEmployee(HeadEmployee, GettingTheID(user));
                    break;
                }
                case '2':
                {
                    cout << "Day increased by 1" << endl;
                    break;
                }
                case '3':
                {
                    cout << "New annual interest: " << endl;
                    double interest;
                    cin >> interest;
                    break;
                }
                case '4':
                {
                    cout << "New overdraft charge: " << endl;
                    double charge;
                    cin >> charge;
                    break;
                }
                case '5':
                {
                    break;
                }
                default:
                {
                    cout << "Invalid Input" << endl;
                    break;
                }
                }
            }
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
                char choice = '0';
                cout << "Welcome!" << endl;
                // CurrentCustomer->GetAccountInfo();
                while (choice != '5')
                {
                    CurrentCustomer->DisplayCustomerMenu();

                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                    case '1':
                    {
                        cout << "View Transactions" << endl;
                        // CurrentCustomer->DisplayTransactionInformation();
                        break;
                    }
                    case '2':
                    {
                        cout << "Deposit amount: " << endl;
                        double amount;
                        cin >> amount;
                        break;
                    }
                    case '3':
                    {
                        cout << "Withdraw" << endl;
                        double amount;
                        cin >> amount;
                        break;
                    }
                    case '4':
                    {
                        CurrentCustomer->ViewPersonalInfo();
                        break;
                    }
                    case '5':
                    {
                        break;
                    }
                    default:
                    {
                        cout << "Invalid Input" << endl;
                        break;
                    }
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
                char choice = '0';

                while (choice != '7')
                {
                    CurrentEmployee->DisplayEmployeeMenu();

                    cout << "Enter your choice: ";
                    cin >> choice;
                    switch (choice)
                    {
                    case '1':
                    {
                        Customer *CurrentCustomer;
                        CurrentCustomer = HeadCustomer;
                        while (CurrentCustomer->NextCustomer != NULL)
                        {
                            CurrentCustomer = CurrentCustomer->NextCustomer;
                        }
                        string userc(CurrentCustomer->Username);
                        CurrentEmployee->AddCustomer(HeadCustomer, GettingTheID(userc));
                        if (CurrentCustomer->NextCustomer != NULL)
                        {
                            CurrentCustomer = CurrentCustomer->NextCustomer;
                        }
                        cout << "Name of the New customer: ";
                        cin >> CurrentCustomer->name;
                        cout << "Phone number of the New customer: ";
                        cin >> CurrentCustomer->phone;
                        cout << "New customer added" << endl;
                        break;
                    }
                    case '2':
                    {
                        cout << "Customer username: ";
                        string username;
                        cin >> username;
                        break;
                    }
                    case '3':
                    {
                        cout << "Customer username: ";
                        string username;
                        cin >> username;
                        break;
                    }
                    case '4':
                    {
                        cout << "Customer username: ";
                        string username;
                        cin >> username;
                        cout << "Deposit amount: " << endl;
                        double amount;
                        cin >> amount;
                        break;
                    }
                    case '5':
                    {
                        cout << "Customer username: ";
                        string username;
                        cin >> username;
                        cout << "Wthdraw amount: " << endl;
                        double amount;
                        cin >> amount;
                        break;
                    }
                    case '6':
                    {
                        cout << "Customer username: ";
                        string username;
                        cin >> username;
                        break;
                    }
                    case '7':
                    {
                        break;
                    }
                    default:
                    {
                        cout << "Invalid Input" << endl;
                        break;
                    }
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
