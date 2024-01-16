#ifndef ITERATOR_H
#define ITERATOR_H

#include "stablo.h"

template<typename Tip>
class Stablo<Tip>::Iterator {
    Cvor *trenutni;

public:
    Iterator(Cvor* trenutni = nullptr):trenutni(trenutni) {};
    Iterator(const Iterator &it) : trenutni(it.trenutni) {};
    Iterator(Iterator* it){
        trenutni = new Cvor(it->trenutni->element, it->trenutni->rod, it->trenutni->ld, it->trenutni->dd);
    };

    Iterator &operator=(const Iterator &it) {
        // provjeravamo da li se radi o dodjeli istog iteratora
        if (this != &it) {
            trenutni = it.trenutni; //vrijednost trenutnog pokazivača se kopira iz it
        }
        return *this; //vracamo referencu na trenutni iterator nakon dodjele
    }

    Tip &operator*() { return trenutni->element; }

    Iterator operator++();

    Iterator operator++(int);

    Iterator operator--();

    Iterator operator--(int);

    bool operator==(const Iterator &cvor) const { return trenutni == cvor.trenutni; }

    bool operator!=(const Iterator &cvor) const { return trenutni != cvor.trenutni; }

    Tip &operator*() const { return trenutni->element; }

    Tip *operator->() const { return &(trenutni->element); }

    //sluzi za pomjeranje na najmanji element u podstablu cvora na koji trenutno pokazuje
    Iterator najmanjiNaGrani();

    //sluzi za pomjeranje na najveci element u podstablu cvora na koji trenutno pokazuje
    Iterator najveciNaGrani();

    Iterator pomjeriNaGrani(function<Cvor *(Cvor *)>);

    friend class Stablo<Tip>;

};

template<typename Tip>
class Stablo<Tip>::Reverse_Iterator {
    Cvor *trenutni;

public:
    Reverse_Iterator(Cvor *trenutni = nullptr) : trenutni(trenutni) {};

    Reverse_Iterator(const Reverse_Iterator &it) : trenutni(it.trenutni) {}

    Reverse_Iterator &operator=(const Reverse_Iterator &it) {
        // provjeravamo da li se radi o dodjeli istog iteratora
        if (this != &it) {
            trenutni = it.trenutni; //vrijednost trenutnog pokazivača se kopira iz it
        }
        return *this; //vracamo referencu na trenutni iterator nakon dodjele
    }

    Tip &operator*() { return trenutni->element; }

    Reverse_Iterator operator++();

    Reverse_Iterator operator++(int);

    Reverse_Iterator operator--();

    Reverse_Iterator operator--(int);

    bool operator==(const Reverse_Iterator &cvor) const { return trenutni == cvor.trenutni; }

    bool operator!=(const Reverse_Iterator &cvor) const { return trenutni != cvor.trenutni; }

    Tip &operator*() const { return trenutni->element; }

    Tip *operator->() const { return &(trenutni->element); }

    Reverse_Iterator najmanjiNaGrani();

    Reverse_Iterator najveciNaGrani();

    Reverse_Iterator pomjeriNaGrani(function<Cvor *(Cvor *)>);

    friend class Stablo<Tip>;
};

#include "iterator.cpp"

#endif // ITERATOR_H