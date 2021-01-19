#include <iostream>
#include "linkedlist.h"

using std::cout;
using std::endl;

int main(){
    LinkedList<int> L;
    L.add(4);
    L.add(3);
    L.add(5);

    L.print();

    LinkedList<int> L2;

    L2.add(7);
    L2.add(8);
    L2.add(9);
    L2.print();

    L2 = L;
    L2.print();

}
