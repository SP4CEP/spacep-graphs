/*
Filename: main.cpp
Authors: Domínguez Acosta María Fernanda
         Murcia Yocupicio Raúl Octavio
         Sandoval del Hoyo María Ximena
Date: 15/01/2021
Description: Main class of 
*/
#include <iostream>
#include <fstream>
#include "linkedlist.h"

using std::cout;
using std::endl;

int main(){
   LinkedList<int> L;
   //
   cout << "case 2: empty list" << endl;
   cout << L.add(3) << endl << endl;
   cout << "list: len " << L.Length() << endl;
   L.print();
   // 
   cout << "case 1: node already on list" << endl;
   cout << L.add(3) << endl << endl;
   cout << "list: len " << L.Length() << endl;
   L.print();
   //
   cout << "case 3: node goes first on list" << endl;
   cout << L.add(1) << endl << endl;
   cout << "list: len " << L.Length() << endl;
   L.print();
   //
   cout << "case 4: node goes middle on list" << endl;
   cout << L.add(2) << endl << endl;
   cout << "list: len " << L.Length() << endl;
   L.print();
   //
   cout << "case 5: node goes last on list" << endl;
   cout << L.add(4) << endl << endl;
   cout << "list: len " << L.Length() << endl;
   L.print();
   //
   cout << "****************** DELETE ********************" <<endl;
   //
   cout << "case 0: not on list (rm 5)" << endl;
   cout << L.remove(5) << endl << endl;
   cout << "list: len " << L.Length() << endl;
   L.print();
   //
   cout << "case 1: first on list (rm 1)" << endl;
   cout << L.remove(1) << endl << endl;
   cout << "list: len " << L.Length() << endl;
   L.print();
   //
   cout << "case 2: middle on list (rm 3)" << endl;
   cout << L.remove(3) << endl << endl;
   cout << "list: len " << L.Length() << endl;
   L.print();
   //
   cout << "case 3: end on list (rm 4)" << endl;
   cout << L.remove(4) << endl << endl;
   cout << "list: len " << L.Length() << endl;
   L.print();
   //
   cout << "case 4: to empty list (rm 2)" << endl;
   cout << L.remove(2) << endl << endl;
   cout << "list: len " << L.Length() << endl;
   L.print();
   //
   cout << "case 4: un empty list (add 4)" << endl;
   cout << L.add(4) << endl << endl;
   cout << "list: len " << L.Length() << endl;
   L.print();

   return 0;
}