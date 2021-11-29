#ifndef BTREE_H
#define BTREE_H

#include "BTreeNode.h"

class BTree {
private:
    BTreeNode* root;
    int degree;
public:
    BTree(int degree) {
        this->degree = degree;
        this->root = nullptr;
    };

    void Insert(int data) {
        if (this->root == nullptr) {
            this->root = new BTreeNode(this->degree, true);
            this->root->Insert(data);
            return;
        }
        else if (this->root->IsFilled()) {
            BTreeNode* newRoot = new BTreeNode(this->degree, false);
            this->root->SetLeafBool(false);

            newRoot->GetChildren()[0] = this->root;
            newRoot->SplitChild(0, this->root);

            this->root = newRoot;
            this->root->LocateCorrectLeaf(data);
        }
        else {
            this->root->LocateCorrectLeaf(data);
        }
    }
    
};

#endif