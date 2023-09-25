#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
#include <ctime>
#include <string>
#include "SecuritySys.h"

using namespace std;

string SecuritySys::encryptPass(string password)
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

string SecuritySys::decryptPass(string encrypted)
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

string SecuritySys::generateOTP()
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

bool SecuritySys::canAttempt()
{
    time_t currTime = time(0);
    if (attempts > 3 && difftime(currTime, lastAttempt) < 30)
        return false;

    if (difftime(currTime, lastAttempt) >= 30)
        attempts = 0;

    return true;
}

bool SecuritySys::attemptLogin(string password, string verifyPass)
{
    if (verifyPass == password)
        return true;

    attempts++;
    lastAttempt = time(0);
    return false;
}

void SecuritySys::sendOTP()
{
    OTP = generateOTP();
    cout << "Your One-time Password is: " << OTP << ". Do not give or send this to other people." << endl;
}

bool SecuritySys::verifyOTP(string onetimepass)
{
    if (OTP == onetimepass)
    {
        attempts = 0;
        return true;
    }
    return false;
}

string SecuritySys::getcurrDate()
{
    time_t currTime = time(0);
    struct tm tstruct;
    char buf[80];
    /* The line `tstruct = *localtime(&currTime);` is assigning the value of the `tm` structure
    returned by the `localtime` function to the variable `tstruct`. */
    tstruct = *localtime(&currTime);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}

bool SecuritySys::securityStatus()
{
    // Need something to check if security system is running well.
    return true;
}

void SecuritySys::auditLog()
{
    ofstream auditFile("audit_log.txt", ios_base::app);
    if (!auditFile)
    {
        cerr << "Error: Unable to open file for audit." << endl;
        exit(0);
    }
    bool runStatus = securityStatus();
    string statusResult = runStatus ? "PASSED" : "FAILED";

    auditFile << "[" << getcurrDate() << "]: " << statusResult << endl;

    auditFile.close();
}
