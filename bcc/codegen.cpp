#include "codegen.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace definitions;

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

            //delete fileout;
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

        emitInitMethod("basic_start", 0);
        *fileout << "\tpush %rbp" << endl;
        *fileout << "\tmov %rsp, %rbp" << endl;
        emitBreakline();

        for (auto i = syntaxTree->child.begin(); i != syntaxTree->child.end(); ++i) {
            switch ((*i)->nodekind) {
                case LineK:
                    emitInitMethod((*i)->attr.val.c_str(), (*i)->lineno + 1);
                    generateLine(*i);

                    if ((i + 1) == syntaxTree->child.end()) {
                        *fileout << "\tleave" << endl;
                        *fileout << "\tret" << endl;
                    }

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
        _tempLine << "L" << locals;

        *fileout << "L" << locals << ":" << endl;
        locals++;
        vector<TreeNode *>::iterator i;
        for (i = tree->child.begin(); i != tree->child.end(); ++i) {
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
        string name = tree->attr.name;
        if (tree->type == String) {
            name += "$";
        }

        if (tree->attr.op == DIM) {
            unsigned int size = atoi(tree->attr.val.c_str());
            const unsigned int size2 = atoi(tree->attr.val2.c_str());

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
            *fileout << "\tmovq _" << name << "@GOTPCREL(%rip), %rdx" << endl;
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
        char *_section;

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
        string name;
        unsigned int size;

        emitAlign(8);

        for (auto i = symtabs.begin(); i != symtabs.end(); ++i) {
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
