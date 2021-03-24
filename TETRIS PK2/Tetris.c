#include "Tetris.h"

void zapisz(struct zapis* rekord, char* nazwaPlikuWejsciowego)
{
	FILE *out;
	if (out = fopen(nazwaPlikuWejsciowego, "ab+"))
	{
		int i = ftell(out);
		fwrite(rekord, sizeof(struct zapis), 1, out);
		fclose(out);
	}
}

void wczytaj(struct zapis najlepsze[10], char* nazwaPlikuWejsciowego)
{
	int i = 0;
	int m;
	FILE *in;
	struct element* Head = 0;
	struct element* tHead;

	if (in = fopen(nazwaPlikuWejsciowego, "rb"))
	{
		fseek(in, 0L, SEEK_SET);
		struct zapis test;
		while (1)
		{

			tHead = Head;
			Head = malloc(sizeof(struct element));
			fread(&(Head->zapis), sizeof(struct zapis), 1, in);
			if (feof(in))
			{
				free(Head);
				Head = tHead;
				break;
			}
			;
			Head->nastepny = tHead;
			i++;


		}
		fclose(in);

		struct zapis pusty = { -1," " };
		struct zapis najlepszy = Head->zapis;
		int indeks = 0;
		struct element* best = Head;

		for (int k = 0; k < 10; k++)
		{
			tHead = Head;
			for (int j = 0; j < i; j++)
			{
				if (tHead->zapis.wynik > najlepszy.wynik)
				{
					best = tHead;
					najlepszy = tHead->zapis;
					indeks = j;
				}
				tHead = tHead->nastepny;
			}
			najlepsze[k] = najlepszy;
			best->zapis = pusty;
			najlepszy = pusty;
		}

		while (Head)
		{
			tHead = Head->nastepny;
			free(Head);
			Head = tHead;
		}
		Head = 0;
	}
}

