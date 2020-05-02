#include <iostream>
#include "AVLtree.h"

int main() {
    AVLtree<int> testAVLTree;
    int a=1,b=4,c=6,d=2,e=3,f=22,g=18;
    testAVLTree.insert(a);
    testAVLTree.insert(b);
    testAVLTree.insert(c);
    testAVLTree.insert(d);
    testAVLTree.insert(e);
    /*
    testAVLTree.insert(f);
    testAVLTree.insert(g);
    */
    return 0;
}