#include "Graf.h"



using namespace std;

////////////////////////////////////////graf////////////////////////////////////////

void Graf::generujGraf(float gestosc, int wierzcholki) 
{
	usunGraf();
	srand(time(NULL));
	liczbaWierzcholkow = wierzcholki;//dane grafu
	liczbaKrawedzi = gestosc * ((wierzcholki * (wierzcholki - 1)) / 2);
	wierzcholekPoczatkowy = 0;
	wierzcholekKoncowy = wierzcholki - 1;
	zainicjujGraf();//incjacja struktury
	int i, wierzcholekA = 0, wierzcholekB;
	float waga;
	vector<int> zbiorWierzcholkowNierozpatrzonych;
	for (i = 1; i < liczbaWierzcholkow; i++) {//zbior zawierajacy wierzcholki bez zadnej krawedzi
		zbiorWierzcholkowNierozpatrzonych.push_back(i);
	}

	for (i = 0; i < liczbaWierzcholkow-1; i++) {//upewnienie sie ze kazdy wierzcholek nalezy do grafu
		wierzcholekB =zbiorWierzcholkowNierozpatrzonych[rand() % zbiorWierzcholkowNierozpatrzonych.size()];//losowanie wierzcholka B
		waga = (rand() % 9)+1;
		dodajKrawedz(wierzcholekA,wierzcholekB,waga);//dodanie krawedzi miedzy grafem a "wolnym" wierzcholkiem
		wierzcholekA = wierzcholekB;
		zbiorWierzcholkowNierozpatrzonych.erase(find(zbiorWierzcholkowNierozpatrzonych.begin(),zbiorWierzcholkowNierozpatrzonych.end(),wierzcholekB));//usuniecie wierzcholka przylaczonego do grafu 
	}

	for (i; i < liczbaKrawedzi; i++) {//uzupelnienie pozostalych krawedzi
		wierzcholekA = rand() % liczbaWierzcholkow;
		wierzcholekB = rand() % liczbaWierzcholkow;
		if (macierzWag[wierzcholekA][wierzcholekB] != inf || wierzcholekA == wierzcholekB || macierzWag[wierzcholekB][wierzcholekA] != inf) {//sprawdzenie czy krawedz juz nie istnieje lub czy krawedz kierune na tens am wierzcholek
			i--;
			continue;
		}
		waga = (rand() % 9) + 1;
		dodajKrawedz(wierzcholekA, wierzcholekB, waga);
	}
	sortujListe(listaSasiadow);//sortownie elementow listy sasiadow - przyda sie do pozniejszych algorytmow
}

void Graf::wczytaj(string sciezka)
{
	usunGraf();
	fstream dane;//handler pliku
	float krawedz[3];
	dane.open(sciezka, fstream::in);//wczytanie pliku
	if (!dane.is_open()) {
		cout << "Bledna sciezka pliku" << endl;
		return;
	}

	dane >> liczbaKrawedzi;//wczytanie danych opisujacych graf
	dane >> liczbaWierzcholkow;
	dane >> wierzcholekPoczatkowy;
	dane >> wierzcholekKoncowy;

	zainicjujGraf();

	for (int i = 0; i < liczbaKrawedzi; i++) {
		dane >> krawedz[0];//wczytanie danych krawedzi
		dane >> krawedz[1]; 
		dane >> krawedz[2];

		if (krawedz[2] < 0) {
			ujemnaWaga = true;
		}

		if (krawedz[0] < 0 && krawedz[0] >= liczbaWierzcholkow) {  //sprawdzenie poprawnosci danych
			cout << "Bledny wierzcholek poczatkowy (linia "<<i+1<<")." << endl;
			continue;
		}
		if (krawedz[1] < 0 && krawedz[1] >= liczbaWierzcholkow) {
			cout << "Bledny wierzcholek koncowy (linia " << i + 1 << ")." << endl;
			continue;
		}
	
		dodajKrawedz(krawedz[0],krawedz[1],krawedz[2]);
	}

	dane.close();//usuniecie handlera
	sortujListe(listaSasiadow);//sortownie elementow listy sasiadow - przyda sie do pozniejszych algorytmow
	cout << "Wczytano graf" << endl;
}

