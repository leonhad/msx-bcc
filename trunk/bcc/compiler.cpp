#include "compiler.h"

namespace bc
{
    
    Compiler::Compiler(string filein, string fileout) throw(string)
    {
        parser = new Parser(filein);
        analyze = new Analyze;
        codegen = new CodeGen(filein, fileout);
        syntaxTree = NULL;
    }
    
    Compiler::~Compiler()
    {
        if (syntaxTree) delete syntaxTree;
        if (parser) delete parser;
        if (analyze) delete analyze;
    }
    
    void Compiler::run() throw(string)
    {
        syntaxTree = parser->parse();

        //cout << "Building Symbol Table..." << endl;
        vector<SYMTAB *> symtab = analyze->buildSymtab(syntaxTree);

        //cout << "Checking Types..." << endl;
        //typeCheck(syntaxTree);
        //cout << "Type Checking Finished" << endl;
        //cout << "Generating assembly code..." << endl;
        codegen->generate(syntaxTree, symtab);
    }
    
}
