//
// File: scan.h
// Author: leonardo.costa
//
// Created on 12 de Setembro de 2006, 14:03
//

#ifndef _scan_H
#define	_scan_H

#include "analyze.h"
#include <fstream>
#include <string>
#include <map>

namespace bc {
    class Scan {
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
}

#endif	/* _scan_H */
