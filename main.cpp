#include <iostream>
#include <string>
#include <fstream>
#include "Class.h"

using namespace std;

int main()
{
    Admin* admin;
    admin = new Admin;

    // ifstream CustomerInfo("Customer.txt");

    // admin->GetCustomerInfo(CustomerInfo);

    admin->GetCustomerInfo();
    admin->DisplayCustomerInfo();

    return 0;
}