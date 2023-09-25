#ifndef SECURITY_SYS_H
#define SECURITY_SYS_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
#include <ctime>
#include <string>

using namespace std;

class SecuritySys
{
private:
    int attempts;
    time_t lastAttempt;
    string OTP;
public:
    SecuritySys() : attempts(0), lastAttempt(0) {}
    string encryptPass(string);
    string decryptPass(string);
    string generateOTP();
    bool canAttempt();
    bool attemptLogin(string, string);
    void sendOTP();
    bool verifyOTP(string);
    string getcurrDate();
    bool securityStatus();
    void auditLog();
};

#endif