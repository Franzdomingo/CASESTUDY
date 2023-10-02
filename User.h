#pragma once
#ifndef USER_H
#define USER_H

#include "BankSystem.h"

inline string BankSystem::generateUserID()
{
    // Implement your logic to generate a unique transaction ID
    // Example: You can use a combination of timestamp and a random number
    return "USR" + to_string(time(nullptr)) + to_string(rand());
}

inline string BankSystem::generateTransactionID()
{
    // Implement your logic to generate a unique transaction ID
    // Example: You can use a combination of timestamp and a random number
    return "TXN" + to_string(time(nullptr)) + to_string(rand());
}

inline string BankSystem::generateSessionID(const string &sessiontype)
{
    if (sessiontype == "Login")
    {
        return "LGN" + to_string(time(nullptr)) + to_string(rand());
    }
    if (sessiontype == "Logout")
    {
        return "LGT" + to_string(time(nullptr)) + to_string(rand());
    }
    else
    {
        return "SSN" + to_string(time(nullptr)) + to_string(rand());
    }
}

inline bool BankSystem::withdrawFunds(const string &username, double amount)
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

                    if (!system.verifyOTP(inputOTP))
                    {
                        cout << "\n*Incorrect OTP. Timeout for 30 seconds..." << endl;
                        sleep_for(seconds(30));
                        return false;
                    }
                }
            }

            if (amount <= 0.0)
            {
                cout << "*Invalid withdrawal amount. Please enter a positive amount." << endl;
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
                cout << "\n*Insufficient balance. Withdrawal failed." << endl;
                return false;
            }
        }
    }

    cout << "*User not found. Withdrawal failed." << endl;
    return false;
}

inline bool BankSystem::makePurchase(const string &username, double amount,
                                     const string &purchaseDescription) // For Refactoring
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

                    if (!system.verifyOTP(inputOTP))
                    {
                        cout << "\n*Incorrect OTP. Timeout for 30 seconds..." << endl;
                        sleep_for(seconds(30));
                        return false;
                    }
                }
            }

            if (amount <= 0.0)
            {
                cout << "*Invalid purchase amount. Please enter a positive amount." << endl;
                return false;
            }

            // Check if the user's balance will go below -5000 after the purchase
            if (user.balance - amount < -5000.0)
            {
                cout << "*Insufficient credit limit. Purchase failed." << endl;
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
    cout << "*User not found. Purchase failed." << endl;
    return false;
}

inline bool BankSystem::payBills(const string &username,
                                 double amount, const string &billDescription) // For Refactoring
{
    for (User &user : users)
    {
        if (user.username == username)
        {
            for (const Profile &profile : user.profiles)
            {
                if (profile.isTwoFactorEnabled)
                {
                    cout << "\nSending an OTP for 2 Factor Authentication." << endl;
                    system.sendOTP();

                    string inputOTP;
                    cout << "\nEnter your OTP: ";
                    cin >> inputOTP;

                    if (!system.verifyOTP(inputOTP))
                    {
                        cout << "\n*Incorrect OTP. Timeout for 30 seconds..." << endl;
                        sleep_for(seconds(30));
                        return false;
                    }
                }
            }

            if (amount <= 0.0)
            {
                cout << "*Invalid bill amount. Please enter a positive amount." << endl;
                return false;
            }
            if (user.balance <= amount)
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
                user.balance += amount;
                // Save the updated user data to the file
                saveDataToFile();
                cout << "Bill payment of $" << amount << " successful. Description: " << billDescription << endl;
                return true;
            }
            else
            {
                cout << "*Insufficient balance. Bill payment failed." << endl;
                return false;
            }
        }
    }
    cout << "*User not found. Bill payment failed." << endl;
    return false;
}

#endif
