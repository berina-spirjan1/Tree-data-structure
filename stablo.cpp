#ifndef STABLO_CPP
#define STABLO_CPP

#include "stablo.h"
#include <iostream>

template<typename Tip>
typename Stablo<Tip>::Cvor *Stablo<Tip>::Find(const Tip vrijednost) const {
    Cvor *trenutni = korijen;
    while (trenutni != nullptr) {
        if (trenutni->element == vrijednost)
            return trenutni;
        if (vrijednost < trenutni->element)
            trenutni = trenutni->ld;
        else trenutni = trenutni->dd;
    }
    return nullptr;
}

template<typename Tip>
pair<typename Stablo<Tip>::Cvor *, bool> Stablo<Tip>::Insert(const Tip vrijednost) {

    Cvor *trenutni = korijen, *prethodni = nullptr;
    while (trenutni != nullptr) {
        if (trenutni->element == vrijednost)
            return {trenutni, false};
        prethodni = trenutni;
        if (vrijednost < trenutni->element)
            trenutni = trenutni->ld;
        else trenutni = trenutni->dd;
    }

    Cvor *novi = new Cvor(vrijednost, prethodni);
    if (korijen == nullptr) {
        korijen = novi;
    } else {
        if (prethodni->element < novi->element)
            prethodni->dd = novi;
        else prethodni->ld = novi;
    }
    n++;
    return {novi, true};
}

template<typename Tip>
void Stablo<Tip>::Ispis(Cvor *cvor) const {
    cout << "Vrijednost: " << cvor->element;
    if (cvor->ld != nullptr)
        cout << " Lijevo dijete: " << cvor->ld->element;
    if (cvor->dd != nullptr)
        cout << " Desno dijete: " << cvor->dd->element;
    cout << endl;
    if (cvor->ld != nullptr)
        Ispis(cvor->ld);
    if (cvor->dd != nullptr)
        Ispis(cvor->dd);
}

template<typename Tip>
void Stablo<Tip>::InOrder(Cvor *cvor) const {
    if (cvor == nullptr) return;
    InOrder(cvor->ld);
    cout << cvor->element << " ";
    InOrder(cvor->dd);
}

template<typename Tip>
int Stablo<Tip>::Visina(Cvor *cvor) const {
    if (cvor == nullptr)
        return -1;
    return max(Visina(cvor->ld), Visina(cvor->dd)) + 1;

}

template<typename Tip>
typename Stablo<Tip>::Cvor *Stablo<Tip>::Pocetak() const {
    if (korijen == nullptr)
        return korijen;
    Cvor *trenutni = korijen;
    while (trenutni->ld != nullptr)
        trenutni = trenutni->ld;
    return trenutni;

}

template<typename Tip>
typename Stablo<Tip>::Cvor *Stablo<Tip>::Sljedbenik(Stablo<Tip>::Cvor *cvor) const {
    if (cvor->dd != nullptr) {
        Cvor *trenutni = cvor->dd;
        while (trenutni->ld != nullptr)
            trenutni = trenutni->ld;
        return trenutni;
    }

    Cvor *trenutni = cvor;

    while (trenutni->rod != nullptr) {
        if (trenutni->rod->ld == trenutni)
            return trenutni->rod;
        if (trenutni->rod->dd == trenutni)
            trenutni = trenutni->rod;
    }

    return nullptr;

}

template<typename Tip>
void Stablo<Tip>::Erase(const Tip vrijednost) {
    Cvor *cvor = Find(vrijednost);
    if (cvor == nullptr) return;

    if (cvor->ld == nullptr && cvor->dd == nullptr) { //ako je list
        if (cvor->rod == nullptr) //ako je korijen
            korijen = nullptr;
        else {
            if (cvor->rod->ld == cvor)
                cvor->rod->ld = nullptr;
            else cvor->rod->dd = nullptr;
        }

    } else if (cvor->ld == nullptr) { //ako nema lijevo dijete
        cvor->dd->rod = cvor->rod;
        if (cvor->rod == nullptr) //ako je korijen
            korijen = cvor->dd;
        else {
            if (cvor->rod->ld == cvor)
                cvor->rod->ld = cvor->dd;
            else cvor->rod->dd = cvor->dd;
        }
    } else if (cvor->dd == nullptr) { //ako nema desno dijete
        cvor->ld->rod = cvor->rod;
        if (cvor->rod == nullptr) //ako je korijen
            korijen = cvor->ld;
        else {
            if (cvor->rod->ld == cvor)
                cvor->rod->ld = cvor->ld;
            else cvor->rod->dd = cvor->ld;
        }
    } else { //ako ima oba djeteta
        Cvor *sljedbenik = Sljedbenik(cvor);
        sljedbenik->ld = cvor->ld;
        cvor->ld->rod = sljedbenik;
        cvor->dd->rod = cvor->rod;
        if (cvor->rod == nullptr) //ako je korijen
            korijen = cvor->dd;
        else {
            if (cvor->rod->ld == cvor)
                cvor->rod->ld = cvor->dd;
            else cvor->rod->dd = cvor->dd;
        }
    }

    delete cvor;
    n--;
}

template<typename Tip>
typename Stablo<Tip>::Cvor *Stablo<Tip>::dajNajmanjiCvor(Stablo::Cvor *cvor) {
    if (cvor == nullptr) // ako je trenutni cvor nullptr, nema najmanjeg cvora, vraćamo nullptr
        return nullptr;
    Cvor *trenutni = cvor;  // postavljamo trenutni cvor kao pocetni cvor
    while (trenutni->ld != nullptr)
        trenutni = trenutni->ld; // prolazimo kroz lijevo podstablo dok ne dodjemo do najmanjeg cvora
    return trenutni; // vracamo najmanji cvor
}

template<typename Tip>
typename Stablo<Tip>::Cvor *Stablo<Tip>::dajNajveciCvor(Stablo::Cvor *cvor) {
    if (cvor == nullptr) //ako je trenutni cvor nullptr, nema najveceg cvora, vracamo nullptr
        return nullptr;
    Cvor *trenutni = cvor; //postavljamo trenutni cvor kao pocetni cvor
    while (trenutni->dd != nullptr)
        trenutni = trenutni->dd; //prolazimo kroz desno podstablo dok ne dodjemo do najveceg cvora
    return trenutni; // vracamo najveci cvor
}

template<typename Tip>
typename Stablo<Tip>::Cvor *Stablo<Tip>::dajSljedbenika(Stablo::Cvor *cvor) {
    if (cvor->dd != nullptr)
        return dajNajmanjiCvor(cvor->dd); // ako postoji desno dijete, sljedbenik je najmanji cvor u desnom podstablu
    Cvor *trenutni = cvor; //ostavljamo trenutni cvor na cvor za kojeg trazimo sljedbenika
    while (trenutni != korijen && trenutni == trenutni->rod->dd)
        trenutni = trenutni->rod; //ako je trenutni cvor desno dijete svog roditelja, idemo prema roditelju
    if (trenutni == korijen)
        return nullptr; //ako smo dosli do korijena i nismo pronasli sljedbenika, vraćamo nullptr
    else return trenutni->rod; //vracamo roditelja kao sljedbenika
}

#endif // STABLO_CPP
