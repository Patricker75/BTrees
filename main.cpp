#include <iostream>

#include "BTree.h"

using namespace std;

int main(int argc, char* argv []) {
    BTree* tree = new BTree(4);

    tree->Insert(0);
    tree->Insert(10);
    tree->Insert(20);
    tree->Insert(30);
    tree->Insert(40);
    tree->Insert(50);
    tree->Insert(60);
    tree->Insert(70);
    tree->Insert(80);
    // tree->Insert(90);
    // tree->Insert(100);

    return 0;
}