#ifndef ADATBAZIS_H_INCLUDED
#define ADATBAZIS_H_INCLUDED

#include "film.h"
#include "doku_film.h"
#include "csaladi_film.h"
#include "inout.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include "memtrace.h"

/**
* Adatbazis osztály.
* Itt tároljuk a filmeket egy dinamikus tömbben.
*/
class Adatbazis{

    ///Adattagok
    size_t db;       ///< A filmek darabszáma
    Film **filmek;   ///< Film pointerekre mutató pointer -> dinamikus tömb


///Tagfüggvények
public:



    /// Paraméter nélküli konstruktor.
    /// Üres adatbázis
    Adatbazis() : db(0){
        filmek = new Film*[db];
    }

    /// Copy konstruktor
    /// @param Adatbazis& ab - másolandó adatbázis
    Adatbazis(const Adatbazis& ab) : db(0){
        *this = ab;
    }

    /// Értékadó operátor
    /// @param Adatbazis& ab - másolandó adatbázis
    Adatbazis& operator=(const Adatbazis& ab){
        if(this != &ab){
            for(size_t i = 0; i<db; ++i)
                delete filmek[i];
            db = ab.db;
            filmek = new Film*[db];
            for(size_t i = 0; i < db; ++i)
                filmek[i] = ab.filmek[i]->clone();
        }
        return *this;
    }


    /// Tároló méretének lekérdezése.
    /// @return - size_t tip. vált. a méretnek
    size_t size() const { return db; }


    /// Adott film lekérdezése az adatbázisból.
    /// Nem létezo 'i' index esetén kivételt dob.
    /// @param i - az index maga - size_t tipusú!
    /// @return - Ha helyes és létezo indexet kapott, akkor visszaadja a tároló i-edik elem cimét, ellenkezo esetben ez egy új elemre való hivatkozás, igy kivételt dob.
    Film& operator[](size_t i);


    /// Film hozzáadása az adatbázishoz.
    /// @param Film* - Absztrakt osztály tipusú változóra mutató pointer
    void add(Film*);


    /// Kilistázza az összes film cimet az adatbázisban.
    /// @param os - ostream
    void listOsszesFilm(std::ostream& os) const;


    /// Kiértékeli, hogy egy adott műfajú film létezik-e az adatbázisban.
    /// @param mufaj - const char* tipus a megadott műfajnak.
    /// @return - bool (TRUE, ha létezik. FALSE, ha nem.)
    bool adottMufaj(const char* mufaj) const;


    /// Kilistázza az összes olyan filmet, amelynek műfaja "csaladi film".
    /// @param os - ostream
    void listCsaladi(std::ostream& os) const;


    /// Kilistázza az összes olyan filmet, amelynek műfaja "dokumentumfilm".
	/// @param os - ostream
    void listDoku(std::ostream& os) const;


    /// Film cimet keres az adatbázisban.
    /// @param cim - const char* a keresendo film cime.
    /// @return int - a (megtalált) film indexe az adatbázisban. Ha nem szerepelt benne, akkor minusz egyet ad.
    int szerepel(String& p_cim) const;


    /// Kezeli a szerepel() függvény visszatérési értékét.
    /// @param cim - const char* a keresendo film cime.
    /// @param os - ostream.
    void listKeres(std::ostream& os, String& p_cim) const;


    /// Adatbázis destruktora.
    ~Adatbazis(){
        for(size_t i = 0; i < db; ++i)
            delete filmek[i];
        delete[] filmek;
    }


    /// Kezeli a fájlból való beolvasást. Beolvassa a filmeket egy adatbázisba
    /// @param ab - az adatbázis, amibe olvasunk
    /// @param fajl_nev - a fájl, amiböl olvasunk.
    void FajlBeolvas(const char* fajl_nev);


    /// Fájlba ir filmeket egy megadott adatbázisból
    /// @param fajl_nev - a fájl neve, amibe irjuk az adatokat
    void FajlbaIras(const char* fajl_nev);

};

#endif // ADATBAZIS_H_INCLUDED
