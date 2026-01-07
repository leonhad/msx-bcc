#pragma once

#include "analyze.h"
#include <fstream>
#include <map>
#include <string>

namespace bc
{
    class Scan
    {
        std::fstream filein;
        unsigned int lineno;
        int current;
        std::map<std::string, TokenType> reserved_words;

      public:
        explicit Scan(const std::string &filein);

        ~Scan();

        TokenType next_token();

        char next_char();

        void unget_char();

        TokenType reserved_lookup(const std::string &name);

        static TokenType get_special_char(char check_char);

        std::string token_string;

        unsigned int current_line_number() const;
    };
}
