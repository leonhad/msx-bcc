//
// File:   parse.h
// Author: leonardo.costa
//
// Created on 8 de Setembro de 2006, 09:26
//

#ifndef _parse_H
#define	_parse_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace bc {
    
    class Loader {
    private:
        ifstream *filein;
        char linebuffer[257];
        
    public:
        Loader(string filein) throw(string);
        ~Loader();
        char next();
        bool eof();
    };
    
}

#endif	/* _parse_H */