void Graf::wyswietlMacierz(vector<vector<float>> macierz)
{
	system("cls");
	if (macierz.size() == 0) {//sprawdzenie istnienia grafu
		cout << "Brak grafu";
		return;
	}

	cout << "Reprezentacja macierzowa" << endl << endl;
	for (int i = 0; i < macierz.size(); i++) {//wywietlenie wierszy
		for (int j = 0; j <(int) macierz.size(); j++) {//wyswtielenie kolumn
			cout << macierz[i][j];

			if (macierz[i][j]== inf) {
				cout << " ";
			}
			else {
				if (macierz[i][j] >=10) {
					cout << "  ";
				}
				else {
					if (macierz[i][j] >=0) {
						cout << "   ";
					}
					else {
						if (macierz[i][j] >=-9) {
							cout << "  ";
						}
						else {
							cout << " ";
						}
					}
				}
			}
		}
		cout << endl;
	}
}

void Graf::wyswietlListe(vector<list<elementListy>> lista)
{
	system("cls");
	if (liczbaWierzcholkow == 0) {//sprawdzenie istnienia grafu
		cout << "Brak grafu";
		return;
	}

	cout << "Reprezentacja listowa" << endl << endl;
	for (int i = 0; i < liczbaWierzcholkow; i++) {//wyswtielenie elemntu listy 
		cout << i << " -> ";
		for (auto& element : lista[i]) {
			cout << "[" << element.wierzcholek << "/" << element.waga << "], ";
		}
		cout << endl;
	}
}

void Graf::usunGraf()
{
	macierzWag.clear();//czyszczenie i usuwanie macierzy wag
	macierzWag.resize(0);

	listaSasiadow.clear();//czyszczenie listy wierzcho?k?w
	listaSasiadow.resize(0);

	liczbaKrawedzi=0;//czyszczenie danych grafu
	liczbaWierzcholkow=0;
	wierzcholekPoczatkowy=0;
	wierzcholekKoncowy=0;
	ujemnaWaga = false;
}

void Graf::zakoncz()
{
	usunGraf();//usuwanie grafu
	system("cls");
	cout << "Usunieto graf" << endl;
	//tester.zakoncz();//usuwanie testera
}


////////////////////////////////////////algorytmy MST////////////////////////////////////////


