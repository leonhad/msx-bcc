#include "compiler.h"
#include "codegen.h"
#include "filename.h"
#include "messages.h"
#include <memory>
#include <string>

using namespace std;

namespace bc
{
    Compiler::Compiler(const char *input, const char *output)
    {
        this->input = input;
        if (this->input.find('.') == string::npos)
        {
            this->input += ".bas";
        }

        if (!output)
        {
            this->output = get_executable_name(remove_extension(input).c_str());
        }

        assembly = get_assembly_name(remove_extension(input).c_str());
    }

    void Compiler::run() const
    {
        Parser parser{this->input};
        const auto syntax_tree = parser.parse();

        debug("building symbol table...");
        Analyze analyze;
        const auto symbols = analyze.buildSymbolTable(syntax_tree);

        // debug("Checking Types...");
        //  typeCheck(syntaxTree);
        //  debug("Type Checking Finished");

        debug("generating assembly code...");
        CodeGen codegen{this->assembly};
        codegen.generate(syntax_tree, symbols);

        compile();
    }

    void Compiler::compile() const
    {
        string assembly_command;
        string link_command;

#ifdef _WIN64
#error Unsupported platform
#elif _WIN32
#error Unsupported platform
#elif __APPLE__
#include "TargetConditionals.h"

#if TARGET_OS_MAC
        assembly_command = "as -arch x86_64 -o ";
        link_command = "ld -L. -lSystem -lbasic /usr/lib/crt1.o -macosx_version_min 10.6 ";
#else
#error Unsupported platform
#endif
#elif __linux
        assembly_command = "as -march generic64 -o ";
        link_command = "ld -L. -lbasic ";
#elif __unix // all unixes not caught above
#error Unsupported platform
#elif __posix
#error Unsupported platform
#endif

        const auto name = remove_extension(input.c_str());
        const auto object = add_extension(name.c_str(), "o");

        assembly_command += object + " " + assembly;
        link_command += object + " -o " + output;

        debug(assembly_command);
        system(assembly_command.c_str());

        debug(link_command);
        system(link_command.c_str());
    }
}
