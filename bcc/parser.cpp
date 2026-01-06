#include "parser.h"
#include <iostream>

using namespace std;
using namespace definitions;

namespace bc
{

    Parser::Parser(string filein)
    {
        scan = new Scan(filein);
    }

    Parser::~Parser()
    {
        if (scan)
            delete scan;
    }

    void Parser::match(TokenType expected)
    {
        if (token == expected)
        {
            token = scan->getToken();
        }
        else
        {
            cerr << "unexpected token: " << token << " " << scan->tokenString << endl;
        }
    }

    TreeNode Parser::parse()
    {
        TreeNode treeNode{ProgramK, 0};

        while ((token = scan->getToken()) != ENDFILE)
        {
            treeNode.addChild(line_sequence());
        }
        return treeNode;
    }

    TreeNode Parser::line_sequence()
    {
        TreeNode line{LineK, scan->getLineno()};
        line.attr.val = scan->tokenString;
        match(NUM);

        while (true)
        {
            switch (token)
            {
            case DIM:
                line.addChild(dim_sequence());
                break;
            case END:
                line.addChild(end_sequence());
                break;
            case PRINT:
                line.addChild(print_sequence());
                break;
            case ID:
                line.addChild(assign_sequence());
                break;
            case ENDLINE:
                break;
            default:
                cerr << "invalid token: " << token << " '" << scan->tokenString << "'" << endl;
                while (token != ENDLINE && token != ENDFILE && token != ERROR && token != ENDCOMMAND)
                {
                    token = scan->getToken();
                }
            }
            if (token == ENDCOMMAND)
            {
                match(ENDCOMMAND);
            }
            else
            {
                break;
            }
        }
        return line;
    }

    TreeNode Parser::assign_sequence()
    {
        TreeNode assign{AssignK, scan->getLineno()};
        assign.attr.name = scan->tokenString;
        match(ID);

        if (token == DOLLAR)
        {
            assign.type = String;
            match(DOLLAR);
        }
        else
        {
            assign.type = Integer;
        }
        match(EQ);
        assign.addChild(exp_sequence());

        return assign;
    }

    TreeNode Parser::exp_sequence()
    {
        TreeNode exp{ExpK, scan->getLineno()};

        if (token == MINUS || token == PLUS)
        {
            exp.attr.op = token;
            match(token);
        }
        if (token == NUM)
        {
            exp.attr.val = (char *)scan->tokenString.c_str();
            exp.kind = ConstK;
        }
        if (token == ID)
        {
            exp.attr.val = (char *)scan->tokenString.c_str();
        }
        return exp;
    }

    TreeNode Parser::end_sequence()
    {
        TreeNode end{EndK, scan->getLineno()};
        match(END);
        return end;
    }

    TreeNode Parser::print_sequence()
    {
        TreeNode print{PrintK, scan->getLineno()};
        match(PRINT);

        // FIXME add more exporessions in print
        bool first = true;
        do
        {
            if (!first)
            {
                if (token == SEMI)
                {
                    match(SEMI);
                }
                else
                {
                    match(COMMA);
                }
            }

            first = false;
        } while (token != ENDLINE && token != ERROR && token != ENDFILE && token != ENDCOMMAND && token == COMMA);

        return print;
    }

    TreeNode Parser::dim_sequence()
    {
        TreeNode dim{DimK, scan->getLineno()};
        match(DIM);
        bool first = true;
        do
        {
            if (!first)
            {
                match(COMMA);
            }
            dim.child.push_back(declare_sequence());
            first = false;
        } while (token != ENDLINE && token != ERROR && token != ENDFILE && token != ENDCOMMAND && token == COMMA);
        return dim;
    }

    TreeNode Parser::declare_sequence()
    {
        TreeNode declare{DeclareK, scan->getLineno()};
        declare.attr.op = DIM;
        declare.attr.name = scan->tokenString;
        match(ID);

        if (token == DOLLAR)
        {
            match(DOLLAR);
            declare.type = String;
        }
        else
        {
            declare.type = Float;
        }

        match(LPAREN);
        declare.attr.val = scan->tokenString;
        match(NUM);
        if (token == COMMA)
        {
            match(COMMA);
            declare.attr.val2 = scan->tokenString;
            match(NUM);
        }
        match(RPAREN);
        return declare;
    }

    TreeNode Parser::stmt_sequence()
    {
        // TreeNode * t = statement();
        // TreeNode * p = t;

        //        if (token == DIM) {
        //            treeNode = Utils::newDimNode(scan->getLineno());
        //        }
        while ((token != ENDFILE) && (token != ENDCOMMAND))
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
        return TreeNode{StmtK, scan->getLineno()};
    }

    TreeNode Parser::statement()
    {
        TreeNode t{StmtK, scan->getLineno()};
        switch (token)
        {
        case IF:
            // t = if_stmt();
            break;
        case ID:
            // t = assign_stmt();
            break;
        default:
            cout << "unexpected token -> " << token << " " << scan->tokenString << endl;
            token = scan->getToken();
            break;
        }

        return t;
    }
}
