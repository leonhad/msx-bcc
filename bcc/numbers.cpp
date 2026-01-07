#include "numbers.h"

#include <stdexcept>

unsigned int to_int(const std::string &str)
{
    unsigned int ret = 0;
    try
    {
        if (!str.empty())
        {
            ret = std::stoi(str);
        }
    }
    catch (std::out_of_range &)
    {
    }
    catch (std::invalid_argument &)
    {
    }

    return ret;
}
