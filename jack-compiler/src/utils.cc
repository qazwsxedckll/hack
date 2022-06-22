#include "utils.h"

using namespace std;

bool IsJackFile(const string& file_name)
{
    auto dot_pos = file_name.find_last_of(".");
    if (dot_pos == string::npos)
    {
        return false;
    }

    if (file_name.substr(dot_pos) == ".jack")
    {
        return true;
    }

    return false;
}
