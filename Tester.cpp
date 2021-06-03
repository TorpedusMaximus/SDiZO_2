#include "Tester.h"


using namespace std;

Tester::Tester()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&czestotliwosc);
	wynik.open("wynik.txt", fstream::app);//handler do pliku
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
	poczatek = odczytCzasu();//rozpoczecie liczenia czasu
}

void Tester::zakonczPomiar(string kodAkcji)
{
	koniec = odczytCzasu();//zakonczenie liczenia czasu 
	czas = (1000000.0 * (koniec - poczatek)) / czestotliwosc;
	wynik << kodAkcji << " "<< setprecision(0) << czas << " us" << endl;//za[pisanie czasu do pliku 
}

void Tester::zakoncz()
{
	wynik.close();//zamkniecie handlera
	cout << "Zapisano pliki" << endl;
}

