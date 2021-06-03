﻿#include "Graf.h"
#include <iostream>
#include <random>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

int main() {
	Graf graf;
	int wybor = 1;
	string sciezka;

	while (1) {  //menu glowne 
		system("cls");
		cout << "1.Wczytaj Graf \n2.Wyswietl \n3.Wyznaczenie minimalnego drzewa rozpinajacego \n4.Wyznaczenie najkrotszej sciezki \n5.Wyczysc graf \n6.Wyjdz" << endl;
		cin >> wybor;
		system("cls");

		switch (wybor) {
		case 1:
			cout << "Podaj sciezke pliku"<< endl;
			//cin >> sciezka;
			graf.wczytaj(sciezka);
			_getch();
			break;
		case 2:
			if (graf.liczbaWierzcholkow == 0) {
				system("cls");
				cout << "Brak grafu" << endl;
				_getch();
				break;
			}
			while(1) {
				system("cls");
				cout << "1.Reprezentacja macierzowa \n2.Reprezentacja listowa" << endl;
				cin >> wybor;

				if (wybor == 1) {
					graf.wyswietlMacierz();
					_getch();
					break;
				}
				if (wybor == 2) {
					graf.wyswietlListe();
					_getch();
					break;
				}	
			}
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
				cout << "1.Algorytm Kruskala \n2.Algorytm Prima" << endl;
				cin >> wybor;

				if (wybor == 1) {
					while (1) {
						system("cls");
						cout << "1.Listowo \n2.Macierzowo" << endl;
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
					}
					_getch();
					break;
				}
				if (wybor == 2) {
					while (1) {
						system("cls");
						cout << "1.Listowo \n2.Macierzowo" << endl;
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
					}
					_getch();
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
				cout << "1.Algorytm Dijkstry \n2.Algorytm Bellmana-Forda" << endl;
				cin >> wybor;

				if (wybor == 1) {
					while (1) {
						system("cls");
						cout << "1.Listowo \n2.Macierzowo" << endl;
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
					}
					_getch();
					break;
				}
				if (wybor == 2) {
					while (1) {
					system("cls");
					cout << "1.Listowo \n2.Macierzowo" << endl;
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
					}
					_getch();
					break;
				}
			}
			break;
		case 5:
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
		case 6:
			graf.zakoncz();
			return 0;
			break;
		}
	}

	return 0;
}
