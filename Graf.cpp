#include "Graf.h"


using namespace std;

void Graf::wczytaj(string sciezka)
{
	usunGraf();
	tester.startPomiaru();
	fstream dane;//handler pliku
	float krawedz[3];
	elementListy temp;
	sciezka = "test.txt";///////////////////////////////////usunac potem
	dane.open(sciezka, fstream::in);//wczytanie pliku
	if (!dane.is_open()) {
		cout << "Bledna sciezka pliku" << endl;
		return;
	}

	dane >> liczbaKrawedzi;//wczytanie danych opisujacych graf
	dane >> liczbaWierzcholkow;
	dane >> wierzcholekPoczatkowy;
	dane >> wierzcholekKoncowy;

	macierzWag.resize(liczbaWierzcholkow, vector<float>(liczbaWierzcholkow, inf));//przygotownaie struktury na dane
	listaSasiadow.resize(liczbaWierzcholkow);

	for (int i = 0; i < liczbaKrawedzi; i++) {
		dane >> krawedz[0];//wczytanie danych krawedzi
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

	dane.close();//usuniecie handlera
	sortujListe(listaSasiadow);
	tester.zakonczPomiar(kodyAkcji[0]);
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
	cout << endl;
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
	usunGraf();//usuwanie grafu
	system("cls");
	cout << "Usunieto graf" << endl;
	tester.zakoncz();//usuwanie testera
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
	vector<list<elementListy>> listaKruskala=listaSasiadow;
	sortujListe(listaKruskala);
	list<elementMinimalnegoDrzewa> krawedzie;
	float minimum = inf;
	int index=0;
	elementMinimalnegoDrzewa element;
	vector<elementMinimalnegoDrzewa> wyniki;//struktura prechowujaca wyniki
	float wagaCalkowita = 0;
	vector<vector<int>>zbiorWierzcholkowRozpatrzonych;
	zbiorWierzcholkowRozpatrzonych.resize(liczbaWierzcholkow);

	for (int i = 0; i < liczbaKrawedzi; i++) {
		minimum = inf;
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			if (listaKruskala[j].size() > 0) {
				if (listaKruskala[j].front().waga < minimum) {
					minimum = listaKruskala[j].front().waga;
					index = j;
				}
			}
		}
		element.waga = minimum;
		element.wierzcholekA = index;
		element.wierzcholekB = listaKruskala[index].front().wierzcholek;
		krawedzie.push_back(element);
		listaKruskala[index].pop_front();
	}
	listaKruskala.clear();
	listaKruskala.resize(0);

	for (int i = 0; i < liczbaWierzcholkow; i++) {
		zbiorWierzcholkowRozpatrzonych[i].push_back(i);
	}

	wyswietlListe(listaSasiadow);

	vector<int>::iterator flagaA, flagaB;
	int indexA, indexB;   //////////////////naprawic
	while (krawedzie.size()) {
		element = krawedzie.front();
		krawedzie.pop_front();
		
		
		for (int i = 0; i < zbiorWierzcholkowRozpatrzonych.size(); i++) {
			flagaA =find(zbiorWierzcholkowRozpatrzonych[i].begin(), zbiorWierzcholkowRozpatrzonych[i].end(), element.wierzcholekA);
			if (flagaA!= zbiorWierzcholkowRozpatrzonych[i].end()) {
				indexA = i;
				break;
			}
		}
		for (int i = 0; i < zbiorWierzcholkowRozpatrzonych.size(); i++) {
			flagaB=find(zbiorWierzcholkowRozpatrzonych[i].begin(), zbiorWierzcholkowRozpatrzonych[i].end(), element.wierzcholekB);
			if (flagaB != zbiorWierzcholkowRozpatrzonych[i].end()){
				indexB = i;
				break;
			}
		}
		if (indexA != indexB) {
			wyniki.push_back(element);
			zbiorWierzcholkowRozpatrzonych[indexA].assign(zbiorWierzcholkowRozpatrzonych[indexB].begin(), zbiorWierzcholkowRozpatrzonych[indexB].end());
			zbiorWierzcholkowRozpatrzonych.erase(zbiorWierzcholkowRozpatrzonych.begin()+indexB);
			wagaCalkowita += element.waga;
		}

	}
	
	wypiszPrima(wyniki, wagaCalkowita);
	
	wyniki.clear();
	wyniki.resize(0);
	zbiorWierzcholkowRozpatrzonych.clear();
	zbiorWierzcholkowRozpatrzonych.resize(0);
	krawedzie.clear();
	krawedzie.resize(0);

}

