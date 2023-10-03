#pragma once
#ifndef USER_H
#define USER_H

#include "BankSystem.h"

inline void BankSystem::processDeposit(const string &username)
{
    double depositAmount;
    cout << "\nEnter the amount to deposit: $";
    cin >> depositAmount;
    cin.ignore(); // Clear the newline character

    if (depositAmount <= 0.0)
    {
        cout << "*Invalid deposit amount. Please enter a positive amount." << endl;
        return;
    }

    if (depositFunds(username, depositAmount))
    {
        cout << " " << endl;
        cout << "Deposit of $" << depositAmount << " successful." << endl;
    }
    else
    {
        cout << "*Deposit failed. Please try again." << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.get();
}

inline void BankSystem::processWithdrawal(const string &username)
{
    double withdrawAmount;
    cout << "\nEnter the amount to withdraw: $";
    cin >> withdrawAmount;
    cin.ignore(); // Clear the newline character

    if (withdrawAmount <= 0.0)
    {
        cout << "*Invalid withdrawal amount. Please enter a positive amount." << endl;
        return;
    }

    if (withdrawFunds(username, withdrawAmount))
    {
        cout << "\nWithdrawal of $" << withdrawAmount << " successful." << endl;
    }
    else
    {
        cout << "*Withdrawal failed. Please try again." << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.get();
}

inline void BankSystem::processPurchase(const string &username)
{
    double purchaseAmount;
    cout << "\nEnter the purchase amount: $";
    cin >> purchaseAmount;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "*Invalid amount. Please enter a valid number." << endl;
    }
    cin.ignore(); // Clear the newline character
    if (purchaseAmount <= 0.0)
    {
        cout << "*Invalid transaction amount. Please enter a positive amount." << endl;
    }
    if (makePurchase(username, purchaseAmount, "Purchase description"))
    {
        cout << "Purchase of $" << purchaseAmount << " successful." << endl;
    }
    else
    {
        cout << "*Purchase failed. Please try again." << endl;
    }
    cout << " " << endl;
    cout << "Press Enter to continue...";
    cin.get();
}

inline void BankSystem::processPayBills(const string &username)
{
    double billAmount;
    cout << "\nEnter the bill amount: $";
    cin >> billAmount;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "*Invalid amount. Please enter a valid number." << endl;
    }
    cin.ignore(); // Clear the newline character
    if (billAmount <= 0.0)
    {
        cout << "*Invalid amount. Please enter a positive amount." << endl;
    }
    if (payBills(username, billAmount, "Bill description"))
    {
        cout << "Bill payment of $" << billAmount << " successful." << endl;
    }
    else
    {
        cout << "*Bill payment failed. Please try again." << endl;
    }

    cout << " " << endl;
    cout << "Press Enter to continue...";
    cin.get();
}

inline void BankSystem::applyForProduct()
{
    string name, username, password, email, phone, accounttype;
    int acctype;
    char enable2FA;
    while (true)
    {
        cout << " " << endl;
        cout << "╔═════════════════════════════════════╗    " << endl;
        cout << "║       Product Application           ║   " << endl;
        cout << "╚═════════════════════════════════════╝    " << endl;
        cout << " " << endl;
        cout << "Enter your full name: ";
        getline(cin, name);

        cout << "Enter username: ";
        getline(cin, username);

        // Check if the username is already taken
        bool usernameTaken = isUsernameTaken(username);
        if (usernameTaken)
        {
            cout << "\n*Username is already taken. Please choose another one." << endl;
            cout << " " << endl;
            cout << "Press Enter to continue...";
            cin.get();
            continue;
        }

        cout << "Enter password: ";
        cin >> password;

        cout << "Enter email: ";
        cin >> email;

        cout << "Enter phone: ";
        cin >> phone;

        cout << "\nDo you want to enable 2FA?(Y/N): ";
        cin >> enable2FA;

        cout << "\nPick account type: " << endl;
        cout << "1. Savings Account" << endl;
        cout << "2. Credit Account" << endl;

        cout << "\nChoose your account type: ";
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
            cout << "*Invalid choice. Please select a valid option." << endl;
            continue;
        }

        // Create a new user account
        bool registrationSuccess = createUser(name, username, password, email, phone, enable2FA, accounttype);
        if (registrationSuccess)
        {
            cout << "Registration successful!" << endl;
            cout << " " << endl;
            cout << "Press Enter to continue...";
            cin.get();
            break;
        }
        else
        {
            cout << "*Registration failed. Please try again." << endl;
            continue;
        }
    }
}

