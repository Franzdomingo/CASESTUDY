#include "GUI.h"

int main()
{
    BankSystem bank("bank_data.json");
    string loggedInUsername;

    while (true)
    {
        BankSystem::displayMainMenu();

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
            ::system("cls");
            bank.applyForProduct();
            ::system("cls");
            break;
        case 3:
            bank.forgotPassword();
            ::system("pause");
            ::system("cls");
            break;
        case 4:
            ::system("cls");
            return 0;
        default:
            cout << "\n*Invalid choice. Please select a valid option." << endl;
            cout << " " << endl;
            ::system("pause");
            ::system("cls");
        }
    }
}
