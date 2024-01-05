// T.G.J.K. Kumarasiri 21/ENG/147
// A.M.N.K.Gayasan 21/ENG/008
// P.Sivabalasri 21/ENG/097

#include <iostream>
#include <string>
#include <fstream>
#include "Class.h"

using namespace std;

int main()
{
    App* app;
    app = new App;

    app->GetCustomerInfo();
    app->GetEmployeeInfo();

    app->user->GetUserInfo();

    app->CheckPassword();

    return 0;
}