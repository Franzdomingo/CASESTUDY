#ifndef CHATAI_H
#define CHATAI_H

#include <iostream>
#include <regex>

using namespace std;

class ChatAI
{
public:
    void chatBot(string message)
    {
        if (regex_search(message, regex("(forgot)(.*)(password)", regex_constants::icase)))
            cout << "If you forgot your password, press the 'Forgot Password?' button and fill in the details.";

        if (regex_search(message, regex("(test)", regex_constants::icase)))
            cout << "No available answer for this yet.";

        if (regex_search(message, regex("(yes)", regex_constants::icase)))
            cout << "No available answer for this yet.";

        if (regex_search(message, regex("(no)", regex_constants::icase)))
            cout << "No available answer for this yet.";

        if (regex_search(message, regex("(maybe)", regex_constants::icase)))
            cout << "No available answer for this yet.";
    }
};

#endif