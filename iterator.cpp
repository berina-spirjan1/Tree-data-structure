#ifndef ITERATOR_CPP
#define ITERATOR_CPP

#include "iterator.h"
#include "stablo.h"

/**
 * @brief Iterator na najmanji element u podstablu trenutnog čvora.
 *
 * Metoda najmanjiNaGrani pomjera iterator na najmanji element u podstablu trenutnog čvora.
 * Ova metoda unutar svoje definicije poziva drugu funkciju pomjeriNaGrani i proslijeđuje
 * joj lambda funkciju, što kao rezultat vraća iterator na lijevo dijete trenutnog čvora.
 * Iterator se pomjera na najmanji element u podstablu tako što se kontinuirano pomjera
 * na lijevo dijete dok god ono postoji. Kao rezultat metoda vraća iterator na najmanji
 * element u podstablu trenutnog čvora.
 *
 * @return Iterator na najmanji element u podstablu trenutnog čvora.
 */
template<typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::najmanjiNaGrani() {
    return pomjeriNaGrani(
            [](Cvor *cvor) {
                return cvor != nullptr ? cvor->ld : nullptr;
            }); //pomjeramo se svaki put na lijevo dijete od trenutnog cvora
}

/**
 * @brief Iterator na najmanji ili najveći element u podstablu trenutnog čvora.
 *
 * Metoda pomjeriNaGrani je implementirana kako bismo izbjegli dupliciranje koda.
 * Kao parametar prima lambda funkciju koja vraća iterator na lijevo ili desno dijete
 * trenutnog čvora, u zavisnosti od potrebe za traženjem najmanjeg ili najvećeg elementa.
 * Iterator se pomjera na najmanji ili najveći element u podstablu tako što se kontinuirano
 * pomjera na lijevo ili desno dijete čvora, dokle god takvo dijete postoji. Kao rezultat
 * poziva metode pomjeriNaGrani dobijamo iterator koji pokazuje na najmanji ili najveći
 * element u podstablu trenutnog čvora.
 *
 * @param funkcijaPomjeranja Lambda funkcija koja vraća iterator na lijevo ili desno dijete trenutnog čvora.
 * @return Iterator na najmanji ili najveći element u podstablu trenutnog čvora.
 */
template<typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::pomjeriNaGrani(function<Cvor * (Cvor * )> funkcijaPomjeranja) {
    if (this->trenutni == nullptr)
        return *this; // Ako je trenutni čvor nullptr, nema najmanjeg/najvećeg elementa, vraćamo trenutni iterator
    while (funkcijaPomjeranja(this->trenutni) != nullptr)
        this->trenutni = funkcijaPomjeranja(
                this->trenutni); // Prolazimo kroz lijevo/desno podstablo dok ne dođemo do najmanjeg/najvećeg elementa
    return *this; // Vraćamo promijenjeni iterator
}


/**
 * @brief Iterator na najveći element u podstablu trenutnog čvora.
 *
 * Metoda najveciNaGrani pomjera iterator na najveći element u podstablu trenutnog čvora.
 * Ova metoda unutar svoje definicije poziva drugu funkciju pomjeriNaGrani i proslijeđuje
 * joj lambda funkciju, što kao rezultat vraća iterator na desno dijete trenutnog čvora.
 * Iterator se pomjera na najveći element u podstablu tako što se kontinuirano pomjera
 * na desno dijete dok god ono postoji. Kao rezultat metoda vraća iterator na najveći
 * element u podstablu trenutnog čvora.
 *
 * @return Iterator na najveći element u podstablu trenutnog čvora.
 */
template<typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::najveciNaGrani() {
    return pomjeriNaGrani([](Cvor *cvor) {
        return cvor != nullptr ? cvor->dd : nullptr;
    }); //pomjeramo se na desno dijete od trenutnog cvora
}


