#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>

using namespace std;

// Define structures for data storage
struct Transaction
{
    string transactionType;
    double amount;
    time_t timestamp;
};

struct User
{
    string username;
    string password;
    string email;
    string phone;
    double balance;
    bool isTwoFactorEnabled;
    vector<Transaction> transactionHistory;
};

class BankSystem
{
private:
    vector<User> users;
    string currentLoggedInUser;
    string dataFilePath; // Path to the data file

public:
    BankSystem(const string &dataFile) : dataFilePath(dataFile)
    {
        // Load data from the file into the 'users' vector during system initialization
        loadDataFromFile();
    }

    // Authenticate a user based on username and password
    bool authenticateUser(const string &username, const string &password)
    {
        for (const User &user : users)
        {
            if (user.username == username && user.password == password)
            {
                return true; // Authentication successful
            }
        }
        return false; // Authentication failed
    }
    // Check if a username is already taken
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

    void setCurrentLoggedInUser(const string &username)
    {
        currentLoggedInUser = username;
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

        users.clear();
        User user;
        while (file >> user.username >> user.password >> user.email >> user.phone >> user.isTwoFactorEnabled)
        {
            users.push_back(user);
        }

        file.close();
    }

    // Save user data from memory to the file
    void saveDataToFile()
    {
        ofstream file(dataFilePath);
        if (!file.is_open())
        {
            cout << "Error: Unable to save data to the file." << endl;
            return;
        }

        for (const User &user : users)
        {
            file << user.username << " " << user.password << " " << user.email << " " << user.phone << " " << user.balance << " " << user.isTwoFactorEnabled << endl;
        }

        file.close();
    }

    bool createUser(const string &username, const string &password, const string &email, const string &phone)
    {
        // Check if the username is already taken
        for (const User &user : users)
        {
            if (user.username == username)
            {
                cout << "Username is already taken. Please choose another one." << endl;
                return false;
            }
        }

        // Create a new user account
        User newUser;
        newUser.username = username;
        newUser.password = password;
        newUser.email = email;
        newUser.phone = phone;
        newUser.balance = 0.0;
        newUser.isTwoFactorEnabled = false; // You can add logic to enable 2FA if needed

        // Add the new user to the vector of users
        users.push_back(newUser);

        // Save the updated user data to the file
        saveDataToFile();

        cout << "User account created successfully." << endl;
        return true;
    }

    bool depositFunds(const string &username, double amount)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                // Update user's transaction history
                Transaction depositTransaction;
                depositTransaction.transactionType = "Deposit";
                depositTransaction.amount = amount;
                depositTransaction.timestamp = time(nullptr);

                user.transactionHistory.push_back(depositTransaction);

                // Update user's balance
                // Assuming you have a balance field in the User struct
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

    // Other methods for implementing the bank system's functionality

    // Implement methods for Signup, Login, Dashboard, Transaction Center, User Profile,
    // Data Analytics Dashboard, Help & Resources, Log Out, and other operations.
};

int main()
{
    BankSystem bank("bank_data.txt");
    while (true)
    {
    login:
        string username, password, email, phone;
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, username);
            cout << "Enter password: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, password);

            // Perform user authentication here
            // You need to check if the provided username and password match a user in your system
            // If authentication is successful, set the 'currentLoggedInUser' variable in your BankSystem class

            // Example pseudo-code for authentication
            if (bank.authenticateUser(username, password))
            {
                bank.setCurrentLoggedInUser(username);
                // Redirect to the user's dashboard or other menu options
                cout << "Login successful!" << endl;
                while (true)
                {
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
                        // Implement Transaction Center here
                        // You can call functions like depositFunds and withdrawFunds from the bank object
                        break;
                    case 2:
                        // Implement User Profile here
                        // Display user information and allow for profile updates if needed
                        break;
                    case 3:
                        // Implement Data Analytics Dashboard here
                        // Provide analytics and insights based on user data
                        break;
                    case 4:
                        // Implement Help & Resources here
                        // Provide user assistance and resources
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
            else
            {
                cout << "Invalid username or password. Please try again." << endl;
            }
        }
        else if (choice == 2)
        {
            cout << "Enter username: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, username);

            // Check if the username is already taken
            bool usernameTaken = bank.isUsernameTaken(username);
            if (usernameTaken)
            {
                cout << "Username is already taken. Please choose another one." << endl;
                continue;
            }
            cout << "Enter password: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, password);

            cout << "Enter email: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, email);

            cout << "Enter phone: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, phone);

            // Create a new user account
            bool registrationSuccess = bank.createUser(username, password, email, phone);
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
            cout << "Goodbye!" << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please select a valid option." << endl;
            break;
        }
    }
    return 0;
}