void Graf::kruskalaLista()
{
	list<elementMinimalnegoDrzewa> krawedzie;//zbior krawedzi
	float minimum = inf;
	int index=0;
	elementMinimalnegoDrzewa elementMST;//zmienna pomocnicza
	vector<elementMinimalnegoDrzewa> wyniki;//struktura prechowujaca wyniki
	float wagaCalkowita = 0;
	vector<vector<int>>zbiorWierzcholkowRozpatrzonych;//ZWR
	zbiorWierzcholkowRozpatrzonych.resize(liczbaWierzcholkow);

	for (int i = 0; i < liczbaWierzcholkow; i++) {//pobranie krawedzi z listy sasiedztwa
		for (auto& element : listaSasiadow[i]) {
			elementMST.wierzcholekA = i;
			elementMST.wierzcholekB = element.wierzcholek;
			elementMST.waga = element.waga;
			krawedzie.push_back(elementMST);
		}
	}
	for (int i = 0; i < liczbaWierzcholkow; i++) {//generownie podrzew z pojedynczych wierzcholkow
		zbiorWierzcholkowRozpatrzonych[i].push_back(i);
	}
	
	sortujListe(krawedzie);//sortowanie krawedzi
	//wyswietlListe(listaSasiadow);
	vector<int>::iterator flagaA, flagaB;
	int indexA, indexB;  

	while ( wyniki.size() < liczbaWierzcholkow-1 ) {
		elementMST = krawedzie.front();//pobranie krawedzi z listy 
		krawedzie.pop_front();
		
		for (int i = 0; i < zbiorWierzcholkowRozpatrzonych.size(); i++) {//wyszukanie poddrzewa z poszukiwanych wierzcholkiem
			flagaA =find(zbiorWierzcholkowRozpatrzonych[i].begin(), zbiorWierzcholkowRozpatrzonych[i].end(), elementMST.wierzcholekA);
			if (flagaA!= zbiorWierzcholkowRozpatrzonych[i].end()) {
				indexA = i;
				break;
			}
		}
		for (int i = 0; i < zbiorWierzcholkowRozpatrzonych.size(); i++) {//wyszukanie poddrzewa z poszukiwanych wierzcholkiem
			flagaB=find(zbiorWierzcholkowRozpatrzonych[i].begin(), zbiorWierzcholkowRozpatrzonych[i].end(), elementMST.wierzcholekB);
			if (flagaB != zbiorWierzcholkowRozpatrzonych[i].end()){
				indexB = i;
				break;
			}
		}
		if (indexA != indexB) {//sprawdzenie czy oba wierzcholki juz znajduja sie w jednym podrzewie
			wyniki.push_back(elementMST);//dodanie krwaedzi do poddrzewa
			for (int i = 0; i < zbiorWierzcholkowRozpatrzonych[indexB].size();i++) {//polaczenie poddrzew
				zbiorWierzcholkowRozpatrzonych[indexA].push_back(zbiorWierzcholkowRozpatrzonych[indexB][i]);
			}
			zbiorWierzcholkowRozpatrzonych.erase(zbiorWierzcholkowRozpatrzonych.begin()+indexB);
			wagaCalkowita += elementMST.waga;//zwiekszenie calkowitem wagi
		}
	}
	//wypiszMST(wyniki, wagaCalkowita);
}

void Graf::kruskalaMacierz()
{
	list<elementMinimalnegoDrzewa> krawedzie;//zbior krawedzi
	float minimum = inf;
	int index = 0;
	elementMinimalnegoDrzewa elementMST;//zmienna pomocnicza
	vector<elementMinimalnegoDrzewa> wyniki;//struktura prechowujaca wyniki
	float wagaCalkowita = 0;
	vector<vector<int>>zbiorWierzcholkowRozpatrzonych;//ZWR
	zbiorWierzcholkowRozpatrzonych.resize(liczbaWierzcholkow);

	for (int i = 0; i < liczbaWierzcholkow; i++) {//pobranie krawedzi z listy sasiedztwa
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			if (macierzWag[i][j] != inf) {
				elementMST.wierzcholekA = i;
				elementMST.wierzcholekB = j;
				elementMST.waga = macierzWag[i][j];
				krawedzie.push_back(elementMST);
			}
		}
	}
	for (int i = 0; i < liczbaWierzcholkow; i++) {//generownie podrzew z pojedynczych wierzcholkow
		zbiorWierzcholkowRozpatrzonych[i].push_back(i);
	}

	sortujListe(krawedzie);//sortowanie krawedzi
	//wyswietlMacierz(macierzWag);
	vector<int>::iterator flagaA, flagaB;
	int indexA, indexB;

	while (wyniki.size() < liczbaWierzcholkow - 1) {
		elementMST = krawedzie.front();//pobranie krawedzi z listy 
		krawedzie.pop_front();

		for (int i = 0; i < zbiorWierzcholkowRozpatrzonych.size(); i++) {//wyszukanie poddrzewa z poszukiwanych wierzcholkiem
			flagaA = find(zbiorWierzcholkowRozpatrzonych[i].begin(), zbiorWierzcholkowRozpatrzonych[i].end(), elementMST.wierzcholekA);
			if (flagaA != zbiorWierzcholkowRozpatrzonych[i].end()) {
				indexA = i;
				break;
			}
		}
		for (int i = 0; i < zbiorWierzcholkowRozpatrzonych.size(); i++) {//wyszukanie poddrzewa z poszukiwanych wierzcholkiem
			flagaB = find(zbiorWierzcholkowRozpatrzonych[i].begin(), zbiorWierzcholkowRozpatrzonych[i].end(), elementMST.wierzcholekB);
			if (flagaB != zbiorWierzcholkowRozpatrzonych[i].end()) {
				indexB = i;
				break;
			}
		}
		if (indexA != indexB) {//sprawdzenie czy oba wierzcholki juz znajduja sie w jednym podrzewie
			wyniki.push_back(elementMST);//dodanie krwaedzi do poddrzewa
			for (int i = 0; i < zbiorWierzcholkowRozpatrzonych[indexB].size(); i++) {//polaczenie poddrzew
				zbiorWierzcholkowRozpatrzonych[indexA].push_back(zbiorWierzcholkowRozpatrzonych[indexB][i]);
			}
			zbiorWierzcholkowRozpatrzonych.erase(zbiorWierzcholkowRozpatrzonych.begin() + indexB);
			wagaCalkowita += elementMST.waga;//zwiekszenie calkowitem wagi
		}
	}
	//wypiszMST(wyniki, wagaCalkowita);
}

