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

struct ProductApplication
{
    string applicationID;
    string producttype;
};

struct Session
{
    string sessionID;
    time_t timestamp;
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
    string helpcontent;
    string helpresources;
    string feedback;
};

struct dashboard
{
    string dashboardID;
    string dashboardcontent;
};

struct User
{
    string username;
    string password;
    double balance;
    vector<Profile> profiles;
    vector<Transaction> transactionhistory;
    vector<ProductApplication> productapplications;
    vector<Session> sessions;
    vector<HelpandResources> helpandresources;
    vector<DataAnalytics> dataanalytics;
    vector<dashboard> dashboards;
};

class BankSystem
{
private:
    vector<User> users;
    vector<Profile> profiles;
    vector<Transaction> transactionhistory;
    vector<ProductApplication> productapplications;
    vector<Session> sessions;
    vector<HelpandResources> helpandresources;
    vector<DataAnalytics> dataanalytics;
    vector<dashboard> dashboards;
    string currentLoggedInUser;
    string dataFilePath; // Path to the data file

public:
    BankSystem(const string &dataFile) : dataFilePath(dataFile)
    {
        // Load data from the file into the 'users' vector during system initialization
        loadDataFromFile();
    }

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

    void setCurrentLoggedInUser(const string &username)
    {
        currentLoggedInUser = username;
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
    bool createUser(const string &username, const string &password, const string &email, const string &phone)
    {
        // Check if the username is already taken
        if (isUsernameTaken(username))
        {
            cout << "Username is already taken. Please choose another one." << endl;
            return false;
        }

        // Create a new user account
        User newUser;
        newUser.username = username;
        newUser.password = password;
        newUser.balance = 0.0;

        // Create a new profile for the user
        Profile newProfile;
        newProfile.email = email;
        newProfile.phone = phone;
        newProfile.isTwoFactorEnabled = false; // You can add logic to enable 2FA if needed

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

        users.clear();
        User user;

        while (true)
        {
            // Read the username and password
            if (!(file >> user.username >> user.password))
                break;

            // Read the balance
            file >> user.balance;

            // Read the profiles
            int profileCount;
            file >> profileCount;
            user.profiles.resize(profileCount);
            for (int i = 0; i < profileCount; ++i)
            {
                Profile profile;
                file >> profile.email >> profile.phone >> profile.isTwoFactorEnabled;
                user.profiles[i] = profile;
            }

            // Read the transaction history
            int transactionCount;
            file >> transactionCount;
            user.transactionhistory.resize(transactionCount);
            for (int i = 0; i < transactionCount; ++i)
            {
                Transaction transaction;
                file >> transaction.transactionID >> transaction.transactionType >> transaction.amount >> transaction.timestamp;
                user.transactionhistory[i] = transaction;
            }

            // Read the other data structures (ProductApplication, Session, etc.) in a similar manner

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
            // Save the username and password
            file << user.username << " " << user.password << endl;

            // Save the balance
            file << user.balance << endl;

            // Save the number of profiles and each profile
            file << user.profiles.size() << endl;
            for (const Profile &profile : user.profiles)
            {
                file << profile.email << " " << profile.phone << " " << profile.isTwoFactorEnabled << endl;
            }

            // Save the number of transactions and each transaction
            file << user.transactionhistory.size() << endl;
            for (const Transaction &transaction : user.transactionhistory)
            {
                file << transaction.transactionID << " " << transaction.transactionType << " " << transaction.amount << " " << transaction.timestamp << endl;
            }

            // Save the other data structures (ProductApplication, Session, etc.) in a similar manner
        }

        file.close();
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