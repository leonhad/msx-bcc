#include "codegen.h"
#include "numbers.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace definitions;

namespace bc
{

    CodeGen::CodeGen(const std::string &output) : output{output}, locals{0}, scope{0}
    {
    }

    CodeGen::~CodeGen()
    {
        if (output)
        {
            if (output.is_open())
            {
                output.flush();
                output.close();
            }
        }
    }

    void CodeGen::emit_init_method(const char *name, unsigned int line)
    {
        string _name = "_";
        _name += name;

        output << ".globl _" << name << endl;
        output << _name << ":" << endl;
    }

    void CodeGen::generate(const TreeNode *syntax_tree, const vector<SYMBOL_TABLE> &symbols)
    {
        emit_comment("BCC compilation from MSX Basic");
        emit_version();
        emit_break_line();

        // vars
        emit_section(S_DATA);
        generate_vars(symbols);

        emit_break_line();

        // Program
        emit_section(S_TEXT);
        output << "Ltext0:" << endl;

        emit_init_method("basic_start", 0);
        output << "\tpush %rbp" << endl;
        output << "\tmov %rsp, %rbp" << endl;
        emit_break_line();

        for (auto i = syntax_tree->child.begin(); i != syntax_tree->child.end(); ++i)
        {
            switch ((*i)->kind)
            {
            case LINE_K:
                emit_init_method((*i)->attr.value.c_str(), (*i)->lineno + 1);
                generate_line(*i);

                if ((i + 1) == syntax_tree->child.end())
                {
                    output << "\tleave" << endl;
                    output << "\tret" << endl;
                }

                emit_break_line();
                break;
            default:
                cerr << "Tipo de TreeNode não esperado. " << endl;
                break;
            }
        }
    }

    void CodeGen::generate_line(TreeNode *tree)
    {
        ostringstream _tempLine;
        _tempLine << "L" << locals;

        output << "L" << locals << ":" << endl;
        locals++;

        for (auto &i : tree->child)
        {
            switch (i->kind)
            {
            case DIM_K:
                generate_dim(i);
                break;
            case END_K:
                output << "\tcall _basic_end" << endl;
                break;
            case PRINT_K:
                generate_print(i);
                break;
            default:
                cerr << "Tipo de TreeNode não esperado." << endl;
                break;
            }
        }
    }

    void CodeGen::generate_dim(TreeNode *tree)
    {
        for (const auto &i : tree->child)
        {
            switch (i->kind)
            {
            case DECLARE_K:
                generate_declare(i);
                break;
            default:
                cerr << "Tipo de TreeNode não esperado." << endl;
                break;
            }
        }
    }

    void CodeGen::generate_declare(const TreeNode *tree)
    {
        string name = tree->attr.name;
        if (tree->type == STRING_T)
        {
            name += "$";
        }

        if (tree->attr.operation == DIM)
        {
            unsigned int size = to_int(tree->attr.value);

            if (const unsigned int size2 = to_int(tree->attr.value_2))
            {
                size *= size2;
            }

            if (tree->type == STRING_T)
            {
                // String size
                size *= 256;
            }
            else if (tree->type == NUMERIC_T)
            {
                // Numeric size
                size *= 4;
            }
            output << "\txorq %rax, %rax" << endl;
            output << "\tmovq $" << size << ", %rcx" << endl;
            output << "\tmovq _" << name << "@GOTPCREL(%rip), %rdx" << endl;
            output << ".LC" << locals << ":" << endl;
            output << "\tmovl %eax, (%edx)" << endl;
            output << "\tloop .LC" << locals << endl;

            locals++;
            emit_break_line();
        }
    }

    void CodeGen::generate_print(const TreeNode *tree)
    {
    }

    void CodeGen::emit_file(const char *file)
    {
    }

    void CodeGen::emit_version()
    {
        output << "\t.version \"1.0\"" << endl;
    }

    void CodeGen::emit_break_line()
    {
        output << endl;
    }

    void CodeGen::emit_section(const SectionType section)
    {
        auto _section = "";

        switch (section)
        {
        case S_RDATA:
            break;
            _section = ".rdata";
        case S_DATA:
            _section = ".data";
            break;
        case S_BSS:
            _section = ".bss";
            break;
        case S_TEXT:
            _section = ".text";
            break;
        }

        output << "\t" << _section << endl;
    }

    void CodeGen::emit_comment(const char *comment)
    {
        output << "\t// " << comment << endl;
    }

    void CodeGen::emit_align(const int align)
    {
        output << "\t.align " << align << endl;
    }

    void CodeGen::generate_vars(const vector<SYMBOL_TABLE> &symbols)
    {
        string name;
        unsigned int size;

        emit_align(8);

        for (const auto &symtab : symbols)
        {
            switch (symtab.variable_type)
            {
            case DIM_V:
                size = symtab.size_left;
                if (symtab.size_right)
                {
                    size *= symtab.size_right;
                }
                name = symtab.name;
                if (symtab.expression_type == STRING_T)
                {
                    name += "$";
                    // String size
                    size *= 256;
                }
                else if (symtab.expression_type == NUMERIC_T)
                {
                    // Numeric size
                    size *= 4;
                }

                output << "\t.lcomm _" << name << "," << size << endl;
                break;
            default:
                break;
            }
        }
    }
}
