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

    Cvor *dajNajmanjiCvor(Cvor *);

    Cvor *dajNajveciCvor(Cvor *);

    Cvor *dajKtiNajveci(Cvor *kr, int k, int &brojac);

    Cvor *dajSljedbenika(Cvor *);

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

    Cvor *Begin() {
        return dajNajmanjiCvor(korijen);
    };

    Cvor *End() {
        return dajNajveciCvor(korijen);
    };

    Cvor *Korijen() {
        return korijen;
    };

    class Iterator;

    class Reverse_Iterator;
};

#include "stablo.cpp"

#endif // STABLO_H
