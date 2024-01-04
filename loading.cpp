  void LoadUserData(const string& username) {
    string filename = username + ".txt"; 

    ifstream userDataFile(filename);
    if (!userDataFile.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return;
    }

    string line;
    vector<string> data;
    while (getline(userDataFile, line)) {
        data.push_back(line);
    }
    userDataFile.close();

    // Process the loaded data here and set the values accordingly
    // Example: Assign loaded data to class variables
    if (data.size() >= 7) {
        strcpy(name, data[0].c_str());
        strcpy(phone, data[1].c_str());

        // Process account details
        string accountDetails = data[2];
        if (accountDetails.find("SavingsAccount:") != string::npos) {
            size_t pos = accountDetails.find("SavingsAccount:");
            string savingsAccount = accountDetails.substr(pos + 15);
            HeadSavingsAccounts->AccountNumber = savingsAccount;
        }
        // Similar parsing can be done for CurrentAccount if needed
		string accountDetails = data[2];
        if (accountDetails.find("CurrentAccount:") != string::npos) {
            size_t pos = accountDetails.find("CurrentAccount:");
            string currentAccount = accountDetails.substr(pos + 15);
            HeadCurrentAccounts->AccountNumber = currentAccount;
        }
        // Process amount
        string amountDetails = data[3];
        if (amountDetails.find("Amount:") != string::npos) {
            size_t pos = amountDetails.find("Amount:");
            string amountStr = amountDetails.substr(pos + 7);
            HeadSavingsAccounts->amount = stod(amountStr);
        }

        // Process transactions
        // ...

        // Process overdraft limit
        string overdraftDetails = data[5];
        if (overdraftDetails.find("OverdraftLimit:") != string::npos) {
            size_t pos = overdraftDetails.find("OverdraftLimit:");
            string overdraftStr = overdraftDetails.substr(pos + 15);
            HeadCurrentAccounts->OverdraftLimit = stod(overdraftStr);
        }

        // Process interest rate
        string interestDetails = data[6];
        if (interestDetails.find("InterestRate:") != string::npos) {
            size_t pos = interestDetails.find("InterestRate:");
            string interestStr = interestDetails.substr(pos + 13);
            HeadSavingsAccounts->AnualInterestRate = stod(interestStr);
        }

        // Further processing of data as required...
    }
}