void przesunKursor(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void wypisaniePlanszy(char plansza[wysokoscPlanszy][szerokoscPlanszy], int wynik, int nastepny, struct zapis najlepsze[10])
{
	system("cls");
	for (int i = 0; i < wysokoscPlanszy; i++)
	{
		for (int j = 0; j < szerokoscPlanszy; j++)
		{
			printf("%c", plansza[i][j]);

		}
		printf("\n");
	}
	przesunKursor(szerokoscPlanszy + 2, wysokoscPlanszy / 4);
	printf("Yours score:");
	przesunKursor(szerokoscPlanszy + 2, wysokoscPlanszy / 4 + 1);
	printf("%d", wynik);
	przesunKursor(szerokoscPlanszy + 1, wysokoscPlanszy / 2);
	printf(" Next: ");
	przesunKursor(szerokoscPlanszy + 5, wysokoscPlanszy / 2 + 2);
	switch (nastepny) {
	case 0:
		printf("OO");
		przesunKursor(szerokoscPlanszy + 5, wysokoscPlanszy / 2 + 3);
		printf("OO");
		break;
	case 1:
		printf("O");
		przesunKursor(szerokoscPlanszy + 5, wysokoscPlanszy / 2 + 3);
		printf("O");
		przesunKursor(szerokoscPlanszy + 5, wysokoscPlanszy / 2 + 4);
		printf("OO");
		break;
	case 2:
		printf(" O");
		przesunKursor(szerokoscPlanszy + 5, wysokoscPlanszy / 2 + 3);
		printf(" O");
		przesunKursor(szerokoscPlanszy + 5, wysokoscPlanszy / 2 + 4);
		printf("OO");
		break;
	case 3:
		printf("O");
		przesunKursor(szerokoscPlanszy + 5, wysokoscPlanszy / 2 + 3);
		printf("O");
		przesunKursor(szerokoscPlanszy + 5, wysokoscPlanszy / 2 + 4);
		printf("O");
		przesunKursor(szerokoscPlanszy + 5, wysokoscPlanszy / 2 + 5);
		printf("O");
		break;
	case 4:
		printf("OO");
		przesunKursor(szerokoscPlanszy + 5, wysokoscPlanszy / 2 + 3);
		printf(" OO");
		break;
	case 5:
		printf(" OO");
		przesunKursor(szerokoscPlanszy + 5, wysokoscPlanszy / 2 + 3);
		printf("OO");
		break;
	case 6:
		printf("OOO");
		przesunKursor(szerokoscPlanszy + 5, wysokoscPlanszy / 2 + 3);
		printf(" O ");
		break;
	}
	przesunKursor(szerokoscPlanszy + 2, wysokoscPlanszy / 2 + 7);
	printf("P-Pause");
	int k = 0;
	przesunKursor(szerokoscPlanszy + 16, wysokoscPlanszy / 4 - 2);
	printf("Best scores:");
	k = 0;
	while (najlepsze[k].wynik >= 0)
	{
		przesunKursor(szerokoscPlanszy + 16, wysokoscPlanszy / 4 + k);
		printf("%d. %d %s ", k + 1, najlepsze[k].wynik, najlepsze[k].imie);
		k++;
	}
	printf("\n");
}

void przesunWBok(char plansza[wysokoscPlanszy][szerokoscPlanszy], int *zmiana, struct klocek* obecny, int n)
{
	struct klocek tempKlocek = *obecny;
	plansza[tempKlocek.x1][tempKlocek.y1] = znakPusty;
	plansza[tempKlocek.x2][tempKlocek.y2] = znakPusty;
	plansza[tempKlocek.x3][tempKlocek.y3] = znakPusty;
	plansza[tempKlocek.x4][tempKlocek.y4] = znakPusty;
	tempKlocek.y1 = tempKlocek.y1 + n;
	tempKlocek.y2 = tempKlocek.y2 + n;
	tempKlocek.y3 = tempKlocek.y3 + n;
	tempKlocek.y4 = tempKlocek.y4 + n;
	if ((plansza[tempKlocek.x1][tempKlocek.y1] != znakKlockow) && (plansza[tempKlocek.x1][tempKlocek.y1] != krawedzie)
		&& (plansza[tempKlocek.x2][tempKlocek.y2] != znakKlockow) && (plansza[tempKlocek.x2][tempKlocek.y2] != krawedzie)
		&& (plansza[tempKlocek.x3][tempKlocek.y3] != znakKlockow) && (plansza[tempKlocek.x3][tempKlocek.y3] != krawedzie)
		&& (plansza[tempKlocek.x4][tempKlocek.y4] != znakKlockow) && (plansza[tempKlocek.x4][tempKlocek.y4] != krawedzie))
	{
		plansza[tempKlocek.x1][tempKlocek.y1] = znakKlockow;
		plansza[tempKlocek.x2][tempKlocek.y2] = znakKlockow;
		plansza[tempKlocek.x3][tempKlocek.y3] = znakKlockow;
		plansza[tempKlocek.x4][tempKlocek.y4] = znakKlockow;
		*zmiana = 1;
		*obecny = tempKlocek;
	}
}

void przesunWDol(char plansza[wysokoscPlanszy][szerokoscPlanszy], int *zmiana, struct klocek* obecny, int*nowy)
{
	struct klocek tempKlocek = *obecny;
	plansza[tempKlocek.x1][tempKlocek.y1] = znakPusty;
	plansza[tempKlocek.x2][tempKlocek.y2] = znakPusty;
	plansza[tempKlocek.x3][tempKlocek.y3] = znakPusty;
	plansza[tempKlocek.x4][tempKlocek.y4] = znakPusty;
	tempKlocek.x1++;
	tempKlocek.x2++;
	tempKlocek.x3++;
	tempKlocek.x4++;
	if ((plansza[tempKlocek.x1][tempKlocek.y1] != znakKlockow) && (plansza[tempKlocek.x1][tempKlocek.y1] != krawedzie)
		&& (plansza[tempKlocek.x2][tempKlocek.y2] != znakKlockow) && (plansza[tempKlocek.x2][tempKlocek.y2] != krawedzie)
		&& (plansza[tempKlocek.x3][tempKlocek.y3] != znakKlockow) && (plansza[tempKlocek.x3][tempKlocek.y3] != krawedzie)
		&& (plansza[tempKlocek.x4][tempKlocek.y4] != znakKlockow) && (plansza[tempKlocek.x4][tempKlocek.y4] != krawedzie))
	{
		plansza[tempKlocek.x1][tempKlocek.y1] = znakKlockow;
		plansza[tempKlocek.x2][tempKlocek.y2] = znakKlockow;
		plansza[tempKlocek.x3][tempKlocek.y3] = znakKlockow;
		plansza[tempKlocek.x4][tempKlocek.y4] = znakKlockow;
		*zmiana = 1;
		*obecny = tempKlocek;
	}
	else
	{
		plansza[tempKlocek.x1 - 1][tempKlocek.y1] = znakKlockow;
		plansza[tempKlocek.x2 - 1][tempKlocek.y2] = znakKlockow;
		plansza[tempKlocek.x3 - 1][tempKlocek.y3] = znakKlockow;
		plansza[tempKlocek.x4 - 1][tempKlocek.y4] = znakKlockow;
		*zmiana = 1;
		*nowy = 1;
	}
}

void obroc(char plansza[wysokoscPlanszy][szerokoscPlanszy], int *zmiana, struct klocek* obecny)
{
	struct klocek tempKlocek = *obecny;
	plansza[tempKlocek.x1][tempKlocek.y1] = znakPusty;
	plansza[tempKlocek.x2][tempKlocek.y2] = znakPusty;
	plansza[tempKlocek.x3][tempKlocek.y3] = znakPusty;
	plansza[tempKlocek.x4][tempKlocek.y4] = znakPusty;
	int x = 0;
	while (tempKlocek.x2 != 0)
	{
		x++;
		tempKlocek.x1--;
		tempKlocek.x2--;
		tempKlocek.x3--;
		tempKlocek.x4--;
	}
	int y = 0;
	while (tempKlocek.y2 != 0)
	{
		y++;
		tempKlocek.y1--;
		tempKlocek.y2--;
		tempKlocek.y3--;
		tempKlocek.y4--;
	}
	struct klocek tempKlocek2 = tempKlocek;
	tempKlocek2.y1 = -tempKlocek.x1 + y;
	tempKlocek2.y2 = -tempKlocek.x2 + y;
	tempKlocek2.y3 = -tempKlocek.x3 + y;
	tempKlocek2.y4 = -tempKlocek.x4 + y;
	tempKlocek2.x1 = tempKlocek.y1 + x;
	tempKlocek2.x2 = tempKlocek.y2 + x;
	tempKlocek2.x3 = tempKlocek.y3 + x;
	tempKlocek2.x4 = tempKlocek.y4 + x;
	if ((plansza[tempKlocek2.x1][tempKlocek2.y1] != znakKlockow) && (plansza[tempKlocek2.x1][tempKlocek2.y1] != krawedzie)
		&& (plansza[tempKlocek2.x2][tempKlocek2.y2] != znakKlockow) && (plansza[tempKlocek2.x2][tempKlocek2.y2] != krawedzie)
		&& (plansza[tempKlocek2.x3][tempKlocek2.y3] != znakKlockow) && (plansza[tempKlocek2.x3][tempKlocek2.y3] != krawedzie)
		&& (plansza[tempKlocek2.x4][tempKlocek2.y4] != znakKlockow) && (plansza[tempKlocek2.x4][tempKlocek2.y4] != krawedzie))
	{
		plansza[tempKlocek2.x1][tempKlocek2.y1] = znakKlockow;
		plansza[tempKlocek2.x2][tempKlocek2.y2] = znakKlockow;
		plansza[tempKlocek2.x3][tempKlocek2.y3] = znakKlockow;
		plansza[tempKlocek2.x4][tempKlocek2.y4] = znakKlockow;
		*zmiana = 1;
		*obecny = tempKlocek2;
	}
	else
	{
		struct klocek tempKlocek3 = *obecny;
		plansza[tempKlocek3.x1][tempKlocek3.y1] = znakKlockow;
		plansza[tempKlocek3.x2][tempKlocek3.y2] = znakKlockow;
		plansza[tempKlocek3.x3][tempKlocek3.y3] = znakKlockow;
		plansza[tempKlocek3.x4][tempKlocek3.y4] = znakKlockow;
	}
}

void pauza()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	char znak;
	SetConsoleTextAttribute(hOut, FOREGROUND_RED);
	przesunKursor(szerokoscPlanszy / 2 - 5, wysokoscPlanszy / 4 - 1);
	printf("-----------");
	przesunKursor(szerokoscPlanszy / 2 - 5, wysokoscPlanszy / 4);
	printf("   PAUSE   ");
	przesunKursor(szerokoscPlanszy / 2 - 5, wysokoscPlanszy / 4 + 1);
	printf("-----------");
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	while (znak = _getch())
	{
		if (znak == -32)
			_getch();
		if (znak == 'P' || znak == 'p')
			break;
	}
}

