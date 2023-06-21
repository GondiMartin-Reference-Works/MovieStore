#include <iostream>
#include <locale>
#include <string>
///Sajátok
#ifdef _WIN32
    #include <windows.h>
#endif
#include "adatbazis.h"
#include "film.h"
#include "csaladi_film.h"
#include "doku_film.h"
#include "string5.h"
#include "inout.h"
#include "memtrace.h"

#define JPORTA_TESZT 1          /// 1 (TRUE), ha csak a tesztesetek kellenek, 0 (FALSE), ha nem csak azok...

using namespace std;

int main()
{
    setlocale(LC_ALL, "");
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif

    cout << "\nUdvozollek film adatbazisomban!" <<endl;

    set_new_handler(outOfMem);

#if JPORTA_TESZT == 0
    TesztEsetek(); /// A teszt esetek egyszeri meghivása a menürendszer elött JPorta számára
#endif //JPORTA_TESZT

#if JPORTA_TESZT >= 1
    Adatbazis *ab = new Adatbazis();
    Film *movie;

    ab->FajlBeolvas("filmek.txt");
     ///------------------------MENÜRENDSZER------------------------------------

     int menuSorszam = 0;

    do{
        menuSorszam = Menu();
        switch(menuSorszam){
            case 1: ab->listOsszesFilm(cout); break;
            case 2: ab->listCsaladi(cout); break;
            case 3: ab->listDoku(cout); break;
            case 4:
                {
                    String cim;
                    cout << "\tAdd meg a film cimet: ";
                    cin >> cim;
                    ab->listKeres(cout, cim);
                    break;
                }

            case 5:
                {
                    /// Műfaj
                    String utasSzov = {"\n\tAdd meg milyen mufaju filmet szeretnel megadni! (1: csaladi, 2: dokumentumfilm): "};
                    int mufaj = SzamBeolvas(1,2,true, utasSzov);
                    /// Cim
                    String cim;
                    cout << "\n\tAdd meg a film cimet: ";
                    cin >> cim;
                    if(ab->szerepel(cim) != -1){
                        cout << "\n\tAdatbazisban mar szerepel!" << endl;
                        break;
                    }
                    /// Kiadási év
                    int kiadev = SzamBeolvas(1921, 2021, true, "\n\tAdd meg a kiadasi evet!: ");
                    /// Lejátszási idő
                    int lejatszIdo = SzamBeolvas(0, 480, true, "\n\tAdd meg a lejatszadi idot!: ");
                    /// Feltölt
                    switch(mufaj){
                        case 1:
                            {
                                int korhatar = SzamBeolvas(5,18,true,"\n\tAdd meg a film korhatarat!: ");
                                movie = new CsaladiFilm(korhatar, cim.c_str(), lejatszIdo, kiadev);
                                ab->add(movie);
                                break;
                            }

                        case 2:
                            {
                                String leiras;
                                cout << "\n\tAdd meg a film rovid leirasat!: ";
                                cin >> leiras;
                                movie = new DokuFilm(leiras.c_str(), cim.c_str(), lejatszIdo, kiadev);
                                ab->add(movie);
                                break;
                            }

                    }
                    break;
                }
            case 6: cout << "\tKilepes" << endl; break;
            case 55: TesztEsetek(); break;
            default: cout << "\tMeg nincs kesz!" << endl; break;
        }
    }while(menuSorszam != 6);
    ab->FajlbaIras("filmek.txt");
    delete ab;
#endif // JPORTA_TESZT
    return 0;
}
