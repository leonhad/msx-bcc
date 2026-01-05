#pragma once

#include <string>

namespace definitions
{

    /* states in scanner DFA */
    enum StateType
    {
        START,
        INNUM,
        INID,
        INSTRING,
        DONE
    };

    /** bookkeeping tokens */
    enum TokenType
    {
        ENDFILE,
        ERROR,
        ENDLINE,
        ENDCOMMAND,
        /* reserved words */
        DATA,
        DIM,
        ELSE,
        FOR,
        IF,
        NEXT,
        THEN,
        TO,
        END,
        PRINT,
        /* multicharacter tokens */
        ID,
        NUM,
        STRING,
        /* special symbols */
        EQ,
        GT,
        LT,
        PLUS,
        MINUS,
        TIMES,
        OVER,
        LPAREN,
        RPAREN,
        SEMI,
        CIFRAO,
        PERCENT,
        ASSIGN,
        COMMA,
        LBRACET,
        RBRACET,
        DOLLAR
    };

    struct ReservedWords
    {
        std::string str;
        TokenType tok;
    };

    enum NodeKind
    {
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

    enum ExpKind
    {
        OpK,
        ConstK,
        IdK
    };

    /* ExpType is used for type checking */
    enum ExpType
    {
        Integer,
        String
    };

    enum SectionType
    {
        S_RDATA,
        S_DATA,
        S_BSS,
        S_TEXT
    };
} // namespace definitions
