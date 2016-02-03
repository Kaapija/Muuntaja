//Tämä moduuli lukee annetun tiedoston.
#include "saannot.hh"
#include "onko_laillinen.hh"
#include "lue.hh"
#include "merkkijonoapu.hh"
#include <iostream>
#include <fstream>
#include <string>



using namespace std;

bool lue_tiedosto(Saannot& koodiolio, string tiedosto) {
    string syoterivi = "";
    bool testeri;
    vector<string> erottimet = { "<=", "*", "+" };
    vector<string> erottimet2 = { "<=", "*", "-" };
    vector<string> erottimet3 = { "<=", "*" };
    vector<string> tuloskentat;
    string rivi2 = "";
    string kohde = "";
    double kerroin = 0;
    string alku = "";
    double reaaliluku = 0;
    int monesko = 0;
    bool laillinenko;
    ifstream tiedosto_olio{ tiedosto };
    while ((getline(tiedosto_olio, syoterivi))) {
        if (syoterivi.size() == 0) { // Hypätään tyhjien rivin ohi.
            continue;
        }
        rivi2 = poista_valilyonnit(syoterivi);
        if (rivi2.at(0) == '#') { // Hypätään kommenttirivien ohi.
            continue;
        }
        else {
            testeri = paloittele_rivi(rivi2, erottimet, tuloskentat); // Laitetaan rivit joissa reaaliluku on positiivinen listaan.
            if (testeri == true) {
                kohde = tuloskentat.at(0);      // Tarkistetaan onko kohdetyyppi laillinen.
                laillinenko = onko_laillinen(kohde);
                if (laillinenko == false) {
                    tiedosto_olio.close();
                    return false;
                }
                kerroin = muuta_string_doubleksi(tuloskentat.at(2));
                alku = tuloskentat.at(4);       // Tarkistetaan onko alkutyyppi laillinen.
                laillinenko = onko_laillinen(alku);
                if (laillinenko == false) {
                    tiedosto_olio.close();
                    return false;
                }
                reaaliluku = muuta_string_doubleksi(tuloskentat.at(6));
                testeri = koodiolio.talleta_rivi_reaaliluvulla(kohde, kerroin, alku, reaaliluku, monesko); // Itse tallennus tapahtuu.
            }
            else {
                testeri = paloittele_rivi(rivi2, erottimet2, tuloskentat);  // Laitetaan rivit joissa reaaliluku on negatiivinen listaan.
                if (testeri == true) {
                    kohde = tuloskentat.at(0);
                    laillinenko = onko_laillinen(kohde);
                    if (laillinenko == false) {
                        tiedosto_olio.close();
                        return false;
                    }
                    kerroin = muuta_string_doubleksi(tuloskentat.at(2));
                    alku = tuloskentat.at(4);
                    laillinenko = onko_laillinen(alku);
                    if (laillinenko == false) {
                        tiedosto_olio.close();
                        return false;
                    }
                    reaaliluku = muuta_string_doubleksi(tuloskentat.at(6));
                    reaaliluku = reaaliluku * (-1);
                    testeri = koodiolio.talleta_rivi_reaaliluvulla(kohde, kerroin, alku, reaaliluku, monesko);
                }
                else {
                    testeri = paloittele_rivi(rivi2, erottimet3, tuloskentat);      // Laitetaan rivit joissa ei ole reaalilukua listaan.
                    if (testeri == true) {
                        kohde = tuloskentat.at(0);
                        laillinenko = onko_laillinen(kohde);
                        if (laillinenko == false) {
                            tiedosto_olio.close();
                            return false;
                        }
                        kerroin = muuta_string_doubleksi(tuloskentat.at(2));
                        alku = tuloskentat.at(4);
                        laillinenko = onko_laillinen(alku);
                        if (laillinenko == false) {
                            tiedosto_olio.close();
                            return false;
                        }
                        reaaliluku = 0;
                        testeri = koodiolio.talleta_rivi_reaaliluvulla(kohde, kerroin, alku, reaaliluku, monesko);
                    }
                    else {
                        cout << "Virhe syotetiedoston lukemisessa: tiedostossa virheellinen rivi!" << endl;
                        tiedosto_olio.close();
                        return false;
                    }
                }
            }
        }
        monesko++;

    }
    tiedosto_olio.close();
    return true;
}

