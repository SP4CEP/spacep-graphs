#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

template <typename T>
struct ListNode<T> {
    T value;
    ListNode<T>* next;
};

template <typename T>
class LinkedList<T> {
public:
    ListNode* start;

    LinkedList();

    ~LinkedList();

    void find()

    bool add(T value);

    bool remove(T value);

    void print();

    int length();

};

#endif // LINKEDLIST_H_INCLUDED
