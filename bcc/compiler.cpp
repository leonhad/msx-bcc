#include "compiler.h"
#include "file_names.h"
#include "messages.h"

#include <memory>
#include <string>

using namespace std;

namespace bc
{
    Compiler::Compiler(const char *filein, const char *fileout)
    {
        this->filein = filein;
        if (this->filein.find('.') == string::npos)
        {
            this->filein += ".bas";
        }

        if (!fileout)
        {
            this->fileout = get_executable_name(remove_extension(filein).c_str());
        }

        fileAssembly = get_assembly_name(remove_extension(filein).c_str());

    }

    void Compiler::run() const
    {
        Parser parser{this->filein};
        const auto syntaxTree = make_unique<TreeNode *>(parser.parse());

        debug("building symbol table...");
        Analyze analyze;
        const auto symbols = analyze.buildSymbolTable(*syntaxTree);

        // debug("Checking Types...");
        //  typeCheck(syntaxTree);
        //  debug("Type Checking Finished");

        debug("generating assembly code...");
        CodeGen codegen = this->fileAssembly;
        codegen.generate(*syntaxTree, symbols);

        compile();
    }

    void Compiler::compile() const
    {
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
        assembly = "as -march generic64 -o ";
        link = "ld -L. -lbasic ";
#elif __unix // all unixes not caught above
#error Unsupported platform
#elif __posix
#error Unsupported platform
#endif

        const auto name = remove_extension(filein.c_str());
        const auto object = add_extension(name.c_str(), "o");

        assembly += object + " " + get_assembly_name(name.c_str());
        link += object + " -o " + fileout;

        debug(assembly);
        system(assembly.c_str());

        debug(link);
        system(link.c_str());
    }
}
