#define __USE_MINGW_ANSI_STDIO 0
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
//#include <windows.h>
using namespace std;

class Pelitili {
private:
    fstream tiliTiedosto;
    string sisalto;

public:
    Pelitili() : tiliTiedosto("pelitili.txt") {}
    void alustaTiedot();
    void tiliValikko();
    void paivita(int, string);
    void tallenna();
    void naytaTiedot();
};

//prototyypit
int paavalikko(Pelitili&);
void rivinSyotto(int*, int);
bool syotteenTarkistus(int*, int);
bool arvoKenoRivi(int*, int);
void naytaKenoRivi(int*);

int main() {
	int valinta;
	int kenoTaso;
	int rivi1[10];
	int arvottuRivi[20];
	srand(time(0));
	int t = 0; //arvottu numero
	Pelitili tili;

	tili.alustaTiedot();
	valinta = paavalikko(tili);

	if (valinta == 0) {
		return 0;
	}
	else if (valinta == 1) {

		cout << "Valitse rivin keno taso 2-10: ";
		kenoTaso = 0;
		while (kenoTaso < 2 || kenoTaso > 10) {
			cin >> kenoTaso;
			if (kenoTaso < 2 || kenoTaso > 10) {
				cout << "Ei kelpaa, ";
			}
		}

		rivinSyotto(rivi1, kenoTaso);

		int i;
		for (i = 0; i < 20; i++) {
			t = 1 + (rand() % 70);
			if (arvoKenoRivi(arvottuRivi, t)) {
				arvottuRivi[i] = t;
			}
			else { i--; }
		}

		naytaKenoRivi(arvottuRivi);
	}
	else if (valinta == 2) {
        tili.tiliValikko();
	}
	else if (valinta == 3) {

	}
	else if (valinta == 4) {

	}
	else if (valinta == 5) {

	}

	system("pause>nul");

}


////////////////////////////////////////////////////////////////
// Tulostaa paavalikon ja kysyy kayttajalta halutun toiminnon.
// Valinta palautetaan paaohjelmaan.
//
////////////////////////////////////////////////////////////////
int paavalikko(Pelitili& tili) {

	char valinta = '0';
	int syotteenKoko;
	cout << "Kenopelisimulaattori" << endl;
	cout << "====================" << endl;
	tili.naytaTiedot();
	cout << "Toiminnot\n";
	cout << "1) Pelaa kenoa\n";
	cout << "2) Pelitili\n";
	cout << "L) Lopeta.\n";

	while (valinta == '0') {
		cout << "Syota valintasi: ";
		cin >> valinta;


		int valintaInt = valinta - '0'; //muutetaan kayttajan valinta char -> int vahentamalla ASCII arvo 48 eli '0'
		if (valinta == 'l' || valinta == 'L') {
            tili.tallenna();
            tili.naytaTiedot();
            cout << "Paina mita tahansa lopettaaksesi ohjelman.";
			return 0;
		}
		else if (valintaInt > 0 && valintaInt < 10) {
			cout << "\nValintasi: " << valintaInt << endl;;
			return valintaInt;
		}
		else {
			cout << "Valinta ei kelpaa! ";
			valinta = '0';
		}
	}
}

////////////////////////////////////////////////////////////////
// Rivin syotto aliohjelma. Funktioon halutun rivin pointteri
// ja pelatun rivin keno taso. Kayttamattomat rivit taytetaan
//	nollilla
////////////////////////////////////////////////////////////////
void rivinSyotto(int* rivi, int taso) {
	int temp;
	char vastaus;
	bool suorita = true;
	bool hyvaksy = false;

	while (suorita) {
		cout << "Syota rivi: ";

		for (int i = 0; i < taso; i++) {
			cin >> temp;
			if (syotteenTarkistus(rivi, temp) == true) {
				rivi[i] = temp;
			}
			else if (syotteenTarkistus(rivi, temp) == false) {
				cout << "Ei kelpaa! Anna toinen" << endl;
				i--;
			}

		}

		for (int k = taso; k < 10; k++) {
			rivi[k] = 0;
		}

		//
		cout << "Rivisi: [ ";
		for (int j = 0; j < taso; j++) {
			cout << rivi[j] << " ";

		}
		cout << "]" << endl;

		cin.clear();    // Restore input stream to working state
		cin.ignore(100, '\n');

		cout << "Hyvaksy rivi (k/e): ";
		hyvaksy = false;
		while (!hyvaksy) {
			hyvaksy = false;

			cin >> vastaus;

			if (vastaus == 'k' || vastaus == 'K') {
				suorita = false;
				hyvaksy = true;
			}
			else if (vastaus == 'e' || vastaus == 'E') {
				vastaus = 'x';
				suorita = true;
				hyvaksy = true;
				for (int n = 0; n < 10; n++) {
					rivi[n] = 0;
				}
			}
			else {
				cin.clear();
				cin.ignore(100, '\n');
				cin >> vastaus;
			}
		}
	}

}