void Graf::kruskalaMacierz()
{
	
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
	wyswietlListe(listaPrima);
	wypiszPrima(wyniki, wagaCalkowita);
	
	zbiorWierzcholkowRozpatrzonych.clear();//czyszczenie 
	wyniki.clear();
	listaPrima.clear();
	zbiorWierzcholkowRozpatrzonych.resize(0);
	wyniki.resize(0);
	listaPrima.resize(0);
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
	wyswietlMacierz(macierzPrima);

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
	wyswietlMacierz(macierzPrima);
	wypiszPrima(wyniki, wagaCalkowita);

	zbiorWierzcholkowRozpatrzonych.clear();//czyszczenie 
	wyniki.clear();
	macierzPrima.clear();
	zbiorWierzcholkowRozpatrzonych.resize(0);
	wyniki.resize(0);
	macierzPrima.resize(0);
}

void Graf::bellmanaFordaLista()
{
	bool ujemnyCykl = false;//sprawdzenie istnienia ujemnego cyklu
	deque<int> kolejkaWierzcholkow;//kolejka wierzcholkow do sprawdzenia
	vector<elementNajkrotszejSciezki> droga(liczbaWierzcholkow);//droga do wierzcholka
	vector<int> historiaKolejki;

	droga[wierzcholekPoczatkowy].sciezka.push_back(wierzcholekPoczatkowy);//ustalenie drogi do wierzcholka startowego
	droga[wierzcholekPoczatkowy].wagaDrogi = 0;
	kolejkaWierzcholkow.push_back(wierzcholekPoczatkowy);

	while (kolejkaWierzcholkow.size() > 0 && !ujemnyCykl) {  //petla sprawdza wsystkie wierzcholki lub konczy w momenci wykrycia ujemnego cyklu 
		int badanyElement = kolejkaWierzcholkow.front();//pobranie wierzcholka do badania
		kolejkaWierzcholkow.pop_front();
		historiaKolejki.push_back(badanyElement);

		for (auto& element : listaSasiadow[badanyElement]) {
			if (droga[badanyElement].wagaDrogi + element.waga < droga[element.wierzcholek].wagaDrogi) {//zmiana drogi w zaleznosci od wagi 
				ujemnyCykl = (find(droga[badanyElement].sciezka.begin(), droga[badanyElement].sciezka.end(), element.wierzcholek) != droga[badanyElement].sciezka.end());//sprawdzenie ujemnego cyklu
				if (ujemnyCykl) {
					break;  
				}

				droga[element.wierzcholek].sciezka = droga[badanyElement].sciezka;//zamiana sciezki na korzystniejsza
				droga[element.wierzcholek].sciezka.push_back(element.wierzcholek);
				droga[element.wierzcholek].wagaDrogi = droga[badanyElement].wagaDrogi + element.waga;

				if (kolejkaWierzcholkow.empty() || find(kolejkaWierzcholkow.begin(), kolejkaWierzcholkow.end(), element.wierzcholek) == kolejkaWierzcholkow.end()) {//dodanie wierzcholka do drogi, lub zamienienie jego kolejnosci jak juz w niej byl
					if (find(historiaKolejki.begin(), historiaKolejki.end(), element.wierzcholek) == historiaKolejki.end()) {
						kolejkaWierzcholkow.push_back(element.wierzcholek);
						historiaKolejki.push_back(element.wierzcholek);
					}
					else {
						kolejkaWierzcholkow.push_front(element.wierzcholek);
					}
				}
			}
		}
	}
	wyswietlListe(listaSasiadow);
	wypiszBelmanaForda(ujemnyCykl, droga);//wypisanie wyniku

	kolejkaWierzcholkow.clear();//oczyszczenie struktur pomocniczych
	droga.clear();
	historiaKolejki.clear();
	kolejkaWierzcholkow.resize(0);//usuniecie strutur pomocniczych
	droga.resize(0);
	historiaKolejki.resize(0);
}

