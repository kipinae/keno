#include <iostream>
#include <cstdlib>
#include <ctime>
//#include <string>
//#include <windows.h>
using namespace std;

//prototyypit
int paavalikko();
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

	valinta = paavalikko();


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
// Tulostaa päävalikon ja kysyy käyttäjältä halutun toiminnon.
// Valinta palautetaan pääohjelmaan.
//
////////////////////////////////////////////////////////////////
int paavalikko() {

	char valinta = '0';
	int syotteenKoko;
	cout << "Kenopelisimulaattori" << endl;
	cout << "====================" << endl;
	cout << endl;
	cout << "Toiminnot\n";
	cout << "1) Pelaa kenoa\n";
	cout << "2) Pelitili\n";
	cout << "l/L Lopeta.\n";



	while (valinta == '0') {
		cout << "Syota valintasi: ";
		cin >> valinta;


		int valintaInt = valinta - '0'; //muutetaan käyttäjän valinta char -> int vähentämällä ASCII arvo 48 eli '0'
		if (valinta == 'l' || valinta == 'L') {
			return 0;
		}
		else if (valintaInt > 0 && valintaInt < 10) {
			cout << "Valintasi: " << valintaInt << endl;;
			return valintaInt;
		}
		else {
			cout << "Valinta ei kelpaa! ";
			valinta = '0';
		}
	}
}


////////////////////////////////////////////////////////////////
// Rivin syöttö aliohjelma. Funktioon halutun rivin pointteri
// ja pelatun rivin keno taso. Käyttämättömät rivit täytetään  
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
// Tarkistaa käyttäjän syötteen, onko numero oikealla alueella
// ja että luku ei ole jo rivissä.
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
//Aliohjelmaan syötetään arvottu numero ja sitä verrataan olemassa olevaan kenoriviin 
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
