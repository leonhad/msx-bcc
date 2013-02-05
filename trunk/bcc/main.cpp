#include <iostream>
#include <stdlib.h>
#include "compiler.h"

using namespace bc;
using namespace std;

int main(int argc, char* argv[]) {
    Compiler *compiler = NULL;
    
    if (argc != 2) {
        cout << argv[0] << ": no input files" << endl;
    } else {
        try {
            char *env = getenv("HOME");
            if (!env) {
                env = getenv("USERPROFILE");
            }
        
            string filein = argv[1];
            string fileout;
            string assembly;
            string link;
            
#ifdef _WIN64
   #error Unsupported platform
#elif _WIN32
   #error Unsupported platform
#elif __APPLE__
    #include "TargetConditionals.h"

    #if TARGET_OS_MAC
        assembly = "as -arch x86_64 -o ";
        link = "ld -L. -lSystem -lbasic /usr/lib/crt1.o -macosx_version_min 10.6 ";
    #else
        #error Unsupported platform
    #endif
#elif __linux
    #error Unsupported platform
#elif __unix // all unices not caught above
    #error Unsupported platform
#elif __posix
    #error Unsupported platform
#endif            
            
            if (filein.find(".") == string::npos) {
                filein += ".bas";
            }
            
            register size_t pos = filein.rfind(".");
            if (pos != string::npos) {
                fileout = filein.substr(0, pos);
                assembly += fileout;
                assembly += ".o ";
                link += fileout;
                link += ".o -o ";
                link += fileout;
                link += " ";
                fileout += ".s";
                assembly += fileout;
            } else {
                throw string("Fail to determine output file");
            }
            compiler = new Compiler(filein, fileout);
            compiler->run();
            
            //cout << "Compiling assembly..." << endl;
            system(assembly.c_str());
            
            //cout << "Linking..." << endl;
            system(link.c_str());
        } catch(string err) {
            cerr << "bcc: " << err << endl;
        } catch(...) {
            cerr << "bcc: Unknown error!" << endl;
        }
        if (compiler) delete compiler;
    }
    return EXIT_SUCCESS;
}
