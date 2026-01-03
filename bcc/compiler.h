#ifndef _compiler_H
#define	_compiler_H

#include <string>
#include <vector>
#include "parser.h"
#include "analyze.h"
#include "codegen.h"

namespace bc {
    
class Compiler {
private:
    vector<int> usedlines;
    Parser *parser;
    TreeNode *syntaxTree;
    Analyze *analyze;
    CodeGen *codegen;
    
public:
    Compiler(string filein, string fileout);
    ~Compiler();
    void run();
};

}

#endif
