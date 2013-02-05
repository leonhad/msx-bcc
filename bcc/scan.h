//
// File:   scan.h
// Author: leonardo.costa
//
// Created on 12 de Setembro de 2006, 14:03
//

#ifndef _scan_H
#define	_scan_H

#include "treenode.h"
#include "analyze.h"
#include <fstream>
#include <string>
#include <map>

using namespace std;
using namespace definitions;

namespace bc {
    class Scan {
    private:
        fstream *filein;
        unsigned int lineno;
        int current;
	map<string, TokenType> reservedWords;

    public:
        Scan(string filein);
        ~Scan();
        TokenType getToken();
        char getNextChar();
        void ungetNextChar();
        TokenType reservedLookup(string s);
	TokenType getSpecialChar(char c);
        string tokenString;
        unsigned int getLineno();
    };
}

#endif	/* _scan_H */

