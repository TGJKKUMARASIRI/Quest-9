#include <iostream>
#include <string>
#include <fstream>
#include "Class.h"

using namespace std;

int main()
{
    // Admin* admin;
    // admin = new Admin;

    // // ifstream CustomerInfo("Customer.txt");

    // // admin->GetCustomerInfo(CustomerInfo);

    // admin->GetCustomerInfo();
    // admin->DisplayCustomerInfo();

    // App* app;
    // app = new App;

    // app->GetCustomerInfo();
    // app->DisplayCustomerInfo();

    // app->GetEmployeeInfo();
    // app->DisplayEmployeeInfo();

    App* app;
    app = new App;

    app->GetCustomerInfo();
    app->GetEmployeeInfo();

    app->user->GetUserInfo();

    app->CheckPassword();

    return 0;
}