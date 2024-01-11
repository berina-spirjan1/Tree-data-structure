#include <iostream>
#include "stablo.h"

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

    /*s.InOrder();
    cout<<endl;
    cout<<s.Visina();
    cout<<endl;*/
    for (auto trenutni = s.Pocetak(); trenutni != nullptr; trenutni = s.Sljedbenik(trenutni))
        cout << trenutni->element << " ";
    cout << endl;
    s.Erase(20);
    for (auto trenutni = s.Pocetak(); trenutni != nullptr; trenutni = s.Sljedbenik(trenutni))
        cout << trenutni->element << " ";
    cout << endl;
    s.Erase(30);
    for (auto trenutni = s.Pocetak(); trenutni != nullptr; trenutni = s.Sljedbenik(trenutni))
        cout << trenutni->element << " ";
    cout << endl;
    s.Erase(10);
    s.Erase(40);
    s.Erase(17);
    s.Erase(35);
    s.Erase(15);
    s.Erase(0);
    s.Erase(60);
    //s.Erase(50);
    for (auto trenutni = s.Pocetak(); trenutni != nullptr; trenutni = s.Sljedbenik(trenutni))
        cout << trenutni->element << " ";

}
