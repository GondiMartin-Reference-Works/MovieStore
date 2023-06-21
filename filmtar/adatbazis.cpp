#include "adatbazis.h"
#include <cstring>
#include "memtrace.h"

using namespace std;

/// Adott film lekérdezése az adatbázisból
/// Nem létezo 'i' index esetén kivételt dob
/// @param i - az index maga - size_t tipusú!
/// @return - Ha helyes és létezo indexet kapott, akkor visszaadja a tároló i-edik elem cimét, ellenkezo esetben ez egy új elemre való hivatkozás, igy kivételt dob.
Film& Adatbazis::operator[](size_t i){
    if(i>=db)
        throw ("Ervenytelen indexeles!");
    return *filmek[i];
}


/// Film hozzáadása az adatbázishoz
/// @param Film* - Absztrakt osztály tipusú változóra mutató pointer
void Adatbazis::add(Film *film){
    ++db;
    Film **tmp = new Film*[db];
    for(size_t i = 0; i<db-1; ++i)
        tmp[i] = filmek[i];
    delete[] filmek;
    tmp[db-1] = film;
    filmek = tmp;
}


/// Kilistázza az összes film cimet az adatbázisban
/// @param os - ostream
void Adatbazis::listOsszesFilm(std::ostream& os) const{
    if(db!=0){
        for(size_t i = 0; i < db; ++i)
            os << "\t" <<(i+1) << ". " << filmek[i]->getCim() << endl;
    }
    else
        os << "\tNincs film az adatbázisban!" << endl;

}


/// Kiértékeli, hogy egy adott mufajú film létezik-e az adatbázisban
/// @param mufaj - const char* tipus a megadott műfajnak
/// @return - bool (TRUE, ha létezik. FALSE, ha nem.)
bool Adatbazis::adottMufaj(const char* mufaj) const{
    for(size_t i = 0; i < db; ++i){
        if(strcmp(filmek[i]->getMufaj().c_str(), mufaj)==0)
            return true;
    }
    return false;
}


/// Kilistázza az összes olyan filmet, amelynek mufaja "csaladi film"
/// @param os - ostream
void Adatbazis::listCsaladi(std::ostream& os) const{
    if(adottMufaj("Csaladi film")){
        for(size_t i = 0; i < db; ++i){
            if(strcmp(filmek[i]->getMufaj().c_str(),"Csaladi film")==0){
                os << '\t';
                filmek[i]->print(os);
            }
        }
    }
    else
        os << "\tNincs csaladi film az adatbazisban!" << endl;
}


/// Kilistázza az összes olyan filmet, amelynek mufaja "dokumentumfilm"
/// @param os - ostream
void Adatbazis::listDoku(std::ostream& os) const{
    if(adottMufaj("Dokumentumfilm")){
        for(size_t i = 0; i < db; ++i){
            if(strcmp(filmek[i]->getMufaj().c_str(),"Dokumentumfilm")==0){
                os << '\t';
                filmek[i]->print(os);
            }
        }
    }
    else
        os << "\tNincs dokumentumfilm az adatbazisban!" << endl;
}


/// Film cimet keres az adatbázisban
/// @param cim - const char* a keresendo film cime
/// @return int - a (megtalált) film indexe az adatbázisban. Ha nem szerepelt benne, akkor minusz egyet ad.
int Adatbazis::szerepel(String& p_cim) const{
    if(db==0)
        return -1;
    else{
        for(size_t i = 0; i < db; ++i){
            if(strcmp(filmek[i]->getCim().c_str(), p_cim.c_str()) == 0)
                return i;
        }
    }
    return -1;
}


/// Kezeli a szerepel() függvény visszatérési értékét
/// @param cim - const char* a keresendo film cime
/// @param os - ostream
void Adatbazis::listKeres(std::ostream& os, String& p_cim) const{
    int index = szerepel(p_cim);
    if(index == -1)
        os << "\tAdatbazisban nem szerepel." << endl;
    else{
        os << '\t';
        filmek[index]->print(os);
    }
}

/// Kezeli a fájlból való beolvasást. Beolvassa a filmeket az adatbázisba
/// @param fajl_nev - a fájl, amiböl olvasunk.
void Adatbazis::FajlBeolvas(const char* fajl_nev){
    fstream fajl;
    fajl.open(fajl_nev, ios::in);
    if(!fajl)
        cout << "A fajl nem letezik!" << endl;
    else{
        Film *movie;
        /**
        * 0: film cime
        * 1: mufaja
        * 2: kiadási éve
        * 3: lejátszási ideje
        * 4: mufaj szerinte: korhatár vagy leirás
        * fajlban: "1:0(2,3,4)
        */
        /// Beolvasás
        String line("");
        while(fajl >> line){
            String cim("");
            String mufaj("");
            String kiad_ev("");
            String lejatsz_ido("");
            String leiras("");
            String kor_hatar("");

            int idx = 0;
            /// Mufaj
            while(line[idx] != ':'){
                String c(line[idx++]);
                mufaj = mufaj + c;
            }
            ++idx;
            /// Cim
            while(line[idx] != '('){
                String c(line[idx++]);
                cim = cim + c;
            }
            ++idx;
            /// Kiadási év
            while(line[idx] != ','){
                String c(line[idx++]);
                kiad_ev = kiad_ev + c;
            }
            ++idx;
            /// Lejátszási idö
            while(line[idx] != ','){
                String c(line[idx++]);
                lejatsz_ido = lejatsz_ido + c;
            }
            ++idx;
            if(strcmp(mufaj.c_str(), "Csaladi film") == 0){
                while(line[idx] != ')'){
                    String c(line[idx++]);
                    kor_hatar = kor_hatar + c;
                }
                movie = new CsaladiFilm(stoi(kor_hatar), cim.c_str(), stoi(lejatsz_ido), stoi(kiad_ev));
            }
            else
            {
                while(line[idx] != ')'){
                    String c(line[idx++]);
                    leiras = leiras + c;
                }
                movie = new DokuFilm(leiras.c_str(), cim.c_str(), stoi(lejatsz_ido), stoi(kiad_ev));
            }
            add(movie);
        }
        fajl.close();
    }
}

/// Fájlba ir filmeket az adatbázisból
/// @param fajl_nev - a fájl neve, amibe irjuk az adatokat
void Adatbazis::FajlbaIras(const char* fajl_nev){
    std::fstream fajl;
    fajl.open(fajl_nev, std::ios::out);
    if(!fajl)
        std::cout << "A fajl nem letezik!" << std::endl;
    else{
        for(size_t i = 0; i < db; i++){
            fajl << filmek[i]->getMufaj() << ':';
            filmek[i]->print(fajl);
        }
        fajl.close();
        //delete_last_line(fajl_nev, ab.size()+1);
        std::cout << "Kiiratas megtortent!" << std::endl;
    }
}
