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
bool provjeriDaLiJePodstablo(Stablo<Tip> &s1, Stablo<Tip> &s2) {
    // provjeravamo da li jedan od korijena nullptr to znaci da sigurno ne moze biti podstablo
    if (s1.Korijen() == nullptr || s2.Korijen() == nullptr) {
        return false;
    }

    //postavljamo trenutne cvorove za oba stabla
    typename Stablo<Tip>::Cvor *trenutniS = s1.Pocetak();
    typename Stablo<Tip>::Cvor *trenutniT = s2.Pocetak();

    //prolazimo kroz oba stabla
    while (trenutniS != nullptr && trenutniT != nullptr) {
        //ako je trenutni element stabla s1 manji od trenutnog elementa stabla s2
        //pomjeramo se na sljedeci element u stablu s1
        if (trenutniS->element < trenutniT->element) {
            trenutniS = s1.Sljedbenik(trenutniS);
        }
        //ako su trenutni elementi u oba stabla jednaki
        //pomjeramo se na sljedece elemente u oba stabla
        else if (trenutniS->element == trenutniT->element) {
            trenutniS = s1.Sljedbenik(trenutniS);
            trenutniT = s2.Sljedbenik(trenutniT);
        }
        //ako je trenutni element s1 veci od trenutnog elementa stabla s2, to znaci da s2 nije podskup od s1
        //pa vracamo false
        else {
            return false;
        }
    }
    //ako smo dosli do kraja stabla s2, onda je s2 podskup od s1
    return trenutniT == nullptr;
}

template<typename Tip>
typename Stablo<Tip>::Cvor *Stablo<Tip>::dajKtiElement(int pozicija, Stablo::Cvor *trenutniCvor, int &brojac) {
    // ako je trenutni cvor nullptr, ne mozemo dalje i vracamo nullptr
    if (trenutniCvor == nullptr)
        return nullptr;

    // rekurzivno trazimo k-ti najmanji element u lijevom podstablu
    typename Stablo<Tip>::Cvor *lijevi = dajKtiElement(pozicija, trenutniCvor->ld, brojac);

    // ako je k-ti najmanji element u lijevom podstablu vracamo ga
    if (lijevi != nullptr)
        return lijevi;

    brojac++;

    // ako je trenutni cvor k-ti najmanji vracamo taj cvor
    if (brojac == pozicija)
        return trenutniCvor;

    // rekurzivno trazimo k-ti najmanji element u desnom podstablu
    typename Stablo<Tip>::Cvor *desni = dajKtiElement(pozicija, trenutniCvor->dd, brojac);

    // vraćamo cvor iz desnog podstabla
    return desni;
}


template<typename Tip>
Tip Stablo<Tip>::operator[](int pozicija) {
    int brojac = 0;
    pozicija++; // dajKtiElement trazi k-ti najveci element, a ne indeks pa uvecavamo za jedan
    typename Stablo<Tip>::Cvor *rezultat = dajKtiElement(pozicija, korijen, brojac);

    if (rezultat == nullptr) {
        throw out_of_range("Trazeni element ne postoji u stablu.");
    }
    return rezultat->element;
}


#endif // STABLO_CPP
