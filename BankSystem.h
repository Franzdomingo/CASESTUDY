#pragma once
#ifndef BANK_SYSTEM_H
#define BANK_SYSTEM_H

#include <iostream>
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

using json = nlohmann::json;
using namespace chrono;
using namespace this_thread;

struct Transaction
{
    string transactionID;
    string transactionType;
    string description;
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
    string username;
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
    // vector<DataAnalytics> dataanalytics;
    vector<dashboard> dashboards;
};

class BankSystem
{
private:
    SecuritySys system;
    ChatAI ai;
    vector<User> users;
    vector<Profile> profiles;
    vector<Transaction> transactionhistory;
    vector<ProductApplication> productapplications;
    vector<Session> sessions;
    vector<HelpandResources> helpandresources;
    vector<dashboard> dashboards;
    string currentLoggedInUser;
    string currentProductType;
    string currentSessionID;
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

            setCurrentLoggedInUser(loggedInUsername);
            cout << "Login successful!" << endl;
            return true;
        }
        else
        {
            cout << "Invalid username or password. Please try again." << endl;
            return false;
        }
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

    void handleDashboardOptions(const string &username)
    {
        while (true)
        {
            displayDashboardMenu(username);
            string productType = getCurrentProductType(username);

            int choice;
            cin >> choice;
            cin.ignore(); // Clear the newline character

            switch (choice)
            {
            case 1:
                handleProductOptions(productType, username);
                break;
            case 2:
                displayProfile(username);
                break;
            case 3:
                viewAnalyticsDashBoard(username);
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

    void handleProductOptions(const string &producttype, const string &username)
    {
        if (producttype == "Savings Account")
        {
            displaySavingsMenu(username);
        }
        else if (producttype == "Credit Account")
        {
            displayCreditMenu(username);
        }
    }

    void displaySavingsMenu(const string &username)
    {
        handleTransactionCenter(username);
    }

    void displayCreditMenu(const string &username)
    {
        handleCreditCenter(username);
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
        setCurrentSessionID(generateSessionID());
    }

    void displayTransactionCredit(const string &username)
    {
        cout << "\nTransaction Center:" << endl;
        cout << "1. Make a Purchase" << endl;
        cout << "2. Pay Bills" << endl;
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
                for (const Transaction &transaction : user.transactionhistory)
                {
                    cout << "\nTransaction History for User: " << user.username << endl;
                    cout << "--------------------------------" << endl;
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

    void handleCreditCenter(const string &username)
    {
        while (true)
        {
            displayTransactionCredit(username);

            int transactionChoice;
            cin >> transactionChoice;
            cin.ignore();

            switch (transactionChoice)
            {
            case 1:
                processPurchase(username);
                break;
            case 2:
                processPayBills(username);
                break;
            case 3:
                displayTransactionHistory(username);
                break;
            case 4:
                return;
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

    void processPurchase(const string &username)
    {
        double purchaseAmount;
        cout << "Enter the purchase amount: $";
        cin >> purchaseAmount;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid amount. Please enter a valid number." << endl;
        }
        cin.ignore(); // Clear the newline character
        if (purchaseAmount <= 0.0)
        {
            cout << "Invalid transaction amount. Please enter a positive amount." << endl;
        }
        if (makePurchase(username, purchaseAmount, "Purchase description"))
        {
            cout << "Purchase of $" << purchaseAmount << " successful." << endl;
        }
        else
        {
            cout << "Purchase failed. Please try again." << endl;
        }
    }

    void processPayBills(const string &username)
    {
        double billAmount;
        cout << "Enter the bill amount: $";
        cin >> billAmount;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid amount. Please enter a valid number." << endl;
        }
        cin.ignore(); // Clear the newline character
        if (billAmount <= 0.0)
        {
            cout << "Invalid amount. Please enter a positive amount." << endl;
        }
        if (payBills(username, billAmount, "Bill description"))
        {
            cout << "Bill payment of $" << billAmount << " successful." << endl;
        }
        else
        {
            cout << "Bill payment failed. Please try again." << endl;
        }
    }

    void handleHelpAndResources()
    {
        string message;
        cout << "\nHi! I'm your AI Assistant. How may I help you?\n"
             << endl;
        getline(cin, message);
        ai.chatBot(message);
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
            bool registrationSuccess = createUser(name, username, password, email, phone, enable2FA, accounttype);
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
                    displayUserSettings(user.username);
                }
            }
        }
        cout << "Press Enter to continue...";
        cin.get();
    }

    void displayUserSettings(const string &username)
    {
        while (true)
        {
            cout << "User Settings" << endl;
            cout << "1. Manage Account" << endl;
            cout << "2. Back to Dashboard" << endl;

            int pchoice;
            cin >> pchoice;

            switch (pchoice)
            {
            case 1:
                handleAccountSettings(username);
                break;

            case 2:
                return;
                break;

            default:
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
            }
        }
    }

    void handleAccountSettings(const string &username)
    {
        string newpass, newemail, newphone, newusername;
        char new2FA;

        cout << "Manage Account" << endl;
        cout << "1. Change Password" << endl;
        cout << "2. Change Email" << endl;
        cout << "3. Change Phone" << endl;
        cout << "4. Change Username" << endl;
        cout << "5. Enable/Disable 2FA" << endl;
        cout << "6. Show Activity Log " << endl;
        cout << "7. Back to Profile" << endl;

        int mchoice;
        cin >> mchoice;

        switch (mchoice)
        {
        case 1:
            cout << "Enter new password: ";
            cin >> newpass;
            ChangePassword(username, newpass);
            break;

        case 2:
            cout << "Enter new email: ";
            cin >> newemail;
            ChangeEmail(username, newemail);
            break;

        case 3:
            cout << "Enter new phone: ";
            cin >> newphone;
            ChangePhone(username, newphone);
            break;

        case 4:
            cout << "Enter new username: ";
            cin >> newusername;
            ChangeUsername(username, newusername);
            break;

        case 5:
            cout << "Do you want to enable 2FA?(Y/N): ";
            cin >> new2FA;
            DE2FA(username, new2FA);
            break;

        case 6:
            displayActivityLog(username);
            break;

        case 7:
            return;
            break;

        default:
            cout << "Invalid choice. Please select a valid option." << endl;
            break;
        }
    }

    void displayActivityLog(const string &username)
    {
        cout << "Activity Log" << endl;
        cout << "1. Transaction History" << endl;
        cout << "2. Session History" << endl;

        int achoice;
        cin >> achoice;

        switch (achoice)
        {
        case 1:
            displayTransactionHistory(username);
            break;
        case 2:
            displaySessions(username);
            break;
        default:
            cout << "Invalid choice. Please select a valid option." << endl;
            break;
        }
    }

    void viewAnalyticsDashBoard(const string &username)
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                cout << "Name: " << user.name << endl;
                cout << "-----------------------------" << endl;
                cout << "Total Networth: " << showTotalNetworth(username) << endl;
                cout << "-----------------------------" << endl;
            }
        }
        cout << "Press Enter to continue...";
        cin.get();
    }

    double showTotalNetworth(const string &username)
    {
        double totalNet = 0;

        for (const User &user : users)
        {
            if (user.username == username)
            {
                for (const Transaction &transaction : user.transactionhistory)
                {
                    if (transaction.transactionType == "Deposit")
                    {
                        totalNet += transaction.amount;
                    }
                }
            }
        }

        return totalNet;
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

                return true;
            }
        }

        cout << "User not found. Deposit failed." << endl;
        return false;
    }

    void displaySessions(const string &username)
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                for (const Session &session : user.sessions)
                {
                    cout << "Session History for User:" << user.username << endl;
                    cout << "----------------------------------------------" << endl;
                    cout << "Session ID: " << session.sessionID << endl;
                    cout << "Username: " << session.username << endl;
                    cout << "Timestamp: " << ctime(&session.timestamp) << endl;
                    cout << "----------------------------------------------" << endl;
                }
            }
        }
    }

    string generateTransactionID()
    {
        // Implement your logic to generate a unique transaction ID
        // Example: You can use a combination of timestamp and a random number
        return "TXN" + to_string(time(nullptr)) + to_string(rand());
    }

    string generateSessionID()
    {
        return "SSN" + to_string(time(nullptr)) + to_string(rand());
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

    bool makePurchase(const string &username, double amount, const string &purchaseDescription)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                if (amount <= 0.0)
                {
                    cout << "Invalid purchase amount. Please enter a positive amount." << endl;
                    return false;
                }
                // Check if the user's balance will go below -5000 after the purchase
                if (user.balance - amount < -5000.0)
                {
                    cout << "Insufficient credit limit. Purchase failed." << endl;
                    return false;
                }
                // Update user's transaction history
                Transaction purchaseTransaction;
                purchaseTransaction.transactionID = generateTransactionID();
                purchaseTransaction.transactionType = "Purchase";
                purchaseTransaction.amount = amount;
                purchaseTransaction.timestamp = time(nullptr);
                purchaseTransaction.description = purchaseDescription;
                user.transactionhistory.push_back(purchaseTransaction);
                // Update user's balance (subtract the purchase amount for a credit card)
                user.balance -= amount;
                // Save the updated user data to the file
                saveDataToFile();
                cout << "Purchase of $" << amount << " successful. Description: " << purchaseDescription << endl;
                return true;
            }
        }
        cout << "User not found. Purchase failed." << endl;
        return false;
    }
    // Function to pay bills
    bool payBills(const string &username, double amount, const string &billDescription)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                if (amount <= 0.0)
                {
                    cout << "Invalid bill amount. Please enter a positive amount." << endl;
                    return false;
                }
                if (user.balance >= amount)
                {
                    // Update user's transaction history
                    Transaction billTransaction;
                    billTransaction.transactionID = generateTransactionID();
                    billTransaction.transactionType = "Bill Payment";
                    billTransaction.amount = amount;
                    billTransaction.timestamp = time(nullptr);
                    billTransaction.description = billDescription;
                    user.transactionhistory.push_back(billTransaction);
                    // Update user's balance
                    user.balance -= amount;
                    // Save the updated user data to the file
                    saveDataToFile();
                    cout << "Bill payment of $" << amount << " successful. Description: " << billDescription << endl;
                    return true;
                }
                else
                {
                    cout << "Insufficient balance. Bill payment failed." << endl;
                    return false;
                }
            }
        }
        cout << "User not found. Bill payment failed." << endl;
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
                SaveSession(username);
                return true;
            }
        }
        return false; // Authentication failed
    }

    void setCurrentLoggedInUser(const string &username)
    {
        currentLoggedInUser = username;
    }

    void setCurrentSessionID(const string &sessionID)
    {
        currentSessionID = sessionID;
    }

    void SaveSession(const string &username)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                Session session;
                session.sessionID = generateSessionID();
                session.username = username;
                session.timestamp = time(nullptr);
                user.sessions.push_back(session);
                // Save the updated user data to the file
                saveDataToFile();
            }
        }
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

    void ChangePassword(const string &username, const string &password)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                user.password = system.encryptPass(password);
                saveDataToFile();
            }
        }
    }

    void ChangeEmail(const string &username, const string &email)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                for (Profile &profile : user.profiles)
                {
                    profile.email = email;
                    saveDataToFile();
                }
            }
        }
    }

    void ChangePhone(const string &username, const string &phone)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                for (Profile &profile : user.profiles)
                {
                    profile.phone = phone;
                    saveDataToFile();
                }
            }
        }
    }

    void ChangeUsername(const string &username, const string &newusername)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                user.username = newusername;
                saveDataToFile();
            }
        }
    }

    void DE2FA(const string &username, const char &twoFA)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                for (Profile &profile : user.profiles)
                {
                    profile.isTwoFactorEnabled = system.enable2FA(twoFA);
                    saveDataToFile();
                }
            }
        }
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
            user.producttype = item.value("producttype", "");
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

            if (item.contains("sessions"))
            {
                for (const auto &sessionItem : item["sessions"])
                {
                    Session session;
                    session.sessionID = sessionItem.value("sessionID", "");
                    session.username = sessionItem.value("username", "");
                    session.timestamp = sessionItem.value("timestamp", 0);
                    user.sessions.emplace_back(session);
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
                userJson["producttype"] = user.producttype;
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

                for (const Session &session : user.sessions)
                {
                    json sessionJson;
                    sessionJson["sessionID"] = session.sessionID;
                    sessionJson["username"] = session.username;
                    sessionJson["timestamp"] = session.timestamp;
                    userJson["sessions"].push_back(sessionJson);
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

#endif