// 
// File:   definitions.h
// Author: p922221
//
// Created on 1 de Abril de 2008, 14:24
//

#ifndef _DEFINITIONS_H
#define	_DEFINITIONS_H

#include <string>

using namespace std;

namespace definitions {
    
    /* states in scanner DFA */
    enum StateType {
        START, INNUM, INID, INSTRING, DONE
    };
    
    /** book-keeping tokens */
    enum TokenType {
        ENDFILE, ERROR, ENDLINE, ENDCOMMAND,
        /* reserved words */
        DATA, DIM, ELSE, FOR, IF, NEXT, THEN, TO, END, PRINT,
        /* multicharacter tokens */
        ID, NUM, STRING,
        /* special symbols */
        EQ, GT, LT, PLUS, MINUS, TIMES, OVER, LPAREN, RPAREN, SEMI,
	CIFRAO, PERCENT, ASSIGN, COMMA, LBRACET, RBRACET, DOLLAR
    };
    
    struct ReservedWords {
        string str;
        TokenType tok;
    };
    
    enum NodeKind {
        ProgramK,
        LineK,
        StmtK,
        ExpK,
        IfK,
        RepeatK,
        AssignK,
        DimK,
        DeclareK,
        EndK,
        PrintK
    };
    
    enum ExpKind {
        OpK,
        ConstK,
        IdK
    };
    
    /* ExpType is used for type checking */
    enum ExpType {
        Integer,
        String
    };
    
    enum SectionType {
        S_RDATA,
        S_DATA,
        S_BSS,
        S_TEXT
    };
}

#endif	/* _DEFINITIONS_H */