void Graf::primaLista()
{
	vector<list<elementListy>> listaPrima;  //graf nieskierowany 
	listaPrima.resize(liczbaWierzcholkow);
	elementListy temp;
	for (int i = 0; i < liczbaWierzcholkow; i++) {//zamiana zapisanego grafu skierowanego na nieskierowany
		for (auto& element : listaSasiadow[i]) {
			listaPrima[i].push_back(element);
			temp.wierzcholek = i;
			temp.waga = element.waga;
			listaPrima[element.wierzcholek].push_back(temp);
		}
	}
	sortujListe(listaPrima);//sortowanie 

	vector<elementMinimalnegoDrzewa> wyniki;//struktura prechowujaca wyniki
	wyniki.resize(liczbaWierzcholkow - 1);
	vector<int> zbiorWierzcholkowRozpatrzonych;//struktura ZWR
	zbiorWierzcholkowRozpatrzonych.push_back(wierzcholekPoczatkowy);//dodanie poczatkowego wierzcholka do ZWR
	int poprzedniWierzcholek = wierzcholekPoczatkowy;
	int nastepnyWierzcholek;
	float wagaCalkowita = 0;
	float minimum;
	

	for (int i = 0; i < liczbaWierzcholkow - 1; i++) {
		minimum = inf;
		for (int j = 0; j <i+1; j++) {
			for (auto& element : listaPrima[zbiorWierzcholkowRozpatrzonych[j]]) {
				bool rozpatrzone = find(zbiorWierzcholkowRozpatrzonych.begin(), zbiorWierzcholkowRozpatrzonych.end(), element.wierzcholek) != zbiorWierzcholkowRozpatrzonych.end();//sprawdzenie stanu wierzcholka
				if (!rozpatrzone) {//sprawdzamy wage krawedzi z wierzcholkiem z poza ZWR
					if (element.waga < minimum) {//porownanie z aktualnym minimum
						poprzedniWierzcholek = zbiorWierzcholkowRozpatrzonych[j];
						minimum = element.waga;
						nastepnyWierzcholek = element.wierzcholek;
					}
					break;//lista jest posortowana, wiec nie tzreba dalej sprawdzac
				}
			}
		}
		zbiorWierzcholkowRozpatrzonych.push_back(nastepnyWierzcholek);//dodwanie wierzcholka do ZWR
		wagaCalkowita += minimum;//zwieksznie wagi calkowitej

		wyniki[i].wierzcholekA = poprzedniWierzcholek;//zapisanie wyniku
		wyniki[i].wierzcholekB = nastepnyWierzcholek;
		wyniki[i].waga = minimum;
	}
	//wyswietlListe(listaPrima);
	//wypiszMST(wyniki, wagaCalkowita);
}

