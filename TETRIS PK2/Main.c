#include "Tetris.h"

int main(int argc, char** argv)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//Uchwyt na wyjście konsoli
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hOut, &cursorInfo);//Kursor przestaje być widoczny
	
	char plansza[wysokoscPlanszy][szerokoscPlanszy];  //Tablica zawierająca planszę gry 
	int tablica[7][8] = { 1,szerokoscPlanszy / 2,2,szerokoscPlanszy / 2 + 1 ,2,szerokoscPlanszy / 2 ,1,szerokoscPlanszy / 2 + 1, //Tablica zawierająca początkowe współrzędne klocków
		1,szerokoscPlanszy / 2,2,szerokoscPlanszy / 2,3,szerokoscPlanszy / 2,3,szerokoscPlanszy / 2 + 1,
		1,szerokoscPlanszy / 2,2,szerokoscPlanszy / 2,3,szerokoscPlanszy / 2,3,szerokoscPlanszy / 2 - 1,
		1,szerokoscPlanszy / 2,2,szerokoscPlanszy / 2,3,szerokoscPlanszy / 2,4,szerokoscPlanszy / 2 ,
		1,szerokoscPlanszy / 2,1,szerokoscPlanszy / 2 + 1,2,szerokoscPlanszy / 2 + 1,2,szerokoscPlanszy / 2 + 2 ,
		1,szerokoscPlanszy / 2,1,szerokoscPlanszy / 2 - 1,2,szerokoscPlanszy / 2 - 1,2,szerokoscPlanszy / 2 - 2,
		1,szerokoscPlanszy / 2,1,szerokoscPlanszy / 2 + 1,1,szerokoscPlanszy / 2 + 2,2,szerokoscPlanszy / 2 + 1 };
	srand(time(NULL));
	struct klocek obecny;
	int nowy = 1; //Zmienna przechowuje informację o tym czy na planszy powinien pojawić się nowy klocek
	int zmiana = 1; //Zmienna przechowuje informację o tym czy nastąpiła jakaś zmiana na planszy
	time_t czas1, czas2;
	czas1 = clock(NULL);
	int wynik;
	double f; //Zmienna definiuje prędkość samoistnego spadania klocka
	int losowa = rand() % 7;
	int k = 1;
	struct zapis test;
	struct zapis najlepsze[10]; //Tablica zawierająca 10 najlepszych wyników
	char* nazwaPlikuWejsciowego = 0;
	if (czytajArgumentyWierszaPolecen(argc, argv, &nazwaPlikuWejsciowego))
	{
		wczytaj(najlepsze,nazwaPlikuWejsciowego); //Wczytanie 10 najlepszych wyników z pliku
	}
	while (k)
	{
		wynik = 0;
		f = 1000;
		poczatekGry(plansza, najlepsze, &hOut,&test);
		int obrot;
		while (1)
		{
			if (nowy == 1)
			{
				usunWiersz(plansza, &wynik, najlepsze, losowa);
				if (losowa == 0)
				{
					obrot = 0;
				}
				else
				{
					obrot = 1;
				}
				if((k = nowyKlocek(plansza, tablica, &obecny, losowa, najlepsze, &hOut, &test, wynik, nazwaPlikuWejsciowego))!=2)
				break;
				losowa = rand() % 7;
				nowy = 0;
			}
			if (zmiana == 1)
			{
				wypisaniePlanszy(plansza, wynik, losowa, najlepsze);
				zmiana = 0;
			}
			if (_kbhit())
			{
				reakcjaNaKlawisze(plansza, &zmiana, &obecny, &nowy, obrot);
			}
			czas2 = clock(NULL);
			if ((czas2 - czas1) > 1000)
				f = f - 100;
			if ((czas2 - czas1) > f)
			{
				czas1 = czas2;
				przesunWDol(plansza, &zmiana, &obecny, &nowy);
			}
				Sleep(30);
		}
	}
	return 0;
}