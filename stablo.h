#ifndef STABLO_H
#define STABLO_H

#include <utility>

using namespace std;

template<typename Tip>
class Stablo {
public:
    struct Cvor {
        Tip element;
        Cvor *ld, *dd, *rod;

        Cvor(Tip el, Cvor *rod = nullptr, Cvor *ld = nullptr, Cvor *dd = nullptr) : element(el), rod(rod), ld(ld),
                                                                                    dd(dd) {}
    };

protected:
    int n;
    Cvor *korijen;

    void Ispis(Cvor *) const;

    void InOrder(Cvor *) const;

    int Visina(Cvor *) const;

    Cvor* dajNajmanjiCvor(Cvor* cvor);

public:
    Stablo() : n(0), korijen(nullptr) {}

    int Size() { return n; }

    bool Empty() { return n == 0; }

    Cvor *Find(const Tip vrijednost) const;

    pair<Cvor *, bool> Insert(const Tip vrijednost);

    void Erase(const Tip vrijednost);

    void Ispis() const { Ispis(korijen); } //za testiranje
    void InOrder() const { InOrder(korijen); }

    int Visina() const { return Visina(korijen); }

    Cvor *Pocetak() const;

    Cvor *Sljedbenik(Cvor *cvor) const;

    Cvor *Korijen() {
        return korijen;
    };

    Cvor *dajNajveciCvor(Cvor *);

    Cvor *dajKtiElement(int pozicija, Cvor *trenutniCvor, int &brojac);

    class Iterator;

    class Reverse_Iterator;

    Tip operator[](int);

    template<typename Tip2>
    friend bool provjeriDaLiJePodskup(Stablo<Tip2> &s1, Stablo<Tip2> &s2);

    Iterator Begin() {
        return Iterator(dajNajmanjiCvor(korijen));
    }

    Iterator End() {
        return Iterator();
    }

    Reverse_Iterator rBegin() {
        return Reverse_Iterator();
    }

    Reverse_Iterator rEnd() {
        return Reverse_Iterator(dajNajmanjiCvor(korijen));
    }

};

#include "stablo.cpp"

#endif // STABLO_H
