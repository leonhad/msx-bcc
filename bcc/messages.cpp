#include "messages.h"
#include "filename.h"
#include <iostream>

using namespace std;

void debug(const string &message)
{
#ifdef DEBUG
    cout << get_appname() << ": " << message << endl;
#endif
}

void info(const string &message)
{
    cout << get_appname() << ": " << message << endl;
}

void error(const string &message)
{
    cerr << get_appname() << ": " << message << endl;
}
