#include <iostream>
#include "stablo.h"
#include "iterator.h"

using namespace std;

int main() {

    Stablo<int> s;
    s.Insert(20);
    s.Insert(50);
    s.Insert(10);
    s.Insert(30);
    s.Insert(40);
    s.Insert(0);
    s.Insert(60);
    s.Insert(35);
    s.Insert(15);
    s.Insert(17);
    Stablo<int>::Iterator iterator(s.Korijen());

    //testiran dio ovo je uredu
    cout << *iterator << ' ';
    cout << *(iterator++) << ' ';
    cout << *iterator-- << ' ';
    cout << *iterator << endl;


    //problem prilikom ispisivanja ne prolazi petlja da se pomice dalje.
//    // ispisivanje u inorder poretku
//    for (auto trenutni = s.Pocetak(); trenutni != s.End(); trenutni++)
//        cout << trenutni->element << " ";

    // Brisanje nekih elemenata
    s.Erase(20);
    s.Erase(30);
    s.Erase(10);

    Stablo<int>::Reverse_Iterator reverse_iterator(s.End());

    //ovaj dio je isto uredu
    cout << *reverse_iterator << ' ';
    cout << *(++reverse_iterator) << ' ';
    cout << *reverse_iterator++ << ' ';
    cout << *reverse_iterator << endl;

    // Ponovni ispis nakon brisanja
//    for (auto trenutni = s.Pocetak(); trenutni != s.End(); trenutni++)
//        cout << trenutni->element << " ";
//    cout << endl;

    return 0;
}
