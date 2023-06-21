#include "inout.h"
#include "gtest_lite.h"
#include "memtrace.h"

using namespace std;

/// Szám beolvasást végrehajtó függvény
/// @param min - ha adott egy tartomány, ahonnan szeretnék egy számot visszaadni, akkor ez a tartomány legkisebb még használható száma
/// @param max - ha adott egy tartomány, ahonnan szeretnék egy számot visszaadni, akkor ez a tartomány legnagyobb még használható száma
/// @param tartomany - logikai érték arra, hogy létezik-e a fent emlitett tartomány
/// @param menuSzoveg - String tipusú változó a szám beolvasás utasitásának
/// @return int - a megfelelö szám
int SzamBeolvas(int min, int max, bool tartomany, String menuSzoveg){
    bool helyes = false;
    int szam;
    int tesztEset = 55;
    do{
        cout << menuSzoveg << endl;
        cout << "\tAdd meg a szamot!: ";
        cin >> szam;
        if(cin.fail()){
            cout << "\tHelytelen bemeneti adatok!" << endl;
            cin.clear();
            cin.ignore(256, '\n');
        }
        else if(tartomany && (szam > max || szam < min) && szam != tesztEset)
            cout << "\tA megadott szam nem volt megfelelo!" << endl;
        else
            helyes = true;
    }while(!helyes);
    return szam;
}


/// Menü sorszámának beolvasása
/// @return - a megfelelö menü sorszám
int Menu(){
    String menuSzoveg = {
        "\n---------------------------------------------------------"
        "\nVálassz az alábbiak közül kérlek!\n"
        "\t1.   ~  Az összes film kilistázása\n"
        "\t2.   ~  Az összes családi film kilistázása\n"
        "\t3.   ~  Az összes dokumentumfilm kilistázása\n"
        "\t4.   ~  Keresés az adatbázisban\n"
        "\t5.   ~  Új film hozzáadasa az adatbázishoz\n"
        "\t6.   ~  Kilépés\n"
        "\t(55) ~  Titkos tesztesetek futtatása\n"
        "---------------------------------------------------------\n"
    };
    return SzamBeolvas(1,6, true, menuSzoveg);
}

/// Saját atoi függvény, ami számmá alakitja a kapott String tipusú változót
/// @param str - a String, amit int-é szeretnénk varázsolni
/// @param base - a számrendszer alapja
int stoi(String& str, int base){
    int szam = 0;
    int fokszam = str.size();
    int szorzo = 1;
    for(int i = 0; i < fokszam-1; ++i)
        szorzo *= base;

    int j = 0;
    const char* data = str.c_str();
    while(data[j] != '\0'){
        (data[j]-'0'<base) ? szam+=szorzo*(data[j++]-'0') : throw "Hiba";
        szorzo /= base;
    }
    return szam;
}


/// Memória hibakezeléshez
void outOfMem(){
    cerr << "Memória megtelik!";
    exit(1);
}


