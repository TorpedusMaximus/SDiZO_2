
#include <iostream>
#include <random>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <fstream>

using namespace std;

long long int read_QPC() { // wartosc licznika czasu 
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}


int main() {
	long long int  frequency; //zmienne do przechowywania czasu i generacji losowych liczb
	random_device rd;
	mt19937 gen(rd());
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	int wybor = 1;
	string sciezka;

	while (1) {  //menu glowne 
		system("cls");
		cout << "\n1.Wczytaj Graf \n2.Wyswietl \n3.Wyznaczenie minimalnego drzewa rozpinajacego \n4.Wyznaczenie najkrotszej sciezki \n5.Wyczysc graf \n6.Wyjdz" << endl;
		cin >> wybor;
		system("cls");

		switch (wybor) {
		case 1:
			cout << "Podaj sciezke pliku"<< endl;
			cin >> sciezka;
			//wyczysc graf 
			//wczytaj
			_getch();
			break;
		case 2:
			while(1) {
				system("cls");
				cout << "\n1.Reprezentacja macierzowa \n2.Reprezentacja listowa" << endl;
				cin >> wybor;

				if (wybor == 1) {
					//wyswietl macierzowo
					_getch();
					break;
				}
				if (wybor == 2) {
					//wyswietl listowo
					_getch();
					break;
				}	
			}
			break;
		case 3:
			while (1) {
				system("cls");
				cout << "\n1.Algorytm Kruskala \n2.Algorytm Prima" << endl;
				cin >> wybor;

				if (wybor == 1) {
					//Kruskal
					_getch();
					break;
				}
				if (wybor == 2) {
					//Prim
					_getch();
					break;
				}
			}
			break;
		case 4:
			while (1) {
				system("cls");
				cout << "\n1.Algorytm Dijkstry \n2.Algorytm Bellmana-Forda" << endl;
				cin >> wybor;

				if (wybor == 1) {
					//Dijkstra
					_getch();
					break;
				}
				if (wybor == 2) {
					//BF
					_getch();
					break;
				}
			}
			break;
		case 5:
			cout << "Rozpoczynam czyszczenie" << endl;
			//wyczysc graf
			cout << "Wyczyszczono strukture" << endl;
			_getch();
			break;
		case 6:
			//wyczysc graf
			return 0;
			break;
		}
	}

	return 0;
}
