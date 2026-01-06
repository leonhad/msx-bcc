#include "filename.h"
#include <filesystem>

using namespace std;
using namespace std::filesystem;

static string appname;
static path exe_directory;

void set_appname(const char *name)
{
    exe_directory = absolute(path(name)).parent_path();
    appname = path(name).filename();
}

std::string get_appname()
{
    return appname;
}

std::string get_apppath()
{
    return exe_directory.string();
}

string remove_extension(const char *filename)
{
    string filein = filename;
    if (const auto position = filein.rfind('.'); position != string::npos)
    {
        return filein.substr(0, position);
    }

    return filein;
}

string add_extension(const char *filename, const char *const extension)
{
    return string(filename) + "." + extension;
}

string get_object_name(const char *filename)
{
    return add_extension(filename, "o");
}

string get_assembly_name(const char *filename)
{
    return add_extension(filename, "s");
}

string get_executable_name(const char *filename)
{
#ifdef _WIN64
    return add_extension(filename, "exe");
#elif _WIN32
    return add_extension(filename, "exe");
#endif

    return filename;
}
