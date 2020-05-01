//
// Created by Dell on 30/04/2020.
//
#define LEAF_HEIGHT 1
#define INVALID_HEIGHTS_BALANCE_A 2
#define INVALID_HEIGHTS_BALANCE_B -2
/*
#define LEAF_BALACE_FACTOR 0
*/
#define EMPTY_NODE_HEIGHT 0

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
    RR_ROLL=1,
    LL_ROLL=2,
    RL_ROLL=3,
    LR_ROLL=4
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

    void deleteTreePostorder (AVLNode* root){
        if (root== nullptr) return;
        deleteTreePostorder(root->leftSon);
        deleteTreePostorder(root->rightSon);
        delete(root);
    }

    void updateHeights(AVLNode* startNode){
        AVLNode* current = startNode;
        int leftSonHeight,rightSonHeight;
        while (current!= nullptr){
            if (current->leftSon== nullptr) leftSonHeight=EMPTY_NODE_HEIGHT;
            else leftSonHeight=current->leftSon->height;
            if (current->rightSon== nullptr) rightSonHeight=EMPTY_NODE_HEIGHT;
            else rightSonHeight=current->rightSon->height;
            if (leftSonHeight>rightSonHeight){
                current->height=leftSonHeight+1;
            }
            else current->height=rightSonHeight+1;
            current=current->father;
        }
    }

    /*
     * recursive option from the root to the key and back of prepareRoll
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

    void roll (AVLNode* startNode){
        AVLNode* current=startNode;
        int leftSonHeight,rightSonHeight,leftSonRightSonHeight,leftSonLeftSonHeight,
            rightSonLeftSonHeight,rightSonRightSonHeight;
        while (current!= nullptr){
            if (current->father->leftSon== nullptr) leftSonHeight=EMPTY_NODE_HEIGHT;
            else leftSonHeight=current->father->leftSon->height;
            if (current->father->rightSon== nullptr) rightSonHeight=EMPTY_NODE_HEIGHT;
            else rightSonHeight=current->father->rightSon->height;
            if (current->father->leftSon->leftSon== nullptr) leftSonLeftSonHeight=EMPTY_NODE_HEIGHT;
            else leftSonLeftSonHeight=current->father->leftSon->leftSon->height;
            if (current->father->leftSon->rightSon== nullptr) leftSonRightSonHeight=EMPTY_NODE_HEIGHT;
            else leftSonRightSonHeight=current->father->leftSon->rightSon->height;
            if (current->father->rightSon->leftSon== nullptr) rightSonLeftSonHeight=EMPTY_NODE_HEIGHT;
            else rightSonLeftSonHeight=current->father->rightSon->leftSon->height;
            if (current->father->rightSon->rightSon== nullptr) rightSonRightSonHeight=EMPTY_NODE_HEIGHT;
            else rightSonRightSonHeight=current->father->rightSon->rightSon->height;
            if (leftSonHeight-rightSonHeight==INVALID_HEIGHTS_BALANCE_A){
                if (leftSonLeftSonHeight-leftSonRightSonHeight==-1)
                    current=LRroll(current)->father;
                else if (leftSonLeftSonHeight-leftSonRightSonHeight==1)
                    current=LLroll(current)->father;
                continue;
            }
            if (leftSonHeight-rightSonHeight==INVALID_HEIGHTS_BALANCE_B){
                if (leftSonLeftSonHeight-leftSonRightSonHeight==-1)
                    current=RRroll(current)->father;
                else if (leftSonLeftSonHeight-leftSonRightSonHeight==1)
                    current=RLroll(current)->father;
                continue;
            }
            current=current->father;
        }
    }

    AVLNode* RRroll(AVLNode* problemNode){
        AVLNode* B=problemNode->rightSon;
        AVLNode* BL=problemNode->rightSon->leftSon;
        B->leftSon=problemNode;
        B->father=problemNode->father;
        problemNode->father=B;
        if (B->father== nullptr)
            root=B;
        problemNode->rightSon=BL;
        BL->father=problemNode;
        if (problemNode->leftSon->height>problemNode->rightSon->height){
            problemNode->height=problemNode->leftSon->height;
        } else problemNode->height=problemNode->rightSon->height;
        if (B->leftSon->height>B->rightSon->height){
            B->height=B->leftSon->height;
        } else B->height=B->rightSon->height;
        return B;
    };

    AVLNode* LLroll(AVLNode* problemNode){
        AVLNode* A=problemNode->leftSon;
        AVLNode* AR=problemNode->leftSon->rightSon;
        A->rightSon=problemNode;
        A->father= problemNode->father;
        problemNode->father=A;
        if (A->father== nullptr)
            root=A;
        problemNode->leftSon=AR;
        AR->father=problemNode;
        if (problemNode->leftSon->height>problemNode->rightSon->height){
            problemNode->height=problemNode->leftSon->height;
        } else problemNode->height=problemNode->rightSon->height;
        if (A->leftSon->height>A->rightSon->height){
            A->height=A->leftSon->height;
        } else A->height=A->rightSon->height;
        return A;
    };

    /*
     * in recitation 5 it says that LR roll is RR roll on problemNode->leftSon
     * and then LL roll on problemNode - this may make the function shorter
     * using the functions RR and LL
     *
    AVLResult LRroll(AVLNode* problemNode){
        RRroll(problemNode->leftSon);
        LLroll(problemNode);
    }
    */
    AVLNode* LRroll(AVLNode* problemNode){
        AVLNode* A=problemNode->leftSon;
        AVLNode* B=problemNode->leftSon->rightSon;
        AVLNode* BR=problemNode->leftSon->rightSon->rightSon;
        AVLNode* BL=problemNode->leftSon->rightSon->leftSon;
        B->rightSon=problemNode;
        B->leftSon=A;
        B->father= problemNode->father;
        if (B->father== nullptr){
            root=B;
        }
        A->father=B;
        B->leftSon=A;
        problemNode->father=B;
        A->rightSon=BL;
        BL->father=A;
        problemNode->leftSon=BR;
        BR->father=problemNode;
        if (problemNode->leftSon->height>problemNode->rightSon->height){
            problemNode->height=problemNode->leftSon->height;
        } else problemNode->height=problemNode->rightSon->height;
        if (A->leftSon->height>A->rightSon->height){
            A->height=A->leftSon->height;
        } else A->height=A->rightSon->height;
        if (B->leftSon->height>B->rightSon->height){
            B->height=B->leftSon->height;
        } else B->height=B->rightSon->height;
        return B;
    };

    /*
     * in recitation 5 it says that RL roll is LL roll on problemNode->rightSon
     * and then RR roll on problemNode - this may make the function shorter
     * using the functions LL and RR
     *
    AVLResult RLroll(AVLNode* problemNode){
        LLroll(problemNode->rightSon);
        RRroll(problemNode);
    }
    */
    AVLNode* RLroll(AVLNode* problemNode){
        AVLNode* A=problemNode->rightSon;
        AVLNode* B=problemNode->rightSon->leftSon;
        AVLNode* BR=problemNode->leftSon->rightSon->rightSon;
        AVLNode* BL=problemNode->leftSon->rightSon->leftSon;
        B->rightSon=problemNode;
        B->rightSon=A;
        B->father= problemNode->father;
        if (B->father== nullptr){
            root=B;
        }
        A->father=B;
        B->rightSon=A;
        problemNode->father=B;
        A->leftSon=BR;
        BR->father=A;
        problemNode->rightSon=BL;
        BL->father=problemNode;
        if (problemNode->leftSon->height>problemNode->rightSon->height){
            problemNode->height=problemNode->leftSon->height;
        } else problemNode->height=problemNode->rightSon->height;
        if (A->leftSon->height>A->rightSon->height){
            A->height=A->leftSon->height;
        } else A->height=A->rightSon->height;
        if (B->leftSon->height>B->rightSon->height){
            B->height=B->leftSon->height;
        } else B->height=B->rightSon->height;
        return B;
    };

    public:

    explicit AVLtree(){
        root = nullptr;
    };

    explicit AVLtree(AVLNode* root):root(root){}

    AVLtree (const AVLtree &avltree)= delete;

    ~AVLtree(){
        deleteTreePostorder(root);
    };

    /*
     * recursive version of AVLtree destructor
     *
    ~AVLtree(){
        AVLNode* current = root;
        if(current->rightSon == nullptr && current->leftSon == nullptr){
            delete(current);
        }
        ~AVLtree(current->leftSon);
        ~AVLtree(current->rightSon);
    };
    */

    AVLNode* insert(T* key){
        if (key==nullptr){
            throw BadParameters();
        }
        if (root== nullptr){
            root=new AVLNode(key, nullptr, nullptr, nullptr);
            return root;
        }
        AVLNode* newAvlNode= nullptr;
        AVLNode* current = root;
        while (current!= nullptr){
            if (current->key==key)
                throw AlreadyExist();
            if (current->key<key) {
                if (current->rightSon==nullptr){
                    newAvlNode=new AVLNode(key,current, nullptr, nullptr);
                    current->rightSon=newAvlNode;
                    break;
                }
                current=current->rightSon;
            }
            else {
                if (current->leftSon== nullptr){
                    newAvlNode =new AVLNode(key,current, nullptr, nullptr);
                    current->leftSon=newAvlNode;
                    break;
                }
                current=current->leftSon;
            }
        }
        AVLRoll* roll;
        updateHeights(current);
        roll(current);
        return newAvlNode;
    }

    AVLResult erase(T* key){
        if (key==nullptr){
            throw BadParameters();
        }
        AVLNode* current = root;
        while (current!= nullptr){
            if (current->key==key){
                if (current->father->key>current->key){
                    if (current->rightSon!= nullptr){
                        current->father->leftSon=current->rightSon;
                        current->rightSon->father=current->father;
                        current->rightSon->leftSon=current->leftSon;
                        current->leftSon->father=current->rightSon;
                        updateHeights(current->rightSon);
                        roll(current->rightSon);
                    } else {
                        current->father->leftSon=current->leftSon;
                        current->leftSon->father=current->father;
                        if (current->leftSon== nullptr){
                            updateHeights(current->father);
                            roll(current->father);
                        } else {
                            updateHeights(current->leftSon);
                            roll(current->leftSon);
                        }
                    }
                } else {
                    if (current->leftSon!= nullptr){
                        current->father->rightSon=current->leftSon;
                        current->leftSon->father=current->father;
                        current->leftSon->rightSon=current->rightSon;
                        current->rightSon->father=current->leftSon;
                        updateHeights(current->leftSon);
                        roll(current->leftSon);
                    } else {
                        current->father->rightSon=current->rightSon;
                        current->rightSon->father=current->father;
                        if (current->rightSon== nullptr){
                            updateHeights(current->father);
                            roll(current->father);
                        } else {
                            updateHeights(current->rightSon);
                            roll(current->rightSon);
                        }
                    }
                }
                delete(current);
                return SUCCESS;
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
