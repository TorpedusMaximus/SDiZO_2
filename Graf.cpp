#include "Graf.h"

using namespace std;

void Graf::wczytaj(string sciezka)
{
	tester.startPomiaru();
	usunGraf();
	fstream dane;
	float krawedz[3];
	elementListy temp;
	sciezka = "test.txt";
	dane.open(sciezka, fstream::in);
	if (!dane.is_open()) {
		cout << "Bledna sciezka pliku" << endl;
		return;
	}

	dane >> liczbaKrawedzi;
	dane >> liczbaWierzcholkow;
	dane >> wierzcholekPoczatkowy;
	dane >> wierzcholekKoncowy;

	macierzWag.resize(liczbaWierzcholkow);
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		macierzWag[i].resize(liczbaWierzcholkow, inf);
	}
	listaSasiadow.resize(liczbaWierzcholkow);

	for (int i = 0; i < liczbaKrawedzi; i++) {
		dane >> krawedz[0];
		dane >> krawedz[1]; 
		dane >> krawedz[2];

		if (krawedz[0] < 0 && krawedz[0] >= liczbaWierzcholkow) {  //sprawdzenie poprawnosci danych
			cout << "Bledny wierzcholek poczatkowy (linia "<<i+1<<")." << endl;
			continue;
		}
		if (krawedz[1] < 0 && krawedz[1] >= liczbaWierzcholkow) {
			cout << "Bledny wierzcholek koncowy (linia " << i + 1 << ")." << endl;
			continue;
		}
		
		macierzWag[(int)krawedz[0]][(int)krawedz[1]] = krawedz[2];//dodanie do macierzy 

	temp.wierzcholek = (int)krawedz[1];  //krawedz sasiedztwa
	temp.waga = krawedz[2];
	listaSasiadow[(int)krawedz[0]].push_back(temp);//dodanie krawedzi do wierzcholka 
     	
	}
	dane.close();
	cout << "Wczytano graf" << endl;
	tester.koniecPomiaru();
	tester.zapisWyniku(kodyAkcji[0]);
}

void Graf::wyswietlMacierz()
{
	system("cls");
	if (liczbaWierzcholkow == 0) {
		cout << "Brak grafu";
		return;
	}

	cout << "Reprezentacja macierzowa" << endl << endl;
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			cout << macierzWag[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Graf::wyswietlListe()
{
	system("cls");
	if (liczbaWierzcholkow == 0) {
		cout << "Brak grafu";
		return;
	}

	cout << "Reprezentacja listowa" << endl << endl;
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		cout << i << " -> ";
		for (auto& element : listaSasiadow[i]) {
			cout << "[" << element.wierzcholek << "/" << element.waga << "], ";
		}
		cout << endl;
	}
}

void Graf::usunGraf()
{
	macierzWag.clear();//czyszczenie i usuwanie macierzy wag
	macierzWag.resize(0);

	for (int i = 0; i < (int)listaSasiadow.size(); i++) { //czyszczenie listy krawêdzi przy wierzcho³ku i
		listaSasiadow[i].clear();
		listaSasiadow[i].resize(0);
	}

	listaSasiadow.clear();//czyszczenie listy wierzcho³ków
	listaSasiadow.resize(0);

	liczbaKrawedzi=0;//czyszczenie danych grafu
	liczbaWierzcholkow=0;
	wierzcholekPoczatkowy=0;
	wierzcholekKoncowy=0;

}

void Graf::zakoncz()
{
	usunGraf();
	system("cls");
	cout << "Usunieto graf" << endl;
	tester.zakoncz();
}


////////////////////////////////////////algorytmy////////////////////////////////////////

void Graf::dijkstryLista()
{
}

void Graf::dijkstryMacierz()
{
}

void Graf::kruskalaLista()
{
}

void Graf::kruskalaMacierz()
{
}

void Graf::primaLista()
{
}

void Graf::primaMacierz()
{
}

void Graf::bellmanaFordaLista()
{
}

void Graf::bellmanaFordaMacierz()
{
}
