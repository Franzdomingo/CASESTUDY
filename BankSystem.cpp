#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <thread>
#include "json.hpp"
#include "SecuritySys.h"
#include "ChatAI.h"

using namespace std;
using json = nlohmann::json;
using namespace chrono;
using namespace this_thread;

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

struct User
{
    string name;
    string username;
    string password;
    string producttype;
    double balance;
    vector<Profile> profiles;
    vector<Transaction> transactionhistory;
};

class BankSystem
{
private:
    SecuritySys system;
    ChatAI ai;
    vector<User> users;
    vector<Profile> profiles;
    vector<Transaction> transactionhistory;
    string currentLoggedInUser;
    string currentProductType;
    string dataFilePath; // Path to the data file

public:
    BankSystem(const string &dataFile) : dataFilePath(dataFile)
    {
        loadDataFromFile();
    }

    void displayMainMenu()
    {
        cout << "\nWelcome to the Bank System" << endl;
        cout << "1. Login" << endl;
        cout << "2. Product Application" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
    }

    void displayDashboardMenu(const string &username)
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                cout << "\nWelcome " << username << "!" << endl;
                cout << "Current Balance: $" << getCurrentBalance(username) << endl;
                cout << "\nDashboard Options:" << endl;
                cout << "1. Transaction Center" << endl;
                cout << "2. User Profile" << endl;
                cout << "3. Data Analytics Dashboard" << endl;
                cout << "4. Help & Resources" << endl;
                cout << "5. Logout" << endl;
                cout << "Enter your choice: ";
            }
        }
    }

    void displayTransactionMenu(const string &username)
    {
        cout << "\nTransaction Center:" << endl;
        cout << "1. Deposit Funds" << endl;
        cout << "2. Withdraw Funds" << endl;
        cout << "3. View Transaction History" << endl;
        cout << "4. Back to Dashboard" << endl;
        cout << "Enter your choice: ";
        setCurrentLoggedInUser(username);
    }

    void displayTransactionHistory(const string &username)
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                cout << "\nTransaction History for User: " << user.username << endl;
                cout << "--------------------------------" << endl;
                for (const Transaction &transaction : user.transactionhistory)
                {
                    cout << "Transaction ID: " << transaction.transactionID << endl;
                    cout << "Transaction Type: " << transaction.transactionType << endl;
                    cout << "Amount: $" << transaction.amount << endl;
                    cout << "Timestamp: " << ctime(&transaction.timestamp);
                    cout << "--------------------------------" << endl;
                }
            }
        }
        // Replaced system("pause") with a more portable solution
        cout << "Press Enter to continue...";
        cin.get();
    }

    bool loginUser(string &loggedInUsername)
    {
        string username, password;
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);

        if (authenticateUser(username, password))
        {
            loggedInUsername = username;
            string productType = getCurrentProductType(loggedInUsername);

            setCurrentLoggedInUser(loggedInUsername);
            setCurrentProductType(productType);
            cout << "Login successful!" << endl;   
            return true;
        }
        else
        {
            cout << "Invalid username or password. Please try again." << endl;
            return false;
        }
    }

    void handleTransactionCenter(const string &username)
    {
        while (true)
        {
            displayTransactionMenu(username);

            int transactionChoice;
            cin >> transactionChoice;
            cin.ignore();

            switch (transactionChoice)
            {
            case 1:
                processDeposit(username);
                break;
            case 2:
                processWithdrawal(username);
                break;
            case 3:
                displayTransactionHistory(username);
                break;
            case 4:
                return; // Return to the dashboard
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
            }
        }
    }

    void processDeposit(const string &username)
    {
        double depositAmount;
        cout << "\nEnter the amount to deposit: $";
        cin >> depositAmount;
        cin.ignore(); // Clear the newline character

        if (depositAmount <= 0.0)
        {
            cout << "Invalid deposit amount. Please enter a positive amount." << endl;
            return;
        }

        if (depositFunds(username, depositAmount))
        {
            cout << "Deposit of $" << depositAmount << " successful." << endl;
            cout << "Press Enter to continue...";
            cin.get();
        }
        else
        {
            cout << "Deposit failed. Please try again." << endl;
        }
        cout << "Press Enter to continue...";
        cin.get();
    }

    void processWithdrawal(const string &username)
    {
        double withdrawAmount;
        cout << "\nEnter the amount to withdraw: $";
        cin >> withdrawAmount;
        cin.ignore(); // Clear the newline character

        if (withdrawAmount <= 0.0)
        {
            cout << "Invalid withdrawal amount. Please enter a positive amount." << endl;
            return;
        }

        if (withdrawFunds(username, withdrawAmount))
        {
            cout << "Withdrawal of $" << withdrawAmount << " successful." << endl;
        }
        else
        {
            cout << "Withdrawal failed. Please try again." << endl;
        }
        cout << "Press Enter to continue...";
        cin.get();
    }

    void handleHelpAndResources()
    {
        string message;
        cout << "\nHi! I'm your AI Assistant. How may I help you?\n"
             << endl;
        getline(cin, message);
        ai.chatBot(message);
    }

    void handleDashboardOptions(const string &username)
    {
        while (true)
        {
            displayDashboardMenu(username);

            int choice;
            cin >> choice;
            cin.ignore(); // Clear the newline character

            switch (choice)
            {
            case 1:
                handleTransactionCenter(username);
                break;
            case 2:
                displayProfile(username);
                break;
            case 3:
                // Data Analytics Dashboard
                break;
            case 4:
                handleHelpAndResources();
                break;
            case 5:
                // Logout the user
                cout << "Logging out..." << endl;
                setCurrentLoggedInUser("");
                return;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
            }
        }
    }

    void applyForProduct()
    {
        string name, username, password, email, phone, accounttype;
        int acctype;
        char enable2FA;
        while (true)
        {
            cout << "\nPress Enter to continue...";
            cin.get();
            cout << "Product Application" << endl;
            cout << "Enter your full name: ";
            getline(cin, name);

            cout << "Enter username: ";
            getline(cin, username);

            // Check if the username is already taken
            bool usernameTaken = isUsernameTaken(username);
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

            cout << "Do you want to enable 2FA?(Y/N): ";
            cin >> enable2FA;

            cout << "Pick account type: " << endl;
            cout << "1. Savings Account" << endl;
            cout << "2. Credit Account" << endl;

            cout << "Choose your account type: ";
            cin >> acctype;

            switch (acctype)
            {
            case 1:
                accounttype = "Savings Account";
                break;
            case 2:
                accounttype = "Credit Account";
                break;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
                continue;
            }

            // Create a new user account
            bool registrationSuccess = createUser(name ,username, password, email, phone, enable2FA, accounttype);
            if (registrationSuccess)
            {
                cout << "Registration successful!" << endl;
                break;
            }
            else
            {
                cout << "Registration failed. Please try again." << endl;
                continue;
            }
        }
    }

    void displayProfile(const string &username)
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                for (const Profile &profile : user.profiles)
                {
                    string show2FAStatus = profile.isTwoFactorEnabled ? "Enabled" : "Disabled";

                    cout << "User Profile" << endl;
                    cout << "--------------------------------" << endl;
                    cout << "Name: " << user.username << endl;
                    cout << "Email: " << profile.email << endl;
                    cout << "Phone: " << profile.phone << endl;
                    cout << "Account: " << user.producttype << endl;
                    cout << "Two Factor Authentication: " << show2FAStatus << endl;
                    cout << "--------------------------------" << endl;
                }
            }
        }
        cout << "Press Enter to continue...";
        cin.get();
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

    string generateTransactionID()
    {
        // Implement your logic to generate a unique transaction ID
        // Example: You can use a combination of timestamp and a random number
        return "TXN" + to_string(time(nullptr)) + to_string(rand());
    }

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
        auto user_it = find_if(users.begin(), users.end(), [&](const User &user)
                               { return user.username == username; });

        if (user_it != users.end())
        {
            string decryptedPass = system.decryptPass(user_it->password);
            if (system.attemptLogin(decryptedPass, password))
            {
                // Check for 2FA within profiles of the user
                for (const Profile &profile : user_it->profiles)
                {
                    if (profile.isTwoFactorEnabled)
                    {
                        cout << "Sending an OTP for 2 Factor Authentication." << endl;
                        system.sendOTP();

                        string inputOTP;
                        cout << "Enter your OTP: ";
                        cin >> inputOTP;

                        if (!system.verifyOTP(inputOTP))
                        {
                            cout << "Incorrect OTP. Timeout for 30 seconds..." << endl;
                            sleep_for(seconds(30));
                            return false;
                        }
                    }
                }
                return true;
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

    bool createUser(const string &name, const string &username, const string &password, const string &email,
                    const string &phone, const char &twoFA, const string &producttype)
    {
        // Check if the username is already taken
        if (isUsernameTaken(username))
        {
            cout << "Username is already taken. Please choose another one." << endl;
            return false;
        }

        // Create a new user account
        User newUser;
        newUser.name = name;
        newUser.username = username;
        newUser.password = system.encryptPass(password);
        newUser.producttype = producttype;
        newUser.balance = 0.0;

        // Create a new profile for the user
        Profile newProfile;
        newProfile.email = email;
        newProfile.phone = phone;
        newProfile.isTwoFactorEnabled = system.enable2FA(twoFA);

        // Add the new profile to the user's profiles vector
        newUser.profiles.push_back(newProfile);

        // Add the new user to the vector of users
        users.push_back(newUser);

        // Save the updated user data to the file
        saveDataToFile();

        cout << "User account created successfully." << endl;
        return true;
    }

    void loadDataFromFile()
    {
        ifstream file(dataFilePath);
        if (!file.is_open())
        {
            cout << "Error: Unable to open data file." << endl;
            return;
        }

        json j;
        file >> j;
        file.close();

        for (const auto &item : j)
        {
            User user;
            user.name = item.value("name", "");
            user.username = item.value("username", "");
            user.password = item.value("password", "");
            user.producttype = item.value("accounttype", "");
            user.balance = item.value("balance", 0.0);

            for (const auto &profileItem : item["profiles"])
            {
                Profile profile;
                profile.email = profileItem.value("email", "");
                profile.phone = profileItem.value("phone", "");
                profile.isTwoFactorEnabled = profileItem.value("isTwoFactorEnabled", false);
                user.profiles.emplace_back(profile);
            }

            if (item.contains("transactionhistory"))
            {
                for (const auto &transactionItem : item["transactionhistory"])
                {
                    Transaction transaction;
                    transaction.transactionID = transactionItem.value("transactionID", "");
                    transaction.transactionType = transactionItem.value("transactionType", "");
                    transaction.amount = transactionItem.value("amount", 0.0);
                    transaction.timestamp = transactionItem.value("timestamp", 0);
                    user.transactionhistory.emplace_back(transaction);
                }
            }

            users.emplace_back(user);
        }
    }

    void saveDataToFile()
    {
        try
        {
            ofstream file(dataFilePath);

            if (!file.is_open())
            {
                cout << "Error: Unable to save data to the file." << endl;
                return;
            }

            json j;

            for (const User &user : users)
            {
                json userJson;
                userJson["name"] = user.name;
                userJson["username"] = user.username;
                userJson["password"] = user.password;
                userJson["accounttype"] = user.producttype;
                userJson["balance"] = user.balance;

                for (const Profile &profile : user.profiles)
                {
                    json profileJson;
                    profileJson["email"] = profile.email;
                    profileJson["phone"] = profile.phone;
                    profileJson["isTwoFactorEnabled"] = profile.isTwoFactorEnabled;
                    userJson["profiles"].push_back(profileJson);
                }

                for (const Transaction &transaction : user.transactionhistory)
                {
                    json transactionJson;
                    transactionJson["transactionID"] = transaction.transactionID;
                    transactionJson["transactionType"] = transaction.transactionType;
                    transactionJson["amount"] = transaction.amount;
                    transactionJson["timestamp"] = transaction.timestamp;
                    userJson["transactionhistory"].push_back(transactionJson);
                }

                j.push_back(userJson);
            }

            file << j.dump(4);

            file.close();
        }
        catch (const json::exception &e) // catching specific exceptions related to the json library
        {
            cout << "JSON error: " << e.what() << endl;
        }
        catch (const exception &e) // generic C++ exceptions
        {
            cout << "Error saving data to file: " << e.what() << endl;
        }
    }
};

int main()
{
    BankSystem bank("bank_data.json");
    string loggedInUsername;

    while (true)
    {
        bank.displayMainMenu();

        int choice;
        cin >> choice;
        cin.ignore(); // Clear the newline character

        switch (choice)
        {
        case 1:
            if (bank.loginUser(loggedInUsername))
            {
                bank.handleDashboardOptions(loggedInUsername);
            }
            break;
        case 2:
            bank.applyForProduct();
            break;
        case 3:
            return 0; // Exit the program
        default:
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    }
    return 0;
}
