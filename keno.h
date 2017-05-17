// Kirjastot
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;
// Globaali valinta kayttajaliittymaan
char valinta;
int main()
{
	do {
		// Taulukot lottonumeroille
		int AlkuNumerot[9];
		int LottoSyote[7];
		int LisaSyote[2];
		int ItseArvottuLotto[7];
		int ItseArvottuLisa[2];
		int JokeriKone[7];
		int JokeriKayttaja[7];
		unsigned short MoniLotto[10][7];
		unsigned short MoniLisa[10][2];
		// Generoidaan 9 uniikkia lottonumeroa
		srand(time(0));
		bool tarkistus;
		for (int i = 0; i < 9; i++) {
			do {
				tarkistus = false;
				AlkuNumerot[i] = 1 + (rand() % 39);
				for (int j = i - 1; j > -1; j--) {
					if (AlkuNumerot[i] == AlkuNumerot[j]) {
						tarkistus = true;
					}
				}
			} while (tarkistus);
		}
		// Kopioidaan alkutaulukon 9 numeroa kahdeksi taulukoksi, jossa toisessa on lottonumerot ja toisessa lisanumerot
		int oikein = 0;
		int LottoNumerot[7], LisaNumerot[2];
		memcpy(LottoNumerot, AlkuNumerot, 7 * sizeof(int));
		memcpy(LisaNumerot, &AlkuNumerot[7], 2 * sizeof(int));
		// Kayttoliittyma, joista valitaan valintaan haluttu toiminto
		cout << "Lottopelisimulaattori" << endl;
		cout << "=====================" << endl;
		cout << endl;
		cout << "Toiminnot:" << endl;
		cout << "1) Oikean lottorivin arvonta." << endl;
		cout << "2) Yhden rivin lotto" << endl;
		cout << "3) Yhden rivin lotto arvotulla tuloksella." << endl;
		cout << "4) Useamman rivin lotto arvotulla tuloksella." << endl;
		cout << "5) Yhden rivin jokeri." << endl;
		cout << "l/L Lopeta." << endl;
		cout << "Syota valintasi: ";
		cin >> valinta;
		cout << endl;
		// Toiminto 1 valittu. Tulostetaan aikaisemmin arvotut lottonumerot ja lisanumerot
		if (valinta == '1') {
			cout << "Lottonumerot: ";
			for (int j = 0; j < 7; j++) {
				cout << LottoNumerot[j] << " ";
			}
			cout << endl;
			cout << "Lisanumerot: " << LisaNumerot[0] << " " << LisaNumerot[1] << " " << endl;
		}
		// Toiminto 2 valittu. Kayttaja syottaa lottorivin, lisanumerot ja oman lottorivin.
		else if (valinta == '2') {
			cout << "Anna arvottu lottorivi: ";
			for (int i = 0; i < 7; i++) {
				cin >> ItseArvottuLotto[i];
			}
			cout << "Anna arvotut lisanumerot: ";
			for (int j = 0; j < 2; j++) {
				cin >> ItseArvottuLisa[j];
			}
			cout << "Anna oma lottorivi: ";
			for (int g = 0; g < 7; g++) {
				cin >> LottoSyote[g];
			}
			// Tarkastetaan ja lasketaan loton ja oman rivin numerot. 
			for (int k = 0; k < 7; k++) {
				for (int h = 0; h < 7; h++) {
					if (ItseArvottuLotto[k] == LottoSyote[h]) {
						oikein++;
					}
				}
			}
			// Jos yli 4 on oikein, tulostetaan voitit, muuten tulostetaan ei vottoa.
			if (oikein >= 4) {
				cout << "Tulos: Voitit!" << endl;
			}
			else {
				cout << "Tulos: Ei voittoa!" << endl;
			}
		}
		// Toiminto 3 valittu. Kayttaja syottaa lottorivinsa ja lisanumeronsa.
		else if (valinta == '3') {
			cout << "Anna oma lottorivi: ";
			for (int i = 0; i < 7; i++) {
				cin >> LottoSyote[i];
			}

			cout << "Anna omat lisanumerot: ";
			for (int j = 0; j < 2; j++) {
				cin >> LisaSyote[j];
			}
			cout << endl;
			// Alussa randomisoidut lottonumerot tulostetaan
			cout << "Arvottu lottorivi: ";
			for (int t = 0; t < 7; t++) {
				cout << LottoNumerot[t] << " ";
			}
			// Alussa randomisoidut lisanumerot tulostetaan ja vertaillaan omaa rivia.
			cout << ", lisanumerot " << LisaNumerot[0] << " " << LisaNumerot[1] << endl;
			cout << "Oma rivi: ";
			for (int r = 0; r < 7; r++) {
				cout << LottoSyote[r] << " ";
			}
			cout << endl;
			// Tarkastetaan ja lasketaan oikeat luvut.
			for (int k = 0; k < 7; k++) {
				for (int h = 0; h < 7; h++) {
					if (LottoNumerot[k] == LottoSyote[h]) {
						oikein++;
					}
				}
			}
			// Jos 6 numeroa on oikein, tarkastetaan lisanumerot.
			if (oikein == 6) {
				for (int k = 0; k < 7; k++) {
					for (int h = 0; h < 7; h++) {
						if (LottoNumerot[k] == LisaSyote[h]) {
							oikein++;
						}
					}
				}
			}
			// Tulostetaan oikeiden numeroiden maara, jos ei tarvitse katsoa lisanumeroita.
			else {
				cout << "Tulos: " << oikein << " oikein." << endl;
			}
		}
		// Toiminto 4 valittu. Aikaisemmin randomisoitu lottorivi jarjestetaan pienimmasta suurimpaan.
		else if (valinta == '4') {
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 6 - i; j++)
				{
					if (LottoNumerot[j] > LottoNumerot[j + 1])
					{
						int temp = LottoNumerot[j];
						LottoNumerot[j] = LottoNumerot[j + 1];
						LottoNumerot[j + 1] = temp;
					}
				}
			}
			// Lisataan taulukko, joka pitaa kirjaa jokaisen lottorivin oikeista numeroista, alkuarvo tietenkin nollaksi ensin.
			int OikeinTaulukko[10] = { 0 };
			// Laskuri pitaa huolen rivin numeroista kayttajalle.
			int laskuri = 1;
			int maara = 0;
			// Kysytaan lottorivien maaraa
			cout << "Anna lottorivien maara: ";
			cin >> maara;
			// Syotetaan jokaisen rivin lottorivi ja lisanumerot. Ne tallennetaan omaan lokeroon taulukossa.
			cout << endl;
			cout << "Anna lottorivisi: ";
			cout << endl;
			for (int i = 0; i < maara; i++) {
				cout << "Rivi " << laskuri << ": ";
				laskuri++;
				for (int j = 0; j < 7; j++) {
					cin >> MoniLotto[i][j];
				}
			}
			// Laskuri aloitetaan alusta, ettei lisanumerot aloita rivilta 3, vaan palaa arvoon 1.
			laskuri = 1;
			cout << endl;
			cout << "Anna lisanumerosi: ";
			cout << endl;
			for (int g = 0; g < maara; g++) {
				cout << "Rivi " << laskuri << ": ";
				laskuri++;
				for (int h = 0; h < 2; h++) {
					cin >> MoniLisa[g][h];
				}
			}
			cout << endl;
			// Jarjestetaan syotetty lottorivi pienimmasta suurimpaan.
			for (int rivi = 0; rivi < maara; rivi++) {
				for (int i = 0; i < 7; i++) {
					for (int j = i; j < 7; j++) {
						if (MoniLotto[rivi][i] > MoniLotto[rivi][j]) {
							int temp = MoniLotto[rivi][i];
							MoniLotto[rivi][i] = MoniLotto[rivi][j];
							MoniLotto[rivi][j] = temp;
						}
					}
				}
			}
			// Jarjestetaan syotetty lisarivi pienimmasta suurimpaan.
			for (int rivi = 0; rivi < maara; rivi++) {
				for (int i = 0; i < 2; i++) {
					for (int j = i; j < 2; j++) {
						if (MoniLisa[rivi][i] > MoniLisa[rivi][j]) {
							int temp = MoniLisa[rivi][i];
							MoniLisa[rivi][i] = MoniLisa[rivi][j];
							MoniLisa[rivi][j] = temp;
						}
					}
				}
			}
			// Tarkastetaan, kuinka monta numeroa on oikein kussakin lottorivissa.
			for (int a = 0; a < maara; a++) {
				for (int k = 0; k < 7; k++) {
					for (int h = 0; h < 7; h++) {
						if (LottoNumerot[k] == MoniLotto[a][h]) {
							OikeinTaulukko[a]++;
						}
					}
				}
			}
			// Tulostetaan loton arvotut numerot, oikeat numerot per lottorivi, oma lottorivi ja lisanumerot.
			cout << "Tulos:" << endl;
			cout << "Arvottu lottorivi: ";
			cout << endl;
			for (int i = 0; i < 7; i++) {
				cout << LottoNumerot[i] << " ";
			}
			// Jarjestetaan lisanumerot
			if (LisaNumerot[0] > LisaNumerot[1]) {
				cout << ", lisanumerot " << LisaNumerot[1] << " " << LisaNumerot[0];
			}
			else {
				cout << ", lisanumerot " << LisaNumerot[0] << " " << LisaNumerot[1];
			}
			laskuri = 1;
			for (int i = 0; i < maara; i++) {
				cout << endl << endl;
				// Jos vahemman kuin 4 oikein, tulostetaan ei voittoa.
				if (OikeinTaulukko[i] < 4) {
					cout << "Rivin oikeat luvut: " << OikeinTaulukko[i] << ", ei voittoa." << endl;
				}
				// Jos tulos ei ole vahemman kuin 4, mutta vahemman kuin 6, tulostetaan voitit!.
				else if (OikeinTaulukko[i] > 3 && OikeinTaulukko[i] < 6) {
					cout << "Rivin oikeat luvut: " << OikeinTaulukko[i] << ", voitit!" << endl;
				}
				// Jos 6 oikein, tarkastetaan lisanumerot
				else if (OikeinTaulukko[i] == 6) {
					for (int a = 0; a < maara; a++) {
						for (int k = 0; k < 7; k++) {
							for (int h = 0; h < 7; h++) {
								if (LottoNumerot[k] == MoniLisa[a][h]) {
									OikeinTaulukko[a]++;
								}
							}
						}
					}
				}
				// Tulostetaan omat lottorivit.
				cout << "Rivi " << laskuri << ": ";
				laskuri++;
				for (int j = 0; j < 7; j++) {
					cout << MoniLotto[i][j] << " ";
				}
			}
			cout << endl;
		}
		// Toiminto 5 valittu. Arvotaan jokeririvi ja suodatetaan samat numerot pois, etta jaljelle jaa uniikit.
		else if (valinta == '5') {
			cout << "Jokeririvi arvottu." << endl;
			int laske = 0;
			bool JokeriTarkistus;
			for (int i = 0; i < 7; i++) {
				do {
					JokeriTarkistus = false;
					JokeriKone[i] = (rand() % 10);
					for (int j = i - 1; j > -1; j--) {
						if (JokeriKone[i] == JokeriKone[j]) {
							JokeriTarkistus = true;
						}
					}
				} while (JokeriTarkistus);
			}
			// Kayttaja syottaa oman rivinsa
			cout << "Anna oma jokeririvi: ";
			for (int h = 0; h < 7; h++) {
				cin >> JokeriKayttaja[h];
			}
			cout << endl;
			// Tarkastetaan, etta numerot ovat samassa jarjestyksessa samoilla numeroilla.
			for (int k = 0; k < 7; k++) {
				if (JokeriKayttaja[k] == JokeriKone[k]) {
					laske++;
				}
			}
			// Tulostetaan tulokset ja oma + randomisoitu jokeririvi
			cout << "Tulos:" << endl;
			cout << "Arvottu jokeririvi: ";
			for (int l = 0; l < 7; l++) {
				cout << JokeriKone[l] << " ";
			}
			cout << endl;
			if (laske == 0 || laske == 1) {
				cout << "Ei voittoa" << endl;
			}
			else {
				cout << laske << " oikein." << endl;
			}
		}
		system("pause");
		cout << endl;
		// Tehdaan toimintoja niin kauan, kuin valinta ei ole lopeta eli "l" tai "L".
	} while (valinta != 'l' && valinta != 'L');

	return 0;
}