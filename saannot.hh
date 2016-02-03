#ifndef SAANNOT_HH
#define SAANNOT_HH

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Saannot {
public:
    Saannot();

    bool onko_olemassa(string tiedoston_nimi);
    bool talleta_rivi_reaaliluvulla(string kohde, double kerroin, string alku, double reaaliluku, int monesko);
    bool onko_ristiriitoja();
    void tee_muunnos(string alku, string kohde, double luku);

private:
    struct Saanto_alkio {
        string kohde_;
        string alku_;
        double kerroin_;
        double reaaliluku_;

    } lista[100];
    int monta_;
};


#endif // SAANNOT_HH