/**
 * @brief Operator prefiksne inkrementacije za klasu Iterator.
 *
 * Operator prefiksne inkrementacije (++it) za klasu Iterator zasniva se na ideji
 * da pomjeramo iterator na sljedeći element u inorder obilasku stabla. Ovo radimo
 * na način da provjeramo da li postoji desno dijete trenutnog čvora. Ukoliko postoji,
 * pomjeramo iterator sve dok ne dođemo do najmanjeg elementa u desnom podstablu.
 * Suprotno, ako ne postoji desno dijete, iterator pomjeramo prema roditelju dok ne
 * dođemo do prvog lijevog djeteta. Kada stignemo do korijena, znači da će nam iterator
 * pokazivati na nullptr i tu se zaustavljamo. Kao rezultat ovaj operator vraća referencu
 * na modifikovani iterator.
 *
 * @return Referenca na modifikovani iterator nakon inkrementacije.
 */
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
        if (this->trenutni->rod != nullptr) {
            this->trenutni = this->trenutni->rod;
        }
    }
    return this;
}

/**
 * @brief Operator postfiksne inkrementacije za klasu Iterator.
 *
 * Operator postfiksne inkrementacije (it++) za klasu Iterator funkcioniše na način
 * da u početku napravimo kopiju trenutnog iteratora, a zatim pomjeramo trenutni (originalni)
 * iterator na sljedeći element u inorder obilasku stabla. Ako postoji desno dijete trenutnog čvora,
 * iterator pomjeramo na najmanji element u desnom podstablu. Ako ne postoji desno dijete, iterator
 * pomjeramo prema roditelju dok ne pronađemo prvo lijevo dijete. U trenutku kada dođemo do korijena,
 * naš iterator će pokazivati na nullptr. Parametar koji prima ovaj operator se naziva dummy parametar,
 * on nam služi samo kako bismo označili postfiksni operator inkrementiranja, ali ga u funkciji ne koristimo.
 * Kao rezultat primjene operatora postfiksne inkrementacije vraćamo kopiju prvobitnog iteratora koja je sada modifikovana.
 *
 * @param DummyParam Dummy parametar (int) koji označava postfiksni operator inkrementiranja, ali se ne koristi u funkciji.
 * @return Kopija prvobitnog iteratora koja je sada modifikovana.
 */
