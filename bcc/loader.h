//
// File:   parse.h
// Author: leonardo.costa
//
// Created on 8 de Setembro de 2006, 09:26
//

#ifndef _parse_H
#define	_parse_H

#include <fstream>
#include <string>

namespace bc {
    
    class Loader {
        std::ifstream *filein;
        char linebuffer[257];
        
    public:
        explicit Loader(std::string filein);
        ~Loader();
        char next();
        bool eof();
    };
    
}

#endif	/* _parse_H */

