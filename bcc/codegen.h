//
// File:   codegen.h
// Author: p922221
//
// Created on 4 de Abril de 2008, 14:26
//

#ifndef _CODEGEN_H
#define	_CODEGEN_H

#include <fstream>
#include <string>
#include "treenode.h"
#include "definitions.h"
#include "symtab.h"

using namespace std;

namespace bc {

    class CodeGen {
    private:
        string filein;
        string currentLine;
        ofstream *fileout;
        unsigned int locals;
        unsigned int scope;

    public:
        CodeGen(string filein, string fileout);
        ~CodeGen();
        void generate(TreeNode *syntaxTree, vector<SYMTAB *> symtabs);

    private:
        void emitFile(const char *file);
        void emitVersion();
        void emitBreakline();
        void emitAlign(int align);
        void emitComment(const char *comment);
        void emitSection(SectionType section);
        void emitInitMethod(const char *name, unsigned int line);
        void generateVars(vector<SYMTAB *> symtabs);
        void generateLine(TreeNode *tree);
        void generateDim(TreeNode *tree);
        void generateDeclare(TreeNode *tree);
        void generatePrint(TreeNode *tree);
    };
}

#endif	/* _CODEGEN_H */
