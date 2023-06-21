#ifndef INOUT_H_INCLUDED
#define INOUT_H_INCLUDED

#include "string5.h"
#include <iostream>
#include "film.h"
#include "csaladi_film.h"
#include "doku_film.h"
#include "adatbazis.h"
#include "memtrace.h"

/**
* A felhasználó és a program közötti kommunikációt megvalósitó fobb függvények egy modulban.
* Itt taláható:
*   - Szám beolvasást segitö függvény
*   - Menüt kezelo függvény
*   - A tesztesetek
*/

/// Menü sorszámának beolvasása
/// @return - a megfelelö menü sorszám
int Menu();


/// Saját atoi függvény, ami számmá alakitja a kapott String tipusú változót
/// @param str - a String, amit int-é szeretnénk varázsolni
/// @param base - a számrendszer alapja
int stoi(String& str, int base = 10);


/// Szám beolvasást végrehajtó függvény
/// @param min - ha adott egy tartomány, ahonnan szeretnék egy számot visszaadni, akkor ez a tartomány legkisebb még használható száma
/// @param max - ha adott egy tartomány, ahonnan szeretnék egy számot visszaadni, akkor ez a tartomány legnagyobb még használható száma
/// @param tartomany - logikai érték arra, hogy létezik-e a fent emlitett tartomány
/// @param menuSzoveg - String tipusú változó a szám beolvasás utasitásának
/// @return int - a megfelelö szám
int SzamBeolvas(int min, int max, bool tartomany, String menuSzoveg = "");


/// Teszteseteket egy kalap alá vevö függvény
void TesztEsetek();


/// Memória hibakezeléshez
void outOfMem();

#endif // INOUT_H_INCLUDED
