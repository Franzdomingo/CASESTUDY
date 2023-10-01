#ifndef CHATAI_H
#define CHATAI_H

using namespace std;

/*
 * The ChatAI class is a mockup chatbot that provides automated responses
 * based on specific keywords or phrases found within a given message.
 */

class ChatAI
{
public:
    // Evaluates the user's message and responds based on predefined patterns.
    void chatBot(string message)
    {
        // Checks if user's message indicates they've forgotten their password.
        if (regex_search(message, regex("(forgot)(.*)(password)", regex_constants::icase)))
            cout << "It seems like you've forgotten your password. Don't worry, you can reset it by clicking the 'Forgot Password?' button and following the instructions provided.";

        // Responds to requests for a guide or tutorial.
        if (regex_search(message, regex("(guide)", regex_constants::icase)))
            cout << "Looking for a guide? We have comprehensive documentation and tutorials available to help you navigate through our system.";

        // Directs users to a transaction guide if they mention "transact".
        if (regex_search(message, regex("(transact)", regex_constants::icase)))
            cout << "You're interested in making a transaction? At the moment, we don't have a specific answer for this. Please refer to our transaction guide for more details.";

        // Provides information on how to contact customer service.
        if (regex_search(message, regex("(contact)", regex_constants::icase)))
            cout << "Need to get in touch? Our customer service team is always ready to help. You can reach us through our Contact Us page.";

        // Assists users with inquiries about their credit limit.
        if (regex_search(message, regex("(credit)(.*)(limit)", regex_constants::icase)))
            cout << "Inquiring about your credit limit? You can check this information in your account settings under the 'Credit Limit' section.";
    }
};

#endif