void Graf::primaMacierz()
{
	vector<vector<float>> macierzPrima;//graf nieskierowany
	macierzPrima.resize(liczbaWierzcholkow, vector<float>(liczbaWierzcholkow, inf));
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		for (int j = 0; j < liczbaWierzcholkow; j++) {//zamiana grafuy skierowanego na nieksierowany
			if (macierzWag[i][j] != numeric_limits<float>::infinity()) {
				macierzPrima[i][j] = macierzWag[i][j];
				macierzPrima[j][i] = macierzWag[i][j];
			}
		}
	}
	//wyswietlMacierz(macierzPrima);

	vector<elementMinimalnegoDrzewa> wyniki;//struktura prechowujaca wyniki
	wyniki.resize(liczbaWierzcholkow - 1);
	vector<int> zbiorWierzcholkowRozpatrzonych;//struktura ZWR
	zbiorWierzcholkowRozpatrzonych.push_back(wierzcholekPoczatkowy);//dodanie poczatkowego wierzcholka do ZWR
	int poprzedniWierzcholek = wierzcholekPoczatkowy;
	int nastepnyWierzcholek;
	float wagaCalkowita = 0;
	float minimum;

	for (int i = 0; i < liczbaWierzcholkow - 1; i++) {
		minimum = inf;
		for (int j = 0; j < i+1; j++) {
			for (int k = 0; k < liczbaWierzcholkow; k++) {
				if (macierzPrima[zbiorWierzcholkowRozpatrzonych[j]][k] != inf) {
					bool rozpatrzone = find(zbiorWierzcholkowRozpatrzonych.begin(),zbiorWierzcholkowRozpatrzonych.end(), k) != zbiorWierzcholkowRozpatrzonych.end();
					if (!rozpatrzone) {
						if (macierzPrima[zbiorWierzcholkowRozpatrzonych[j]][k] < minimum) {
							poprzedniWierzcholek = zbiorWierzcholkowRozpatrzonych[j];
							minimum = macierzPrima[zbiorWierzcholkowRozpatrzonych[j]][k];
							nastepnyWierzcholek = k;
						}
					}
				}
			}
		}
		zbiorWierzcholkowRozpatrzonych.push_back(nastepnyWierzcholek);
		wagaCalkowita += minimum;

		wyniki[i].wierzcholekA = poprzedniWierzcholek;//zapisanie wyniku
		wyniki[i].wierzcholekB = nastepnyWierzcholek;
		wyniki[i].waga = minimum;
	}
	//wyswietlMacierz(macierzPrima);
	//wypiszMST(wyniki, wagaCalkowita);
}


////////////////////////////////////////algorytmy najkrotszej sciezki////////////////////////////////////////


void Graf::dijkstryLista()
{
	if (ujemnaWaga) {//sprawdzenie czy mozna preprowadzic algorytm
		cout << "W grafie znajduja sie ujemne wagi" << endl;
		return;
	}

	vector<elementNajkrotszejSciezki> droga;//drogi do wierzcholkow
	droga.resize(liczbaWierzcholkow);
	vector<int> zbiorWierzcholkowRozpatrzonych;//ZWR
	float minimum;
	int index;

	droga[0].wagaDrogi = 0;//waga wierzcholka poczatkowego 

	while (zbiorWierzcholkowRozpatrzonych.size() < liczbaWierzcholkow) {
		minimum = inf;
		for (int i = 0; i < droga.size(); i++) {//wybrnaie wierzcholka o minimalnej wadze
			if (find(zbiorWierzcholkowRozpatrzonych.begin(), zbiorWierzcholkowRozpatrzonych.end(), i) != zbiorWierzcholkowRozpatrzonych.end()) {
				//sprawedzenie czy wierzcholek juz byl sprawdzany
				continue;
			}
			if (droga[i].wagaDrogi < minimum) {//wybranie najlepszej drogi 
				minimum = droga[i].wagaDrogi;
				index = i;
			}
		}
		zbiorWierzcholkowRozpatrzonych.push_back(index);

		for (auto& element : listaSasiadow[index]) {//relaksacja
			if (droga[index].wagaDrogi + element.waga < droga[element.wierzcholek].wagaDrogi) {
				droga[element.wierzcholek].poprzedniWierzcholek = index;
				droga[element.wierzcholek].wagaDrogi = droga[index].wagaDrogi + element.waga;
				droga[element.wierzcholek].poprzedniElement = &droga[index];
			}
		}
	}
	//wyswietlListe(listaSasiadow);//wywietlenie wynikow
	//wypiszDroge(false, droga);
}

