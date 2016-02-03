// Sääntö-luokka. Määritellään kaikki metodit ja säilö, mitä ohjelmassa on.

#include "saannot.hh"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

Saannot::Saannot() {
}

bool Saannot::onko_olemassa(string tiedoston_nimi) {     // Tarkistetaan onko syötetty tiedosto olemassa.

    ifstream tiedosto_olio{ tiedoston_nimi };
    if (not tiedosto_olio) {
        tiedosto_olio.close();
        return false;
    }
    string syoterivi = "";
    while (getline(tiedosto_olio, syoterivi)) {
    }

    tiedosto_olio.close();
    return true;
}

bool Saannot::talleta_rivi_reaaliluvulla(string kohde, double kerroin, string alku, double reaaliluku, int monesko) {        // Tallennetaan tauluun luettu rivi.
    lista[monesko].kohde_ = kohde;
    lista[monesko].alku_ = alku;
    lista[monesko].kerroin_ = kerroin;
    lista[monesko].reaaliluku_ = reaaliluku;
    monta_ = monesko;
    return true;
}

bool Saannot::onko_ristiriitoja() {      // Tarkistetaan onko ristiriitoja, duplikaatti ei vaikuta tulostamiseen, sen arvo tallennetaan, mutta vain ensimmäistä käytetään.
    for (int i = 0; i < monta_; i++) {
        if (lista[i].kohde_ == lista[i].alku_) {
            return false;
        }
        for (int k = (i + 1); k < monta_; k++) {
            if (lista[i].kohde_ == lista[k].kohde_) {
                if (lista[i].alku_ == lista[k].alku_) {
                    if (lista[i].kerroin_ != lista[k].kerroin_) {
                        return false;
                    }
                    else if (lista[i].reaaliluku_ != lista[k].reaaliluku_) {
                        return false;
                    }
                }
            }
            if (lista[i].kohde_ == lista[k].alku_) {
                int testeri = 0;
                int testeri2 = 0;
                testeri = 1 / lista[i].kerroin_;
                testeri2 = lista[i].reaaliluku_ / lista[i].kerroin_;
                if (testeri != lista[k].kerroin_ && lista[i].kohde_ == lista[k].alku_ && lista[i].alku_ == lista[k].kohde_) {
                    return false;
                }
                else if (testeri2 != lista[k].reaaliluku_ && lista[i].kohde_ == lista[k].alku_) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Saannot::tee_muunnos(string alku, string kohde, double luku) {      // Tulostetaan haluttu muutos.
    int varmiste = 0;
    int varmiste2 = 0;
    for (int i = 0; i < monta_; i++) {
        if (alku == lista[i].alku_ && kohde == lista[i].kohde_ && varmiste == 0) {
            cout << setprecision(3) << fixed << luku * lista[i].kerroin_ + lista[i].reaaliluku_ << endl;
            varmiste = varmiste + 1;
        }
    }
    for (int i = 0; i < monta_; i++) {
        if (alku == lista[i].kohde_ && kohde == lista[i].alku_ && varmiste == 0 && varmiste2 == 0) {
            cout << setprecision(3) << fixed << (1 / lista[i].kerroin_) * luku - lista[i].reaaliluku_ / lista[i].kerroin_ << endl;
            varmiste2 = varmiste2 + 1;
        }
    }
    if (varmiste == 0 && varmiste2 == 0) {
        cout << "Virhe kayttajan syotteessa: tuntematon muunnos! " << endl;
    }
}
