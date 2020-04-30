//
// Created by Dell on 30/04/2020.
//
#define LEAF_HEIGHT 1

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <iostream>

using std::exception;

typedef enum AVLResult_t {
    SUCCESS=1,
    FAILURE=0
}AVLResult;

typedef enum AVLRoll_t{
    NO_ROLL=0,

}AVLRoll;

template <class T>
class AVLtree {

    class AVLNode{
        T* key;
        AVLNode* father;
        AVLNode* rightSon;
        AVLNode* leftSon;
        int height;

        public:
        explicit AVLNode() = delete;
        AVLNode(T* key,AVLNode* father,AVLNode* rightSon,AVLNode* leftSon,int height=LEAF_HEIGHT):
                key(key),father(father),rightSon(rightSon),leftSon(leftSon),height(height){}
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

    /*
     * recursive option from the root to the key and back
     *
    void updateHeightsFrom(AVLNode* current,T* key){
        if (root->key == key) return;
        if (root->leftSon->key<key){
            updateHeightsFrom(root->rightSon,key);
        }
        else {
            updateHeightsFrom(root->leftSon,key);
        }
        if (root->leftSon->height>root->rightSon->height){
            root->height=root->leftSon->height+1;
        }
        else root->height=root->rightSon->height+1;
    }
    */

    void updateHeightsFrom(AVLNode* leaf){
        AVLNode* current = leaf->father;
        while (current->father!= nullptr){
            if (current->leftSon->height>current->rightSon->height){
                current->height=current->leftSon->height+1;
            }
            else current->height=current->rightSon->height+1;
            current=current->father;
        }
    }

    public:
    explicit AVLtree(){
        root = nullptr;
    };

    explicit AVLtree(AVLNode* root):root(root){}

    AVLtree (const AVLtree &avltree)= delete;

    ~AVLtree(){
        // we need to do postorder and delete the nodes
        AVLNode* current = root;
        if(current->rightSon == nullptr && current->leftSon == nullptr){
            delete(current);
        }
        ~AVLtree(current->leftSon);
        ~AVLtree(current->rightSon);
    };

    AVLNode* insert(T* key){
        if (root== nullptr){
            root=new AVLNode(key,LEAF_HEIGHT, nullptr, nullptr, nullptr);
        }
        if (key==nullptr){
            throw BadParameters();
        }
        AVLNode* current = root;
        while (current!= nullptr){
            if (current->key==key)
                throw AlreadyExist();
            if (current->key<key) {
                if (current->rightSon==nullptr){
                    AVLNode* newAvlNode=new AVLNode(key,current, nullptr, nullptr);
                    current->rightSon=newAvlNode;
                    return newAvlNode;
                }
                current=current->rightSon;
            }
            else {
                if (current->leftSon== nullptr){
                    AVLNode* newAvlNode =new AVLNode(key,current, nullptr, nullptr);
                    current->leftSon=newAvlNode;
                    return newAvlNode;
                }
                current=current->leftSon;
            }
        }
        updateHeightsFrom(current);
        int roll=chooseRoll(root);
        // we need to do a roll
    }

    AVLResult erase(T* key){
        if (key==nullptr){
            throw BadParameters();
        }
        AVLNode* current = root;
        while (current!= nullptr){
            if (current->key==key){
                delete(current);
            }
            if (current->key<key)
                current=current->rightSon;
            else current=current->leftSon;
        }
        throw NotFound();
    }

    AVLNode* find (T* key){
        if (key==nullptr){
            throw BadParameters();
        }
        AVLNode* current = root;
        while (current!= nullptr){
            if (current->key==key)
                return current;
            if (current->key<key)
                current=current->rightSon;
            else current=current->leftSon;
        }
        throw NotFound();
    }

    class NotFound : public exception{};
    class BadParameters : public  exception{};
    class AlreadyExist : public exception{};
};


#endif //AVLTREE_AVLTREE_H
