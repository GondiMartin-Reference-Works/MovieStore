#ifndef CSALADI_FILM_H_INCLUDED
#define CSALADI_FILM_H_INCLUDED

#include "film.h"
#include "memtrace.h"

/**
* Családi film osztály.
* Megörökli a Film adattagjait.
* Továbbá rendelkezik egy újjal, ez a film korhatára.
*/
class CsaladiFilm;
std::ostream& operator<<(std::ostream& os, const CsaladiFilm& cs);
class CsaladiFilm : public Film{

    ///Adattag
    int korhatar;     ///< Családi film korhatára

///Tagfüggvények
public:


    /// Konstruktor
    /// Ez a default is!
    /// @param cim - String tipusú változó cimnek
    /// @param kiadEv - int tip. vált. kiadási évnek
    /// @param lejatszIdo - int tip. vált. lejátszási idõnek
    /// @param mufaj - String tip. vált. műfajnak
    /// @param korhatar - int tip. vált. korhatárnak
    CsaladiFilm(int korhatar, const char *cim, int lejatszIdo, int kiadEv, const char *mufaj = "Csaladi film")
        : Film(cim, lejatszIdo, kiadEv, mufaj), korhatar(korhatar) {};


    /// Clone függvény
    CsaladiFilm* clone(){
        return new CsaladiFilm(*this);
    }


    /// Lekérdezi a film korhatárát
    int getKorhatar() const {return korhatar;}


    /// Kiirja a családi film adatait
    void print(std::ostream& os) const {
        os << *this << std::endl;
    }


    /// Destruktor
    /// Megszünteti az objektumot.
    ~CsaladiFilm() {};
};

/// Globális inserter függvény a családi film attribútumainak kiirásához.
/// @param os - ostream
/// @param cs - CsaladiFilm& referencia a családi filmre
/// @return os
inline std::ostream& operator<<(std::ostream& os, const CsaladiFilm& cs){
    return os << (Film&)cs << cs.getKorhatar() << ")";
}

#endif // CSALADI_FILM_H_INCLUDED
