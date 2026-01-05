#ifndef _compiler_H
#define	_compiler_H

#include <string>
#include "parser.h"
#include "codegen.h"

namespace bc {
    
class Compiler {
    Parser *parser;
    TreeNode *syntaxTree;
    CodeGen *codegen;
    
public:
    Compiler(std::string filein, std::string fileout);
    ~Compiler();
    void run();
};

}

#endif
