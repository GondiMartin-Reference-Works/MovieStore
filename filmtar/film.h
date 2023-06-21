#ifndef FILM_H_INCLUDED
#define FILM_H_INCLUDED

#include "string5.h"
#include <iostream>
#include "memtrace.h"

/**
* Film ABSZTRAKT osztály.
* A cim-ben tároljuk a film cimének karaktereit,
* a kiadEv a film kiadásának éve,
* a lejatszIdo a film lejátszási ideje PERCBEN,
* a mufaj a film mufajának a karaktereit tárolja.
*/
class Film{

    ///Adattagok
    String cim;     ///< Film cime
    int lejatszIdo; ///< Film lejátszási ideje
    int kiadEv;     ///< Film kiadási éve
    String mufaj;   ///< Film mufaja

///Tagfüggvények
public:


    /// Paraméteres konstruktor.
    /// Ez a default is!
    /// @param cim - String tipusú változó cimnek
    /// @param kiadEv - int tip. vált. kiadási évnek
    /// @param lejatszIdo - int tip. vált. lejátszási idönek
    /// @param mufaj - String tip. vált. műfajnak
    Film(const char *cim, int lejatszIdo, int kiadEv, const char *mufaj = "N/A")
        : cim(cim), lejatszIdo(lejatszIdo), kiadEv(kiadEv), mufaj(mufaj) {};


    /// Clone függvény
    virtual Film* clone() = 0;


    /// Visszaadja a film cimét.
    /// @return - String tip. változó.
    String getCim() const {return cim;}


    /// Visszaadja a film kiadási évét.
    /// @return - int tip. vált.
    int getKiadEv() const {return kiadEv;}


    /// Visszaadja a film lejátszási idejét.
    /// @return - int tip. vált.
    int getLejatszIdo() const {return lejatszIdo;}


    /// Visszaadja a film műfaját.
    /// @return - String tip. vált.
    String getMufaj() const {return mufaj;}


    /// Kiirja a film attribútumait.
    /// Tisztán virtuális függvény, emiatt is ABSZTRAKT a Film osztály.
    /// A leszármazott osztályok print() függvényei hivódnak meg igazából.
    virtual void print(std::ostream& os) const = 0;


    /// Destruktor
    /// Megszünteti az objektumot.
    virtual ~Film() {};
};

/// Globális inserter az alaposztály adatainak a kiirásához.
/// @param os - ostream
/// @param f - Film& tipusú referencia a megadott filmre
/// @return os
inline std::ostream& operator<<(std::ostream& os, const Film& f) {
     return os << f.getCim() << "(" << f.getKiadEv() << "," << f.getLejatszIdo() << ",";
}

#endif // FILM_H_INCLUDED
