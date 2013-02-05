//
// File:   treenod.h
// Author: leonardo.costa
//
// Created on 11 de Setembro de 2006, 13:01
//

#ifndef _treenod_h
#define	_treenod_h

#include <vector>
#include <string>
#include "definitions.h"
#include "attributes.h"

using namespace std;
using namespace definitions;

namespace bc {
    
    class TreeNode {
    public:
        TreeNode(NodeKind kind, unsigned int lineno);
        ~TreeNode();
        
        vector<TreeNode *> child;
        TreeNode *sibling;
        int lineno;
        NodeKind nodekind;
        union Kind {
            NodeKind stmt;
            ExpKind exp;
        } kind;
        Attributes attr;
        ExpType type;
    };
    
}

#endif
