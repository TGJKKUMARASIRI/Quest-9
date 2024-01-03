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

struct Account {
    int accountNumber;
    Account* next;

    Account(int number) : accountNumber(number), next(nullptr) {}
};

class BankEmployee : public User {
private:
    struct Customer {
        std::string name;
        Account* accounts;

        Customer(const std::string& cname) : name(cname), accounts(nullptr) {}
    };

    struct Node {
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
                std::cout << "Created account for " << customerName << " of type " << accountType << " with number " << accountNumber << std::endl;
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
                        // Code to deposit money into an account
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
                        // Code to withdraw money from an account
                        std::cout << "Withdrawn $" << amount << " from account " << accountNumber << " of " << customerName << std::endl;
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
};

    void ViewTransactions(int accountNumber) {
        Node* current = customersHead;
        while (current) {
            Account* currAccount = current->customer.accounts;
            while (currAccount) {
                if (currAccount->accountNumber == accountNumber) {
                    // Code to view transactions of an account
                    std::cout << "Viewing transactions for account " << accountNumber << std::endl;
                    // Example: Fetch and display transactions
                    return;
                }
                currAccount = currAccount->next;
            }
            current = current->next;
        }
        std::cout << "Account " << accountNumber << " not found" << std::endl;
    }
};