inline void BankSystem::handleAccountSettings(const string &username)
{
    string newpass, newemail, newphone, newusername;
    char new2FA;
    cout << " " << endl;
    cout << "╔═════════════════════════════════════╗    " << endl;
    cout << "║           Manage Account            ║   " << endl;
    cout << "╠═════════════════════════════════════╣    " << endl;
    cout << "║  1. Change Password                 ║" << endl;
    cout << "║  2. Change Email                    ║" << endl;
    cout << "║  3. Change Phone                    ║" << endl;
    cout << "║  4. Change Username                 ║" << endl;
    cout << "║  5. Enable/Disable 2FA              ║" << endl;
    cout << "║  6. Show Activity Log               ║" << endl;
    cout << "║  7. Back to Profile                 ║" << endl;
    cout << "╚═════════════════════════════════════╝   " << endl;
    cout << " " << endl;

    int mchoice;
    cout << "\nEnter: ";
    cin >> mchoice;
    switch (mchoice)
    {
    case 1:
        cout << "\nEnter new password: ";
        cin >> newpass;
        ChangePassword(username, newpass);
        break;

    case 2:
        cout << "\nEnter new email: ";
        cin >> newemail;
        ChangeEmail(username, newemail);
        break;

    case 3:
        cout << "\nEnter new phone: ";
        cin >> newphone;
        ChangePhone(username, newphone);
        break;

    case 4:
        cout << "\nEnter new username: ";
        cin >> newusername;
        ChangeUsername(username, newusername);
        break;

    case 5:
        cout << "\nDo you want to enable 2FA?(Y/N): ";
        cin >> new2FA;
        DE2FA(username, new2FA);
        break;

    case 6:
        displayActivityLog(username);
        break;

    case 7:
        return;

    default:
        cout << "*Invalid choice. Please select a valid option." << endl;
        break;
    }
}

inline void BankSystem::displayProfile(const string &username)
{
    for (const User &user : users)
    {
        if (user.username == username)
        {
            for (const Profile &profile : user.profiles)
            {
                string show2FAStatus = profile.isTwoFactorEnabled ? "Enabled" : "Disabled";
                cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
                cout << "                      User Profile                            " << endl;
                cout << "══════════════════════════════════════════════════════════════" << endl;
                cout << "  Name: " << user.name << endl;
                cout << "  Username: " << user.username << endl;
                cout << "  Email: " << profile.email << endl;
                cout << "  Phone: " << profile.phone << endl;
                cout << "  Account: " << user.producttype << endl;
                cout << "  Two Factor Authentication: " << show2FAStatus << endl;
                cout << "══════════════════════════════════════════════════════════════" << endl;
                displayUserSettings(user.username);
            }
        }
    }
}

inline void BankSystem::displayUserSettings(const string &username)
{

    while (true)
    {
        cout << " " << endl;
        cout << "╭────────────────────────╮" << endl;
        cout << "│     User Settings      │" << endl;
        cout << "├────────────────────────┤" << endl;
        cout << "│ 1. Manage Account      │" << endl;
        cout << "│ 2. Back to Dashboard   │" << endl;
        cout << "╰────────────────────────╯" << endl;
        cout << " " << endl;

        int pchoice;
        cout << "Enter: ";
        cin >> pchoice;
        cout << endl;
        switch (pchoice)
        {
        case 1:
            handleAccountSettings(username);
            break;

        case 2:
            return;
            // break;

        default:
            cout << "Invalid choice. Please select a valid option." << endl;
            break;
        }
    }
}

inline void BankSystem::displayActivityLog(const string &username)
{
    cout << " " << endl;
    cout << "╭───────────────────────────╮" << endl;
    cout << "│      Activity Log         │" << endl;
    cout << "├───────────────────────────┤" << endl;
    cout << "│ 1. Transaction History    │" << endl;
    cout << "│ 2. Session History        │" << endl;
    cout << "│ 3. Help History           │" << endl;
    cout << "╰───────────────────────────╯" << endl;
    cout << " " << endl;

    int achoice;
    cout << "Enter: ";
    cin >> achoice;

    switch (achoice)
    {
    case 1:
        displayTransactionHistory(username);
        break;
    case 2:
        displaySessions(username);
        break;
    case 3:
        displayHelpHistory(username);
        break;
    default:
        cout << "*Invalid choice. Please select a valid option." << endl;
        break;
    }
}

inline void BankSystem::displaySessions(const string &username)
{
    for (const User &user : users)
    {
        if (user.username == username)
        {
            cout << " " << endl;
            cout << "╔════════════════════════════════════════════╗    " << endl;
            cout << "║               Session History              ║    " << endl;
            cout << "╚════════════════════════════════════════════╝    " << endl;
            cout << " User: " << user.username << endl;
            cout << "──────────────────────────────────────────────" << endl;
            for (const Session &session : user.sessions)
            {
                cout << "Session ID: " << session.sessionID << endl;
                cout << "Username: " << session.username << endl;
                cout << "Timestamp: " << ctime(&session.timestamp);
                cout << "──────────────────────────────────────────────" << endl;
            }
        }
    }
}

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
