#include <limits>
#include <list>

using namespace std;

struct elementListy { // element listy krawedzi 
	int wierzcholek;
	float waga;
};

struct elementMinimalnegoDrzewa { // element wyniku algorytmu prima
	int wierzcholekA;
	int wierzcholekB;
	float waga;
};

struct elementNajkrotszejSciezki {  // element listy drog w algorytmie bellmana-forda
	float inf = numeric_limits<float>::infinity();
	float wagaDrogi = inf;
	int poprzedniWierzcholek=-1;
	elementNajkrotszejSciezki* poprzedniElement;
};