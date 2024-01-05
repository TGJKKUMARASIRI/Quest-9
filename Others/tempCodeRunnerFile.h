void GetAccountInfo()
    {
        string username(Username);
        username += ".txt";
        ifstream AccountInfo(username);

        if (!AccountInfo.is_open())
        {
            cerr << "Error opening file" << endl;
            return;
        }

        char Buffer[128];
        AccountInfo.getline(Buffer, 128);
        cout << Buffer << endl; //comment
        string AccType = Buffer;
        if (stoi(AccType) == 0)
        {
            savingsAccount = new SavingsAccounts;
            AccountInfo.getline(Buffer, 128);
            cout << Buffer << endl; //comment
            savingsAccount->AnualInterestRate = stod(Buffer);
            // should reed the last line of the file to get the ammount
            while (AccountInfo.eof() == false)
            {
                AccountInfo.getline(Buffer, 128);
                cout << Buffer << endl; //comment
            }
            string Amount = Buffer;
            savingsAccount->amount = stod(Amount);
        }
        else
        {
        }
        AccountInfo.close();
    }