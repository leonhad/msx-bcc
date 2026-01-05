#pragma once

#include "analyze.h"
#include <fstream>
#include <map>
#include <string>

namespace bc
{
    class Scan
    {
        std::fstream *filein;
        unsigned int lineno;
        int current;
        std::map<std::string, definitions::TokenType> reservedWords;

      public:
        explicit Scan(std::string filein);

        ~Scan();

        definitions::TokenType getToken();

        char getNextChar();

        void ungetNextChar();

        definitions::TokenType reservedLookup(std::string s);

        definitions::TokenType getSpecialChar(char c);

        std::string tokenString;

        unsigned int getLineno();
    };
} // namespace bc
