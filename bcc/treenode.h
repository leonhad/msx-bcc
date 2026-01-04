//
// File:   treenod.h
// Author: leonardo.costa
//
// Created on 11 de Setembro de 2006, 13:01
//

#ifndef _treenod_h
#define	_treenod_h

#include <vector>
#include "definitions.h"
#include "attributes.h"

namespace bc {
    
    class TreeNode {
    public:
        TreeNode(definitions::NodeKind kind, unsigned int lineno);
        ~TreeNode();
        
        std::vector<TreeNode *> child;
        TreeNode *sibling;
        int lineno;
        definitions::NodeKind nodekind;
        union Kind {
            definitions::NodeKind stmt;
            definitions::ExpKind exp;
        } kind;
        Attributes attr;
        definitions::ExpType type;
    };
    
}

#endif