void reakcjaNaKlawisze(char plansza[wysokoscPlanszy][szerokoscPlanszy], int *zmiana, struct klocek* obecny, int* nowy, int obrot)
{

	switch (_getch()) {
	case strzalki:
		switch (_getch()) {
		case dol://do do³u
			przesunWDol(plansza, zmiana, obecny, nowy);
			break;
		case lewo://w lewo
			przesunWBok(plansza, zmiana, obecny, -1);
			break;
		case prawo://w prawo
			przesunWBok(plansza, zmiana, obecny, 1);
			break;
		case gora://do gory
			if (obrot == 1)
				obroc(plansza, zmiana, obecny);
			break;
		}
		break;
	case 'p':
		pauza();
		break;
	case 'P':
		pauza();
		break;
	}
}
void usunWiersz(char plansza[wysokoscPlanszy][szerokoscPlanszy], int* wynik, struct zapis najlepsze[10], int nastepny)
{
	int wierszy = 0; //Zmienna przechowuje iloœæ wierszy usuniêtych za jednym razem
	int pelny; //Zmienna przechowuje informacjê, czy dany wiersz zosta³ w pe³ni wype³niony
	for (int i = 1; i < wysokoscPlanszy - 1; i++)
	{
		pelny = 1;
		for (int j = 1; j < szerokoscPlanszy - 1; j++)
		{
			if (plansza[i][j] == znakPusty)
			{
				pelny = 0;
				break;
			}
		}
		if (pelny == 1)
		{
			wierszy++;
			for (int j = 1; j < szerokoscPlanszy - 1; j++)
			{
				plansza[i][j] = znakPusty;
			}
			wypisaniePlanszy(plansza, *wynik, nastepny, najlepsze);
			for (int j = i; j > 0; j--)
			{
				for (int k = 1; k < szerokoscPlanszy - 1; k++)
				{
					plansza[j][k] = plansza[j - 1][k];
					if (plansza[j][k] == krawedzie)
					{
						plansza[j][k] = znakPusty;
					}
				}
			}
		}
	}
	switch (wierszy) {
	case 1:
		*wynik = *wynik + 100;
		break;
	case 2:
		*wynik = *wynik + 250;
		break;
	case 3:
		*wynik = *wynik + 400;
		break;
	case 4:
		*wynik = *wynik + 500;
		break;
	}
}

