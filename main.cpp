//Energiamuunnoskone. Lukee annetun tiedoston ja laittaa sen lainalaisuudet stl-säiliöön.
//Tämän jälkeen tekee pyydetyt muunnokset.
#include "saannot.hh"
#include "muunnin.hh"
#include "lue.hh"
#include "onko_laillinen.hh"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    Saannot saannot;
    string syote = "";
    bool tarkiste;
    int kaynnistin = 1;
    cout << "Syota saantotiedoston nimi: ";
    getline(cin, syote);
    tarkiste = saannot.onko_olemassa(syote);    // Onko tiedosto olemassa?
    if (tarkiste == false) {
        cout << "Virhe syotetiedoston lukemisessa: tiedostoa ei ole!" << endl;
        return EXIT_FAILURE;
    }
    else {
        tarkiste = lue_tiedosto(saannot, syote);        // Onko virheellisiä rivejä?
        if (tarkiste == false) {
            cout << "Virhe syotetiedoston lukemisessa: virhellinen rivi!" << endl;
            return EXIT_FAILURE;
        }
        tarkiste = saannot.onko_ristiriitoja(); // Onko ristiriitoja?
        if (tarkiste == false) {
            cout << "Virhe syotetiedoston lukemisessa: ristiriitoja tiedostossa!" << endl;
            return EXIT_FAILURE;
        }
    }

    while (kaynnistin == 1) {        // Käyttöliittymä päälle.
        cout << "muunnospyynto> ";
        getline(cin, syote);
        if (syote.size() == 0) {
            break;
        }
        else {
            muunnin(saannot, syote); // Tehdään muutos.
        }
    }

    return EXIT_SUCCESS;
}
