//
// File:   analyze.h
// Author: p922221
//
// Created on 2 de Abril de 2008, 11:35
//

#ifndef _ANALYZE_H
#define	_ANALYZE_H

#include "treenode.h"
#include "symtab.h"

namespace bc
{
    class Analyze
    {
    private:
        Symtab *symtab;
        
    public:
        Analyze();
        ~Analyze();
        vector<SYMTAB *> buildSymtab(TreeNode * syntaxTree);
        
    private:
        void traverse(TreeNode * treeNode, void (Analyze::* preProc)(TreeNode *), void (Analyze::* postProc)(TreeNode *));
        void insertNode(TreeNode * treeNode);
        void nullProc(TreeNode * treeNode);
    };
}

#endif	/* _ANALYZE_H */

