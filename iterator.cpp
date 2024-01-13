#ifndef ITERATOR_CPP
#define ITERATOR_CPP

#include "iterator.h"
#include "stablo.h"
#include <iostream>


template<typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::najmanjiNaGrani() {
    return pomjeriNaGrani(
            [](Cvor *cvor) { return cvor->ld; }); //pomjeramo se svaki put na lijevo dijete od trenutnog cvora
}

template<typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::pomjeriNaGrani(function<Cvor * (Cvor * )> funkcijaPomjeranja) {
    if (this->trenutni == nullptr)
        return *this; // Ako je trenutni čvor nullptr, nema najmanjeg/najvećeg elementa, vraćamo trenutni iterator
    while (funkcijaPomjeranja(this->trenutni) != nullptr)
        this->trenutni = funkcijaPomjeranja(
                this->trenutni); // Prolazimo kroz lijevo/desno podstablo dok ne dođemo do najmanjeg/najvećeg elementa
    return *this; // Vraćamo promijenjeni iterator
}

template<typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::najveciNaGrani() {
    return pomjeriNaGrani([](Cvor *cvor) { return cvor->dd; }); //pomjeramo se na desno dijete od trenutnog cvora
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

template<typename Tip>
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


template<typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::operator--() {
    if (this->trenutni->ld != nullptr) {
        // ako postoji lijevo dijete, idemo na najveci element u lijevom podstablu
        this->trenutni = this->trenutni->ld;
        this->najveciNaGrani();
    } else {
        // ako nema lijevog djeteta,pomjerimo se ka roditelju sve dok ne nadjemo prvo desno dijete
        while (this->trenutni->rod != nullptr && this->trenutni == this->trenutni->rod->ld) {
            this->trenutni = this->trenutni->rod;
        }
        // kada dodjemo do korijena, iterator će pokazivati na nullptr, inace se pomjeramo na roditelja trenutnog cvora
        if (this->trenutni->rod != nullptr) {
            this->trenutni = this->trenutni->rod;
        }
    }
    return *this;
}

template<typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::operator--(int) {
    Iterator kopija = *this;  // pravimo kopiju trenutnog iteratora
    if (this->trenutni->ld != nullptr) {
        // ako postoji lijevo dijete od trenutnog cvora, idemo na najveci element u lijevom podstablu
        this->trenutni = this->trenutni->ld;
        this->najveciNaGrani();
    } else {
        // ako nema lijevog djeteta, pomjeramo se prema roditelju od trenutnog cvora
        // sve dok ne dodjemo do prvog desnog djeteta
        while (this->trenutni->rod != nullptr && this->trenutni == this->trenutni->rod->ld) {
            this->trenutni = this->trenutni->rod;
        }
        // kada dođemo do korijena iterator će pokazivati na nullptr, inace se pomjeramo na njegovog roditelja
        if (this->trenutni->rod != nullptr) {
            this->trenutni = this->trenutni->rod;
        }
    }
    return kopija;  // vracamo kopiju prvobitnog iteratora koja je sada modifikovana
}

template<typename Tip>
typename Stablo<Tip>::Reverse_Iterator Stablo<Tip>::Reverse_Iterator::najveciNaGrani() {
    return pomjeriNaGrani([](Cvor *cvor) { return cvor->dd; }); //pomjeramo se na desno dijete od trenutnog cvora
}

template<typename Tip>
typename Stablo<Tip>::Reverse_Iterator
Stablo<Tip>::Reverse_Iterator::pomjeriNaGrani(std::function<Cvor * (Cvor * )> funkcijaPomjeranja) {
    if (this->trenutni == nullptr)
        return *this; // ako je trenutni cvor nullptr, nema najmanjeg/najveceg elementa, vraćamo trenutni iterator
    while (funkcijaPomjeranja(this->trenutni) != nullptr)
        this->trenutni = funkcijaPomjeranja(
                this->trenutni); // prolazimo kroz lijevo/desno podstablo dok ne dođemo do najmanjeg/najveceg elementa
    return *this; // vracamo promijenjeni iterator
}

template<typename Tip>
typename Stablo<Tip>::Reverse_Iterator Stablo<Tip>::Reverse_Iterator::najmanjiNaGrani() {
    return pomjeriNaGrani(
            [](Cvor *cvor) { return cvor->ld; }); //pomjeramo se svaki put na lijevo dijete od trenutnog cvora
}


template<typename Tip>
typename Stablo<Tip>::Reverse_Iterator Stablo<Tip>::Reverse_Iterator::operator++() {
    if (this->trenutni != nullptr) {
        if (this->trenutni->ld != nullptr) {
            // ako postoji lijevo dijete, idemo na najveci element u lijevom podstablu
            this->trenutni = this->trenutni->ld;
            this->najveciNaGrani();  // funkcija koja postavlja iterator na najveci element u podstablu
            return *this;
        }
        while (this->trenutni->rod != nullptr && this->trenutni == this->trenutni->rod->ld) {
            // ako trenutni cvor nema lijevo dijete i trenutni cvor je lijevo dijete svog roditelja,
            // idemo prema roditelju sve dok ne nadjemo prvi cvor koji nije lijevo dijete svog roditelja
            this->trenutni = this->trenutni->rod;
        }
        // ako dodjemo do korijena, iterator će pokazivati na nullptr
        if (this->trenutni->rod == nullptr) {
            return *this;
        } else {
            // ako nismo dosli do korijena, idemo na roditelja trenutnog cvora
            this->trenutni = this->trenutni->rod;
            return *this;  // Return the modified iterator
        }
    } else {
        // ako je pokazivac već nullptr, vracamo postojeci iterator
        return *this;
    }
}

template<typename Tip>
typename Stablo<Tip>::Reverse_Iterator Stablo<Tip>::Reverse_Iterator::operator++(int) {
    // kreiramo kopiju trenutnog iteratora
    Reverse_Iterator kopija = *this;

    // ako trenutni čvor ima lijevo dijete, pomjeri se na njegovo dijete i zatim na najdesniji element u njegovom podstablu
    if (this->trenutni->ld != nullptr) {
        this->trenutni = this->trenutni->ld;
        this->najveciNaGrani();
        return kopija;
    }

    // ako trenutni cvor nema lijevo dijete, idemo prema gore do prvog čvora koji je desno dijete svog roditelja
    while (this->trenutni->rod != nullptr && this->trenutni == this->trenutni->rod->ld) {
        this->trenutni = this->trenutni->rod;
    }

    // ako smo došli do korijena, vracamo originalni iterator
    if (this->trenutni->rod == nullptr) {
        return kopija;
    } else {
        // pomjeramo se na roditelj čvor
        this->trenutni = this->trenutni->rod;
        return kopija;
    }
}

template<typename Tip>
typename Stablo<Tip>::Reverse_Iterator Stablo<Tip>::Reverse_Iterator::operator--() {
    // ako postoji desno dijete, pomjeramo se na najmanji element u desnom podstablu
    if (this->trenutni->dd != nullptr) {
        this->trenutni = this->trenutni->dd;
        this->najmanjiNaGrani();
    } else {
        // ako nema desnog djeteta, idi prema gore do prvog cvora koji je lijevo dijete svog roditelja
        while (this->trenutni->rod != nullptr && this->trenutni == this->trenutni->rod->dd) {
            this->trenutni = this->trenutni->rod;
        }
        // ako smo došli do korijena, iterator će pokazivati na nullptr, inace idi na roditelja trenutnog cvora
        if (this->trenutni->rod != nullptr) {
            this->trenutni = this->trenutni->rod;
        }
    }
    return *this;
}


template<typename Tip>
typename Stablo<Tip>::Reverse_Iterator Stablo<Tip>::Reverse_Iterator::operator--(int) {
    Reverse_Iterator kopija = *this;  // pravimo kopiju trenutnog iteratora
    if (this->trenutni->ld != nullptr) {
        // ako postoji lijevo dijete od trenutnog cvora, idemo na najveci element u lijevom podstablu
        this->trenutni = this->trenutni->ld;
        this->najveciNaGrani();
    } else {
        // ako nema lijevog djeteta, pomjeramo se prema roditelju od trenutnog cvora
        // sve dok ne dodjemo do prvog desnog djeteta
        while (this->trenutni->rod != nullptr && this->trenutni == this->trenutni->rod->ld) {
            this->trenutni = this->trenutni->rod;
        }
        // kada dođemo do korijena iterator će pokazivati na nullptr, inace se pomjeramo na njegovog roditelja
        if (this->trenutni->rod != nullptr) {
            this->trenutni = this->trenutni->rod;
        }
    }
    return kopija;  // vracamo kopiju prvobitnog iteratora koja je sada modifikovana
}


#endif // ITERATOR_CPP
