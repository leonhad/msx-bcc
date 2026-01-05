#include "compiler.h"
#include "messages.h"
#include "file_names.h"
#include <iostream>

using namespace bc;
using namespace std;

int main(const int argc, char *argv[])
{
    set_appname(argv[0]);

    if (argc != 2)
    {
        error("no input file.");
    }
    else
    {
        try
        {
            Compiler compiler(argv[1], nullptr);
            compiler.run();
        }
        catch (exception &err)
        {
            error(err.what());
        }
        catch (string &err)
        {
            error(err);
        }
        catch (...)
        {
            error("unknown error.");
        }
    }

    return EXIT_SUCCESS;
}
