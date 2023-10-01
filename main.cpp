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
        system("cls");       
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