#include <iostream>
#include <random>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <fstream>

using namespace std;

long long int read_QPC() { // wartosc licznika czasu 
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}


int main() {
	long long int  frequency; //zmienne do przechowywania czasu i generacji losowych liczb
	random_device rd;
	mt19937 gen(rd());
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	int wybor = 1;

	while (1) {  //menu glowne 
		system("cls");
		cout << "Wybierz sturture do testow. \n1.Tablica \n2.Lista \n3.Kopiec \n4.Wyjdz" << endl;
		cin >> wybor;
		switch (wybor) {
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:
			return 0;
			break;
		}
	}

	return 0;
}
