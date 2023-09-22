#include <iostream>
#include <cstring>

using namespace std;

string encryptPass(string password)
{
    const int passlength = password.length();
    char *pass = new char[passlength + 1];
    strcpy(pass, password.c_str());

    for (int i = 0; (i < passlength && pass[i] != '\0'); i++)
        pass[i] = pass[i] + 2;

    password.assign(pass, passlength);

    delete[] pass;
    return password;
}

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



int main()
{
    cout << encryptPass("password") << endl;
    cout << decryptPass("rcuuyqtf") << endl;
    return 0;
}