#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>
#include "SecuritySys.h"

using namespace std;

// Define structures for data storage
struct Transaction
{
    string transactionID;
    string transactionType;
    double amount;
    time_t timestamp;
};
struct Profile
{
    string email;
    string phone;
    bool isTwoFactorEnabled;
};

struct ProductApplication
{
    string applicationID;
    string producttype;
};

struct Session
{
    string sessionID;
    time_t timestamp;
};

struct DataAnalytics
{
    string dataID;
    string businessinsights;
    string transactionpatterns;
};

struct HelpandResources
{
    string helpID;
    string helpcontent;
    string helpresources;
    string feedback;
};

struct dashboard
{
    string dashboardID;
    string dashboardcontent;
};

struct User
{
    string name;
    string username;
    string password;
    string producttype;
    double balance;
    vector<Profile> profiles;
    vector<Transaction> transactionhistory;
    vector<ProductApplication> productapplications;
    vector<Session> sessions;
    vector<HelpandResources> helpandresources;
    vector<DataAnalytics> dataanalytics;
    vector<dashboard> dashboards;
};

class BankSystem
{
private:
    SecuritySys system;
    vector<User> users;
    vector<Profile> profiles;
    vector<Transaction> transactionhistory;
    vector<ProductApplication> productapplications;
    vector<Session> sessions;
    vector<HelpandResources> helpandresources;
    vector<DataAnalytics> dataanalytics;
    vector<dashboard> dashboards;
    string currentLoggedInUser;
    string currentProductType;
    string dataFilePath; // Path to the data file

public:
    BankSystem(const string &dataFile) : dataFilePath(dataFile)
    {
        // Load data from the file into the 'users' vector during system initialization
        loadDataFromFile();
    }
    // Display Transaction History
    void displayTransactionHistory(const string &username) const
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                cout << "Transaction History for User: " << user.username << endl;
                cout << "--------------------------------" << endl;
                for (const Transaction &transaction : user.transactionhistory)
                {
                    cout << "Transaction ID: " << transaction.transactionID << endl;
                    cout << "Transaction Type: " << transaction.transactionType << endl;
                    cout << "Amount: $" << transaction.amount << endl;
                    cout << "Timestamp: " << ctime(&transaction.timestamp);
                    cout << "--------------------------------" << endl;
                }
                return;
            }
        }
    }

    bool depositFunds(const string &username, double amount)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                // Update user's transaction history
                Transaction depositTransaction;
                depositTransaction.transactionID = generateTransactionID(); // Call a function to generate a unique transaction ID
                depositTransaction.transactionType = "Deposit";
                depositTransaction.amount = amount;
                depositTransaction.timestamp = time(nullptr);

                user.transactionhistory.push_back(depositTransaction);

                // Update user's balance
                user.balance += amount;

                // Save the updated user data to the file
                saveDataToFile();

                cout << "Deposit of $" << amount << " successful." << endl;
                return true;
            }
        }

        cout << "User not found. Deposit failed." << endl;
        return false;
    }

    // Function to generate a unique transaction ID (you can implement this as per your needs)
    string generateTransactionID()
    {
        // Implement your logic to generate a unique transaction ID
        // Example: You can use a combination of timestamp and a random number
        return "TXN" + to_string(time(nullptr)) + to_string(rand());
    }

    // Modify your BankSystem class to include the following functions:

    // Withdraw Funds
    bool withdrawFunds(const string &username, double amount)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                if (amount <= 0.0)
                {
                    cout << "Invalid withdrawal amount. Please enter a positive amount." << endl;
                    return false;
                }

                if (user.balance >= amount)
                {
                    // Update user's transaction history
                    Transaction withdrawTransaction;
                    withdrawTransaction.transactionID = generateTransactionID(); // Call a function to generate a unique transaction ID
                    withdrawTransaction.transactionType = "Withdrawal";
                    withdrawTransaction.amount = amount;
                    withdrawTransaction.timestamp = time(nullptr);

                    user.transactionhistory.push_back(withdrawTransaction);

                    // Update user's balance
                    user.balance -= amount;

                    // Save the updated user data to the file
                    saveDataToFile();

                    return true;
                }
                else
                {
                    cout << "Insufficient balance. Withdrawal failed." << endl;
                    return false;
                }
            }
        }

        cout << "User not found. Withdrawal failed." << endl;
        return false;
    }

    bool authenticateUser(const string &username, const string &password)
    {
        for (const User &user : users)
        {
            string decryptedPass = system.decryptPass(user.password);
            if (user.username == username && decryptedPass == password)
            {
                return true; // Authentication successful
            }
        }
        return false; // Authentication failed
    }

    void setCurrentLoggedInUser(const string &username)
    {
        currentLoggedInUser = username;
    }
    bool isValidProductType(const string &producttype)
    {
        // Define a list of valid product types in your system
        vector<string> validProductTypes = {"Savings Account", "Credit Account"};

        // Check if the provided product type is in the list of valid types
        for (const string &validType : validProductTypes)
        {
            if (producttype == validType)
            {
                return true; // The product type is valid
            }
        }

        return false; // The product type is not valid
    }
    void setCurrentProductType(const string &producttype)
    {
        // Check if the provided product type is valid before setting it
        // You can add logic to validate product types here
        if (isValidProductType(producttype))
        {
            currentProductType = producttype;
        }
        else
        {
            cout << "Invalid product type." << endl;
            // Handle the error or return an error code as needed
        }
    }

    string getCurrentProductType(const string &username) const
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                return user.producttype;
            }
        }

        // Return a default value or an appropriate indicator if the user is not found
        return "Unknown"; // You can choose a different indicator if needed
    }

    bool isUsernameTaken(const string &username) const
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                return true; // Username is already taken
            }
        }
        return false; // Username is available
    }

    double getCurrentBalance(const string &username) const
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                return user.balance;
            }
        }

        // Return a negative value or another suitable indicator if the user is not found
        return -1.0; // You can choose a different indicator if needed
    }
    bool createUser(const string &username, const string &password, const string &email, const string &phone, const string &producttype, const string &name)
    {
        // Check if the username is already taken
        if (isUsernameTaken(username))
        {
            cout << "Username is already taken. Please choose another one." << endl;
            return false;
        }

        // Create a new user account
        User newUser;
        newUser.producttype = producttype;
        newUser.name = name;
        newUser.username = username;
        newUser.password = system.encryptPass(password);
        newUser.balance = 0.0;

        // Create a new profile for the user
        Profile newProfile;
        newProfile.email = email;
        newProfile.phone = phone;
        newProfile.isTwoFactorEnabled = false; // You can add logic to enable 2FA if needed

        // Add the new profile to the user's profiles vector
        newUser.profiles.push_back(newProfile);

        // Add the new user to the vector of users
        users.push_back(newUser);

        // Save the updated user data to the file
        saveDataToFile();

        cout << "User account created successfully." << endl;
        return true;
    }

    // Load user data from the file into memory
    void loadDataFromFile()
    {
        ifstream file(dataFilePath, ios::binary); // Open file in binary mode.
        if (!file.is_open())
        {
            cout << "Error: Unable to open data file." << endl;
            return;
        }

        users.clear();
        User user;

        while (file >> user.username >> user.password >> user.producttype)
        {
            // Read the balance
            if (!(file >> user.balance))
                break;

            // Read the profiles
            int profileCount;
            if (!(file >> profileCount))
                break;
            user.profiles.resize(profileCount);
            for (int i = 0; i < profileCount; ++i)
            {
                Profile profile;
                if (!(file >> profile.email >> profile.phone >> profile.isTwoFactorEnabled))
                    break;
                user.profiles[i] = profile;
            }

            // Read the transaction history
            int transactionCount;
            if (!(file >> transactionCount))
                break;
            user.transactionhistory.resize(transactionCount);
            for (int i = 0; i < transactionCount; ++i)
            {
                Transaction transaction;
                if (!(file >> transaction.transactionID >> transaction.transactionType >> transaction.amount >> transaction.timestamp))
                    break;
                user.transactionhistory[i] = transaction;
            }

            users.push_back(user);
        }

        file.close();
    }

    // Save user data from memory to the file
    void saveDataToFile()
    {
        ofstream file(dataFilePath, ios::binary); // Open file in binary mode.
        if (!file.is_open())
        {
            cout << "Error: Unable to save data to the file." << endl;
            return;
        }

        for (const User &user : users)
        {
            // Save the username and password
            file << user.username << " " << user.password << " " << user.producttype << endl;

            // Save the balance
            file << user.balance << endl;

            // Save the number of profiles and each profile
            file << user.profiles.size() << endl;
            for (const Profile &profile : user.profiles)
            {
                file << profile.email << " " << profile.phone << " " << profile.isTwoFactorEnabled << endl;
            }

            // Save the number of transactions and each transaction
            file << user.transactionhistory.size() << endl;
            for (const Transaction &transaction : user.transactionhistory)
            {
                file << transaction.transactionID << " " << transaction.transactionType << " " << transaction.amount << " " << transaction.timestamp << endl;
            }

            // Save the other data structures (ProductApplication, Session, etc.) in a similar manner
        }

        file.flush(); // Ensure everything is written in the file.
        file.close();
    }
};

