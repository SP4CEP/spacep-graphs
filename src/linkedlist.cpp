/*
Filename: linkedlist.cpp
Authors: Domínguez Acosta María Fernanda
         Murcia Yocupicio Raúl Octavio
         Sandoval del Hoyo María Ximena
Date: 16/01/2021
Description: Functions of the implementetion of a linked list
*/
#include <iostream>
#include "linkedlist.h"

template class LinkedList<int>;
template class LinkedList<std::string>;

using std::cout;
using std::endl;

//**********************************************************************//

template <class T>
LinkedList<T>::LinkedList(){
    start = nullptr;
    length = 0;
}

//**********************************************************************//

template <class T>
LinkedList<T>::~LinkedList(){
    ListNode<T> *p;
    while(start){
        p = start;
        start = p->next;
        delete p;
    }
}

//**********************************************************************//

template <class T>
ListNode<T>* LinkedList<T>::find(T value){
    ListNode<T> *p=start;

    while(p != nullptr){
        if(p->value == value) return p;
        p = p->next;
    }
    return nullptr;
}

//**********************************************************************//

template <class T>
bool LinkedList<T>::add(T value){
   // case 1: the node is already in the list
   if(find(value)) return false;
   
   ListNode<T> *p = (ListNode<T>*) new ListNode<T>;
    p->value = value;
    length++;

   // case 2: empty list
   if(start == nullptr){
       start = p;
       p->next = nullptr;
       return true;

    // case 3: node goes first on the list
   }else if(start->value > p->value){
       p->next = start;
       start = p;
       return true;
   }

   ListNode<T> *q = start;
   while(q->next != nullptr){

       // case 4: node goes in the middle of the list
       if((q->next)->value > p->value){
           p->next = q->next;
           q->next = p;
           return true;
       }
       q = q->next;
   }

   // case 5: node goes at the end
   q->next = p;
   p->next = nullptr;
   return true;
}

//**********************************************************************//

template <class T>
void LinkedList<T>::print(){
    ListNode<T> *p = start;
    while(p){
        std::cout << p->value << "  ";
        p = p->next;
    }
    std::cout << std::endl;
}
//**********************************************************************//

template <class T>
bool LinkedList<T>::remove(T value){
    ListNode<T> *p = find(value);
    // case 1: the node is not in the list
   if(p == nullptr) return false;

    // case 2: node is first on the list
    if(start == p){
        length--;
       start = p->next;
       delete p;
       return true;
   }
    // case 3: node is in the middle/last of the list
   ListNode<T> *q = start;
   while(q){
       if(q->next == p){
           length--;
           q->next = p->next;
           delete p;
           return true;
       }
       q = q->next;
   }
   return false;
}
//**********************************************************************//

template <class T>
int LinkedList<T>::Length(){
    return length;
}
//**********************************************************************//