void Graf::dijkstryMacierz()
{
	if (ujemnaWaga) {//sprawdzenie czy mozna preprowadzic algorytm
		cout << "W grafie znajduja sie ujemne wagi" << endl;
		return;
	}

	vector<elementNajkrotszejSciezki> droga;//drogi do wierzcholkow
	droga.resize(liczbaWierzcholkow);
	vector<int> zbiorWierzcholkowRozpatrzonych;//ZWR
	float minimum;
	int index;

	droga[0].wagaDrogi = 0;//waga wierzcholka poczatkowego 

	while (zbiorWierzcholkowRozpatrzonych.size() < liczbaWierzcholkow) {
		minimum = inf;
		for (int i = 0; i < droga.size(); i++) {//wybrnaie wierzcholka o minimalnej wadze
			if (find(zbiorWierzcholkowRozpatrzonych.begin(), zbiorWierzcholkowRozpatrzonych.end(), i) != zbiorWierzcholkowRozpatrzonych.end()) {
				//sprawedzenie czy wierzcholek juz byl sprawdzany
				continue;
			}
			if (droga[i].wagaDrogi < minimum) {//wybranie najlepszej drogi 
				minimum = droga[i].wagaDrogi;
				index = i;
			}
		}
		zbiorWierzcholkowRozpatrzonych.push_back(index);

		for (int i = 0; i < liczbaWierzcholkow; i++) {
			if (macierzWag[index][i] != inf) {
				if (droga[index].wagaDrogi + macierzWag[index][i] < droga[i].wagaDrogi) {
					droga[i].poprzedniWierzcholek = index;
					droga[i].wagaDrogi = droga[index].wagaDrogi + macierzWag[index][i];
					droga[i].poprzedniElement = &droga[index];
				}
			}
		}
	}
	//wyswietlMacierz(macierzWag);//wywietlenie wynikow
	//wypiszDroge(false, droga);
}

void Graf::bellmanaFordaLista()
{
	bool ujemnyCykl=false;
	vector<elementNajkrotszejSciezki> droga;//drogi do wierzcholkow
	droga.resize(liczbaWierzcholkow);
	vector<int> zbiorWierzcholkowRozpatrzonych;//ZWR
	float minimum;
	int index;
	bool relaksacja;

	droga[0].wagaDrogi = 0;//waga wierzcholka poczatkowego 

	for (int j = 0; j < liczbaKrawedzi - 1; j++) {
		relaksacja = false;
		for (int i = 0; i < liczbaWierzcholkow ; i++) {
			for (auto& element : listaSasiadow[i]) {
				if (droga[i].wagaDrogi + element.waga < droga[element.wierzcholek].wagaDrogi) {
					droga[element.wierzcholek].wagaDrogi = droga[i].wagaDrogi + element.waga;//relaksacja
					droga[element.wierzcholek].poprzedniWierzcholek = i;
					droga[element.wierzcholek].poprzedniElement = &droga[i];
					relaksacja = true;
				}
			}
			if (!ujemnyCykl) {
				ujemnyCykl = znajdzCykl(droga[i], i);//sprawdzenie ujemnego cykl
			}
		}
		if (!relaksacja) {
			//break;
		}
	}
	//wyswietlListe(listaSasiadow);//wywietlenie wynikow
	//wypiszDroge(ujemnyCykl, droga);
}

