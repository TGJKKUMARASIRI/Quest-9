21_ENG_097 P.SIVABALASRI

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

class User;
class Adminstrator;
class Employee;
class Customer;
class Account;
class SavingAccount;
class CurrentAccount;
class Bank;



class User {
public:
    string username;
    string password;

    User(string uname, string pwd) : username(uname), password(pwd) {}
};

class Administrator : public User {
public:
    Administrator(string uname) : User(uname, "Password@1234") {}

    void addEmployee(Employee& employee);
    void increaseDate();
    void setInterestAndCharge(double annualSavingInterest, double overdraftCharge);
};

class Employee : public User {
public:
    Employee(string uname) : User(uname, "Password@1234") {}

    void addCustomer(Customer& customer);
    void createAccount(Customer& customer, string accountType, double initialBalance);
    void closeAccount(Customer& customer);
    void deposit(Customer& customer, double amount, string depositorName);
    void withdraw(Customer& customer, double amount);
    void setOverdraftLimit(CurrentAccount& account, double limit);
    void viewTransactions(Account& account);
};

class Customer : public User {
public:
    string name;
    string mobileNumber;

    Customer(string uname, string customerName, string mobile) : User(uname, "Password@1234"), name(customerName), mobileNumber(mobile) {}
};

class Account {
public:
    int accountNumber;
    string customerName;
    string contactDetails;
    double balance;
    vector<string> transactions;

    Account(int accNumber, string custName, string contact) : accountNumber(accNumber), customerName(custName), contactDetails(contact), balance(0.0) {}

    void recordTransaction(string transaction);
};

class SavingAccount : public Account {
public:
    double annualInterest;

    SavingAccount(int accNumber, string custName, string contact, double interest) : Account(accNumber, custName, contact), annualInterest(interest) {}

    void calculateInterest();
};

class CurrentAccount : public Account {
public:
    double overdraftLimit;
    double overdraftCharge;

    CurrentAccount(int accNumber, string custName, string contact, double overdraftLimit, double overdraftCharge) : Account(accNumber, custName, contact), overdraftLimit(overdraftLimit), overdraftCharge(overdraftCharge) {}
};

class Bank {
public:
    double bankBalance;

    Bank() : bankBalance(1000000.0) {}

    void simulateExternalDeposit(int accountNumber, double amount, string depositorName);
};

// Definitions for Administrator class methods
void Administrator::addEmployee(Employee& employee) {
    // Simplified implementation to add an employee
    cout << "Employee added: " << employee.username << endl;
}

void Administrator::increaseDate() {
    // Simplified implementation to increase the date
    cout << "Date increased by 1 day." << endl;
}

void Administrator::setInterestAndCharge(double annualSavingInterest, double overdraftCharge) {
    // Simplified implementation to set interest and charge
    cout << "Annual Saving Interest set to: " << annualSavingInterest << endl;
    cout << "Overdraft Charge set to: " << overdraftCharge << endl;
}

// Definitions for Employee class methods
void Employee::addCustomer(Customer& customer) {
    // Simplified implementation to add a customer
    cout << "Customer added: " << customer.username << endl;
}

void Employee::createAccount(Customer& customer, string accountType, double initialBalance) {
    // Simplified implementation to create an account
    cout << "Account created for customer: " << customer.username << " with initial balance: " << initialBalance << endl;
}

void Employee::closeAccount(Customer& customer) {
    // Simplified implementation to close an account
    cout << "Account closed for customer: " << customer.username << endl;
}

void Employee::deposit(Customer& customer, double amount, string depositorName) {
    // Simplified implementation to deposit money
    cout << "Deposited $" << amount << " to account of customer: " << customer.username << " by depositor: " << depositorName << endl;
}

void Employee::withdraw(Customer& customer, double amount) {
    // Simplified implementation to withdraw money
    cout << "Withdrawn $" << amount << " from account of customer: " << customer.username << endl;
}

void Employee::setOverdraftLimit(CurrentAccount& account, double limit) {
    // Simplified implementation to set overdraft limit
    cout << "Overdraft limit set to $" << limit << " for account: " << account.accountNumber << endl;
}

void Employee::viewTransactions(Account& account) {
    // Simplified implementation to view transactions
    cout << "Transactions for account: " << account.accountNumber << endl;
    for (const auto& transaction : account.transactions) {
        cout << transaction << endl;
    }
}

// Definitions for Account class methods
void Account::recordTransaction(string transaction) {
    // Simplified implementation to record a transaction
    transactions.push_back(transaction);
}

// Definitions for SavingAccount class methods
void SavingAccount::calculateInterest() {
    // Simplified implementation to calculate interest
    cout << "Interest calculated for Saving Account: " << accountNumber << endl;
}

int main() {
    // Example usage
    Administrator admin("admin001");
    Employee employee("employee001");
    Customer customer("customer001", "John Doe", "1234567890");
    SavingAccount savingAccount(1, "John Doe", "1234567890", 0.05);
    CurrentAccount currentAccount(2, "Jane Doe", "9876543210", 1000.0, 0.1);
    Bank bank;

    // Perform operations as required
    admin.addEmployee(employee);
    admin.increaseDate();
    admin.setInterestAndCharge(0.06, 0.2);

    employee.addCustomer(customer);
    employee.createAccount(customer, "Savings", 500.0);
    employee.deposit(customer, 200.0, "External Depositor");
    employee.withdraw(customer, 50.0);
    employee.setOverdraftLimit(currentAccount, 1500.0);
    employee.viewTransactions(savingAccount);

    savingAccount.calculateInterest();

    return 0;
}

