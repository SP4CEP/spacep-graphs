/*
Filename: linkedlist.cpp
Author: Domínguez Acosta María Fernanda
Date: 16/01/2021
Description: Functions of the implementetion of a linked list
*/
#include <iostream>
#include "linkedlist.h"

using std::cout;
using std::endl;

//**********************************************************************//

LinkedList::LinkedList(){
    start = nullptr;
    length = 0;
}

//**********************************************************************//

LinkedList::~LinkedList(){
    ListNode *p;
    while(start){
        p = start;
        start = p->next;
        delete p;
    }
}

//**********************************************************************//

ListNode* LinkedList::find(int value){
    ListNode *p=start;

    while(p != nullptr){
        if(p->value == value) return p;
        p = p->next;
    }
    return nullptr;
}

//**********************************************************************//

bool LinkedList::add(int value){
   // case 1: the node is already in the list
   if(find(value)) return false;
   
   ListNode *p = (ListNode*) new ListNode;
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

   ListNode *q = start;
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

void LinkedList::print(){
    ListNode *p = start;
    while(p){
        std::cout << p->value << "  ";
        p = p->next;
    }
    std::cout << std::endl;
}
//**********************************************************************//

bool LinkedList::remove(int value){
    ListNode *p = find(value);
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
   ListNode *q = start;
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

int LinkedList::Length(){
    return length;
}
//**********************************************************************//