void Graf::bellmanaFordaMacierz()
{
	bool ujemnyCykl = false;
	vector<elementNajkrotszejSciezki> droga;//drogi do wierzcholkow
	droga.resize(liczbaWierzcholkow);
	vector<int> zbiorWierzcholkowRozpatrzonych;//ZWR
	float minimum;
	int index;
	bool relaksacja;

	droga[0].wagaDrogi = 0;//waga wierzcholka poczatkowego 

	for (int glowny = 0; glowny < liczbaKrawedzi - 1; glowny++) {
		relaksacja = false;
		for (int index = 0; index < liczbaWierzcholkow; index++) {
			for (int i = 0; i < liczbaWierzcholkow; i++) {
				if (macierzWag[index][i] != inf) {
					if (droga[index].wagaDrogi + macierzWag[index][i] < droga[i].wagaDrogi) {
						droga[i].poprzedniWierzcholek = index;
						droga[i].wagaDrogi = droga[index].wagaDrogi + macierzWag[index][i];
						droga[i].poprzedniElement = &droga[index];
						relaksacja = true;
					}
				}
			}
			if (!ujemnyCykl) {
				ujemnyCykl = znajdzCykl(droga[index], index);//sprawdzenie ujemnego cykl
			}
		}
		if (!relaksacja) {
			//break;
		}
	}
	//wyswietlMacierz(macierzWag);//wywietlenie wynikow
	//wypiszDroge(ujemnyCykl, droga);
}


////////////////////////////////////////pomocnicze////////////////////////////////////////


void Graf::wypiszDroge(bool ujemnyCykl, vector<elementNajkrotszejSciezki> droga) {
	if (ujemnyCykl) {//sprawdzenie istnienia ujemnego cyklu
		cout << endl << endl << "Cykl ujemny" << endl;
	}
	else {
		cout << endl << endl;
	}
	cout  << "Koniec : Wartosc drogi : Droga" << endl << endl;
	elementNajkrotszejSciezki element;
	cout << "0 : 0 : 0" << endl;
	for (int a = 1; a < (int)droga.size(); a++) {//wyswietlenie wag i drog 
		cout << a << " : " << droga[a].wagaDrogi << " : ";
		if (!ujemnyCykl) {
			element = droga[a];
		wypiszSciezke(element);
		cout << a;
		}
		cout << endl;
	}
	cout << endl;
}

void Graf::wypiszSciezke(elementNajkrotszejSciezki element)
{
	if (element.poprzedniWierzcholek == -1) {

	}
	else {
		wypiszSciezke(*element.poprzedniElement);
		cout << element.poprzedniWierzcholek << " -> ";
	}
}

void Graf::wypiszMST(vector<elementMinimalnegoDrzewa> wyniki, int wagaCalkowita)
{
	cout <<endl<<endl<<"Wierzcholki : Waga" <<endl<< endl;
	for (int i = 0; i < wyniki.size(); i++) {
		cout << wyniki[i].wierzcholekA << " -> " << wyniki[i].wierzcholekB << " : " << wyniki[i].waga << endl;
	}
	cout << "MST = " << wagaCalkowita << endl;
}

void Graf::sortujListe(vector<list<elementListy>> &lista)
{
	for (int i = 0; i < lista.size(); i++) {
		lista[i].sort([](const elementListy& a, const elementListy& b) {
			return a.waga < b.waga;
			});
	}
}

void Graf::sortujListe(list<elementMinimalnegoDrzewa> &lista)
{
	lista.sort([](const elementMinimalnegoDrzewa& a, const elementMinimalnegoDrzewa& b) {
		return a.waga < b.waga;
		});
}

bool Graf::znajdzCykl(elementNajkrotszejSciezki element, int wierzcholek)
{
	if (element.poprzedniWierzcholek == -1) {
		return false;
	}
	else {
		if (element.poprzedniWierzcholek==wierzcholek) {
			return true;
		}
		return znajdzCykl(*element.poprzedniElement,wierzcholek);
	}
}

void Graf::zainicjujGraf()
{
	macierzWag.resize(liczbaWierzcholkow, vector<float>(liczbaWierzcholkow, inf));//przygotownaie struktury na dane
	listaSasiadow.resize(liczbaWierzcholkow);
}

void Graf::dodajKrawedz(int wierzcholekA, int wierzcholekB, float waga)
{
	elementListy temp;
	macierzWag[wierzcholekA][wierzcholekB] = waga;//dodanie do macierzy 

	temp.waga = waga;  //krawedz sasiedztwa
	temp.wierzcholek = wierzcholekB;
	listaSasiadow[wierzcholekA].push_back(temp);//dodanie krawedzi do wierzcholka 
}
