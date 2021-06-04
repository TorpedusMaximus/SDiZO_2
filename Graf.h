#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include <deque>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tester.h"
#include "elementy.h"

using namespace std;

class Graf{
public:
	//dane grafu
	Tester tester;
	string kodyAkcji[5] = { "wczytanie","MST-K","MST-P","NSG-D","NSG-BF"};
	int liczbaKrawedzi = 0, liczbaWierzcholkow = 0, wierzcholekPoczatkowy = 0, wierzcholekKoncowy = 0;
	float inf = numeric_limits<float>::infinity();
	vector<list<elementListy>> listaSasiadow; 
	vector<vector<float>> macierzWag;
	
	//zarzadzanie grafem
	void wczytaj(string sciezka);
	void wyswietlMacierz(vector<vector<float>> macierz);
	void wyswietlListe(vector<list<elementListy>> lista);
	void usunGraf();
	void zakoncz();

	//algorytmy
	void dijkstryLista();
	void dijkstryMacierz();
	void kruskalaLista();
	void kruskalaMacierz();
	void primaLista();
	void primaMacierz();
	void bellmanaFordaLista();
	void bellmanaFordaMacierz();

private:
	void wypiszDroge(bool ujemnyCykl,vector<elementNajkrotszejSciezki> drogi);
	void wypiszMST(vector<elementMinimalnegoDrzewa> wyniki, int wagaCalkowita);
	void sortujListe(vector<list<elementListy>> &lista);
	void sortujListe(list<elementMinimalnegoDrzewa> &lista);
};

