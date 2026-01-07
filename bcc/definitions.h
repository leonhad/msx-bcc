#pragma once

#include <string>

/* states in scanner DFA */
enum StateType
{
    START,
    IN_NUMBER,
    IN_ID,
    IN_STRING,
    DONE
};

/** bookkeeping tokens */
enum TokenType
{
    END_FILE,
    ERROR,
    END_LINE,
    END_COMMAND,
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
    std::string name;
    TokenType token;
};

enum NodeKind
{
    PROGRAM_K,
    LINE_K,
    STATEMENT_K,
    EXPRESSION_K,
    IF_K,
    REPEAT_K,
    ASSIGN_K,
    DIM_K,
    DECLARE_K,
    END_K,
    PRINT_K,
    // Expressions
    OPERATION_K,
    CONSTANT_K,
    ID_K
};

/* ExpressionType is used for type checking */
enum ExpressionType
{
    NUMERIC_T,
    STRING_T
};

enum SectionType
{
    S_RDATA,
    S_DATA,
    S_BSS,
    S_TEXT
};