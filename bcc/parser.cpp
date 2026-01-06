#include "parser.h"
#include <iostream>

using namespace std;
using namespace definitions;

namespace bc
{

    Parser::Parser(const string &file_input) : line{EOF}, program_line{EOF}, current_token{END_FILE}, scan{file_input}
    {
    }

    void Parser::match(const TokenType expected)
    {
        if (current_token == expected)
        {
            current_token = scan.next_token();
        }
        else
        {
            cerr << "unexpected token: " << current_token << " " << scan.token_string << endl;
        }
    }

    TreeNode *Parser::parse()
    {
        const auto treeNode = new TreeNode{PROGRAM_K, 0};

        while ((current_token = scan.next_token()) != END_FILE)
        {
            treeNode->add_child(line_sequence());
        }

        return treeNode;
    }

    TreeNode *Parser::line_sequence()
    {
        const auto current_line = new TreeNode{LINE_K, scan.current_line_number()};
        current_line->attr.value = scan.token_string;
        match(NUM);

        while (true)
        {
            switch (current_token)
            {
            case DIM:
                current_line->add_child(dim_sequence());
                break;
            case END:
                current_line->add_child(end_sequence());
                break;
            case PRINT:
                current_line->add_child(print_sequence());
                break;
            case ID:
                current_line->add_child(assign_sequence());
                break;
            case END_LINE:
                break;
            default:
                cerr << "invalid token: " << current_token << " '" << scan.token_string << "'" << endl;
                while (current_token != END_LINE && current_token != END_FILE && current_token != ERROR && current_token != END_COMMAND)
                {
                    current_token = scan.next_token();
                }
            }
            if (current_token == END_COMMAND)
            {
                match(END_COMMAND);
            }
            else
            {
                break;
            }
        }

        return current_line;
    }

    TreeNode *Parser::assign_sequence()
    {
        const auto assign = new TreeNode{ASSIGN_K, scan.current_line_number()};
        assign->attr.name = scan.token_string;
        match(ID);

        if (current_token == DOLLAR)
        {
            assign->type = STRING_T;
            match(DOLLAR);
        }
        else
        {
            assign->type = NUMERIC_T;
        }
        match(EQ);
        assign->add_child(exp_sequence());

        return assign;
    }

    TreeNode *Parser::exp_sequence()
    {
        const auto exp = new TreeNode{EXPRESSION_K, scan.current_line_number()};

        if (current_token == MINUS || current_token == PLUS)
        {
            exp->attr.operation = current_token;
            match(current_token);
        }
        if (current_token == NUM)
        {
            exp->attr.value = scan.token_string;
            exp->kind = CONSTANT_K;
        }
        if (current_token == ID)
        {
            exp->attr.value = scan.token_string;
        }

        return exp;
    }

    TreeNode *Parser::end_sequence()
    {
        const auto end = new TreeNode{END_K, scan.current_line_number()};
        match(END);
        return end;
    }

    TreeNode *Parser::print_sequence()
    {
        const auto print = new TreeNode{PRINT_K, scan.current_line_number()};
        match(PRINT);

        // FIXME add more expressions in print
        bool first = true;
        do
        {
            if (!first)
            {
                if (current_token == SEMI)
                {
                    match(SEMI);
                }
                else
                {
                    match(COMMA);
                }
            }

            first = false;
        } while (current_token != END_LINE && current_token != ERROR && current_token != END_FILE && current_token != END_COMMAND && current_token == COMMA);

        return print;
    }

    TreeNode *Parser::dim_sequence()
    {
        const auto dim = new TreeNode{DIM_K, scan.current_line_number()};
        match(DIM);
        bool first = true;
        do
        {
            if (!first)
            {
                match(COMMA);
            }

            dim->add_child(declare_sequence());
            first = false;
        } while (current_token != END_LINE && current_token != ERROR && current_token != END_FILE && current_token != END_COMMAND && current_token == COMMA);
        return dim;
    }

    TreeNode *Parser::declare_sequence()
    {
        const auto declare = new TreeNode{DECLARE_K, scan.current_line_number()};
        declare->attr.operation = DIM;
        declare->attr.name = scan.token_string;
        match(ID);

        if (current_token == DOLLAR)
        {
            match(DOLLAR);
            declare->type = STRING_T;
        }
        else
        {
            declare->type = NUMERIC_T;
        }

        match(LPAREN);
        declare->attr.value = scan.token_string;
        match(NUM);
        if (current_token == COMMA)
        {
            match(COMMA);
            declare->attr.value_2 = scan.token_string;
            match(NUM);
        }

        match(RPAREN);
        return declare;
    }

    TreeNode *Parser::stmt_sequence()
    {
        // TreeNode * t = statement();
        // TreeNode * p = t;

        //        if (token == DIM_V) {
        //            treeNode = Utils::newDimNode(scan.current_line_number());
        //        }
        while ((current_token != END_FILE) && (current_token != END_COMMAND))
        {
            // while ((token != ENDFILE) && (token != THEN) && (token != ELSE)) {
            /*TreeNode * q;
             * match(SEMI);
             * q = statement();
             * if (q!=NULL) {
             * // now p cannot be NULL either
             * if (t==NULL) {
             * t = p = q;
             * } else {
             * p->sibling = q;
             * p = q;
             * }
             * }
             */
        }
        return nullptr;
    }

    TreeNode *Parser::statement()
    {
        const auto t = new TreeNode{STATEMENT_K, scan.current_line_number()};
        switch (current_token)
        {
        case IF:
            // t = if_stmt();
            break;
        case ID:
            // t = assign_stmt();
            break;
        default:
            cout << "unexpected token -> " << current_token << " " << scan.token_string << endl;
            current_token = scan.next_token();
            break;
        }

        return t;
    }
}
