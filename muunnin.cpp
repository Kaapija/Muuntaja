// Muutosmoottori ohjelmalle.
#include "saannot.hh"
#include "muunnin.hh"
#include "merkkijonoapu.hh"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool muunnin(Saannot& koodiolio, string syote) {
    string temp = "";
    int lopetin = 0;
    string lahtoyksikko = "";
    string kohdeyksikko = "";
    double luku = 0;
    int tarkiste = 0;
    int koko = 0; // Tuli warningejä jos vertailin stringien kokoja ilman välikättä, joten loin nämä kaksi muuttujaa poistamaan warningit.
    int koko2 = 0;
    string aakkoset = "ABCDEFGHIJKLMNOPQRSTUWVXYZabcdefghijklmnopqrstuwvxyz";
    poista_valilyonnit_alusta_ja_lopusta(syote);
    koko = syote.size();
    koko2 = aakkoset.size();
    for (int i = 0; i < koko; i++) {         // Luetaan syötettä kunnes tulee ensimmäinen kirjain. Tästä saadaan syötteestä muunnettava luku.
        for (int k = 0; k < koko2; k++) {
            if (syote.at(i) == aakkoset.at(k)) {
                lopetin = 1;
                break;
            }
        }
        if (lopetin == 1) {
            break;
        }
        else {
            tarkiste++;
        }
    }
    for (int i = 0; i < tarkiste; i++) {
        temp.push_back(syote.at(i)); // Tallennetaan muunnettava luku.
    }
    temp = poista_valilyonnit(temp);
    if (onko_double_string(temp) == false) {
        cout << "Virhe kayttajan syotteessa: virheellinen muunosspyynto!" << endl;
        return false;
    }
    luku = muuta_string_doubleksi(temp);
    for (int i = tarkiste; i < koko; i++) {       // Alkutyyppi sijaitsee muunnettavan arvon ja kohdearvon välissä, haetaan se erilliseen muuttujaan.
        if (syote.at(i) == ' ') {
            break;
        }
        else {
            lahtoyksikko.push_back(syote.at(i)); // Tallennetaan erilliseen muuttujaan.
        }
        tarkiste++;
    }

    for (int i = tarkiste; i < koko; i++) {       // Kohdetyyppi on alkutyypin jälkeen, otetaan talteen.
        kohdeyksikko.push_back(syote.at(i));
    }
    poista_valilyonnit_alusta_ja_lopusta(kohdeyksikko);         // Poistetaan ylimääräiset välit, tabulaattorilla tehdyt välit aiheuttavat virheellisiä syötteitä.
    poista_valilyonnit_alusta_ja_lopusta(lahtoyksikko);         // Tehtävänannossa sanotaan: " Aivan kuten syötetiedostoa luettaessa,
                                                                // käyttäjän näppäismistöltä syöttämissä muunnospyynnöissäkin voi olla ylimääräisiä _välilyöntejä_. ..." joten minusta asiaa ei tarvitse korjata.
    koodiolio.tee_muunnos(lahtoyksikko, kohdeyksikko, luku);        // Koodiolion avulla saadaan tehtyä muutos.
    return true;
}

