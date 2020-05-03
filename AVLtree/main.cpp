#include <iostream>
#include "AVLtree.h"

struct songKey{
    int songID;
    int songNumberOfPlays;
};

struct artistKey{
    int artistID;
};

struct artistData{
    // arrays, AVLtree of songs ...
};

class AVLSongsTree : public AVLtree<songKey,int>{

    public:

    explicit AVLSongsTree()= default;

};

class AVLArtistsTree : public AVLtree<artistKey,artistData>{

    public:

    explicit AVLArtistsTree()= default;

};


int main() {
    AVLtree<int,int> testAVLTree;
    int zero=0,a=1,b=4,c=6,d=2,e=3,f=22,g=18;
    testAVLTree.insert(a,zero);
    testAVLTree.insert(b,zero);
    testAVLTree.insert(c,zero);
    testAVLTree.insert(d,zero);
    testAVLTree.insert(e,zero);
    testAVLTree.insert(f,zero);
    testAVLTree.insert(g,zero);
    return 0;
}