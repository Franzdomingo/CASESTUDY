#pragma once
#ifndef SECURITY_SYS_H
#define SECURITY_SYS_H

using namespace std;

class SecuritySys
{
private:
    int attempts;
    time_t lastAttempt;
    string OTP;

public:
    // Constructor initializes attempts and last attempt
    SecuritySys() : attempts(0), lastAttempt(0) {}

    // Encrypts given password by adding 2 to ASCII value of each character.
    string encryptPass(string password)
    {
        const int passlength = password.length();
        char *pass = new char[passlength + 1];
        strcpy(pass, password.c_str());

        for (int i = 0; (i < passlength && pass[i] != '\0'); i++)
            pass[i] = pass[i] + 2;

        password.assign(pass, passlength);

        delete[] pass; // Delete after using to avoid memory leak.
        return password;
    }

    // Decrypts given password by subtracting 2 from ASCII value of each character.
    string decryptPass(string encrypted)
    {
        const int passlength = encrypted.length();
        char *pass = new char[passlength + 1];
        strcpy(pass, encrypted.c_str());

        for (int i = 0; (i < passlength && pass[i] != '\0'); i++)
            pass[i] = pass[i] - 2;

        encrypted.assign(pass, passlength);

        delete[] pass;
        return encrypted;
    }

    // Generates a 6 digit One-time Password.
    string generateOTP()
    {
        const int length = 6;
        random_device rand;
        mt19937 generator(rand());
        uniform_int_distribution<int> distributor(0, 9);

        string otp;

        for (int i = 0; i < length; i++)
            otp += to_string(distributor(generator));

        return otp;
    }

    // Determines if another login attempt can be made.
    // After 3 failed attempts, user has to wait 30 seconds.
    bool canAttempt()
    {
        time_t currTime = time(0);
        if (attempts > 3 && difftime(currTime, lastAttempt) < 30)
            return false;

        if (difftime(currTime, lastAttempt) >= 30)
            attempts = 0;

        return true;
    }

    // Attempts to login and tracks failed attempts.
    bool attemptLogin(const string &password, const string &verifyPass)
    {
        if (verifyPass == password)
            return true;

        attempts++;
        lastAttempt = time(0);
        return false;
    }

    bool enable2FA(const char &answer)
    {
        if (toupper(answer) == 'Y')
            return true;

        return false;
    }

    void sendOTP()
    {
        OTP = generateOTP();
        cout << "Your One-time Password is: " << OTP << ". Do not give or send this to other people." << endl;
    }

    bool verifyOTP(const string &onetimepass)
    {
        if (OTP == onetimepass)
        {
            attempts = 0;
            return true;
        }
        return false;
    }

    string getcurrDate()
    {
        time_t currTime = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&currTime);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

        return buf;
    }

    // Dummy function to represent security system check.
    bool securityStatus(const bool &status)
    {
        if (status)
            return true;

        return false;
    }

    void auditLog(const bool &status)
    {
        try
        {
            ofstream auditFile("audit_log.txt");
            if (!auditFile)
            {
                cerr << "Error: Unable to open file for audit." << endl;
                return;
            }

            bool currentStatus = securityStatus(status);
            string statusResult = currentStatus ? "PASSED" : "FAILED";

            auditFile << "[" << getcurrDate() << "]: " << statusResult << endl;

            auditFile.close();
        }
        catch (const exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
};

#endif