template<typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::operator++(int) {
    Iterator kopija(this);  // pravimo kopiju trenutnog iteratora
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

/**
 * @brief Operator prefiksnog dekrementiranja za klasu Iterator.
 *
 * Operator prefiksnog dekrementiranja (--it) za klasu Iterator koristi se kako bi se
 * iterator pomjerio na prethodni element u inorder poretku stabla. Ako za trenutni čvor
 * postoji lijevo dijete, iterator se pomjera na najveći element u lijevom podstablu.
 * U suprotnom, ukoliko ne postoji lijevo dijete, iterator se pomjera ka roditelju sve
 * dok ne dođe do prvog desnog djeteta. Kada stignemo do korijena, iterator će pokazivati
 * na nullptr. Kao rezultat vraćamo modifikovani iterator.
 *
 * @return Modifikovani iterator nakon dekrementiranja.
 */
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

/**
 * @brief Operator postfiksnog dekrementiranja za klasu Iterator.
 *
 * Operator postfiksnog dekrementiranja (it--) za klasu Iterator pravi kopiju trenutnog
 * iteratora, a zatim mijenja trenutni iterator. Ako postoji lijevo dijete trenutnog čvora,
 * iterator se pomjera na najveci element u lijevom podstablu. Ako ne postoji lijevo dijete,
 * iterator se pomjera ka roditelju sve dok ne dođemo do prvog desnog djeteta. Ako dođemo do
 * korijena, iterator će pokazivati na nullptr. Kao rezultat iz operatora vraćamo kopiju prvobitnog
 * iteratora koja je sada modifikovana.
 *
 * @param DummyParam Dummy parametar koji označava postfiksni operator dekrementiranja, ali se ne koristi u funkciji.
 * @return Kopija prvobitnog iteratora koja je sada modifikovana.
 */
template<typename Tip>
typename Stablo<Tip>::Iterator Stablo<Tip>::Iterator::operator--(int) {
    Iterator kopija(this);  // pravimo kopiju trenutnog iteratora
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

/**
 * \brief Vraća iterator koji pokazuje na najveći element na trenutnoj grani stabla.
 *
 * Funkcija se koristi unutar Reverse_Iterator klase kako bismo pronašli najveći element
 * na trenutnoj grani binarnog stabla pretrage. Pomičemo iterator s trenutne pozicije na
 * desno dijete trenutnog čvora (ukoliko postoji).
 *
 * \return Reverse_Iterator koji pokazuje na najveći element na trenutnoj grani.
 */
template<typename Tip>
typename Stablo<Tip>::Reverse_Iterator Stablo<Tip>::Reverse_Iterator::najveciNaGrani() {
    return pomjeriNaGrani([](Cvor *cvor) {
        return cvor != nullptr ? cvor->dd : nullptr;
    }); //pomjeramo se na desno dijete od trenutnog cvora
}

/**
 * \brief Pomičemo iterator na najmanji ili najveći element na trenutnoj grani stabla.
 *
 * Funkcija se koristi unutar Reverse_Iterator klase kako bi iterator bio pomaknut
 * na najmanji ili najveći element na trenutnoj grani binarnog stabla pretrage. Prolazimo
 * kroz lijevo ili desno podstablo sve dok ne dođemo do najmanjeg ili najvećeg elementa.
 *
 * \param funkcijaPomjeranja Funkcija koja određuje smjer pomjeranja po grani (npr., lijevo ili desno).
 *
 * \return Promijenjeni Reverse_Iterator koji pokazuje na najmanji ili najveći element na trenutnoj grani.
 */
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

/**
 * \brief Pomičemo iterator na najmanji element na trenutnoj grani stabla.
 *
 * Funkcija se koristi unutar Reverse_Iterator klase kako bi iterator bio pomaknut
 * na najmanji element na trenutnoj grani binarnog stabla pretrage. Prolazimo kroz lijevo
 * podstablo sve dok ne dođemo do najmanjeg elementa.
 *
 * \return Promijenjeni Reverse_Iterator koji pokazuje na najmanji element na trenutnoj grani.
 */

template<typename Tip>
typename Stablo<Tip>::Reverse_Iterator Stablo<Tip>::Reverse_Iterator::najmanjiNaGrani() {
    return pomjeriNaGrani(
            [](Cvor *cvor) {
                return cvor != nullptr ? cvor->ld : nullptr;
            }); //pomjeramo se svaki put na lijevo dijete od trenutnog cvora
}


/**
 * \brief Povećava iterator na sledeći element u obrnutom poretku stabla.
 *
 * Funkcija se koristi unutar Reverse_Iterator klase kako bi iterator bio povećan
 * na sljedeći element u obrnutom poretku binarnog stabla pretrage. Ako trenutni čvor
 * ima lijevo dijete, pomičemo se na najveći element u lijevom podstablu. Inače, vraćamo
 * se prema roditeljskom čvoru sve dok ne pronađemo prvi čvor koji nije lijevo dijete
 * svog roditelja.
 *
 * \return Promijenjeni Reverse_Iterator koji pokazuje na sljedeći element u obrnutom poretku.
 */
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

/**
 * \brief Povećava iterator na sljedeći element u obrnutom poretku stabla.
 *
 * Funkcija se koristi unutar Reverse_Iterator klase kako bi iterator bio povećan
 * na sljedeći element u obrnutom poretku binarnog stabla pretrage. Ako trenutni čvor
 * ima lijevo dijete, pomičemo se na njegovo dijete i zatim na najdesniji element u
 * njegovom podstablu. Inače, vraćamo originalni iterator i pomjeramo trenutni iterator
 * prema roditelju sve dok ne pronađemo prvi čvor koji nije lijevo dijete svog roditelja.
 *
 * \param int Dummy parametar (nije u upotrebi, koristi se samo za prepoznavanje postinkrementa).
 *
 * \return Originalni Reverse_Iterator prije povećanja.
 */
template<typename Tip>
typename Stablo<Tip>::Reverse_Iterator Stablo<Tip>::Reverse_Iterator::operator++(int) {
    // kreiramo kopiju trenutnog iteratora
    Reverse_Iterator kopija(this);

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

/**
 * \brief Smanjuje iterator na prethodni element u obrnutom poretku stabla.
 *
 * Funkcija se koristi unutar Reverse_Iterator klase kako bi iterator bio smanjen
 * na prethodni element u obrnutom poretku binarnog stabla pretrage. Ako trenutni čvor
 * ima desno dijete, pomičemo se na najmanji element u desnom podstablu. Inače, vraćamo
 * se prema roditeljskom čvoru sve dok ne pronađemo prvi čvor koji nije desno dijete
 * svog roditelja.
 *
 * \return Promijenjeni Reverse_Iterator koji pokazuje na prethodni element u obrnutom poretku.
 */
template<typename Tip>
typename Stablo<Tip>::Reverse_Iterator Stablo<Tip>::Reverse_Iterator::operator--() {
    if (trenutni != nullptr) {
        if (trenutni->dd != nullptr) {
            // ako postoji desno dijete, pomjeramo se na najmanji element u desnom podstablu
            trenutni = trenutni->dd;
            najmanjiNaGrani();
        } else {
            // ako nema desnog djeteta, idemo prema gore do prvog čvora koji je lijevo dijete svog roditelja
            while (trenutni->rod != nullptr && trenutni == trenutni->rod->dd) {
                trenutni = trenutni->rod;
            }
            // ako smo došli do korijena, iterator će pokazivati na nullptr,
            // inače idemo na roditelja trenutnog čvora.
            if (trenutni->rod != nullptr) {
                trenutni = trenutni->rod;
            }
        }
    }

    return *this;  // vraćamo promijenjeni iterator
}

/**
 * \brief Smanjuje iterator na prethodni element u obrnutom poretku stabla.
 *
 * Funkcija se koristi unutar Reverse_Iterator klase kako bi iterator bio smanjen
 * na prethodni element u obrnutom poretku binarnog stabla pretrage. Ako trenutni čvor
 * ima desno dijete, pomičemo se na najmanji element u desnom podstablu. Inače, vraćamo
 * originalni iterator i pomjeramo trenutni iterator prema roditelju sve dok ne pronađemo
 * prvi čvor koji nije desno dijete svog roditelja.
 *
 * \param int Dummy parametar (nije u upotrebi, koristi se samo za prepoznavanje postdekrementa).
 *
 * \return Originalni Reverse_Iterator prije smanjenja.
 */
template<typename Tip>
typename Stablo<Tip>::Reverse_Iterator Stablo<Tip>::Reverse_Iterator::operator--(int) {
    Reverse_Iterator kopija(*this);  // pravimo kopiju trenutnog iteratora

    if (trenutni != nullptr) {
        if (trenutni->dd != nullptr) {
            // ako postoji desno dijete, pomjeramo se na najmanji element u desnom podstablu
            trenutni = trenutni->dd;
            najmanjiNaGrani();
        } else {
            // ako nema desnog djeteta, idemo prema gore do prvog čvora koji je lijevo dijete svog roditelja
            while (trenutni->rod != nullptr && trenutni == trenutni->rod->dd) {
                trenutni = trenutni->rod;
            }
            // ako smo došli do korijena, iterator će pokazivati na nullptr,
            // inače idemo na roditelja trenutnog čvora.
            if (trenutni->rod != nullptr) {
                trenutni = trenutni->rod;
            }
        }
    }

    return kopija;  // vraćamo kopiju prvobitnog iteratora koja je sada modifikovana
}


#endif // ITERATOR_CPP
