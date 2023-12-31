#pragma once
#ifndef BANK_SYSTEM_H
#define BANK_SYSTEM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <algorithm>
#include <thread>
#include "json.hpp"
#include "SecuritySys.h"

using json = nlohmann::json;
using namespace chrono;
using namespace this_thread;

struct Transaction
{
    string transactionID;
    string transactionType;
    string description;
    double amount{};
    time_t timestamp{};
};
struct Profile
{
    string email;
    string phone;
    bool isTwoFactorEnabled{};
};
struct ProductApplication
{
    string productID;
    string producttype;
};
struct Session
{
    string sessionID;
    string username;
    time_t timestamp{};
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
    string helpandresourcesType;
    string helpandresourcesDescription;
    string feedback;
};
struct dashboard
{
    string dashboardID;
    string dashboardcontent;
};
struct Administrator
{
    string adminID;
    string name;
    string username;
    string password;
};
struct User
{
    string userID;
    string name;
    string username;
    string password;
    string producttype;
    bool iscustomerservice{};
    bool isadmin{}; // To check if the user is an admin or not
    double balance{};
    vector<Profile> profiles;
    vector<Transaction> transactionhistory;
    vector<ProductApplication> productapplications;
    vector<Session> sessions;
    vector<HelpandResources> helpandresources;
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
    vector<dashboard> dashboards;
    string currentLoggedInUser;
    string currentProductType;
    string currentSessionID;
    string dataFilePath; // Path to the data file

public:
    // [[maybe_unused]]: supress a warning on unused methods and/or variables that is issued by the compiler.
    explicit BankSystem(string dataFile) : dataFilePath(std::move(dataFile))
    {
        loadDataFromFile();
    }

    // User Interface prototype functions
    static void displayMainMenu();
    bool loginUser(string &loggedInUsername);
    void logout(const string &username);
    void forgotPassword();
    void displayDashboardMenu(const string &username);
    void handleDashboardOptions(const string &username);
    void handleProductOptions(const string &producttype, const string &username);
    void displaySavingsMenu(const string &username);
    void displayCreditMenu(const string &username);
    void displayTransactionMenu(const string &username);
    void displayTransactionCredit(const string &username);
    void displayTransactionHistory(const string &username);
    void handleTransactionCenter(const string &username);
    void handleCreditCenter(const string &username);
    void handleHelpAndResources(const string &username);

    // User prototype functions
    void processDeposit(const string &username);
    void processWithdrawal(const string &username);
    void processPurchase(const string &username);
    void processPayBills(const string &username);
    void applyForProduct();
    void displayProfile(const string &username);
    void displayUserSettings(const string &username);
    void handleAccountSettings(const string &username);
    void displayActivityLog(const string &username);
    void viewAnalyticsDashBoard(const string &username);
    static string generateTransactionID();
    void displaySessions(const string &username);
    static string generateSessionID(const string &sessiontype);
    bool withdrawFunds(const string &username, double amount);
    bool makePurchase(const string &username, double amount, const string &purchaseDescription);
    bool payBills(const string &username, double amount, const string &billDescription);
    static string generateUserID();

    // Admin prototype functions
    void adminhandleAccountSettings(const string &username);
    void admindepositFunds();
    void adminwithdrawFunds();
    void adminmakePurchase();
    void adminpayBills();
    bool deleteUserByUsername(const std::string &usernameToDelete);
    void handleManageUsers(const string &username);
    void updateUser();
    void deleteUser();
    void displayHelpHistory(const string &username);
    void displayAllHelpAndResources();
    void replyHelpAndResources();
    void displayUserDataByUsername(const std::string &usernameToDisplay) const;
    void displayAllUserData() const;

    double showInterestEarned(const string &username) // For Refactoring
    {
        double interestRate = 0.05; // Annual interest rate
        double interestEarned = 0;

        time_t now = time(nullptr); // get current time

        for (const User &user : users)
        {
            if (user.username == username)
            {
                for (const Transaction &transaction : user.transactionhistory)
                {
                    if (transaction.transactionType == "Deposit")
                    {
                        // Calculate interest for this deposit
                        double principal = transaction.amount;
                        int years = difftime(now, transaction.timestamp) / (60 * 60 * 24 * 365.25); // convert seconds to years
                        double amount = principal * pow(1 + interestRate, years);
                        double interest = amount - principal;

                        // Add to total interest earned
                        interestEarned += interest;
                    }
                }
            }
        }

        return interestEarned;
    }

