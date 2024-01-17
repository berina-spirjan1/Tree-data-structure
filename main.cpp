#include <iostream>
#include "stablo.h"
#include "iterator.h"

using namespace std;

int main() {

//    Stablo<int> s;
//    s.Insert(20);
//    s.Insert(50);
//    s.Insert(10);
//    s.Insert(30);
//    s.Insert(40);
//    s.Insert(0);
//    s.Insert(60);
//    s.Insert(35);
//    s.Insert(15);
//    s.Insert(17);
//    s.InOrder();

//    Stablo<int>::Iterator iterator(s.Korijen());

    Stablo<int> s;
    s.Insert(20);
    s.Insert(30);
    s.Insert(25);
    s.Insert(35);
    s.Insert(10);
    s.Insert(5);
    s.Insert(15);
    s.Insert(32);
    s.Insert(12);
    s.Insert(17);
    s.Insert(18);

//    s.Insert(11);
//    s.Insert(10);
//    s.Insert(9);
//    s.Insert(8);
//    s.Insert(7);
//    s.Insert(6);
//    s.Insert(56);
//    s.Insert(5);
//    s.Insert(4);
//    s.Insert(3);
//    s.Insert(2);
//    s.Insert(1);

    s.InOrder();

    Stablo<int> s2;
    s2.Insert(30);
    s2.Insert(20);
    s2.Insert(25);
//    s2.Insert(25);
//    s2.Insert(32);

//    cout << "Drugo stablo: ";
//    s2.InOrder();
//    cout <<"Trazim drugi element: "<<s2[2]<< endl;

    cout << endl << "Da li je podstablo: " << provjeriDaLiJePodskup(s, s2) << endl;
//
    cout << "Pocetak:" << *s.Begin() << endl;
    cout << "Kraj:" << *s.End() << endl;

    cout << endl << "Iterator prefix incrementing:";
    for (auto trenutni = s.Begin(); trenutni != s.End(); ++trenutni) {
        cout << " " << *trenutni << " ";
    }

    cout << endl << "Iterator postfix incrementing:";
    for (auto trenutni = s.Begin(); trenutni != s.End(); trenutni++)
        cout << " " << *trenutni << " ";

    cout << endl << "Iterator prefix decrementing:";
    for (auto trenutni = s.End(); trenutni != s.Begin(); --trenutni)
        cout << " " << *trenutni << " ";

    cout << endl << "Iterator postfix decrementing:";
    for (auto trenutni = s.End(); trenutni != s.Begin(); trenutni--)
        cout << " " << *trenutni << " ";

    cout << endl;
    // Brisanje nekih elemenata
//    s.Erase(20);
//    s.Erase(30);
//    s.Erase(10);

    Stablo<int>::Reverse_Iterator reverse_iterator(s.rEnd());

    cout << endl;
    cout << "Reverse iterator postfixni decrement:";
    for (auto trenutni = s.rEnd(); trenutni != s.rBegin(); trenutni--)
        cout << *trenutni << " ";

    cout << endl;
    cout << "Reverse iterator prefixni decrement:";
    for (auto trenutni = s.rEnd(); trenutni != s.rBegin(); --trenutni)
        cout << *trenutni << " ";

    cout << endl;
    cout << "Reverse iterator postfixni increment:";
    for (auto trenutni = s.rBegin(); trenutni != s.rEnd(); trenutni++)
        cout << *trenutni << " ";

    cout << endl;
    cout << "Reverse iterator prefixni increment:";
    for (auto trenutni = s.rBegin(); trenutni != s.rEnd(); ++trenutni)
        cout << *trenutni << " ";
    cout << endl;


    return 0;
}
