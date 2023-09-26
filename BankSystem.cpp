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
    vector<User> users;
    string currentLoggedInUser;
    string dataFilePath;
    string currentProductType;

public:
    BankSystem(const string &dataFile) : dataFilePath(dataFile)
    {
        loadDataFromFile();
    }
    // Display Transaction History
    void displayTransactionHistory(const string &username)
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
            }
        }
    }

    void displayProfile(const string &username)
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                cout << "User Profile" << endl;
                cout << "--------------------------------" << endl;
                cout << "Name: " << user.username << endl;
                for (const Profile &profile : user.profiles)
                {
                    cout << "Email: " << profile.email << endl;
                    cout << "Phone: " << profile.phone << endl;
                    cout << "Two Factor Authentication: " << endl;
                    cout << profile.isTwoFactorEnabled ? "Enabled" : "Disabled";
                    cout << "\n--------------------------------" << endl;
                }
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
                        cout << "Enter the OTP: ";
                        string inputOTP;
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

    bool createUser(const string &username, const string &password, const string &email, const string &phone, const char &twoFA, const string &producttype, const string &name)
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

    // Load user data from the file into memory
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
            user.username = item.value("username", "");
            user.producttype = item.value("producttype", "");
            user.name = item.value("name", "");
            user.password = item.value("password", "");
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

    // Save user data from memory to the file
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
                userJson["username"] = user.username;
                userJson["producttype"] = user.producttype;
                userJson["name"] = user.name;
                userJson["password"] = user.password;
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
    while (true)
    {
    login:
        string username, password, email, phone, name;
        char enable2FA;
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
                dashboard:
                    string message;

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
                            if (productType == "Savings Account")
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
                                    system("pause");
                                    break;

                                case 4:
                                    goto dashboard;
                                    // Back to Dashboard
                                    break;

                                default:
                                    cout << "Invalid choice. Please select a valid option." << endl;
                                }
                            }

                            break;
                        case 2:
                            bank.displayProfile(username);
                            break;
                        case 3:
                            // Implement Data Analytics Dashboard here
                            // Provide analytics and insights based on user data
                            break;
                        case 4:
                            ChatAI ai;
                            cout << "Hi! I'm your AI Assistant. How may I help you?" << endl;
                            cin >> message;
                            cin.clear();

                            ai.chatBot(message);

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
            getline(cin, username);

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

            cout << "Do you want to enable 2FA?(Y/N): ";
            cin >> enable2FA;

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
            bool registrationSuccess = bank.createUser(username, password, email, phone, enable2FA, accounttype, name);
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
            break;
        }
    }
    return 0;
}
