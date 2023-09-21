#include <iostream>
#include <regex>

using namespace std;
using namespace regex_constants;

class AI
{
public:
    void chatBot(string message)
    {
        regex case1("(forgot)(.* | \s)(password)", icase);
        regex case2("()", icase);

        if(regex_match(message, case1))
            cout << "If you forgot your password, press the \"Forgot Password?\" button and fill in the details.";
    }
};