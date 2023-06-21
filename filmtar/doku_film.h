#ifndef DOKU_FILM_H_INCLUDED
#define DOKU_FILM_H_INCLUDED

#include "film.h"
#include "memtrace.h"

/**
* Dokumentumfilm osztály.
* Megörökli a Film adattagjait.
* Továbbá rendelkezik egy újjal, ez a film leirás.
*/
class DokuFilm;
std::ostream& operator<<(std::ostream& os, const DokuFilm& d);
class DokuFilm : public Film{

    ///Adattag
    String leiras;     ///< Dokumentumfilm leirása

///Tagfüggvények
public:


    /// Konstruktor
    /// Ez a default is!
    /// @param cim - String tipusú változó cimnek
    /// @param kiadEv - int tip. vált. kiadási évnek
    /// @param lejatszIdo - int tip. vált. lejátszási idõnek
    /// @param mufaj - String tip. vált. műfajnak
    /// @param leiras - String tip. vált. a leirásnak
    DokuFilm(const char *leiras, const char *cim, int lejatszIdo, int kiadEv, const char *mufaj = "Dokumentumfilm")
        : Film(cim, lejatszIdo, kiadEv, mufaj), leiras(leiras) {};


    /// Clone függvény
    DokuFilm* clone(){
        return new DokuFilm(*this);
    }


    /// Lekérdezi a film leirását
    String getLeiras() const {return leiras;}


    /// Kiirja a dokumentumfilm adatait
    void print(std::ostream& os) const {
        os << *this << std::endl;
    }


    /// Destruktor
    /// Megszünteti az objektumot.
    ~DokuFilm() {};

};

/// Globális inserter függvény a családi film attribútumainak kiirásához
/// @param os - ostream
/// @param d - DokuFilm& referencia a dokumentumfilmre
/// @return os
inline std::ostream& operator<<(std::ostream& os, const DokuFilm& d){
    return os << (Film&)d << d.getLeiras() << ")";
}

#endif // DOKU_FILM_H_INCLUDED