int main()
{
    BankSystem bank("bank_data.txt");

    while (true)
    {
    login:
        string username, password, email, phone, name;
        cout << "Welcome to the Bank System" << endl;
        cout << "1. Login" << endl;
        cout << "2. Product Application" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(); // Clear the newline character

        if (choice == 1)
        {
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            // Example pseudo-code for authentication
            if (bank.authenticateUser(username, password))
            {
                bank.setCurrentLoggedInUser(username);
                // Redirect to the user's dashboard or other menu options
                cout << "Login successful!" << endl;

                // Inside your main function, after successful login:
                string productType = bank.getCurrentProductType(username);

                bank.setCurrentProductType(productType);

                cout << "Login successful! You have a " << productType << " account." << endl;

                // Check the account type and perform actions accordingly
                if (productType == "Savings Account")
                {
                    // Perform actions specific to savings account
                    cout << "You have a Savings Account." << endl;
                    // Add code to handle savings account actions here
                }
                else if (productType == "Credit Account")
                {
                    // Perform actions specific to credit account
                    cout << "You have a Credit Account." << endl;
                    // Add code to handle credit account actions here
                }

                while (true)
                {
                    if (productType == "Savings Account")
                    {
                    dashboard:
                        cout << "\nWelcome " << username << "!" << endl;
                        cout << "Current Balance: $" << bank.getCurrentBalance(username) << endl;
                        cout << "\nDashboard Options:" << endl;
                        cout << "1. Transaction Center" << endl;
                        cout << "2. User Profile" << endl;
                        cout << "3. Data Analytics Dashboard" << endl;
                        cout << "4. Help & Resources" << endl;
                        cout << "5. Logout" << endl;
                        cout << "Enter your choice: ";

                        int choice;
                        cin >> choice;
                        cin.ignore(); // Clear the newline character

                        switch (choice)
                        {
                        case 1:
                            // Inside your main function, after successful login:

                            while (true)
                            {

                                cout << "\nTransaction Center:" << endl;
                                cout << "1. Deposit Funds" << endl;
                                cout << "2. Withdraw Funds" << endl;
                                cout << "3. View Transaction History" << endl;
                                cout << "4. Back to Dashboard" << endl;
                                cout << "Enter your choice: ";
                                bank.setCurrentLoggedInUser(username);
                                int transactionChoice;
                                string currentLoggedInUser;
                                cin >> transactionChoice;
                                cin.ignore(); // Clear the newline character

                                switch (transactionChoice)
                                {
                                case 1:
                                    // Deposit Funds
                                    double depositAmount;
                                    cout << "Enter the amount to deposit: $";
                                    cin >> depositAmount;
                                    cin.ignore(); // Clear the newline character

                                    if (depositAmount <= 0.0)
                                    {
                                        cout << "Invalid deposit amount. Please enter a positive amount." << endl;
                                        continue;
                                    }

                                    if (bank.depositFunds(username, depositAmount))
                                    {
                                        cout << "Deposit of $" << depositAmount << " successful." << endl;
                                    }
                                    else
                                    {
                                        cout << "Deposit failed. Please try again." << endl;
                                    }
                                    break;

                                case 2:
                                    // Withdraw Funds
                                    double withdrawAmount;
                                    cout << "Enter the amount to withdraw: $";
                                    cin >> withdrawAmount;
                                    cin.ignore(); // Clear the newline character

                                    if (withdrawAmount <= 0.0)
                                    {
                                        cout << "Invalid withdrawal amount. Please enter a positive amount." << endl;
                                        continue;
                                    }

                                    if (bank.withdrawFunds(username, withdrawAmount))
                                    {
                                        cout << "Withdrawal of $" << withdrawAmount << " successful." << endl;
                                    }
                                    else
                                    {
                                        cout << "Withdrawal failed. Please try again." << endl;
                                    }
                                    break;

                                case 3:
                                    // View Transaction History
                                    bank.displayTransactionHistory(username);
                                    break;

                                case 4:
                                    goto dashboard;
                                    // Back to Dashboard
                                    break;

                                default:
                                    cout << "Invalid choice. Please select a valid option." << endl;
                                }
                            }
                            if (productType == "Credit Account")
                            {
                                cout << "\nWelcome " << username << "!" << endl;
                            }
                            break;
                        case 2:
                            // Implement User Profile here
                            // Display user information and allow for profile updates if needed
                            break;
                        case 3:
                            // Implement Data Analytics Dashboard here
                            // Provide analytics and insights based on user data
                            break;
                        case 4:
                            // Implement Help & Resources here
                            // Provide user assistance and resources
                            break;
                        case 5:
                            // Logout the user
                            cout << "Logging out..." << endl;
                            bank.setCurrentLoggedInUser("");
                            goto login;
                            break;
                        default:
                            cout << "Invalid choice. Please select a valid option." << endl;
                        }
                    }
                }
            }
            else
            {
                cout << "Invalid username or password. Please try again." << endl;
            }
        }
        else if (choice == 2)
        {
            cout << "Product Application" << endl;
            cout << "Enter Full name: ";
            getline(cin, name);
            cout << "Enter username: ";
            cin >> username;

            // Check if the username is already taken
            bool usernameTaken = bank.isUsernameTaken(username);
            if (usernameTaken)
            {
                cout << "Username is already taken. Please choose another one." << endl;
                continue;
            }
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter phone: ";
            cin >> phone;
        Cardselection:
            cout << "Pick account type: " << endl;
            cout << "1. Savings Account" << endl;
            cout << "2. Credit Account" << endl;
            cout << "Enter your choice: ";
            int acctype;
            string accounttype; // Declare the variable here

            cin >> acctype;

            switch (acctype)
            {
            case 1:
                accounttype = "Savings Account"; // Assign the value here
                break;
            case 2:
                accounttype = "Credit Account"; // Assign the value here
                break;
            default:
                // go back to pick account type
                cout << "Invalid choice. Please select a valid option." << endl;
                goto Cardselection;
                break;
            }

            // Create a new user account
            bool registrationSuccess = bank.createUser(username, password, email, phone, accounttype, name);
            if (registrationSuccess)
            {
                cout << "Registration successful!" << endl;
            }
            else
            {
                cout << "Registration failed. Please try again." << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "Goodbye!" << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please select a valid option." << endl;
            break;
        }
    }
    return 0;
}