void Graf::bellmanaFordaMacierz()
{
	bool ujemnyCykl = false;//sprawdzenie istnienia ujemnego cyklu
	deque<int> kolejkaWierzcholkow;//kolejka wierzcholkow do sprawdzenia
	vector<elementNajkrotszejSciezki> droga(liczbaWierzcholkow);//droga do wierzcholka
	vector<int> historiaKolejki;

	droga[wierzcholekPoczatkowy].sciezka.push_back(wierzcholekPoczatkowy);//ustalenie drogi do wierzcholka startowego
	droga[wierzcholekPoczatkowy].wagaDrogi = 0;
	kolejkaWierzcholkow.push_back(wierzcholekPoczatkowy);

	while (kolejkaWierzcholkow.size() > 0 && !ujemnyCykl) { //petla sprawdza wsystkie wierzcholki lub konczy w momenci wykrycia ujemnego cyklu 
		int badanyElement = kolejkaWierzcholkow.front();//pobranie wierzcholka do badania
		kolejkaWierzcholkow.pop_front();
		historiaKolejki.push_back(badanyElement);

		for (int i = 0; i < liczbaWierzcholkow; i++) {
			if (droga[badanyElement].wagaDrogi + macierzWag[badanyElement][i] < droga[i].wagaDrogi) {
				ujemnyCykl = (find(droga[badanyElement].sciezka.begin(), droga[badanyElement].sciezka.end(), i) != droga[badanyElement].sciezka.end());//sprawdzenie ujemnego cyklu
				if (ujemnyCykl) {
					break;
				}

				droga[i].sciezka = droga[badanyElement].sciezka;//zamiana sciezki na korzystniejsza
				droga[i].sciezka.push_back(i);
				droga[i].wagaDrogi = droga[badanyElement].wagaDrogi + macierzWag[badanyElement][i];

				if (kolejkaWierzcholkow.empty() || find(kolejkaWierzcholkow.begin(), kolejkaWierzcholkow.end(), i) == kolejkaWierzcholkow.end()) {

					if (find(historiaKolejki.begin(), historiaKolejki.end(), i) == historiaKolejki.end()) {//dodanie wierzcholka do drogi, lub zamienienie jego kolejnosci jak juz w niej byl
						kolejkaWierzcholkow.push_back(i);
						historiaKolejki.push_back(i);
					}
					else {
						kolejkaWierzcholkow.push_front(i);
					}
				}
			}
		}
	}
	wyswietlMacierz(macierzWag);
	wypiszBelmanaForda(ujemnyCykl, droga);//wypisanie wyniku

	kolejkaWierzcholkow.clear();//oczyszczenie struktur pomocniczych
	droga.clear();
	historiaKolejki.clear();
	kolejkaWierzcholkow.resize(0);//usuniecie strutur pomocniczych
	droga.resize(0);
	historiaKolejki.resize(0);
}


////////////////////////////////////////pomocnicze////////////////////////////////////////


void Graf::wypiszBelmanaForda(bool ujemnyCykl, vector<elementNajkrotszejSciezki> droga) {
	if (ujemnyCykl) {//sprawdzenie istnienai ujemnego cyklu
		cout <<endl<< "Cykl ujemny" << endl;
	}
	else {
		cout <<endl<< "koniec : wartosc drogi : droga" << endl;

		for (int a = 0; a < (int)droga.size(); a++) {//wyswietlenie wag i drog 
			cout << a << " : " << droga[a].wagaDrogi << " : ";
			int i = 0;
			for (auto& element : droga[a].sciezka) {
				cout << element ;
				i++;
				if (i < droga[a].sciezka.size()) {
					cout << " -> ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

}

void Graf::wypiszPrima(vector<elementMinimalnegoDrzewa> wyniki, int wagaCalkowita)
{
	cout <<endl<<"wierzcholki : waga" << endl;
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