#ifndef ITERATOR_CPP
#define ITERATOR_CPP

#include "iterator.h"
#include "stablo.h"
#include <iostream>
//
//template<typename Tip>
//typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::najmanjiNaGrani() {
//    if (this->trenutni == nullptr)
//        return this; // ako je trenutni cvor nullptr, nema najmanjeg elementa, vracamo trenutni iterator (iterator na trenutni element ostaje nepromijenjen)
//    while (this->trenutni->ld != nullptr)
//        this->trenutni = this->trenutni->ld; // prolazimo kroz lijevo podstablo dok ne dodjemo do najmanjeg elementa
//    return this; // vracamo promijenjeni iterator na najmanji element
//}
//
//template<typename Tip>
//typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::najveciNaGrani() {
//    if (this->trenutni == nullptr)
//        return this; // ako je trenutni cvor nullptr, nema najmanjeg elementa, vracamo trenutni iterator (iterator na trenutni element ostaje nepromijenjen)
//    while (this->trenutni->dd != nullptr)
//        this->trenutni = this->trenutni->dd;  // prolazimo kroz desno podstablo dok ne dodjemo do najveceg elementa
//    return this; // vracamo promijenjeni iterator koji ce pokazivati na najveci element
//}

template <typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::najmanjiNaGrani() {
    return pomjeriNaGrani([](Cvor* cvor) { return cvor->ld; }); //pomjeramo se svaki put na lijevo dijete od trenutnog cvora
}

template <typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::najveciNaGrani() {
    return pomjeriNaGrani([](Cvor* cvor) { return cvor->dd; }); //pomjeramo se na desno dijete od trenutnog cvora
}

template <typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::pomjeriNaGrani(function<Cvor*(Cvor*)> funkcijaPomjeranja) {
    if (this->trenutni == nullptr)
        return this; // Ako je trenutni čvor nullptr, nema najmanjeg/najvećeg elementa, vraćamo trenutni iterator
    while (funkcijaPomjeranja(this->trenutni) != nullptr)
        this->trenutni = funkcijaPomjeranja(this->trenutni); // Prolazimo kroz lijevo/desno podstablo dok ne dođemo do najmanjeg/najvećeg elementa
    return this; // Vraćamo promijenjeni iterator
}

template<typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::operator++() {
    if (this->trenutni->dd != nullptr) {
        // Ako postoji desno dijete, idemo na najmanji element u desnom podstablu
        this->trenutni = this->trenutni->dd;
        this->najmanjiNaGrani();
    } else {
        // Ako nema desnog djeteta, idemo prema roditelju dok ne pronadjemo prvo lijevo dijete
        while (this->trenutni->rod != nullptr && this->trenutni == this->trenutni->rod->dd) {
            this->trenutni = this->trenutni->rod;
        }
        // kada dodjemo do korijena, iterator ce pokazivati na null, inače idemo na roditelja trenutnog cvora
        if (this->trenutni->rod == nullptr) {
            return *this;
        } else {
            this->trenutni = this->trenutni->rod;
        }
    }
    return this;
}

template <typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::operator++(int) {
    Iterator kopija(this);  // pravimo kopiju trenutnog iteratora
    if (this->trenutni->dd != nullptr) {
        // Ako postoji desno dijete od trenutnog cvora, idemo na najmanji element u desnom podstablu
        this->trenutni = this->trenutni->dd;
        this->najmanjiNaGrani();
    } else {
        // Ako nema desnog djeteta, idemo prema roditelju od trenutnog cvora
        // sve dok ne dodjemo do prvog lijevog djeteta
        while (this->trenutni->rod != nullptr && this->trenutni == this->trenutni->rod->dd) {
            this->trenutni = this->trenutni->rod;
        }
        // kada dodjemo do korijena iterator ce pokazivati na nullptr, inace se pomjeramo na njegovog roditelja
        if (this->trenutni->rod != nullptr) {
            this->trenutni = this->trenutni->rod;
        }
    }
    return kopija;  // vracamo kopiju prvobitnog iteratora koja je sada modifikovana
}



#endif // ITERATOR_CPP
