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
            cout << "It seems like you've forgotten your password. Don't worry, you can reset it by clicking the 'Forgot Password?' button and following the instructions provided.";

        if (regex_search(message, regex("(guide)", regex_constants::icase)))
            cout << "Looking for a guide? We have comprehensive documentation and tutorials available to help you navigate through our system.";

        if (regex_search(message, regex("(transact)", regex_constants::icase)))
            cout << "You're interested in making a transaction? At the moment, we don't have a specific answer for this. Please refer to our transaction guide for more details.";

        if (regex_search(message, regex("(contact)", regex_constants::icase)))
            cout << "Need to get in touch? Our customer service team is always ready to help. You can reach us through our Contact Us page.";

        if (regex_search(message, regex("(credit)(.*)(limit)", regex_constants::icase)))
            cout << "Inquiring about your credit limit? You can check this information in your account settings under the 'Credit Limit' section.";
    }
};

#endif
