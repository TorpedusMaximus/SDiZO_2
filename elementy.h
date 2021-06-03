#include <limits>
#include <list>

using namespace std;

struct elementListy { // element listy krawedzi 
	int wierzcholek;
	float waga;
};

struct elementPrima { // element wyniku algorytmu prima
	int wierzcholekA;
	int wierzcholekB;
	int waga;
};

struct elementBelmanaForda {  // element listy drog w algorytmie bellmana-forda
	float inf = numeric_limits<float>::infinity();
	float wagaDrogi = inf;
	list<int> sciezka;
};