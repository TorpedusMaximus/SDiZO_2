#include <Windows.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Tester {
public:
	long long int czestotliwosc, poczatek, koniec, czas;  //zmienne do przechowywania czasu i generacji losowych liczb
	fstream wynik;

	Tester();
	void startPomiaru();
	void koniecPomiaru();
	void zapisWyniku(string kodAkcji);
	void zakoncz();

private:
	long long int odczytCzasu();
};


