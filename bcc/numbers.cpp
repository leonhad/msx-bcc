#include "numbers.h"

#include <exception>

unsigned int toInt(const std::string &str)
{
    unsigned int ret = 0;
    try
    {
        if (!str.empty())
        {
            ret = std::stoi(str);
        }
    }
    catch (std::exception &)
    {
    }

    return ret;
}
