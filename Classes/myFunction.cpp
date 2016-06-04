#include <myFunction.h>

int strtoInt (const string& str, int pos, const string& delim)
{
    if (delim.empty()) {
        return atoi(str.c_str());
    } else {
        int pos1 = str.find(delim, pos) + delim.length();
        int pos2 = str.find(delim, pos1);
        string temp = str.substr(pos1, pos2 - pos1);
        return atoi(temp.c_str());
    }
}


bool checkCommand (const string& commands, const string delim)
{
//    bool result = true;
    int length = commands.length();
    if (length <= 0)
        return false;
    if (string(commands.substr(0, delim.length())) != delim)
        return false;
    if (commands.substr(commands.length() - delim.length(), delim.length()) != delim)
        return false;

    return true;
}
