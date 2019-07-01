// 
// File:   attributes.h
// Author: p922221
//
// Created on 1 de Abril de 2008, 14:21
//

#ifndef _ATTRIBUTES_H
#define	_ATTRIBUTES_H

#include "definitions.h"
#include <string>

using namespace definitions;

namespace bc {
    class Attributes {
    public:
        TokenType op;
        std::string val;
        std::string val2;
        std::string name;
        
        Attributes();
        ~Attributes();
    };
}

#endif	/* _ATTRIBUTES_H */

