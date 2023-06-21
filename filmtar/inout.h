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
* A felhaszn�l� �s a program k�z�tti kommunik�ci�t megval�sit� fobb f�ggv�nyek egy modulban.
* Itt tal�hat�:
*   - Sz�m beolvas�st segit� f�ggv�ny
*   - Men�t kezelo f�ggv�ny
*   - A tesztesetek
*/

/// Men� sorsz�m�nak beolvas�sa
/// @return - a megfelel� men� sorsz�m
int Menu();


/// Saj�t atoi f�ggv�ny, ami sz�mm� alakitja a kapott String tipus� v�ltoz�t
/// @param str - a String, amit int-� szeretn�nk var�zsolni
/// @param base - a sz�mrendszer alapja
int stoi(String& str, int base = 10);


/// Sz�m beolvas�st v�grehajt� f�ggv�ny
/// @param min - ha adott egy tartom�ny, ahonnan szeretn�k egy sz�mot visszaadni, akkor ez a tartom�ny legkisebb m�g haszn�lhat� sz�ma
/// @param max - ha adott egy tartom�ny, ahonnan szeretn�k egy sz�mot visszaadni, akkor ez a tartom�ny legnagyobb m�g haszn�lhat� sz�ma
/// @param tartomany - logikai �rt�k arra, hogy l�tezik-e a fent emlitett tartom�ny
/// @param menuSzoveg - String tipus� v�ltoz� a sz�m beolvas�s utasit�s�nak
/// @return int - a megfelel� sz�m
int SzamBeolvas(int min, int max, bool tartomany, String menuSzoveg = "");


/// Teszteseteket egy kalap al� vev� f�ggv�ny
void TesztEsetek();


/// Mem�ria hibakezel�shez
void outOfMem();

#endif // INOUT_H_INCLUDED
