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

    void updateHeightFrom(AVLNode* root,T* key){
        if (root->leftSon->key==key||root->rightSon->key==key){

        }


        if (root->key == key) return;
        updateHeightFrom();
    }

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

    AVLNode* insert(T* key){
        if (key==nullptr){
            throw BadParameters();
        }
        AVLNode* current = root;
        while (current!= nullptr){
            if (current->key==key)
                throw AlreadyExist();
            if (current->key<key) {
                if (current->rightSon==nullptr){
                    AVLNode* newAvlNode=new AVLNode(key,LEAF_HEIGHT,current, nullptr, nullptr);
                    current->rightSon=newAvlNode;
                    return newAvlNode;
                }
                current=current->rightSon;
            }
            else {
                if (current->leftSon== nullptr){
                    AVLNode* newAvlNode =new AVLNode(key,LEAF_HEIGHT,current, nullptr, nullptr);
                    current->leftSon=newAvlNode;
                    return newAvlNode;
                }
                current=current->leftSon;
            }
        }
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
