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
    string currentLoggedInUser;
    string dataFilePath; // Path to the data file

public:
    BankSystem(const string &dataFile) : dataFilePath(dataFile)
    {
        // Load data from the file into the 'users' vector during system initialization
        loadDataFromFile();
    }
    string generateApplicationID()
    {
        // You can generate a unique ID based on the current timestamp, or use a library like UUID to generate one.
        // Here, we are generating a simple timestamp-based ID.
        time_t currentTime = time(nullptr);
        return to_string(currentTime);
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
        while (file >> user.username >> user.password >> user.balance)
        {
            // Load profiles
            Profile profile;
            file >> profile.email >> profile.phone >> profile.isTwoFactorEnabled;
            user.profiles.push_back(profile);

            // Load transaction history
            Transaction transaction;
            while (file >> transaction.transactionID >> transaction.transactionType >> transaction.amount >> transaction.timestamp)
            {
                user.transactionhistory.push_back(transaction);
            }

            // Load product applications
            ProductApplication productApp;
            while (file >> productApp.applicationID >> productApp.producttype)
            {
                user.productapplications.push_back(productApp);
            }

            // Load sessions
            Session session;
            while (file >> session.sessionID >> session.timestamp)
            {
                user.sessions.push_back(session);
            }

            // Load help and resources
            HelpandResources help;
            while (file >> help.helpID >> help.helpcontent >> help.helpresources >> help.feedback)
            {
                user.helpandresources.push_back(help);
            }

            // Load data analytics
            DataAnalytics analytics;
            while (file >> analytics.dataID >> analytics.businessinsights >> analytics.transactionpatterns)
            {
                user.dataanalytics.push_back(analytics);
            }

            // Load dashboards
            dashboard dash;
            while (file >> dash.dashboardID >> dash.dashboardcontent)
            {
                user.dashboards.push_back(dash);
            }
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
            file << user.username << " " << user.password << " " << user.balance << endl;

            // Save profiles
            for (const Profile &profile : user.profiles)
            {
                file << profile.email << " " << profile.phone << " " << profile.isTwoFactorEnabled << endl;
            }

            // Save transaction history
            for (const Transaction &transaction : user.transactionhistory)
            {
                file << transaction.transactionID << " " << transaction.transactionType << " " << transaction.amount << " " << transaction.timestamp << endl;
            }

            // Save product applications
            for (const ProductApplication &productApp : user.productapplications)
            {
                file << productApp.applicationID << " " << productApp.producttype << endl;
            }

            // Save sessions
            for (const Session &session : user.sessions)
            {
                file << session.sessionID << " " << session.timestamp << endl;
            }

            // Save help and resources
            for (const HelpandResources &help : user.helpandresources)
            {
                file << help.helpID << " " << help.helpcontent << " " << help.helpresources << " " << help.feedback << endl;
            }
            // Save data analytics
            for (const DataAnalytics &analytics : user.dataanalytics)
            {
                file << analytics.dataID << " " << analytics.businessinsights << " " << analytics.transactionpatterns << endl;
            }

            // Save dashboards
            for (const dashboard &dash : user.dashboards)
            {
                file << dash.dashboardID << " " << dash.dashboardcontent << endl;
            }
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
        newUser.balance = 0.0;

        // Create a new profile
        Profile newProfile;
        newProfile.email = email;
        newProfile.phone = phone;
        newProfile.isTwoFactorEnabled = false; // You can add logic to enable 2FA if needed

        newUser.profiles.push_back(newProfile);

        // Add the new user to the vector of users
        users.push_back(newUser);

        // Save the updated user data to the file
        saveDataToFile();

        cout << "User account created successfully." << endl;
        return true;
    }

    bool applyForProduct(const string &username, const string &productType)
    {
        for (User &user : users)
        {
            if (user.username == username)
            {
                // Create a new product application
                ProductApplication productApp;
                productApp.applicationID = generateApplicationID(); // You need to implement a function to generate unique IDs
                productApp.producttype = productType;

                // Add the product application to the user's list
                user.productapplications.push_back(productApp);

                // Save the updated user data to the file
                saveDataToFile();

                cout << "Application for " << productType << " submitted successfully." << endl;
                return true;
            }
        }

        cout << "User not found. Product application failed." << endl;
        return false;
    }

    // Implement other methods for handling product applications, such as listing applications, processing them, etc.

    // ... Rest of the BankSystem class implementation ...
};

int main()
{
    BankSystem bank("bank_data.txt");
    string choice, username, password, email, phone, productType; // Declare variables here

    while (true)
    {
        // ... Your main menu loop ...

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character

        if (choice == "2") // Use strings for comparison
        {
            cout << "Enter username: ";
            getline(cin, username);

            // Check if the username is already taken
            bool usernameTaken = bank.isUsernameTaken(username);
            if (usernameTaken)
            {
                cout << "Username is already taken. Please choose another one." << endl;
                continue;
            }
            cout << "Enter password: ";
            getline(cin, password);

            cout << "Enter email: ";
            getline(cin, email);

            cout << "Enter phone: ";
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
        else if (choice == "6") // Use strings for comparison
        {
            cout << "Enter the product type you want to apply for: ";
            getline(cin, productType);

            // Apply for a product
            bool applicationSuccess = bank.applyForProduct(username, productType);
            if (applicationSuccess)
            {
                cout << "Product application submitted successfully." << endl;
            }
            else
            {
                cout << "Product application failed. Please try again." << endl;
            }
        }
        // ... Handle other menu options ...
    }

    return 0;
}
