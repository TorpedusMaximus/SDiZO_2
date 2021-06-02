#include "Tester.h"

using namespace std;

Tester::Tester()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&czestotliwosc);
	wynik.open("wynik.txt", fstream::app);
	wynik << endl;
}

long long int Tester::odczytCzasu() { // wartosc licznika czasu 
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}

void Tester::startPomiaru()
{
	poczatek = odczytCzasu();
}

void Tester::koniecPomiaru()
{
	koniec = odczytCzasu();
	czas = (1000000.0 * (koniec - poczatek)) / czestotliwosc;
}

void Tester::zapisWyniku(string kodAkcji)
{
	cout << kodAkcji << " " << czas << " ms" << endl;
	wynik << kodAkcji << " " << czas << " ms" << endl;
}

void Tester::zakoncz()
{
	wynik.close();
	cout << "Zapisano pliki" << endl;
}