void poczatekGry(char plansza[wysokoscPlanszy][szerokoscPlanszy], struct zapis najlepsze[10], HANDLE* hOut, struct zapis* test)
{
	for (int i = 0; i < wysokoscPlanszy; i++) //Ustawienie planszy do stanu pocz¹tkowego 
	{
		for (int j = 0; j < szerokoscPlanszy; j++)
		{
			if (i == 0 || i == wysokoscPlanszy - 1 || j == 0 || j == szerokoscPlanszy - 1)
				plansza[i][j] = krawedzie;
			else
				plansza[i][j] = znakPusty;
		}
	}
	wypisaniePlanszy(plansza, 0, -1, najlepsze);
	SetConsoleTextAttribute(*hOut, FOREGROUND_RED);
	przesunKursor(szerokoscPlanszy / 5, wysokoscPlanszy / 2);
	printf("Nickname:");
	SetConsoleTextAttribute(*hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	przesunKursor(szerokoscPlanszy / 5, wysokoscPlanszy / 2 + 1);
	scanf("%9s", test->imie);
	wypisaniePlanszy(plansza, 0, -1, najlepsze);
	SetConsoleTextAttribute(*hOut, FOREGROUND_RED);
	przesunKursor(szerokoscPlanszy / 4, wysokoscPlanszy / 2);
	printf("S-Start");
	SetConsoleTextAttribute(*hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	char znak;
	while (1)
	{
		znak = _getch();
		if (znak == 'S' || znak == 's')
		{
			break;
		}
	}
}

int nowyKlocek(char plansza[wysokoscPlanszy][szerokoscPlanszy], int tablica[7][8], struct klocek* obecny, int losowa, struct zapis najlepsze[10], HANDLE* hOut, struct zapis* test, int wynik, char* nazwaPlikuWejsciowego)
{
	obecny->x1 = tablica[losowa][0];
	obecny->y1 = tablica[losowa][1];
	obecny->x2 = tablica[losowa][2];
	obecny->y2 = tablica[losowa][3];
	obecny->x3 = tablica[losowa][4];
	obecny->y3 = tablica[losowa][5];
	obecny->x4 = tablica[losowa][6];
	obecny->y4 = tablica[losowa][7];
	if (plansza[obecny->x1][obecny->y1] == znakKlockow ||
		plansza[obecny->x2][obecny->y2] == znakKlockow ||
		plansza[obecny->x3][obecny->y3] == znakKlockow ||
		plansza[obecny->x4][obecny->y4] == znakKlockow)
	{
		return KoniecGry(plansza, najlepsze, hOut, test, obecny, wynik, nazwaPlikuWejsciowego);
	}
	plansza[obecny->x1][obecny->y1] = znakKlockow;
	plansza[obecny->x2][obecny->y2] = znakKlockow;
	plansza[obecny->x3][obecny->y3] = znakKlockow;
	plansza[obecny->x4][obecny->y4] = znakKlockow;
	return 2;
}

int KoniecGry(char plansza[wysokoscPlanszy][szerokoscPlanszy], struct zapis najlepsze[10], HANDLE* hOut, struct zapis* test, struct klocek* obecny, int wynik, char* nazwaPlikuWejsciowego)
{
	plansza[obecny->x1][obecny->y1] = znakKlockow;
	plansza[obecny->x2][obecny->y2] = znakKlockow;
	plansza[obecny->x3][obecny->y3] = znakKlockow;
	plansza[obecny->x4][obecny->y4] = znakKlockow;
	test->wynik = wynik;
	if (nazwaPlikuWejsciowego != 0)
	{
		zapisz(test, nazwaPlikuWejsciowego);
		wczytaj(najlepsze, nazwaPlikuWejsciowego);
	}
	wypisaniePlanszy(plansza, wynik, -1, najlepsze);
	SetConsoleTextAttribute(*hOut, FOREGROUND_RED);
	przesunKursor(szerokoscPlanszy / 2 - 7, wysokoscPlanszy / 4 - 1);
	printf("---------------");
	przesunKursor(szerokoscPlanszy / 2 - 7, wysokoscPlanszy / 4);
	printf("    The End    ");
	przesunKursor(szerokoscPlanszy / 2 - 7, wysokoscPlanszy / 4 + 1);
	printf("---------------");
	przesunKursor(szerokoscPlanszy / 4, wysokoscPlanszy / 2);
	printf("R-Restart");
	przesunKursor(szerokoscPlanszy / 4, wysokoscPlanszy / 2 + 1);
	printf("E-End");
	SetConsoleTextAttribute(*hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	char znak;
	while (1)
	{
		znak = _getch();
		if (znak == 'r' || znak == 'R')
		{
			return 1;
		}
		if (znak == 'e' || znak == 'E')
		{
			return 0;
		}
	}
}

int czytajArgumentyWierszaPolecen(int argc, char** argv, char** nazwaPlikuWejsciowego)
{
	if (argc > 2)
	{
		if (argv[1] = "-i")
		{
			*nazwaPlikuWejsciowego = argv[2];
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}