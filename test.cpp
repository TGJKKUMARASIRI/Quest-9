#include <iostream>
#include <string>

class User {
protected:
    std::string username;
    std::string password;

public:
    User(const std::string& uname, const std::string& pwd) : username(uname), password(pwd) {}

    void HidePassword() {
        // Code to hide password input (platform-specific)
    }
};

class Account {
public:
    int accountNumber;
    double overdraftLimit;
    double balance; // Additional field to store balance
    Account* next;

    Account(int number) : accountNumber(number), overdraftLimit(0.0), balance(0.0), next(nullptr) {}
};

class BankEmployee : public User {
private:
    class Customer {
    public:
        std::string name;
        Account* accounts;

        Customer(const std::string& cname) : name(cname), accounts(nullptr) {}
    };

    class Node {
    public:
        Customer customer;
        Node* next;

        Node(const std::string& cname) : customer(cname), next(nullptr) {}
    };

    Node* customersHead;

public:
    BankEmployee(const std::string& uname, const std::string& pwd) : User(uname, pwd), customersHead(nullptr) {}

    void AddCustomer(const std::string& customerName) {
        Node* newNode = new Node(customerName);
        newNode->next = customersHead;
        customersHead = newNode;
        std::cout << "Added customer: " << customerName << std::endl;
    }

    void CreateAccount(const std::string& customerName, const std::string& accountType) {
        int accountNumber = rand() % 1000 + 1000; // Example random account number

        Node* current = customersHead;
        while (current) {
            if (current->customer.name == customerName) {
                Account* newAccount = new Account(accountNumber);
                newAccount->next = current->customer.accounts;
                current->customer.accounts = newAccount;

                if (accountType == "Current") {
                    // Set overdraft limit for current account
                    newAccount->overdraftLimit = 500; // Example overdraft limit for a current account
                }

                std::cout << "Created " << accountType << " account for " << customerName << " with number " << accountNumber << std::endl;
                return;
            }
            current = current->next;
        }

        std::cout << "Customer not found: " << customerName << std::endl;
    }

    void CloseAccount(const std::string& customerName, int accountNumber) {
        Node* current = customersHead;
        while (current) {
            if (current->customer.name == customerName) {
                Account* prev = nullptr;
                Account* currAccount = current->customer.accounts;
                while (currAccount) {
                    if (currAccount->accountNumber == accountNumber) {
                        if (prev)
                            prev->next = currAccount->next;
                        else
                            current->customer.accounts = currAccount->next;

                        delete currAccount;
                        std::cout << "Closed account " << accountNumber << " for " << customerName << std::endl;
                        return;
                    }
                    prev = currAccount;
                    currAccount = currAccount->next;
                }
                std::cout << "Account " << accountNumber << " not found for " << customerName << std::endl;
                return;
            }
            current = current->next;
        }

        std::cout << "Customer not found: " << customerName << std::endl;
    }

    void Deposit(const std::string& customerName, int accountNumber, double amount) {
        Node* current = customersHead;
        while (current) {
            if (current->customer.name == customerName) {
                Account* currAccount = current->customer.accounts;
                while (currAccount) {
                    if (currAccount->accountNumber == accountNumber) {
                        currAccount->balance += amount;
                        std::cout << "Deposited $" << amount << " into account " << accountNumber << " of " << customerName << std::endl;
                        return;
                    }
                    currAccount = currAccount->next;
                }
                std::cout << "Account " << accountNumber << " not found for " << customerName << std::endl;
                return;
            }
            current = current->next;
        }
        std::cout << "Customer not found: " << customerName << std::endl;
    }

    void Withdraw(const std::string& customerName, int accountNumber, double amount) {
        Node* current = customersHead;
        while (current) {
            if (current->customer.name == customerName) {
                Account* currAccount = current->customer.accounts;
                while (currAccount) {
                    if (currAccount->accountNumber == accountNumber) {
                        if (currAccount->balance >= amount) {
                            currAccount->balance -= amount;
                            std::cout << "Withdrawn $" << amount << " from account " << accountNumber << " of " << customerName << std::endl;
                        } else {
                            std::cout << "Insufficient funds in account " << accountNumber << " of " << customerName << std::endl;
                        }
                        return;
                    }
                    currAccount = currAccount->next;
                }
                std::cout << "Account " << accountNumber << " not found for " << customerName << std::endl;
                return;
            }
            current = current->next;
        }
        std::cout << "Customer not found: " << customerName << std::endl;
    }

    void SetOverdraftLimit(int accountNumber, double limit) {
        Node* current = customersHead;
        while (current) {
            Account* currAccount = current->customer.accounts;
            while (currAccount) {
                if (currAccount->accountNumber == accountNumber) {
                    currAccount->overdraftLimit = limit;
                    std::cout << "Set overdraft limit of $" << limit << " for account " << accountNumber << std::endl;
                    return;
                }
                currAccount = currAccount->next;
            }
            current = current->next;
        }
        std::cout << "Account " << accountNumber << " not found" << std::endl;
    }

    void ViewTransactions(int accountNumber) {
        Node* current = customersHead;
        while (current) {
            Account* currAccount = current->customer.accounts;
            while (currAccount) {
                if (currAccount->accountNumber == accountNumber) {
                    std::cout << "Viewing transactions for account " << accountNumber << std::endl;
                    // Fetch and display transactions (for example, log text file)
                    return;
                }
                currAccount = currAccount->next;
            }
            current = current->next;
        }
        std::cout << "Account " << accountNumber << " not found" << std::endl;
    }
};

int main() {
    // Example usage
    BankEmployee bankEmployee("username", "password");

    bankEmployee.AddCustomer("Customer1");
    bankEmployee.CreateAccount("Customer1", "Savings");
    bankEmployee.SetOverdraftLimit(1001, 500); // Set overdraft limit for account number 1001 to $500
    bankEmployee.Deposit("Customer1", 1001, 1000); // Deposit $1000 to account number 1001 for Customer1
    bankEmployee.Withdraw("Customer1", 1001, 700); // Withdraw $700 from account number 1001 for Customer1
    bankEmployee.ViewTransactions(1001); // View transactions for account number 1001

    return 0;
}
