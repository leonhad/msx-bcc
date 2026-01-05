// 
// File:   attributes.h
// Author: p922221
//
// Created on 1 de Abril de 2008, 14:21
//

#ifndef ATTRIBUTES_H
#define	ATTRIBUTES_H

#include "definitions.h"
#include <string>

namespace bc {
    class Attributes {
    public:
        definitions::TokenType op;
        std::string val;
        std::string val2;
        std::string name;

        Attributes();

        ~Attributes();
    };
}

#endif	/* ATTRIBUTES_H */
