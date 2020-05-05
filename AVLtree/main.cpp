#include <iostream>
#include "AVLtree.h"

int main() {
    AVLtree<int,int> testAVLTree;
    int zero=0,a=1,b=4,c=6,d=2,e=3,f=22,g=18,h=10,i=12;
    testAVLTree.insert(a,zero);
    testAVLTree.insert(b,zero);
    testAVLTree.insert(c,zero);
    testAVLTree.insert(d,zero);
    testAVLTree.insert(e,zero);
    testAVLTree.insert(f,zero);
    testAVLTree.insert(g,zero);
    testAVLTree.insert(h,zero);
    testAVLTree.insert(i,zero);
    testAVLTree.erase(g);
    testAVLTree.erase(c);
    testAVLTree.erase(b);
    try {
        testAVLTree.find(g);
    }
    catch (AVLtree<int,int>::NotFound& e){
        printf("18 is not a value in the tree");
    }
    catch (AVLtree<int,int>::BadParameters& e){
        printf("bad parameters!");
    }
    try {
        (testAVLTree.find(e));
    }
    catch (AVLtree<int,int>::NotFound& e){
        printf("3 is a value in the tree");
    }
    catch (AVLtree<int,int>::BadParameters& e){
        printf("bad parameters!");
    }
    return 0;
}