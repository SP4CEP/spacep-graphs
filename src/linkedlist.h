#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

//template <typename T>
struct ListNode{
    int value;
    ListNode* next;
};

//template <class T>
class LinkedList{

    ListNode *start;
    int length;

public:

    LinkedList();
    ~LinkedList();
    ListNode* find(int value);
    bool add(int value);
    bool remove(int value);
    void print();
    int Length();

};

#endif // LINKEDLIST_H_INCLUDED
