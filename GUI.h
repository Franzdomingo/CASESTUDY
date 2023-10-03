#pragma once
#ifndef GUI_H
#define GUI_H

#include <windows.h>
#include "Admin.h"
#include "User.h"
#include "BankSystem.h"

inline void BankSystem::displayMainMenu()
{
    SetConsoleOutputCP(CP_UTF8);
    cout << "\n"
         << endl;
    cout << "╔══════════════════════════════════════╗   " << endl;
    cout << "║      ╔═══════════════════════╗       ║   " << endl;
    cout << "║      ║   CENTRAL TRUST BANK  ║       ║   " << endl;
    cout << "║      ╚═══════════════════════╝       ║   " << endl;
    cout << "╚══════════════════════════════════════╝   " << endl;
    cout << "                                           " << endl;
    cout << "┌──────────────────────────────────────┐   " << endl;
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
    ::system("cls");
    cout << "\n"
         << endl;
    cout << "╔══════════════════════════════════════╗   " << endl;
    cout << "║      ╔═══════════════════════╗       ║   " << endl;
    cout << "║      ║   CENTRAL TRUST BANK  ║       ║   " << endl;
    cout << "║      ╚═══════════════════════╝       ║   " << endl;
    cout << "╚══════════════════════════════════════╝   " << endl;
    cout << "                                       " << endl;
    cout << "╔══════════════════════════════════════╗    " << endl;
    cout << "║                Login                 ║    " << endl;
    cout << "╚══════════════════════════════════════╝    " << endl;
    cout << "  " << endl;
    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

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
        ::system("cls");
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
    ::system("cls");
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
}

inline void BankSystem::displayDashboardMenu(const string &username)
{
    for (const User &user : users)
    {
        if (user.username == username)
        {
            if (isadmin(username))
            {
                ::system("cls");
                cout << "╔═════════════════════════════════════╗    " << endl;
                cout << "║            Administrator            ║    " << endl;
                cout << "╚═════════════════════════════════════╝    " << endl;
                cout << "                                           " << endl;
                cout << "╔═════════════════════════════════════╗    " << endl;
                cout << "║         Dashboard Options:          ║     " << endl;
                cout << "╠═════════════════════════════════════╣    " << endl;
                cout << "║  1. Manage Users                    ║     " << endl;
                cout << "║  2. Help & Resources                ║     " << endl;
                cout << "║  3. Logout                          ║     " << endl;
                cout << "╚═════════════════════════════════════╝" << endl;
                cout << " " << endl;
                cout << "Enter your choice: ";
            }
            else if (iscustomerservice(username))
            {
                ::system("cls");
                cout << "╔═════════════════════════════════════╗    " << endl;
                cout << "║          Customer Service           ║    " << endl;
                cout << "╚═════════════════════════════════════╝    " << endl;
                cout << "                                           " << endl;
                cout << "╔═════════════════════════════════════╗    " << endl;
                cout << "║         Dashboard Options:          ║     " << endl;
                cout << "╠═════════════════════════════════════╣    " << endl;
                cout << "║  1. Messages                        ║     " << endl;
                cout << "║  2. Logout                          ║     " << endl;
                cout << "╚═════════════════════════════════════╝" << endl;
                cout << " " << endl;
                cout << "Enter your choice: ";
            }
            else
            {
                ::system("cls");
                SetConsoleOutputCP(CP_UTF8);
                cout << " " << endl;
                cout << "╭─────────────────────────────────────╮" << endl;
                cout << "│         CENTRAL TRUST BANK          │" << endl;
                cout << "╰─────────────────────────────────────╯" << endl;
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
        cout << " " << endl;
        if (isadmin(username))
        {
            switch (choice)
            {
            case 1:
                handleManageUsers(username);
                cin.get();
                break;
            case 2:
                ::system("cls");
                displayAllHelpAndResources();
                replyHelpAndResources();
                break;
            case 3:
                // Logout the user
                cout << "Logging out..." << endl;
                logout(username);
                setCurrentLoggedInUser("");
                cout << " " << endl;
                cout << "Press Enter to continue...";
                cin.get();
                ::system("cls");
                return;
            default:
                cout << "*Invalid choice. Please select a valid option." << endl;
            }
        }
        else if (iscustomerservice(username))
        {
            switch (choice)
            {
            case 1:
                ::system("cls");
                displayAllHelpAndResources();
                replyHelpAndResources();
                break;
            case 2:
                // Logout the user
                cout << "Logging out..." << endl;
                logout(username);
                setCurrentLoggedInUser("");
                cout << " " << endl;
                cout << "Press Enter to continue...";
                cin.get();
                ::system("cls");
                return;
            default:
                cout << "*Invalid choice. Please select a valid option." << endl;
            }
        }
        else
        {
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
                handleHelpAndResources(username);
                break;
            case 5:
                // Logout the user
                cout << "\nLogging out..." << endl;
                logout(username);
                setCurrentLoggedInUser("");
                cout << "──────────────────────────────────" << endl;
                cout << "Press Enter to continue...";
                cin.get();
                ::system("cls");
                return;
            default:
                cout << "*Invalid choice. Please select a valid option." << endl;
            }
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
    ::system("cls");
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
    ::system("cls");
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
                cout << "Description: " << transaction.description << endl;
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
        case 3:;
            ::system("cls");
            displayTransactionHistory(username);
            cout << " " << endl;
            cout << "Press Enter to continue...";
            cin.get();
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
            ::system("cls");
            break;
        case 2:
            processPayBills(username);
            ::system("cls");
            break;
        case 3:
            ::system("cls");
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

inline void BankSystem::handleHelpAndResources(const string &username)
{
    ::system("cls");
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
    switch (jhchoice)
    {
    case 1:
        cout << "\nHi! I'm your AI Assistant. How may I help you?\n"
             << endl;
        cout << "Enter inquiry: ";
        getline(cin, message);
        chatBot(message, username);
        cout << " " << endl;
        cout << "Press Enter to continue...";
        cin.get();
        break;
    case 2:
        ::system("cls");
        cout << " " << endl;
        cout << "╭────────────────────────────────────────────────╮" << endl;
        cout << "│                  Contact Us                    │" << endl;
        cout << "├────────────────────────────────────────────────┤" << endl;
        cout << "│  Email: Uniportal@proton.me                    │" << endl;
        cout << "│  Phone: 1-800-123-4567                         │" << endl;
        cout << "│  Address: 123 Main St, New York, NY 10001      │" << endl;
        cout << "╰────────────────────────────────────────────────╯" << endl;
        cout << "                                                  " << endl;
        cout << "╭────────────────────────────────────────────────╮         " << endl;
        cout << "│  1. Send a message                             │         " << endl;
        cout << "│  2. Back to Dashboard                          │         " << endl;
        cout << "╰────────────────────────────────────────────────╯         " << endl;
        cout << " " << endl;
        int schoice;
        cout << "Enter your choice: ";
        cin >> schoice;
        cout << " " << endl;
        if (schoice == 1)
        {
            askHelp(username);
            cout << "\nMessage sent successfully!" << endl;
            cout << " " << endl;
            cout << "Press Enter to continue...";
            cin.get();
        }
        else if (schoice == 2)
        {
            break;
        }
        else
        {
            cout << "*Invalid choice. Please select a valid option." << endl;
            return;
        }
        break;
    case 3:
        return;
    default:
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
}

inline void BankSystem::viewAnalyticsDashBoard(const string &username)
{
    for (const User &user : users)
    {
        if (user.username == username)
        {
            ::system("cls");
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

#endif
