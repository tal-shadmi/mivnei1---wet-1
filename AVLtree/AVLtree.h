//
// Created by Dell on 30/04/2020.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

typedef enum AVLResult_t {
    SUCCESS=1,
    FAILURE=0
}AVLResult;

template <class T>
class AVLtree {

    class AVLNode{
        T* key;
        int height;
        AVLNode* father;
        AVLNode* rightSon;
        AVLNode* leftSon;

        public:
        explicit AVLNode() = delete;
        AVLNode(T* key,int height,AVLNode* father,AVLNode* rightSon,AVLNode* leftSon):
                key(key),height(height),father(father),rightSon(rightSon),leftSon(leftSon){}
        ~AVLNode() = default;
        friend bool operator<(AVLNode &node1,AVLNode &node2){
            return  node1.key<node2.key;
        }
        friend bool operator==(AVLNode &node1,AVLNode &node2){
            return  node1.key==node2.key;
        }
    };

    AVLNode* root;

    AVLResult RRroll();
    AVLResult LLroll();
    AVLResult LRroll();
    AVLResult RLroll();

    public:
    explicit AVLtree(){
        root = nullptr;
    };

    explicit AVLtree(AVLNode* root):root(root){}

    AVLtree (const AVLtree &avltree)= delete;

    ~AVLtree(){
        if(root->rightSon == nullptr && root->leftSon == nullptr){
            ~AVLNode();
        }
        ~AVLtree(root->leftSon);
        ~AVLtree(root->rightSon);
    };

    AVLResult insert(T* key){

    }

    AVLResult erase(T* key){

    }

    AVLResult find (T* key){

    }
};


#endif //AVLTREE_AVLTREE_H
