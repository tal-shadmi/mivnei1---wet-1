#include <iostream>
#include "AVLtree.h"
#include "List.h"
using std::cout;
using std::endl;

int main() {
    List<int, char> my_list;
    my_list.printList();
    ListNode<int ,char> *node3 = my_list.insertFirst(1,'a');
    cout << "data: " << node3->data << endl;
    my_list.printList();
    my_list.insertFirst(2,'b');
    my_list.insertFirst(4,'d');
    my_list.printList();
    ListNode<int ,char> *node1 = my_list.getFirst();
    cout << "first: " << node1->key << endl;
    my_list.insertAfterNode(3,'c',node1);
    ListNode<int ,char> *node2 = my_list.getLast();
    cout << "last: " << node2->key << endl;
    ListNode<int ,char> *node4 = my_list.findByKey(4);
    cout << "node4 data: " << node4->data << endl;
    my_list.printList();
    my_list.erase(node1);
    my_list.printList();

    /*
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
     */
    return 0;
}