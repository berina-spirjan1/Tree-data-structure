#ifndef ITERATOR_H
#define ITERATOR_H

#include "stablo.h"

template<typename Tip>
class Stablo<Tip>::Iterator {
    Cvor *trenutni;

public:
    Iterator(Cvor *trenutni = nullptr) : trenutni(trenutni) {}

    Iterator(const Iterator &it) : trenutni(it.trenutni) {}

    Iterator &operator=(const Iterator &it) {
        if (this != &it) {
            trenutni = it.trenutni;
        }
        return *this;
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
        if (this != &it) {
            trenutni = it.trenutni;
        }
        return *this;
    }

    Tip &operator*() { return trenutni->element; }

    Reverse_Iterator operator++();

    Reverse_Iterator operator++(int);

    Reverse_Iterator operator--();

    Reverse_Iterator operator--(int);

    Reverse_Iterator najmanjiNaGrani();

    Reverse_Iterator najveciNaGrani();

    friend class Stablo<Tip>;
};

#include "iterator.cpp"

#endif // ITERATOR_H