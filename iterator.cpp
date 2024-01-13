#ifndef ITERATOR_CPP
#define ITERATOR_CPP

#include "iterator.h"
#include "stablo.h"
#include <iostream>


template <typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::najmanjiNaGrani() {
    return pomjeriNaGrani([](Cvor* cvor) { return cvor->ld; }); //pomjeramo se svaki put na lijevo dijete od trenutnog cvora
}

template <typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::pomjeriNaGrani(function<Cvor*(Cvor*)> funkcijaPomjeranja) {
    if (this->trenutni == nullptr)
        return *this; // Ako je trenutni čvor nullptr, nema najmanjeg/najvećeg elementa, vraćamo trenutni iterator
    while (funkcijaPomjeranja(this->trenutni) != nullptr)
        this->trenutni = funkcijaPomjeranja(this->trenutni); // Prolazimo kroz lijevo/desno podstablo dok ne dođemo do najmanjeg/najvećeg elementa
    return *this; // Vraćamo promijenjeni iterator
}

template <typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::najveciNaGrani() {
    return pomjeriNaGrani([](Cvor* cvor) { return cvor->dd; }); //pomjeramo se na desno dijete od trenutnog cvora
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
    Iterator kopija = *this;  // pravimo kopiju trenutnog iteratora
    if (this->trenutni->dd != nullptr) {
        // Ako postoji desno dijete od trenutnog cvora, idemo na najmanji element u desnom podstablu
        this->trenutni = this->trenutni->dd;
        this->najmanjiNaGrani();
    } else {
        // Ako nema desnog djeteta, pomjeramo se na roditelja od trenutnog cvora
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


template <typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::operator--() {
    if (this->trenutni->ld != nullptr) {
        // Ako postoji lijevo dijete, idemo na najveći element u lijevom podstablu
        this->trenutni = this->trenutni->ld;
        this->najveciNaGrani();
    } else {
        // Ako nema lijevog djeteta,pomjerimo se ka roditelju sve dok ne nađemo prvo desno dijete
        while (this->trenutni->rod != nullptr && this->trenutni == this->trenutni->rod->ld) {
            this->trenutni = this->trenutni->rod;
        }
        // Kada dođemo do korijena, iterator će pokazivati na nullptr, inače se pomjeramo na roditelja trenutnog čvora
        if (this->trenutni->rod != nullptr) {
            this->trenutni = this->trenutni->rod;
        }
    }
    return *this;
}

template <typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::operator--(int) {
    Iterator kopija = *this;  // Pravimo kopiju trenutnog iteratora
    if (this->trenutni->ld != nullptr) {
        // Ako postoji lijevo dijete od trenutnog čvora, idemo na najveći element u lijevom podstablu
        this->trenutni = this->trenutni->ld;
        this->najveciNaGrani();
    } else {
        // Ako nema lijevog djeteta, pomjeramo se prema roditelju od trenutnog čvora
        // sve dok ne dođemo do prvog desnog djeteta
        while (this->trenutni->rod != nullptr && this->trenutni == this->trenutni->rod->ld) {
            this->trenutni = this->trenutni->rod;
        }
        // Kada dođemo do korijena iterator će pokazivati na nullptr, inače se pomjeramo na njegovog roditelja
        if (this->trenutni->rod != nullptr) {
            this->trenutni = this->trenutni->rod;
        }
    }
    return kopija;  // Vraćamo kopiju prvobitnog iteratora koja je sada modifikovana
}

template <typename Tip>
typename Stablo<Tip>::Reverse_Iterator Stablo<Tip>::Reverse_Iterator::operator++() {
    if (this->trenutni != nullptr) {
        if (this->trenutni->ld != nullptr) {
            // Ako postoji lijevo dijete, idemo na najveći element u lijevom podstablu
            this->trenutni = this->trenutni->ld;
            this->najveciNaGrani();  // Funkcija koja postavlja iterator na najveći element u podstablu
            return this;
        }
        while (this->trenutni->rod != nullptr && this->trenutni == this->trenutni->rod->ld) {
            // Ako trenutni čvor nema lijevo dijete i trenutni čvor je lijevo dijete svog roditelja,
            // idemo prema roditelju sve dok ne nađemo prvi čvor koji nije lijevo dijete svog roditelja
            this->trenutni = this->trenutni->rod;
        }
        // Ako dođemo do korijena, iterator će pokazivati na nullptr
        if (this->trenutni->rod == nullptr) {
            return this;
        } else {
            // Ako nismo došli do korijena, idemo na roditelja trenutnog čvora
            this->trenutni = this->trenutni->rod;
            return this;
        }
    } else {
        // Ako je pokazivač već nullptr, vraćamo postojeći iterator
        return this;
    }
}




#endif // ITERATOR_CPP