    double showPaymentStatus(const string &username)
    {
        double paymentStatus = 0;

        for (const User &user : users)
        {
            if (user.username == username)
            {
                for (const Transaction &transaction : user.transactionhistory)
                {
                    if (transaction.transactionType == "Bill Payment")
                    {
                        paymentStatus += transaction.amount;
                    }
                }
            }
        }

        return paymentStatus;
    }

    double showtotalPaid(const string &username) // For Refactoring
    {
        double totalPaid = 0;

        for (const User &user : users)
        {
            if (user.username == username)
            {
                for (const Transaction &transaction : user.transactionhistory)
                {
                    if (transaction.transactionType == "Bill Payment")
                    {
                        totalPaid += transaction.amount;
                    }
                }
            }
        }

        return totalPaid;
    }

    double showtotalSpent(const string &username) // For Refactoring
    {
        double totalSpent = 0;

        for (const User &user : users)
        {
            if (user.username == username)
            {
                for (const Transaction &transaction : user.transactionhistory)
                {
                    if (transaction.transactionType == "Purchase" || transaction.transactionType == "Deposit")
                    {
                        totalSpent += transaction.amount;
                    }
                }
            }
        }

        return totalSpent;
    }

    double showTotalNetworth(const string &username) // For Refactoring
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

    bool depositFunds(const string &username, double amount) // For Refactoring
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                // Check for 2FA within profiles of the user
                for (const Profile &profile : user.profiles)
                {
                    if (profile.isTwoFactorEnabled)
                    {
                        cout << "\nSending an OTP for 2 Factor Authentication." << endl;
                        system.sendOTP();

                        string inputOTP;
                        cout << "\nEnter your OTP: ";
                        cin >> inputOTP;
                        cin.ignore();

                        if (!system.verifyOTP(inputOTP))
                        {
                            cout << "\n*Incorrect OTP. Timeout for 30 seconds..." << endl;
                            sleep_for(seconds(30));
                            return false;
                        }
                    }
                }

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
        return false;
    }

    static string generateProductID(const string &producttype)
    {
        if (producttype == "Savings Account")
        {
            return "SAV" + to_string(time(nullptr)) + to_string(rand());
        }
        if (producttype == "Credit Account")
        {
            return "CRD" + to_string(time(nullptr)) + to_string(rand());
        }
        else
        {
            return "PRD" + to_string(time(nullptr)) + to_string(rand());
        }
    }

    bool authenticateUser(const string &username, const string &password)
    {
        auto user_it = find_if(users.begin(), users.end(),
                               [&](const User &user)
                               { return user.username == username; });

        // User not found.
        if (user_it == users.end())
        {
            return false;
        }

        string decryptedPass = SecuritySys::decryptPass(user_it->password);

        if (!system.attemptLogin(decryptedPass, password))
        {
            return false; // Incorrect password
        }

        // Check for 2FA within profiles of the user
        for (const Profile &profile : user_it->profiles)
        {
            if (profile.isTwoFactorEnabled)
            {
                cout << "\n---Sending an OTP for 2 Factor Authentication---" << endl;
                system.sendOTP();

                string inputOTP;
                cout << "\nEnter your OTP: ";
                cin >> inputOTP;
                cin.ignore();

                if (!system.verifyOTP(inputOTP))
                {
                    cout << "\n*Incorrect OTP. Timeout for 30 seconds..." << endl;
                    sleep_for(seconds(30));
                    return false;
                }
            }
        }
        SaveSession(username, "Login");
        return true; // Successful authentication
    }

    void setCurrentLoggedInUser(const string &username)
    {
        currentLoggedInUser = username;
    }

    void setCurrentSessionID(const string &sessionID)
    {
        currentSessionID = sessionID;
    }

    void SaveSession(const string &username, const string &sessiontype)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                Session session;
                session.sessionID = generateSessionID(sessiontype);
                session.username = username;
                session.timestamp = time(nullptr);
                user.sessions.push_back(session);

                // Save the updated user data to the file
                saveDataToFile();
                system.auditLog(true);
                return; // Exit the function once the session is saved for the user.
            }
        }
        // If we've reached here, it means the user wasn't found.
        system.auditLog(false);
    }

    static bool isValidProductType(const string &producttype)
    {
        // Define a list of valid product types in your system
        vector<string> validProductTypes = {"Savings Account", "Credit Account"};

        // Check if the provided product type is in the list of valid types
        return find(validProductTypes.begin(), validProductTypes.end(), producttype) != validProductTypes.end();
    }

    void setCurrentProductType(const string &producttype)
    {
        if (!isValidProductType(producttype))
        {
            cout << "Invalid product type." << endl;
            // Handle the error or return an error code if necessary
            return;
        }

        currentProductType = producttype;
    }

    // [[nodiscard]]: indicates that return value of a function shouldn't be ignored.
    [[nodiscard]] string getCurrentProductType(const string &username) const
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                return user.producttype;
            }
        }
        // If we've reached here, the user wasn't found
        return "Unknown"; // You can choose a different indicator if needed
    }

    [[nodiscard]] bool isUsernameTaken(const string &username) const
    {
        return std::any_of(users.begin(), users.end(),
                           [&username](const User &user)
                           { return user.username == username; });
    }

    [[nodiscard]] double getCurrentBalance(const string &username) const
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                return user.balance;
            }
        }

        // If we've reached here, the user wasn't found
        return -1.0; // Choose a different indicator if needed
    }

    bool isadmin(const string &username)
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                return user.isadmin;
            }
        }
        return false;
    }

    bool iscustomerservice(const string &username)
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                return user.iscustomerservice;
            }
        }
        return false;
    }

    void chatBot(const string &message, const string &username)
    {
        string feedback; // Declare the feedback variable once.

        // Checks if user's message indicates they've forgotten their password.
        if (regex_search(message, regex("(forgot)(.*)(password)", regex_constants::icase)))
        {
            feedback = "It seems like you've forgotten your password. Don't worry, you can reset it by clicking the 'Forgot Password?' button and following the instructions provided.";
            cout << feedback;
        }

        // Responds to requests for a guide or tutorial.
        if (regex_search(message, regex("(guide)", regex_constants::icase)))
        {
            feedback = "Looking for a guide? We have comprehensive documentation and tutorials available to help you navigate through our system.";
            cout << feedback;
        }

        // Directs users to a transaction guide if they mention "transact".
        if (regex_search(message, regex("(transact)", regex_constants::icase)))
        {
            feedback = "You're interested in making a transaction? At the moment, we don't have a specific answer for this. Please refer to our transaction guide for more details.";
            cout << feedback;
        }

        // Provides information on how to contact customer service.
        if (regex_search(message, regex("(contact)", regex_constants::icase)))
        {
            feedback = "Need to get in touch? Our customer service team is always ready to help. You can reach us through our Contact Us page.";
            cout << feedback;
        }

        // Assists users with inquiries about their credit limit.
        if (regex_search(message, regex("(credit)(.*)(limit)", regex_constants::icase)))
        {
            feedback = "Inquiring about your credit limit? You can check this information in your account settings under the 'Credit Limit' section.";
            cout << feedback;
        }

        SaveHelpandResources(username, "AI", message, feedback);
    }

    void askHelp(const string &username)
    {
        string message;
        cout << "Enter your message: ";

        // Clear any remaining newline characters from the input stream
        cin.ignore();

        getline(cin, message);

        SaveHelpandResources(username, "Help", message, "");
    }

    void SaveHelpandResources(const string &username, const string &helpandresourcesType, const string &helpandresourcesDescription, const string &feedback)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                // Create a new HelpandResources object
                HelpandResources helpandresources;
                helpandresources.helpID = generateHelpID(helpandresourcesType);
                helpandresources.helpandresourcesType = helpandresourcesType;
                helpandresources.helpandresourcesDescription = helpandresourcesDescription;
                helpandresources.feedback = feedback;

                // Push the new helpandresources object into the user's vector
                user.helpandresources.push_back(helpandresources);

                // Save the updated user data to the file
                saveDataToFile();

                // Log the action as successful
                system.auditLog(true);

                return; // Exit the function once the session is saved for the user.
            }
        }
        // If we've reached here, it means the user wasn't found.
        system.auditLog(false);
    }

    string generateHelpID(const string &helpandresourcesType)
    {
        if (helpandresourcesType == "AI")
        {
            return "HAI" + to_string(time(nullptr)) + to_string(rand());
        }
        else if (helpandresourcesType == "Help")
        {
            return "HLP" + to_string(time(nullptr)) + to_string(rand());
        }
        else
        {
            return "HSR" + to_string(time(nullptr)) + to_string(rand());
        }
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
        newUser.userID = generateUserID(); // Call a function to generate a unique user ID
        newUser.name = name;
        newUser.username = username;
        newUser.password = SecuritySys::encryptPass(password);
        newUser.isadmin = false;
        newUser.producttype = producttype;
        newUser.balance = 0.0;

        // Create a new profile for the user
        Profile newProfile;
        newProfile.email = email;
        newProfile.phone = phone;
        newProfile.isTwoFactorEnabled = SecuritySys::enable2FA(twoFA);

        ProductApplication newProductApplication;
        newProductApplication.producttype = producttype;
        newProductApplication.productID = generateProductID(producttype);

        newUser.productapplications.push_back(newProductApplication);
        // Add the new profile to the user's profiles vector
        newUser.profiles.push_back(newProfile);

        // Add the new user to the vector of users
        users.push_back(newUser);

        // Save the updated user data to the file
        saveDataToFile();

        cout << "\nUser account created successfully." << endl;
        return true;
    }

    void makeUserAdmin(const string &username)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                user.isadmin = true;
                cout << "User " << user.username << " is now an admin." << endl;
                saveDataToFile();
            }
        }
    }

    void makeUserCustomerService(const string &username)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                user.iscustomerservice = true;
                cout << "User " << user.username << " is now a customer service." << endl;
                saveDataToFile();
            }
        }
    }

    void ChangePassword(const string &username, const string &password)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                for (Profile &profile : user.profiles)
                {
                    if (profile.isTwoFactorEnabled)
                    {
                        cout << "\nSending an OTP for 2 Factor Authentication." << endl;
                        system.sendOTP();

                        string inputOTP;
                        cout << "\nEnter your OTP: ";
                        cin >> inputOTP;
                        cin.ignore();

                        if (!system.verifyOTP(inputOTP))
                        {
                            cout << "\n*Incorrect OTP. Timeout for 30 seconds..." << endl;
                            sleep_for(seconds(30));
                            return;
                        }
                    }
                    user.password = SecuritySys::encryptPass(password);
                    string decrypass = SecuritySys::decryptPass(user.password);
                    cout << "Password changed to " << decrypass << " successfully." << endl;
                    saveDataToFile();
                }
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
                    if (profile.isTwoFactorEnabled)
                    {
                        cout << "\nSending an OTP for 2 Factor Authentication." << endl;
                        system.sendOTP();

                        string inputOTP;
                        cout << "\nEnter your OTP: ";
                        cin >> inputOTP;
                        cin.ignore();

                        if (!system.verifyOTP(inputOTP))
                        {
                            cout << "\n*Incorrect OTP. Timeout for 30 seconds..." << endl;
                            sleep_for(seconds(30));
                            return;
                        }
                    }
                    profile.email = email;
                    cout << "Email changed to " << profile.email << " successfully." << endl;
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
                    if (profile.isTwoFactorEnabled)
                    {
                        cout << "\nSending an OTP for 2 Factor Authentication." << endl;
                        system.sendOTP();

                        string inputOTP;
                        cout << "\nEnter your OTP: ";
                        cin >> inputOTP;
                        cin.ignore();

                        if (!system.verifyOTP(inputOTP))
                        {
                            cout << "\n*Incorrect OTP. Timeout for 30 seconds..." << endl;
                            sleep_for(seconds(30));
                            return;
                        }
                    }
                    profile.phone = phone;
                    cout << "Phone changed to " << profile.phone << " successfully." << endl;
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
                for (Profile &profile : user.profiles)
                {
                    if (profile.isTwoFactorEnabled)
                    {
                        cout << "\nSending an OTP for 2 Factor Authentication." << endl;
                        system.sendOTP();

                        string inputOTP;
                        cout << "\nEnter your OTP: ";
                        cin >> inputOTP;
                        cin.ignore();

                        if (!system.verifyOTP(inputOTP))
                        {
                            cout << "\n*Incorrect OTP. Timeout for 30 seconds..." << endl;
                            sleep_for(seconds(30));
                            return;
                        }
                    }
                    user.username = newusername;
                    cout << "Username changed to " << user.username << " successfully." << endl;
                    saveDataToFile();
                }
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
                    if (profile.isTwoFactorEnabled)
                    {
                        cout << "\nSending an OTP for 2 Factor Authentication." << endl;
                        system.sendOTP();

                        string inputOTP;
                        cout << "\nEnter your OTP: ";
                        cin >> inputOTP;
                        cin.ignore();

                        if (!system.verifyOTP(inputOTP))
                        {
                            cout << "\n*Incorrect OTP. Timeout for 30 seconds..." << endl;
                            sleep_for(seconds(30));
                            return;
                        }
                    }
                    profile.isTwoFactorEnabled = SecuritySys::enable2FA(twoFA);
                    string show2FAStatus = profile.isTwoFactorEnabled ? "Enabled" : "Disabled";
                    cout << "Two Factor Authentication: " << show2FAStatus << endl;
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
            system.auditLog(false);
            return;
        }

        json j;
        file >> j;
        file.close();

        for (const auto &item : j)
        {
            User user;
            user.userID = item.value("id", "");
            user.name = item.value("name", "");
            user.username = item.value("username", "");
            user.isadmin = item.value("isadmin", false);
            user.iscustomerservice = item.value("iscustomerservice", false);
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
                    transaction.description = transactionItem.value("description", "");
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

            if (item.contains("productapplications"))
            {
                for (const auto &productapplicationItem : item["productapplications"])
                {
                    ProductApplication productapplication;
                    productapplication.producttype = productapplicationItem.value("producttype", "");
                    productapplication.productID = productapplicationItem.value("productID", "");
                    user.productapplications.emplace_back(productapplication);
                }
            }

            if (item.contains("helpandresources"))
            {
                for (const auto &helpandresourcesItem : item["helpandresources"])
                {
                    HelpandResources resources;
                    resources.helpID = helpandresourcesItem.value("helpandresourcesID", "");
                    resources.helpandresourcesType = helpandresourcesItem.value("helpandresourcesType", "");
                    resources.helpandresourcesDescription = helpandresourcesItem.value("helpandresourcesDescription", "");
                    user.helpandresources.emplace_back(resources);
                }
            }
            users.emplace_back(user);
            system.auditLog(true);
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
                system.auditLog(true);
                return;
            }
            json j;
            for (const User &user : users)
            {
                json userJson;
                userJson["id"] = user.userID;
                userJson["name"] = user.name;
                userJson["username"] = user.username;
                userJson["password"] = user.password;
                userJson["isadmin"] = user.isadmin;
                userJson["iscustomerservice"] = user.iscustomerservice;
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
                    transactionJson["description"] = transaction.description;
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
                for (const ProductApplication &productapplication : user.productapplications)
                {
                    json productapplicationJson;
                    productapplicationJson["producttype"] = productapplication.producttype;
                    productapplicationJson["productID"] = productapplication.productID;
                    userJson["productapplications"].push_back(productapplicationJson);
                }
                for (const HelpandResources &resources : user.helpandresources)
                {
                    json helpandresourcesJson;
                    helpandresourcesJson["helpandresourcesID"] = resources.helpID;
                    helpandresourcesJson["helpandresourcesType"] = resources.helpandresourcesType;
                    helpandresourcesJson["helpandresourcesDescription"] = resources.helpandresourcesDescription;
                    userJson["helpandresources"].push_back(helpandresourcesJson);
                }
                j.push_back(userJson);
            }
            file << j.dump(4);
            file.close();
        }
        catch (const json::exception &e) // catching specific exceptions related to the json library
        {
            cout << "JSON error: " << e.what() << endl;
            system.auditLog(false);
        }
        catch (const exception &e) // generic C++ exceptions
        {
            cout << "Error saving data to file: " << e.what() << endl;
            system.auditLog(false);
        }
    }
};

#endif
