#ifndef ITERATOR_H
#define ITERATOR_H

#include "stablo.h"

template<typename Tip>
class Stablo<Tip>::Iterator {
    Cvor *trenutni;
public:
    Iterator(Cvor *trenutni = nullptr) : trenutni(trenutni) {}

    Iterator(Iterator *it) {
        trenutni = new Cvor(it->trenutni->element, it->trenutni->rod, it->trenutni->ld, it->trenutni->dd);
    }

    void operator=(Iterator *it){
        trenutni = new Cvor(it->trenutni->element, it->trenutni->rod, it->trenutni->ld, it->trenutni->dd);
    }

};

#include "iterator.cpp"

#endif // ITERATOR_H