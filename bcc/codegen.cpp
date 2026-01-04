#include "codegen.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

namespace bc {

    CodeGen::CodeGen(string filein, string fileout) {
        this->filein = filein;
        this->fileout = new ofstream(fileout.c_str());
        locals = 0;
        scope = 0;
    }

    CodeGen::~CodeGen() {
        if (fileout) {
            if (fileout->is_open()) {
                fileout->flush();
                fileout->close();
            }
            delete fileout;
        }
    }

    void CodeGen::emitInitMethod(const char *name, unsigned int line) {
        string _name = "_";
        _name += name;

        //emitAlign(2);
        *fileout << ".globl _" << name << endl;
        *fileout << _name << ":" << endl;
    }

    void CodeGen::generate(TreeNode *syntaxTree, vector<SYMTAB *> symtabs) {
        emitComment("BCC compilation from MSX Basic");
        emitFile(filein.c_str());
        emitVersion();
        emitBreakline();

        // vars
        emitSection(S_DATA);
        generateVars(symtabs);

        emitBreakline();

        // Program
        emitSection(S_TEXT);
        *fileout << "Ltext0:" << endl;
        //emitAlign(2);
        //*fileout << ".globl _basic_start" << endl;

        emitInitMethod("basic_start", 0);
        //emitStabs("basic_start:F1", 36, 0, 0, "_basic_start");
        //*fileout << "_basic_start:" << endl;
        //*fileout << "\t.file 1 \"" << filein.c_str() << "\"" << endl;

        *fileout << "\tpush %rbp" << endl;
        *fileout << "\tmov %rsp, %rbp" << endl;
        emitBreakline();

//        if (syntaxTree->child.size() > 0) {
//            *fileout << "\tjmp _" << syntaxTree->child[0]->attr.val << endl;
//        }

        //*fileout << "Lend:" << endl;
        //*fileout << "\tcall _basic_end" << endl;
        emitBreakline();

        //*fileout << "\tleave" << endl;
        //*fileout << "\tret" << endl;
        emitBreakline();

        vector<TreeNode *>::iterator i;
        for (i = syntaxTree->child.begin(); i != syntaxTree->child.end(); i++) {
            switch ((*i)->nodekind) {
                case LineK:
                    emitInitMethod((*i)->attr.val.c_str(), (*i)->lineno + 1);
                    generateLine(*i);

                    i++;
                    if (i == syntaxTree->child.end()) {
                        *fileout << "\tleave" << endl;
                        *fileout << "\tret" << endl;
                    } else {
                        //*fileout << "\tjmp _" << (*i)->attr.val << endl;
                    }
                    i--;

                    emitBreakline();
                    break;
                default:
                    cerr << "Tipo de TreeNode não esperado. " << endl;
                    break;
            }
        }
    }

    void CodeGen::generateLine(TreeNode *tree) {
        ostringstream _tempLine;
        _tempLine << "L" << locals; // << "-_" << tree->attr.val;

        *fileout << "L" << locals << ":" << endl;
        locals++;
        vector<TreeNode *>::iterator i;
        for (i = tree->child.begin(); i != tree->child.end(); i++) {
            switch ((*i)->nodekind) {
                case DimK:
                    generateDim(*i);
                    break;
                case EndK:
                    *fileout << "\tcall _basic_end" << endl;
                    break;
                case PrintK:
                    generatePrint(*i);
                    break;
                default:
                    cerr << "Tipo de TreeNode não esperado." << endl;
                    break;
            }
        }
    }

    void CodeGen::generateDim(TreeNode *tree) {
        vector<TreeNode *>::iterator i;
        for (i = tree->child.begin(); i != tree->child.end(); i++) {
            switch ((*i)->nodekind) {
                case DeclareK:
                    generateDeclare(*i);
                    break;
                default:
                    cerr << "Tipo de TreeNode não esperado." << endl;
                    break;
            }
        }
    }

    void CodeGen::generateDeclare(TreeNode *tree) {
        register unsigned int size;
        string name = tree->attr.name;
        if (tree->type == String) {
            name += "$";
        }

        if (tree->attr.op == DIM) {
            register unsigned int size2;

            size = atoi(tree->attr.val.c_str());
            size2 = atoi(tree->attr.val2.c_str());
            if (size2) {
                size *= size2;
            }
            if (tree->type == String) {
                // String size
                size *= 256;
            } else if (tree->type == Integer) {
                // Integer size
                size *= 4;
            }
            *fileout << "\txorq %rax, %rax" << endl;
            *fileout << "\tmovq $" << size << ", %rcx" << endl;
            *fileout << "\tmovq _" << name << "(%rip), %rdx" << endl;
            *fileout << ".LC" << locals << ":" << endl;
            *fileout << "\tmovl %eax, (%edx)" << endl;
            *fileout << "\tloop .LC" << locals << endl;

            locals++;
            emitBreakline();
        }
    }

    void CodeGen::generatePrint(TreeNode *tree) {

    }

    void CodeGen::emitFile(const char *file) {

    }

    void CodeGen::emitVersion() {
        *fileout << "\t.version \"1.0\"" << endl;
    }

    void CodeGen::emitBreakline() {
        *fileout << endl;
    }

    void CodeGen::emitSection(SectionType section) {
        register char *_section;

        switch (section) {
            case S_RDATA:
                break;
                _section = (char*) ".rdata";
            case S_DATA:
                _section = (char*) ".data";
                break;
            case S_BSS:
                _section = (char*) ".bss";
                break;
            case S_TEXT:
                _section = (char*) ".text";
                break;
        }
        *fileout << "\t" << _section << endl;
    }

    void CodeGen::emitComment(const char *comment) {
        *fileout << "\t// " << comment << endl;
    }

    void CodeGen::emitAlign(int align) {
        *fileout << "\t.align " << align << endl;
    }

    void CodeGen::generateVars(vector<SYMTAB *> symtabs) {
        vector<SYMTAB *>::iterator i;
        string name;
        register unsigned int size;

        emitAlign(8);

        for (i = symtabs.begin(); i != symtabs.end(); i++) {
            switch ((*i)->varType) {
                case DimV:
                    size = (*i)->size1;
                    if ((*i)->size2) {
                        size *= (*i)->size2;
                    }
                    name = (*i)->name;
                    if ((*i)->expType == String) {
                        name += "$";
                        // String size
                        size *= 256;
                    } else if ((*i)->expType == Integer) {
                        // Integer size
                        size *= 4;
                    }
                    *fileout << "\t.lcomm _" << name << "," << size << endl;
                    break;
                default:
                    break;
            }
        }
    }
}
