#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class User
{
public:
    string Password;
    string Username;
};

class Employee : public User
{
public:
    Employee* NextEmployee;
    char Bufffer[128];	
    
};

class Customer : public User
{
public:
    Customer* NextCustomer;
    char Username[128];
    char name[128];
    char phone[128];
    char amount[128];
};

class Admin : public User
{
public:
    Employee* HeadEmployee;
    Customer* HeadCustomer;

    //function to get the customer information from the file while creating a customer linked list
    void GetCustomerInfo()
    {
        ifstream CustomerInfo("Customer.txt");
        Customer* CurrentCustomer;
        HeadCustomer = new Customer;
        CurrentCustomer = HeadCustomer;
        while (CustomerInfo.eof() == false)
        {
            CustomerInfo.getline(CurrentCustomer->Username, 128);
            CustomerInfo.getline(CurrentCustomer->name, 128);
            CustomerInfo.getline(CurrentCustomer->phone, 128);
            CustomerInfo.getline(CurrentCustomer->amount, 128);
            CurrentCustomer->NextCustomer = new Customer;
            CurrentCustomer = CurrentCustomer->NextCustomer;
        }
    }

    //function to display the customer information
    void DisplayCustomerInfo()
    {
        Customer* CurrentCustomer;
        CurrentCustomer = HeadCustomer;
        while (CurrentCustomer->NextCustomer != NULL)
        {
            cout << CurrentCustomer->Username << endl;
            cout << CurrentCustomer->name << endl;
            cout << CurrentCustomer->phone << endl;
            cout << CurrentCustomer->amount << endl;
            CurrentCustomer = CurrentCustomer->NextCustomer;
        }
    }
};

