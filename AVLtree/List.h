//
// Created by kfir2 on 06/05/2020.
//

#ifndef AVLTREE_LIST_H
#define AVLTREE_LIST_H

#include <iostream>
using std::exception;
class NotFound : public exception{};
class BadParameters : public exception{};
class AlreadyExist : public exception{};
template <class Key, class Data>
class ListNode {

public:
    Key key;       //will be used for num_of_plays
    Data data;     //will be used for artists tree
    ListNode<Key,Data> *next;
    ListNode<Key,Data> *previous;

    explicit ListNode<Key,Data>() = delete;

    ListNode<Key,Data>(Key key, Data data, ListNode* next, ListNode *previous):
            key (key), data(data), next(next), previous(previous){}

    ~ListNode<Key,Data>() = default;

    friend bool operator<(ListNode<Key,Data> &node1, ListNode<Key,Data> &node2) {
        return node1.key < node2.key;
    }

    friend bool operator==(ListNode<Key,Data> &node1, ListNode<Key,Data> &node2) {
        return node1.key == node2.key;
    }
    friend class ListNode;
};

/*template<class T>
struct node {

    node<T>* next;
    T data;
};
*/

template <class Key, class Data>
class List {
    ListNode<Key, Data> *first;
    ListNode<Key, Data> *last;
public:
    List<Key, Data>():first(nullptr), last(nullptr){};
    ~List(){
        ListNode<Key, Data> *i = first;
        ListNode<Key, Data> *next;
        while (i!= nullptr ){
            next = i->next;
            delete i;
            i = next;
        }
    }
    ListNode<Key, Data>* getFirst(){
        return this->first;
    }
    ListNode<Key, Data>* getLast(){
        return this->last;
    }
    ListNode<Key, Data>* insertFirst(Key key, Data data) {
        if(key == NULL || data == NULL){
            throw BadParameters();
        }
        ListNode<Key, Data> *new_element = new ListNode<Key, Data>;
        new_element->data = data;
        new_element->key = key;
        new_element->previous = NULL;
        if (this->first==NULL) {                    // The list is empty
            first = new_element;
            first->next = NULL;
            last = first;
        } else {
            if (last == first) {               // The list has one element
                new_element->next = last;
                last->previous =  new_element;
                first = new_element;
            } else {                        // The list has more than one element
                ListNode<Key, Data> *tmp = first;
                first->previous = new_element;
                first = new_element;
                first->next = tmp;
            }

        }
        return this;

    }
    ListNode<Key, Data>* insertAfterNode(Key key, Data data, ListNode<Key, Data> element) {
        if(key == NULL || data == NULL){
            throw BadParameters();
        }
        if(element == first){
            return insertFirst(key,data);
        }
        else{
            ListNode<Key, Data> *new_element = new ListNode<Key, Data>;
            new_element->data = data;
            new_element->key = key;
            if (element == last) {
                new_element->next = NULL;
                new_element->previous = last;
                last->next = new_element;
                last = new_element;
            }
            else{
                new_element->next = element.next;
                new_element->previous = element;
                element.next->previous = new_element;
                element.next = new_element;
            }
            return new_element;
        }

    }
    ListNode<Key, Data>* findByKey(Key key){
        if (key==NULL){
            throw BadParameters();
        }
        ListNode<Key, Data> *i = first;
        while (i!= nullptr ){
            if(i->key = key){
                return i;
            }
            i = i->next;
        }
        throw NotFound();
    }
};

/*

    void erase(Key &key){
        if (key==NULL){
            throw BadParameters();
        }
        AVLNode* current = root;
        AVLNode* connectionNode;
        while (current!= nullptr){
            if (current->key==key){
                if (current->father!= nullptr){
                    if (current->leftSon!= nullptr){
                        connectionNode=current->leftSon;
                        while (connectionNode->rightSon!= nullptr)
                            connectionNode=connectionNode->rightSon;
                        if (current->father->key>current->key)
                            current->father->leftSon=current->leftSon;
                        else if (current->father->key<current->key)
                            current->father->rightSon=current->leftSon;
                        current->leftSon->father=current->father;
                        connectionNode->rightSon=current->rightSon;
                        if (current->leftSon!= nullptr){
                            current->rightSon->father=connectionNode;
                        }
                        updateHeights(connectionNode);
                        roll(connectionNode);
                    } else {
                        if (current->father->key>current->key)
                            current->father->leftSon=current->rightSon;
                        else if (current->father->key<current->key)
                            current->father->rightSon=current->rightSon;
                        if (current->rightSon== nullptr){
                            updateHeights(current->father);
                            roll(current->father);
                        } else {
                            current->rightSon->father=current->father;
                            updateHeights(current->rightSon);
                            roll(current->rightSon);
                        }
                    }
                } else {
                    if (current->leftSon!= nullptr){
                        connectionNode=current->leftSon;
                        while (connectionNode->rightSon!= nullptr)
                            connectionNode=connectionNode->rightSon;
                        root=current->leftSon;
                        current->leftSon->father= nullptr;
                        connectionNode->rightSon=current->rightSon;
                        if (current->leftSon!= nullptr){
                            current->rightSon->father=connectionNode;
                        }
                        updateHeights(connectionNode);
                        roll(connectionNode);
                    } else {
                        root=current->rightSon;
                        current->rightSon->father= nullptr;
                        if (current->rightSon!= nullptr){
                            updateHeights(current->rightSon);
                            roll(current->rightSon);
                        }
                    }
                }
                delete(current);
                return;
            }
            if (current->key<key)
                current=current->rightSon;
            else current=current->leftSon;
        }
        throw NotFound();
    }

};
 */

template<typename T>
class list1 {
    list1();
    list1(const list1& c);
    list1(int num, const T& val = T());
    list1& operator=(const list1& c);
    void push_back(const T& val);
    void pop_back();
    void push_front(const T& val);
    void pop_front();
    int size() const;
};



#endif //AVLTREE_LIST_H
