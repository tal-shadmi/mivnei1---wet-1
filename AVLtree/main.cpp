#include <iostream>
#include "AVLtree.h"

int main() {
    AVLtree<int, int> tree;

    int a=1,b=2,c=3,d=4,e=5,f=6,g=7,h=8,i=9,j=10,k=11,l=12,m=13,n=14,o=15,p=16,
            q=17,r=18,s=19,t=20,u=21,v=22,w=23,x=24,y=25,z=26;
    //-------------------3 BF: -1 Height: 2----------------------------------//
    //-------------------5 BF: 0 Height: 1-----------------------------------//
    //root deletion no roll successor is a neighbour
    //correct output
    //2 BF: 0 Height: 0
    //3 BF: 1 Height: 1
    //5 BF: 1 Height: 2
    //6 BF: 0 Height: 0
    tree.insert(d,d);
    tree.insert(e,e);
    tree.insert(c,c);
    tree.insert(b,b);
    tree.insert(f,f);
    tree.erase(d);
    tree.printTree();
    tree.treeClear();
    return 0;
}