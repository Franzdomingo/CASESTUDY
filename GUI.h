#pragma once
#ifndef GUI_H
#define GUI_H

#include <windows.h>
#include "User.h"
#include "BankSystem.h"

inline void BankSystem::displayMainMenu()
{
    SetConsoleOutputCP(CP_UTF8);
    cout << "\n"
         << endl;
    cout << "════════════════════════════════════════    " << endl;
    cout << "┌──────────────────────────────────────┐ " << endl;
    cout << "│             Bank System              │   " << endl;
    cout << "└──────────────────────────────────────┘   " << endl;
    cout << "════════════════════════════════════════    " << endl;
    cout << "                                            " << endl;
    cout << "┌──────────────────────────────────────┐ " << endl;
    cout << "│ ┌──────────────────────────────────┐ │   " << endl;
    cout << "│ │  1. Login                        │ │   " << endl;
    cout << "│ │  2. Product Application          │ │   " << endl;
    cout << "│ │  3. Forgot Password              │ │   " << endl;
    cout << "│ │  4. Exit                         │ │   " << endl;
    cout << "│ └──────────────────────────────────┘ │   " << endl;
    cout << "└──────────────────────────────────────┘   " << endl;
    cout << "                                           " << endl;
    cout << "Enter your choice: ";
}

inline bool BankSystem::loginUser(string &loggedInUsername)
{
    cout << "╔═════════════════════════════════════╗    " << endl;
    cout << "║                Login                ║    " << endl;
    cout << "╚═════════════════════════════════════╝    " << endl;
    cout << "  " << endl;
    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    if (isadmin(username))
    {
        cout << " " << endl;
        cout << "        ---Administrator---" << endl;
        cout << " " << endl;
        cout << "Press Enter to continue...";
        cin.get();
        return true;
    }

    if (authenticateUser(username, password))
    {
        loggedInUsername = username;

        setCurrentLoggedInUser(loggedInUsername);
        cout << " " << endl;
        cout << "        ---Login successful!---" << endl;
        cout << " " << endl;
        cout << "Press Enter to continue...";
        cin.get();
        return true;
    }
    else
    {
        cout << " " << endl;
        cout << "*Invalid username or password. Please try again." << endl;
        cout << " " << endl;
        cout << "Press Enter to continue...";
        cin.get();
        return false;
    }
}

inline void BankSystem::logout(const string &username)
{
    auto it = std::find_if(users.begin(), users.end(),
                           [&username](const User &user)
                           { return user.username == username; });

    if (it != users.end())
    {
        SaveSession(username, "Logout");
        cout << "Logged out successfully." << endl;
    }
}

inline void BankSystem::forgotPassword()
{
    cout << "╭────────────────────────────────────────────────────────────╮" << endl;
    cout << "│                     Forgot Password                        │" << endl;
    cout << "╰────────────────────────────────────────────────────────────╯" << endl;
    [[maybe_unused]] char choice;
    cout << "\nEnter your email: ";
    string email;
    cin >> email;
    bool emailFound = false; // To track whether the email was found or not

    for (User &user : users)
    {
        for (Profile &profile : user.profiles)
        {
            if (profile.email == email)
            {
                cout << "\n                    ---Email found!---" << endl;
                cout << "\nSending an OTP for " << profile.email << " 2 Factor Authentication." << endl;

                system.sendOTP();

                string inputOTP;
                cout << "\nEnter your OTP: ";
                cin >> inputOTP;
                if (!system.verifyOTP(inputOTP))
                {
                    cout << "\n*Incorrect OTP. Timeout for 30 seconds..." << endl;

                    sleep_for(seconds(30));
                    return;
                }
                cout << "\n──────────────────────────────────────────────────────────────" << endl;
                cout << "\nEnter new password: ";
                string newpass;
                cin >> newpass;
                ChangePassword(user.username, newpass);
                cout << "\n            ---Password changed successfully!---" << endl;
                emailFound = true; // Mark the email as found
            }
        }
    }

    if (!emailFound)
    {
        cout << "\n*Email not found. Please try again." << endl;
    }
    cout << " " << endl;
    cout << "Press Enter to continue...";
    cin.get();
}

