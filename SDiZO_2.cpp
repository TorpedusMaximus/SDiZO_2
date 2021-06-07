#include "Graf.h"
#include <iostream>
#include <random>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "Tester.h"

using namespace std;

void proceduraTestowa() {
	Graf graf;
	Tester tester;
	float gestosci[4] = { 0.25, 0.5, 0.75, 0.99 };
	int liczbaWierzcholkow[5] = { 50, 100, 175, 250, 350 };
	for (int i = 0; i < 5; i++) {
		for (int ii = 0; ii < 4; ii++) {
			for (int petla = 0; petla < 100; petla++) {
				graf.generujGraf(gestosci[ii],liczbaWierzcholkow[i]);
				tester.startPomiaru();
				graf.bellmanaFordaMacierz();//algorytm do badania
				tester.zakonczPomiar();
				graf.usunGraf();
			}
			tester.wypisz("\n");
			cout << i << " " << ii << endl;
		}
	}

	graf.zakoncz();
	tester.zakoncz();
}

void menu() {
	Graf graf;
	int wybor = 1;
	float gestosc;
	int liczbaWierzcholkow, gestoscProcenty;
	string sciezka;

	while (1) {  //menu glowne 
		system("cls");
		cout << "Menu\n1.Wczytaj Graf\n2.Generuj graf\n3.Wyswietl \n4.Wyznaczenie minimalnego drzewa rozpinajacego \n5.Wyznaczenie najkrotszej sciezki \n6.Wyczysc graf\n7.Procedura testowa\n8.Wyjdz" << endl;
		cin >> wybor;
		system("cls");

		switch (wybor) {
		case 1:
			cout << "Podaj sciezke pliku" << endl;
			cin >> sciezka;
			if (sciezka.find(".txt") == string::npos) {
				sciezka = sciezka + ".txt";
			}
			graf.wczytaj(sciezka);
			_getch();
			break;
		case 2:
			cout << "Podaj gestosc w % i liczbe wierzcholkow generowanego grafu" << endl;
			cin >> gestoscProcenty;
			cin >> liczbaWierzcholkow;
			gestosc = (1.0 * gestoscProcenty) / 100;
			graf.generujGraf(gestosc,liczbaWierzcholkow);
			_getch();
			break;
		case 3:
			if (graf.liczbaWierzcholkow == 0) {
				system("cls");
				cout << "Brak grafu" << endl;
				_getch();
				break;
			}
			while (1) {
				system("cls");
				cout << "Wyswietl\n1.Reprezentacja macierzowa \n2.Reprezentacja listowa\n3.Wroc" << endl;
				cin >> wybor;

				if (wybor == 1) {
					graf.wyswietlMacierz(graf.macierzWag);
					_getch();
					break;
				}
				if (wybor == 2) {
					graf.wyswietlListe(graf.listaSasiadow);
					_getch();
					break;
				}
				if (wybor == 3) {
					break;
				}
			}
			break;
		case 4:
			if (graf.liczbaWierzcholkow == 0) {
				system("cls");
				cout << "Brak grafu" << endl;
				_getch();
				break;
			}
			while (1) {
				system("cls");
				cout << "Wyznaczenie minimalnego drzewa rozpinajacego\n1.Algorytm Kruskala \n2.Algorytm Prima\n3.Wroc" << endl;
				cin >> wybor;

				if (wybor == 1) {
					while (1) {
						system("cls");
						cout << "Algorytm Kruskala\n1.Listowo \n2.Macierzowo\n3.Wroc" << endl;
						cin >> wybor;
						if (wybor == 1) {
							system("cls");
							graf.kruskalaLista();
							break;
						}
						if (wybor == 2) {
							system("cls");
							graf.kruskalaMacierz();
							break;
						}
						if (wybor == 3) {
							break;
						}
					}
					if (wybor != 3) {
						_getch();
						break;
					}
				}
				if (wybor == 2) {
					while (1) {
						system("cls");
						cout << "Algorytm Prima\n1.Listowo \n2.Macierzowo\n3.Wroc" << endl;
						cin >> wybor;
						if (wybor == 1) {
							system("cls");
							graf.primaLista();
							break;
						}
						if (wybor == 2) {
							system("cls");
							graf.primaMacierz();
							break;
						}
						if (wybor == 3) {
							break;
						}
					}
					if (wybor != 3) {
						_getch();
						break;
					}
				}
				if (wybor == 3) {
					break;
				}
			}
			break;
		case 5:
			if (graf.liczbaWierzcholkow == 0) {
				system("cls");
				cout << "Brak grafu" << endl;
				_getch();
				break;
			}
			while (1) {
				system("cls");
				cout << "Wyznaczenie najkrotszej sciezki\n1.Algorytm Dijkstry \n2.Algorytm Bellmana-Forda\n3.Wroc" << endl;
				cin >> wybor;

				if (wybor == 1) {
					while (1) {
						system("cls");
						cout << "Algorytm Dijkstry\n1.Listowo \n2.Macierzowo\n3.Wroc" << endl;
						cin >> wybor;
						if (wybor == 1) {
							system("cls");
							graf.dijkstryLista();
							break;
						}
						if (wybor == 2) {
							system("cls");
							graf.dijkstryMacierz();
							break;
						}
						if (wybor == 3) {
							break;
						}
					}
					if (wybor != 3) {
						_getch();
						break;
					}
				}
				if (wybor == 2) {
					while (1) {
						system("cls");
						cout << "Algorytm Bellmana-Forda\n1.Listowo \n2.Macierzowo\n3.Wroc" << endl;
						cin >> wybor;
						if (wybor == 1) {
							system("cls");
							graf.bellmanaFordaLista();
							break;
						}
						if (wybor == 2) {
							system("cls");
							graf.bellmanaFordaMacierz();
							break;
						}
						if (wybor == 3) {
							break;
						}
					}
					if (wybor != 3) {
						_getch();
						break;
					}
				}
				if (wybor == 3) {
					break;
				}
			}
			break;
		case 6:
			if (graf.liczbaWierzcholkow == 0) {
				cout << "Brak grafu" << endl;
				_getch();
				break;
			}
			cout << "Rozpoczynam czyszczenie" << endl;
			graf.usunGraf();
			cout << "Wyczyszczono strukture" << endl;
			_getch();
			break;
		case 7:
			proceduraTestowa();
			break;
		case 8:
			graf.zakoncz();
			return;
			break;
		}
	}

}

int main() {
	menu();
	//proceduraTestowa();
	return 0;
}
