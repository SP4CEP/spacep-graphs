#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

template <typename T>
struct ListNode{
    T value;
    ListNode<T>* next;
};

template <class T>
class LinkedList{

    ListNode<T> *start;
    int length;

public:
    /**
     * @brief Linkedlist structure constructor
     **/
    LinkedList();

    /**
     * @brief Linkedlist structure destroyer(?)
     **/
    ~LinkedList();

    /**
     * @brief Function that looks if a value is already in the list.
     * @param value stored in the node.
     * @return The node of the value on the list.
     **/
    ListNode<T>* find(T value);

    /**
     * @brief Function that stores a new node in the list.
     * @param value that will be stored in the node.
     * @return true if succesfuly added to the list, false otherwise.
     **/
    bool add(T value);

    /**
     * @brief Function that removes a node from the list.
     * @param value stored in the node to remove.
     * @return true if succesfuly deleted, false otherwise.
     **/
    bool remove(T value);

    /**
     * @brief Function that prints the list.
     **/
    void print();

    /**
     * @brief Function that returns the length of the list.
     **/
    int Length();

};

#endif // LINKEDLIST_H_INCLUDED
