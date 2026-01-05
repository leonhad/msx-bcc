#include "compiler.h"

namespace bc
{
    
    Compiler::Compiler(std::string filein, std::string fileout)
    {
        parser = new Parser(filein);
        codegen = new CodeGen(filein, fileout);
        syntaxTree = nullptr;
    }
    
    Compiler::~Compiler()
    {
        if (syntaxTree) delete syntaxTree;
        if (parser) delete parser;
    }
    
    void Compiler::run()
    {
        syntaxTree = parser->parse();

        //cout << "Building Symbol Table..." << endl;
        Analyze analyze;
        auto symtab = analyze.buildSymtab(syntaxTree);

        //cout << "Checking Types..." << endl;
        //typeCheck(syntaxTree);
        //cout << "Type Checking Finished" << endl;
        //cout << "Generating assembly code..." << endl;
        codegen->generate(syntaxTree, symtab);
    }
    
}