inline void BankSystem::displayDashboardMenu(const string &username)
{
    for (const User &user : users)
    {
        if (user.username == username)
        {
            SetConsoleOutputCP(CP_UTF8);
            cout << " " << endl;

            cout << "╭──────────────────────────────────────╮" << endl;
            cout << "│             Bank System              │" << endl;
            cout << "╰──────────────────────────────────────╯" << endl;
            cout << " " << endl;
            cout << " Welcome " << user.name << "!" << endl;
            cout << "  " << endl;
            cout << " Current Balance: $" << getCurrentBalance(username) << endl;
            cout << "                                           " << endl;
            cout << "╔═════════════════════════════════════╗    " << endl;
            cout << "║         Dashboard Options:          ║     " << endl;
            cout << "╠═════════════════════════════════════╣    " << endl;
            cout << "║  1. Transaction Center              ║     " << endl;
            cout << "║  2. User Profile                    ║     " << endl;
            cout << "║  3. Data Analytics Dashboard        ║     " << endl;
            cout << "║  4. Help & Resources                ║     " << endl;
            cout << "║  5. Logout                          ║     " << endl;
            cout << "╚═════════════════════════════════════╝" << endl;
            cout << " " << endl;
            cout << "Enter your choice: ";
        }
    }
}

inline void BankSystem::handleDashboardOptions(const string &username)
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
            logout(username);
            setCurrentLoggedInUser("");
            cout << "Press Enter to continue...";
            cin.get();
            return;
        default:
            cout << "*Invalid choice. Please select a valid option." << endl;
        }
    }
}

inline void BankSystem::handleProductOptions(const string &producttype, const string &username)
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

inline void BankSystem::displaySavingsMenu(const string &username)
{
    handleTransactionCenter(username);
}

inline void BankSystem::displayCreditMenu(const string &username)
{
    handleCreditCenter(username);
}

inline void BankSystem::displayTransactionMenu(const string &username)
{
    cout << " " << endl;
    cout << "╔═════════════════════════════════════╗    " << endl;
    cout << "║         Transaction Center:         ║    " << endl;
    cout << "╠═════════════════════════════════════╣    " << endl;
    cout << "║  1. Deposit Funds                   ║     " << endl;
    cout << "║  2. Withdraw Funds                  ║     " << endl;
    cout << "║  3. View Transaction History        ║     " << endl;
    cout << "║  4. Back to Dashboard               ║    " << endl;
    cout << "╚═════════════════════════════════════╝    " << endl;
    cout << " " << endl;
    cout << "Enter your choice: ";
    setCurrentLoggedInUser(username);
}

inline void BankSystem::displayTransactionCredit(const string &username)
{
    cout << " " << endl;
    cout << "╔═════════════════════════════════════╗    " << endl;
    cout << "║         Transaction Center:         ║    " << endl;
    cout << "╠═════════════════════════════════════╣    " << endl;
    cout << "║  1. Make a Purchase                 ║     " << endl;
    cout << "║  2. Pay Bills                       ║     " << endl;
    cout << "║  3. View Transaction History        ║     " << endl;
    cout << "║  4. Back to Dashboard               ║    " << endl;
    cout << "╚═════════════════════════════════════╝     " << endl;
    cout << " " << endl;
    cout << "Enter your choice: ";
    setCurrentLoggedInUser(username);
}

inline void BankSystem::displayTransactionHistory(const string &username)
{
    for (const User &user : users)
    {
        if (user.username == username)
        {
            cout << "╔═════════════════════════════════════╗    " << endl;
            cout << "║        Transaction History          ║    " << endl;
            cout << "╚═════════════════════════════════════╝    " << endl;
            cout << " User: " << user.username << endl;
            cout << "───────────────────────────────────────" << endl;
            for (const Transaction &transaction : user.transactionhistory)
            {
                cout << "Transaction ID: " << transaction.transactionID << endl;
                cout << "Transaction Type: " << transaction.transactionType << endl;
                cout << "Amount: $" << transaction.amount << endl;
                cout << "Timestamp: " << ctime(&transaction.timestamp);
                cout << "───────────────────────────────────────" << endl;
            }
        }
    }
}

