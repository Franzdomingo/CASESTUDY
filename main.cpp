#include <iostream>
#include "BankSystem.h"

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
            bank.forgotPassword();
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    }
    return 0;
}