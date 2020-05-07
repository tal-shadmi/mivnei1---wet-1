//
// Created by kfir2 on 06/05/2020.
//

#ifndef AVLTREE_LIST_H
#define AVLTREE_LIST_H

#include <iostream>
using std::exception;
using std::cout;
using std::endl;

class NotFound : public exception{};
class BadParameters : public exception{};
//class AlreadyExist : public exception{};

template <class Key, class Data>
class ListNode {

public:
    Key key;       //will be used for num_of_plays
    Data data;     //will be used for artists tree
    ListNode<Key,Data> *next;
    ListNode<Key,Data> *previous;

    explicit ListNode<Key,Data>();  // = delete;

    ListNode<Key,Data>(Key key, Data data, ListNode* next, ListNode *previous):
            key (key), data(data), next(next), previous(previous){}

    ~ListNode<Key,Data>() = default;

    friend bool operator<(ListNode<Key,Data> &node1, ListNode<Key,Data> &node2) {
        return node1.key < node2.key;
    }

    friend bool operator==(ListNode<Key,Data> &node1, ListNode<Key,Data> &node2) {
        return node1.key == node2.key;
    }
    //friend class ListNode;
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
    List<Key, Data>() : first(nullptr), last(nullptr) {};

    ~List() {
        ListNode<Key, Data> *i = first;
        ListNode<Key, Data> *next;
        while (i != nullptr) {
            next = i->next;
            delete i;
            i = next;
        }
    }

    ListNode<Key, Data> *getFirst() {
        return this->first;
    }

    ListNode<Key, Data> *getLast() {
        return this->last;
    }

    ListNode<Key, Data> * insertFirst(Key key, Data data) {
        if (key == NULL || data == NULL) {
            throw BadParameters();
        }
        ListNode<Key, Data> *new_element = new ListNode<Key, Data>(key, data, first,
                                                                   nullptr);
        if (this->first == NULL) {                    // The list is empty
            first = new_element;
            last = first;
        } else {
            if (last == first) {               // The list has one element
                last->previous = new_element;
            } else {                        // The list has more than one element
                ListNode<Key, Data> *tmp = first;
                first->previous = new_element;
            }
            first = new_element;

        }
        return new_element;
    }

    ListNode<Key, Data> *insertAfterNode(Key key, Data data, ListNode<Key, Data>* element) {
        if (key == NULL || data == NULL || element == nullptr) {
            throw BadParameters();
        }
        ListNode<Key, Data> *temp = element->next;
        ListNode<Key, Data> *new_element = new ListNode<Key, Data>(key, data, temp,
                                                                   element);
        element->next = new_element;
        if (element == last) {
            last = new_element;
        } else {
            temp->previous = new_element;
        }
        return new_element;
    }

    ListNode<Key, Data> *findByKey(Key key) {
        if (key == NULL) {
            throw BadParameters();
        }
        ListNode<Key, Data> *i = first;
        while (i != nullptr) {
            if (i->key == key) {
                return i;
            }
            i = i->next;
        }
        throw NotFound();
    }

    void erase(ListNode<Key, Data>* element) {
        if (element == NULL) {
            throw BadParameters();
        }
        if(element == first && element == last){        // The list has one element
            first= nullptr;
            last = nullptr;
            delete element;
            return;
        }
        if(element == first){
            first = element->next;
            first->previous = nullptr;
            delete element;
            return;
        }
        if(element == last){
            last = element->previous;
            last->next = nullptr;
            delete element;
            return;
        }
        element->previous->next = element->next;
        element->next->previous = element->previous;;
        delete element;
    }

    void printList(){
        ListNode<Key, Data> *i = first;
        if(i == nullptr){
            cout << "List is empty" << endl;
            return;
        }
        while (i != last) {
            cout << i->key << ", ";
            i = i->next;
        }
        cout << i->key << endl;
    }
};


#endif //AVLTREE_LIST_H
