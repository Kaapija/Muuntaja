// Luettavan tiedoston virheentarkistelu.
#include "onko_laillinen.hh"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Tämä funktio tarkistaa onko mjono sallitussa muodossa.

bool onko_laillinen(string mjono) {
    string AAKKOSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ/";
    string aakkoset = "abcdefghijklmnopqrstuvwxyz/";
    int testeri = 0;
    int pituus = mjono.size();
    for (int i = 0; i < pituus; i++) {
        for (int k = 0; k < 27; k++) {
            if (mjono.at(i) == AAKKOSET.at(k)) {
                testeri = testeri + 1;
            }
            else if (mjono.at(i) == aakkoset.at(k)) {
                testeri = testeri + 1;
            }
            else if (mjono.at(i) == '/' && i == 0) {
                return false;
            }
        }
    }
    if (mjono.back() == '/') {
        return false;
    }
    if (testeri == pituus) {
        return true;
    }
    return false;
}

