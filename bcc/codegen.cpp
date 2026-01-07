#include "codegen.h"

#include "messages.h"
#include "numbers.h"

#include <algorithm>
#include <iostream>

using namespace std;

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

    void CodeGen::emit_init_method(const char *name)
    {
        output << "\t.p2align 4" << endl;
        output << "\t.type _" << name << ", @function " << endl;
        output << "\t.globl _" << name << endl;
        output << "_" << name << ":" << endl;
    }

    void CodeGen::generate(const TreeNode *syntax_tree, const vector<SYMBOL_TABLE> &table)
    {
        this->symbols = table;

        emit_comment("BCC compilation from MSX Basic");
        emit_version();
        emit_break_line();

        // vars
        emit_section(S_DATA);
        generate_vars();

        emit_break_line();

        // Program
        emit_section(S_TEXT);
        output << "Ltext0:" << endl;

        emit_init_method("basic_start");
        output << "\tpush %rbp" << endl;
        output << "\tmov %rsp, %rbp" << endl;
        emit_break_line();

        for (const auto &i : syntax_tree->child)
        {
            switch (i->kind)
            {
            case LINE_K:
                generate_line(i);

                emit_break_line();
                break;
            default:
                error("Unexpected treenode. ");
                break;
            }
        }

        output << "\tleave" << endl;
        output << "\tret" << endl;
    }

    void CodeGen::generate_line(const TreeNode *tree)
    {
        output << "L" << tree->attr.value << ":" << endl;

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
            case ASSIGN_K:
                generate_assign(i);
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

    void CodeGen::generate_assign(const TreeNode *tree)
    {
        const auto name = tree->attr.name;
        const auto search_symbol = find_if(symbols.begin(), symbols.end(), [name](const auto &table) { return table.name == name; } );
        if (search_symbol == symbols.end())
        {
            throw runtime_error("variable '" + name + "' not found in symbol table");
        }

        const auto& symbol = *search_symbol;

        if (symbol.variable_type == VARIABLE_V)
        {
            if (symbol.expression_type == NUMERIC_T)
            {
                // set value in eax
                if (tree->child.size() == 1 && tree->child[0]->kind == CONSTANT_K)
                {
                    output << "\tmovq $" << tree->child[0]->attr.value << ", %rax" << endl;
                }

                // get value to eax
                output << "\tmovq %rax, _" << name << "@GOTPCREL(%rip)" << endl;
            }
        }
    }

    void CodeGen::generate_dim(const TreeNode *tree)
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

    void CodeGen::generate_vars()
    {
        emit_align(8);

        for (const auto &symtab : symbols)
        {
            unsigned int size = symtab.size_left;
            string name = symtab.name;
            if (symtab.expression_type == STRING_T)
            {
                name += "$";
            }

            output << "\t.globl	_" << name << endl;
            output << "_" << name << ":" << endl;
            switch (symtab.variable_type)
            {
            case DIM_V:
                if (symtab.size_right)
                {
                    size *= symtab.size_right;
                }
                if (symtab.expression_type == STRING_T)
                {
                    // String size
                    size *= 256;
                }
                else if (symtab.expression_type == NUMERIC_T)
                {
                    // Numeric size
                    size *= 8;
                }

                emit_align(32);
                output << "\t.zero " << size << endl;
                output << "\t.type _" << name << ",@object" << endl;
                output << "\t.size _" << name << "," << size << endl;
                break;
            case VARIABLE_V:
                if (symtab.expression_type == STRING_T)
                {
                    // String size
                    size = 256;
                }
                else if (symtab.expression_type == NUMERIC_T)
                {
                    size = 8;
                }

                emit_align(4);
                output << "\t.zero " << size << endl;
                output << "\t.long 0" << endl;
                // output << "\t.type @integer" << endl;
                output << "\t.size _" << name << ", " << size << endl;
            default:
                break;
            }
        }
    }
}