/// Teszteseteket egy kalap alá vevo függvény
void TesztEsetek(){

    Film* movie;    /// Általános film pointer a tesztesetekhez.

    /// Teszteljük az adatok kiiratását
    /// Cim, kiadási év, lejátszási idö, és müfajtól függöen a korhatar/leiras
    /// Ez most legyen a családi
    TEST(családi film, print){
        CsaladiFilm cs(4, "The Lion King", 87, 1994);
        std::stringstream ss;
        cs.print(ss);
        EXPECT_STREQ("The Lion King(1994,87,4)\n", ss.str().c_str());
    }ENDM

    /// Teszteljük az adatok kiiratását
    /// Cim, kiadási év, lejátszási idö, és müfajtól függöen a korhatar/leiras
    /// Most pedig a dokumentumfilm
    movie = new DokuFilm("2008-as globalis gazdasagi valsag tortenete.", "Inside Job", 108, 2010);
    TEST(dokumentumfilm, print){
        std::stringstream ss;
        movie->print(ss);
        EXPECT_STREQ("Inside Job(2010,108,2008-as globalis gazdasagi valsag tortenete.)\n", ss.str().c_str());
    }ENDM


    /// Adatbázis tesztelése vol.1
    /// Létrehozzunk egy üres adatbázist
    Adatbazis ab; ///Adatbázis létrehozása itt, hogy késöbb használni lehessen
    TEST(adatbázis, konstruktor){
        size_t nulla = 0;
        EXPECT_EQ(nulla, ab.size());
    }ENDM

    /// Adatbázis tesztelése vol.2
    /// Most hozzáadjuk a korábban felvett 'movie' (filmet) az adatbázishoz.
    TEST(adatbázis, add){
        ab.add(movie);             /// Hozzáadjuk, ez lesz az adatbázis elsö eleme...
        std::stringstream ss;
        ab.listOsszesFilm(ss);     /// Most kiirjuk az összes film cimét, vagyis azt az egyet
        EXPECT_STREQ("\t1. Inside Job\n", ss.str().c_str());
    }ENDM


    /// Most hozzáadunk kicsit több filmet, és kiirjuk mindegyiknek a cimet
    movie = new DokuFilm("Life's meaning", "Life", 42, 1942);
    ab.add(movie);
    movie = new CsaladiFilm(14, "Rajzfilmek", 120, 2010);
    ab.add(movie);
    TEST(adatbázis, listOsszesFilm){
        std::stringstream ss;
        ab.listOsszesFilm(ss);
        EXPECT_STREQ("\t1. Inside Job\n\t2. Life\n\t3. Rajzfilmek\n", ss.str().c_str());
    }ENDM

    /// Most megkeressünk egy adott filmet cim szerint
    String keresendo1("Inside Job");
    TEST(adatbázis, listKeres){
        std::stringstream ss;
        ab.listKeres(ss, keresendo1);
        EXPECT_STREQ("\tInside Job(2010,108,2008-as globalis gazdasagi valsag tortenete.)\n", ss.str().c_str());
    }ENDM

    /// Ha nem szerepel egy keresett cim
    String keresendo2("Nincs");
    TEST(adatbázis, listKeres(Nincs)){
        std::stringstream ss;
        ab.listKeres(ss, keresendo2);
        EXPECT_STREQ("\tAdatbazisban nem szerepel.\n", ss.str().c_str());
    }ENDM

    /// Ellenörizzük a túl indexelést
    /// Jelenleg 3 film van benne, vagyis a filmek[3]-ra kivételt kell dobnia
    TEST(adatbázis, operator[]){
        std::stringstream ss;
        try{
            ab[3].print(ss);
        }
        catch(const char* p){
            ss << p;
        }
        EXPECT_STREQ("Ervenytelen indexeles!", ss.str().c_str());
    }ENDM

    /// Film keresése üres adatbázisban
    /// Üres adatbázisban való keresésért minusz egyet ad
    String cim("Valami");
    TEST(adatbázis, szerepel()){
        Adatbazis ures_ab;
        int ertek = ures_ab.szerepel(cim);
        EXPECT_EQ(-1, ertek);

        /// Ugyanigy, ha viszont nem üres adatbázisban vagyunk, de nem létezö film cimet keresünk
        ertek = ab.szerepel(cim);
        EXPECT_EQ(-1, ertek);
    }ENDM

    /// Kilistázzuk az összes családi filmet
    TEST(adatbázis, listCsaladi()){
        std::stringstream ss;
        ab.listCsaladi(ss);
        EXPECT_STREQ("\tRajzfilmek(2010,120,14)\n", ss.str().c_str());
    }ENDM

    TEST(adatbázis, copy){
        Adatbazis ab1;
        ab1.add(new CsaladiFilm(14, "Rajzfilmek", 120, 2010));
        Adatbazis ab2(ab1);
        EXPECT_EQ(ab1.size(), ab2.size());
    }ENDM
}

