#include "inout.h"
#include "gtest_lite.h"
#include "memtrace.h"

using namespace std;

/// Sz�m beolvas�st v�grehajt� f�ggv�ny
/// @param min - ha adott egy tartom�ny, ahonnan szeretn�k egy sz�mot visszaadni, akkor ez a tartom�ny legkisebb m�g haszn�lhat� sz�ma
/// @param max - ha adott egy tartom�ny, ahonnan szeretn�k egy sz�mot visszaadni, akkor ez a tartom�ny legnagyobb m�g haszn�lhat� sz�ma
/// @param tartomany - logikai �rt�k arra, hogy l�tezik-e a fent emlitett tartom�ny
/// @param menuSzoveg - String tipus� v�ltoz� a sz�m beolvas�s utasit�s�nak
/// @return int - a megfelel� sz�m
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


/// Men� sorsz�m�nak beolvas�sa
/// @return - a megfelel� men� sorsz�m
int Menu(){
    String menuSzoveg = {
        "\n---------------------------------------------------------"
        "\nV�lassz az al�bbiak k�z�l k�rlek!\n"
        "\t1.   ~  Az �sszes film kilist�z�sa\n"
        "\t2.   ~  Az �sszes csal�di film kilist�z�sa\n"
        "\t3.   ~  Az �sszes dokumentumfilm kilist�z�sa\n"
        "\t4.   ~  Keres�s az adatb�zisban\n"
        "\t5.   ~  �j film hozz�adasa az adatb�zishoz\n"
        "\t6.   ~  Kil�p�s\n"
        "\t(55) ~  Titkos tesztesetek futtat�sa\n"
        "---------------------------------------------------------\n"
    };
    return SzamBeolvas(1,6, true, menuSzoveg);
}

/// Saj�t atoi f�ggv�ny, ami sz�mm� alakitja a kapott String tipus� v�ltoz�t
/// @param str - a String, amit int-� szeretn�nk var�zsolni
/// @param base - a sz�mrendszer alapja
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


/// Mem�ria hibakezel�shez
void outOfMem(){
    cerr << "Mem�ria megtelik!";
    exit(1);
}


/// Teszteseteket egy kalap al� vevo f�ggv�ny
void TesztEsetek(){

    Film* movie;    /// �ltal�nos film pointer a tesztesetekhez.

    /// Tesztelj�k az adatok kiirat�s�t
    /// Cim, kiad�si �v, lej�tsz�si id�, �s m�fajt�l f�gg�en a korhatar/leiras
    /// Ez most legyen a csal�di
    TEST(csal�di film, print){
        CsaladiFilm cs(4, "The Lion King", 87, 1994);
        std::stringstream ss;
        cs.print(ss);
        EXPECT_STREQ("The Lion King(1994,87,4)\n", ss.str().c_str());
    }ENDM

    /// Tesztelj�k az adatok kiirat�s�t
    /// Cim, kiad�si �v, lej�tsz�si id�, �s m�fajt�l f�gg�en a korhatar/leiras
    /// Most pedig a dokumentumfilm
    movie = new DokuFilm("2008-as globalis gazdasagi valsag tortenete.", "Inside Job", 108, 2010);
    TEST(dokumentumfilm, print){
        std::stringstream ss;
        movie->print(ss);
        EXPECT_STREQ("Inside Job(2010,108,2008-as globalis gazdasagi valsag tortenete.)\n", ss.str().c_str());
    }ENDM


    /// Adatb�zis tesztel�se vol.1
    /// L�trehozzunk egy �res adatb�zist
    Adatbazis ab; ///Adatb�zis l�trehoz�sa itt, hogy k�s�bb haszn�lni lehessen
    TEST(adatb�zis, konstruktor){
        size_t nulla = 0;
        EXPECT_EQ(nulla, ab.size());
    }ENDM

    /// Adatb�zis tesztel�se vol.2
    /// Most hozz�adjuk a kor�bban felvett 'movie' (filmet) az adatb�zishoz.
    TEST(adatb�zis, add){
        ab.add(movie);             /// Hozz�adjuk, ez lesz az adatb�zis els� eleme...
        std::stringstream ss;
        ab.listOsszesFilm(ss);     /// Most kiirjuk az �sszes film cim�t, vagyis azt az egyet
        EXPECT_STREQ("\t1. Inside Job\n", ss.str().c_str());
    }ENDM


    /// Most hozz�adunk kicsit t�bb filmet, �s kiirjuk mindegyiknek a cimet
    movie = new DokuFilm("Life's meaning", "Life", 42, 1942);
    ab.add(movie);
    movie = new CsaladiFilm(14, "Rajzfilmek", 120, 2010);
    ab.add(movie);
    TEST(adatb�zis, listOsszesFilm){
        std::stringstream ss;
        ab.listOsszesFilm(ss);
        EXPECT_STREQ("\t1. Inside Job\n\t2. Life\n\t3. Rajzfilmek\n", ss.str().c_str());
    }ENDM

    /// Most megkeress�nk egy adott filmet cim szerint
    String keresendo1("Inside Job");
    TEST(adatb�zis, listKeres){
        std::stringstream ss;
        ab.listKeres(ss, keresendo1);
        EXPECT_STREQ("\tInside Job(2010,108,2008-as globalis gazdasagi valsag tortenete.)\n", ss.str().c_str());
    }ENDM

    /// Ha nem szerepel egy keresett cim
    String keresendo2("Nincs");
    TEST(adatb�zis, listKeres(Nincs)){
        std::stringstream ss;
        ab.listKeres(ss, keresendo2);
        EXPECT_STREQ("\tAdatbazisban nem szerepel.\n", ss.str().c_str());
    }ENDM

    /// Ellen�rizz�k a t�l indexel�st
    /// Jelenleg 3 film van benne, vagyis a filmek[3]-ra kiv�telt kell dobnia
    TEST(adatb�zis, operator[]){
        std::stringstream ss;
        try{
            ab[3].print(ss);
        }
        catch(const char* p){
            ss << p;
        }
        EXPECT_STREQ("Ervenytelen indexeles!", ss.str().c_str());
    }ENDM

    /// Film keres�se �res adatb�zisban
    /// �res adatb�zisban val� keres�s�rt minusz egyet ad
    String cim("Valami");
    TEST(adatb�zis, szerepel()){
        Adatbazis ures_ab;
        int ertek = ures_ab.szerepel(cim);
        EXPECT_EQ(-1, ertek);

        /// Ugyanigy, ha viszont nem �res adatb�zisban vagyunk, de nem l�tez� film cimet keres�nk
        ertek = ab.szerepel(cim);
        EXPECT_EQ(-1, ertek);
    }ENDM

    /// Kilist�zzuk az �sszes csal�di filmet
    TEST(adatb�zis, listCsaladi()){
        std::stringstream ss;
        ab.listCsaladi(ss);
        EXPECT_STREQ("\tRajzfilmek(2010,120,14)\n", ss.str().c_str());
    }ENDM

    TEST(adatb�zis, copy){
        Adatbazis ab1;
        ab1.add(new CsaladiFilm(14, "Rajzfilmek", 120, 2010));
        Adatbazis ab2(ab1);
        EXPECT_EQ(ab1.size(), ab2.size());
    }ENDM
}

