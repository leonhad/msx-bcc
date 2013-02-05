//
// File:   parser.h
// Author: leonardo.costa
//
// Created on 8 de Setembro de 2006, 10:22
//

#ifndef _parser_H
#define	_parser_H

#include "loader.h"
#include "globals.h"
#include "treenode.h"
#include "scan.h"

#include <string>

using namespace std;

namespace bc {
    
    class Parser {
    private:
        int line;
        int program_line;
        /* holds current token */
        TokenType token;
        Scan *scan;
        
    public:
        Parser(string filein);
        ~Parser();
        TreeNode *parse();

    private:
        TreeNode *line_sequence();
        TreeNode *dim_sequence();
        TreeNode *declare_sequence();
        TreeNode *end_sequence();
        TreeNode *print_sequence();
        TreeNode *assign_sequence();
        TreeNode *exp_sequence();
        TreeNode *stmt_sequence();
        TreeNode *statement();
        void match(TokenType expected);
    };
    
}

#endif	/* _parser_H */

