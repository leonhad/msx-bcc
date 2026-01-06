#include "codegen.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace definitions;

namespace bc
{

    CodeGen::CodeGen(const std::string &output) : locals{0}, scope{0}
    {
        this->outputFile = new ofstream(output);
    }

    CodeGen::~CodeGen()
    {
        if (outputFile)
        {
            if (outputFile->is_open())
            {
                outputFile->flush();
                outputFile->close();
            }

            // delete fileout;
        }
    }

    void CodeGen::emitInitMethod(const char *name, unsigned int line) const
    {
        string _name = "_";
        _name += name;

        *outputFile << ".globl _" << name << endl;
        *outputFile << _name << ":" << endl;
    }

    void CodeGen::generate(TreeNode *syntaxTree, const vector<SYMBOL_TABLE> &symtabs)
    {
        emitComment("BCC compilation from MSX Basic");
        emitVersion();
        emitBreakline();

        // vars
        emitSection(S_DATA);
        generateVars(symtabs);

        emitBreakline();

        // Program
        emitSection(S_TEXT);
        *outputFile << "Ltext0:" << endl;

        emitInitMethod("basic_start", 0);
        *outputFile << "\tpush %rbp" << endl;
        *outputFile << "\tmov %rsp, %rbp" << endl;
        emitBreakline();

        for (auto i = syntaxTree->child.begin(); i != syntaxTree->child.end(); ++i)
        {
            switch ((*i)->kind)
            {
            case LineK:
                emitInitMethod((*i)->attr.val.c_str(), (*i)->lineno + 1);
                generateLine(*i);

                if ((i + 1) == syntaxTree->child.end())
                {
                    *outputFile << "\tleave" << endl;
                    *outputFile << "\tret" << endl;
                }

                emitBreakline();
                break;
            default:
                cerr << "Tipo de TreeNode não esperado. " << endl;
                break;
            }
        }
    }

    void CodeGen::generateLine(TreeNode *tree)
    {
        ostringstream _tempLine;
        _tempLine << "L" << locals;

        *outputFile << "L" << locals << ":" << endl;
        locals++;
        vector<TreeNode *>::iterator i;
        for (i = tree->child.begin(); i != tree->child.end(); ++i)
        {
            switch ((*i)->kind)
            {
            case DimK:
                generateDim(*i);
                break;
            case EndK:
                *outputFile << "\tcall _basic_end" << endl;
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

    void CodeGen::generateDim(TreeNode *tree)
    {
        for (const auto & i : tree->child)
        {
            switch (i->kind)
            {
            case DeclareK:
                generateDeclare(i);
                break;
            default:
                cerr << "Tipo de TreeNode não esperado." << endl;
                break;
            }
        }
    }

    void CodeGen::generateDeclare(TreeNode *tree)
    {
        string name = tree->attr.name;
        if (tree->type == String)
        {
            name += "$";
        }

        if (tree->attr.op == DIM)
        {
            unsigned int size = atoi(tree->attr.val.c_str());

            if (const unsigned int size2 = atoi(tree->attr.val2.c_str()))
            {
                size *= size2;
            }

            if (tree->type == String)
            {
                // String size
                size *= 256;
            }
            else if (tree->type == Integer)
            {
                // Integer size
                size *= 4;
            }
            *outputFile << "\txorq %rax, %rax" << endl;
            *outputFile << "\tmovq $" << size << ", %rcx" << endl;
            *outputFile << "\tmovq _" << name << "@GOTPCREL(%rip), %rdx" << endl;
            *outputFile << ".LC" << locals << ":" << endl;
            *outputFile << "\tmovl %eax, (%edx)" << endl;
            *outputFile << "\tloop .LC" << locals << endl;

            locals++;
            emitBreakline();
        }
    }

    void CodeGen::generatePrint(TreeNode *tree)
    {
    }

    void CodeGen::emitFile(const char *file)
    {
    }

    void CodeGen::emitVersion()
    {
        *outputFile << "\t.version \"1.0\"" << endl;
    }

    void CodeGen::emitBreakline()
    {
        *outputFile << endl;
    }

    void CodeGen::emitSection(const SectionType section) const
    {
        char *_section;

        switch (section)
        {
        case S_RDATA:
            break;
            _section = (char *)".rdata";
        case S_DATA:
            _section = (char *)".data";
            break;
        case S_BSS:
            _section = (char *)".bss";
            break;
        case S_TEXT:
            _section = (char *)".text";
            break;
        }
        *outputFile << "\t" << _section << endl;
    }

    void CodeGen::emitComment(const char *comment) const
    {
        *outputFile << "\t// " << comment << endl;
    }

    void CodeGen::emitAlign(const int align) const
    {
        *outputFile << "\t.align " << align << endl;
    }

    void CodeGen::generateVars(const vector<SYMBOL_TABLE> &symtabs) const
    {
        string name;
        unsigned int size;

        emitAlign(8);

        for (const auto &symtab : symtabs)
        {
            switch (symtab.varType)
            {
            case DimV:
                size = symtab.size1;
                if (symtab.size2)
                {
                    size *= symtab.size2;
                }
                name = symtab.name;
                if (symtab.expType == String)
                {
                    name += "$";
                    // String size
                    size *= 256;
                }
                else if (symtab.expType == Integer)
                {
                    // Integer size
                    size *= 4;
                }
                *outputFile << "\t.lcomm _" << name << "," << size << endl;
                break;
            default:
                break;
            }
        }
    }
}