////////////////////////////////////////////////////////////////
// Tarkistaa kayttajan syotteen, onko numero oikealla alueella
// ja etta luku ei ole jo rivissa.
// Funktioon halutun rivin pointteri ja tarkistettava numero
////////////////////////////////////////////////////////////////
bool syotteenTarkistus(int* rivi, int numero) {
	bool tarkistus = false;

	if (numero > 0 && numero <= 70) {
		for (int i = 0; i < 10; i++) {
			if (rivi[i] == numero) {
				tarkistus = false;
				return tarkistus;
			}
			else {
				tarkistus = true;
			}
		}
	}

	return tarkistus;
}

////////////////////////////////////////////////////////////////
//Aliohjelmaan syotetaan arvottu numero ja sita verrataan olemassa olevaan kenoriviin
//
//
////////////////////////////////////////////////////////////////
bool arvoKenoRivi(int* kenorivi, int t) {


	bool tarkistus = true;

	int i = 0;
	int j = 0;
	for (i = 0; i < 20; i++) {

		if (t > 0 && t <= 70) {
			for (j = 0; j < 20; j++) {
				if (kenorivi[j] == t) {
					tarkistus = false;
				}
			}
		}
		if (tarkistus == true) {
			return true;
		}
		return false;
	}
}

void naytaKenoRivi(int* kenorivi) {
	//
	cout << "Arvottu Keno Rivi: [ ";
	for (int i = 0; i < 20; i++) {
		cout << kenorivi[i] << " ";

	}
	cout << "]" << endl;

}

////////////////////////////////////////////////////////////////
//Alustetaan pelitili
//
//
////////////////////////////////////////////////////////////////
void Pelitili::alustaTiedot() {
    string rivi;
    if (tiliTiedosto.is_open()) {
        while (!tiliTiedosto.eof()) {
            getline(tiliTiedosto, rivi);
            this->sisalto.append(rivi);
            this->sisalto.append("\n");
        }
    }
}

////////////////////////////////////////////////////////////////
//Pelaajatilivalikko
//
//
////////////////////////////////////////////////////////////////
void Pelitili::tiliValikko() {
    int val;
    string uusiNimi, uusiSaldoStr;
    int uusiSaldo;

    cout << "\nMita haluat tehda?\n";
    cout << "1. Nayta tiedot\n";
    cout << "2. Vaihda pelaajanimi\n";
    cout << "3. Lisaa saldoa\n";
    cout << "4. Siirry paavalikkoon\n";
    cout << "Valitse: ";
    cin >> val;

    switch (val) {
    case 1:
        naytaTiedot();
        tiliValikko();
        break;
    case 2:
        cout << "Anna uusi nimi: ";
        cin >> uusiNimi;
        paivita(val, uusiNimi);
        break;
    case 3:
        cout << "Kuinka paljon lisataan saldoa? ";
        cin >> uusiSaldo;
        uusiSaldoStr = to_string(uusiSaldo);
        paivita(val, uusiSaldoStr);
        break;
    case 4:
        paavalikko(*this);
        break;
    default:
        cout << "Valinta ei kelpaa!";
        tiliValikko();
    }
}

////////////////////////////////////////////////////////////////
//Paivita nimi
//
//
////////////////////////////////////////////////////////////////
void Pelitili::paivita(int rivi, string arvo) {

    string alkuS;
    string loppuS = "\n";

    switch (rivi) {
    //Nimi
    case 2:
        alkuS = "Nimi: ";
        break;
    //Saldo
    case 3:
        alkuS = "Saldo: ";
        break;
    default:
        cout << "Pelaajatilin paivitys epaonnistui.\n";
        tiliValikko();
    }

    unsigned int alku = this->sisalto.find(alkuS) + alkuS.length();
    unsigned int loppu = this->sisalto.find("\n", alku);

    if (alku != string::npos && loppu != string::npos) {
        string vanha = this->sisalto.substr(alku, loppu - alku);
        this->sisalto.replace(alku, vanha.length(), arvo);
    }
    else {
        cout << "Pelaajatilin paivitys epaonnistui.\n";
    }
    tiliValikko();
}

////////////////////////////////////////////////////////////////
//Pelaajatiedon tallennus tiedostoon
//
//
////////////////////////////////////////////////////////////////
void Pelitili::tallenna() {
    if (tiliTiedosto.is_open()) {
        //TODO: ei toimi
//        tiliTiedosto << this->sisalto;
//        cout << "\nPelitilin tiedot tallennettu." << endl;
    }
    tiliTiedosto.close();
}

////////////////////////////////////////////////////////////////
//Naytetaan pelitilin tiedot
//
//
////////////////////////////////////////////////////////////////
void Pelitili::naytaTiedot() {
    cout << "\n" << this->sisalto;
}
