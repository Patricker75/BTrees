#ifndef BTREENODE_H
#define BTREENODE_H

class BTreeNode {
private:
    int* keys;
    BTreeNode** children;

    int numKeys;
    int degree;
    bool isLeaf;
public:
    BTreeNode(int degree, bool isLeaf) {
        this->degree = degree;
        this->isLeaf = isLeaf;

        this->numKeys = 0;

        this->keys = new int[degree - 1];
        this->children = new BTreeNode*[degree];
        for (int i = 0; i < degree; i++) {
            this->children[i] = nullptr;
        }
    };

    void Insert(int data) {
        for (int i = 0; i < this->numKeys; i++) {
            if (data < this->keys[i]) {
                int temp = this->keys[i];
                this->keys[i] = data;
                data = temp;
            }
        }

        this->keys[this->numKeys] = data;
        this->numKeys++;
    }
    
    void LocateCorrectLeaf(int data) {
        if (this->isLeaf) {
            this->Insert(data);
        }
        else {
            for (int i = 0; i < this->numKeys; i++) {
                if (data < this->keys[i]) {
                    if (this->children[i]->IsFilled()) {
                        this->SplitChild(i, this->children[i]);
                        this->LocateCorrectLeaf(data);
                        return;
                    }
                    else {
                        this->children[i]->LocateCorrectLeaf(data);
                        return;
                    }
                }
            }

            if (this->children[this->numKeys]->IsFilled()) {
                this->SplitChild(this->numKeys, this->children[this->numKeys]);
                this->LocateCorrectLeaf(data);
            }
            else {
                this->children[this->numKeys]->LocateCorrectLeaf(data);
            }
        }
    }

    void SplitChild(int indexOfChild, BTreeNode* child) {
        int median = this->GetMedian();

        BTreeNode* newChild = new BTreeNode(this->degree, child->isLeaf);

        for (int i = median + 1; i < child->numKeys; i++) {
            newChild->Insert(child->keys[i]);
            child->numKeys--;
        }

        this->Insert(child->keys[median]);
        child->numKeys--;

        this->children[indexOfChild + 1] = newChild;
    }

    BTreeNode** GetChildren() {
        return this->children;
    }

    bool SetLeafBool(bool isLeaf) {
        this->isLeaf = isLeaf;
    }

    int GetMedian() {
        if (this->degree % 2 == 0) {
            return this->degree / 2 - 1;
        }
        return this->degree / 2;
    }

    bool IsFilled() {
        return this->numKeys == this->degree - 1;
    }
};

#endif