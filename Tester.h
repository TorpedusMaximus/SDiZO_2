#include <Windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

class Tester {
public:
	long long int czestotliwosc, poczatek, koniec, czas;  //zmienne do przechowywania czasu i generacji losowych liczb
	fstream wynik;

	Tester();
	void startPomiaru();
	void zakonczPomiar(string kodAkcji);
	void zakoncz();

private:
	long long int odczytCzasu();
};


