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
#include <forward_list>
#include "elementy.h"

using namespace std;

class Graf{
public:
	//dane grafu
	string kodyAkcji[5] = { "wczytanie","MST-K","MST-P","NSG-D","NSG-BF"};
	int liczbaKrawedzi = 0, liczbaWierzcholkow = 0, wierzcholekPoczatkowy = 0, wierzcholekKoncowy = 0;
	float inf = numeric_limits<float>::infinity();
	vector<list<elementListy>> listaSasiadow; 
	vector<vector<float>> macierzWag;
	bool ujemnaWaga;
	
	//zarzadzanie grafem
	void generujGraf(float gestosc, int wierzcholki);
	void wczytaj(string sciezka);
	void wyswietlMacierz(vector<vector<float>> macierz);
	void wyswietlListe(vector<list<elementListy>> lista);
	void usunGraf();
	void zakoncz();

	//algorytmy MST
	void kruskalaLista();
	void kruskalaMacierz();
	void primaLista();
	void primaMacierz();

	//algorytmy najkrotszej sciezki
	void dijkstryLista();
	void dijkstryMacierz();
	void bellmanaFordaLista();
	void bellmanaFordaMacierz();

private:
	//fukcje pomocnicze
	void wypiszDroge(bool ujemnyCykl,vector<elementNajkrotszejSciezki> drogi);
	void wypiszSciezke(elementNajkrotszejSciezki element);
	void wypiszMST(vector<elementMinimalnegoDrzewa> wyniki, int wagaCalkowita);
	void sortujListe(vector<list<elementListy>> &lista);
	void sortujListe(list<elementMinimalnegoDrzewa> &lista);
	bool znajdzCykl(elementNajkrotszejSciezki element, int wierzcholek);
	void zainicjujGraf();
	void dodajKrawedz(int wierzcholekA, int wierzcholekB, float waga);
};