inline void BankSystem::handleTransactionCenter(const string &username)
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
            cout << " " << endl;
            break;
        case 4:
            return; // Return to the dashboard
        default:
            cout << "*Invalid choice. Please select a valid option." << endl;
        }
    }
}

inline void BankSystem::handleCreditCenter(const string &username)
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
            cout << " " << endl;
            cout << "Press Enter to continue...";
            cin.get();
            break;
        case 4:
            return;
        default:
            cout << "*Invalid choice. Please select a valid option." << endl;
        }
    }
}

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

inline void BankSystem::handleHelpAndResources()
{
    cout << " " << endl;
    cout << "╔═════════════════════════════════════╗    " << endl;
    cout << "║          Help & Resources           ║    " << endl;
    cout << "╠═════════════════════════════════════╣    " << endl;
    cout << "║  1. Chat with AI Assistant          ║     " << endl;
    cout << "║  2. Contact US                      ║     " << endl;
    cout << "║  3. Back to Dashboard               ║     " << endl;
    cout << "╚═════════════════════════════════════╝     " << endl;
    cout << " " << endl;
    cout << "Enter your choice: ";

    int jhchoice;
    string message;
    cin >> jhchoice;
    cin.ignore();
    cout << endl;
    switch (jhchoice)
    {
    case 1:
        cout << "\nHi! I'm your AI Assistant. How may I help you?\n" << endl;
        getline(cin, message);
        ai.chatBot(message);
        break;
    case 2:
        cout << " " << endl;
        cout << "╭────────────────────────────────────────────────╮" << endl;
        cout << "│                  Contact Us                    │" << endl;
        cout << "├────────────────────────────────────────────────┤" << endl;
        cout << "│  Email: Uniportal@proton.me                    │" << endl;
        cout << "│  Phone: 1-800-123-4567                         │" << endl;
        cout << "│  Address: 123 Main St, New York, NY 10001      │" << endl;
        cout << "╰────────────────────────────────────────────────╯" << endl;
        cout << " " << endl;

        cout << "Press Enter to continue...";
        cin.get();
        break;
    case 3:
        return;
    default:
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
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

inline void BankSystem::displayActivityLog(const string &username)
{
    cout << " " << endl;
    cout << "╭───────────────────────────╮" << endl;
    cout << "│      Activity Log         │" << endl;
    cout << "├───────────────────────────┤" << endl;
    cout << "│ 1. Transaction History    │" << endl;
    cout << "│ 2. Session History        │" << endl;
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
    default:
        cout << "*Invalid choice. Please select a valid option." << endl;
        break;
    }
}

inline void BankSystem::viewAnalyticsDashBoard(const string &username)
{
    for (const User &user : users)
    {
        if (user.username == username)
        {
            cout << " " << endl;
            cout << "╔═════════════════════════════════════╗    " << endl;
            cout << "║           Data Analytics            ║   " << endl;
            cout << "╚═════════════════════════════════════╝   " << endl;
            cout << " Name: " << user.name << endl;
            cout << "───────────────────────────────────────" << endl;
            if (user.producttype == "Savings Account")
            {
                cout << "Total Networth: " << showTotalNetworth(username) << endl;
                cout << "Total Interest Earned: " << showInterestEarned(username) << endl;
            }
            else if (user.producttype == "Credit Account")
            {
                cout << "Total Spent: " << showtotalSpent(username) << endl;
                cout << "Total Paid: " << showtotalPaid(username) << endl;
            }

            cout << "───────────────────────────────────────" << endl;
        }
    }
    cout << " " << endl;
    cout << "Press Enter to continue...";
    cin.get();
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

#endif
