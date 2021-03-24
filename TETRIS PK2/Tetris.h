#ifndef TETRIS_H
#define TETRIS_H
#define _CRT_SECURE_NO_WARNINGS
#define szerokoscPlanszy 16
#define wysokoscPlanszy 20
#define strzalki 224
#define gora 72
#define dol 80
#define prawo 77
#define lewo 75
#define znakKlockow 'O'
#define znakPusty ' '
#define krawedzie 'X'
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

struct klocek {
	int x1, y1;
	int x2, y2;
	int x3, y3;
	int x4, y4;
};

struct zapis {
	int wynik;
	char imie[10];
};

struct element {
	struct element* nastepny;
	struct zapis zapis;
};

/*
Funkcja dopisuje wynik i imi� gracza na koniec pliku binarnego przechowuj�cego wszystkie wyniki.

parametry funkcji :
-----------------------
rekord - wska�nik na strukture przechowuj�c� imi� oraz wynik gracza we w�a�nie zako�czonej rozgrywce
nazwaPlikuWejsciowego - nazwa pliku przechowuj�cego wyniki

*/
void zapisz(struct zapis* rekord, char* nazwaPlikuWejsciowego);

/*
Funkcja wczytuje wszystkie wyniki z pliku do pami�ci, nast�pnie zachowuje 10 najlepszych wynik�w w statycznej tablicy a zalokowan� wcze�niej pami�c zwalnia.

parametry funkcji :
---------------------- -
najlepsze - statyczna 10 elementowa tablica przechowuj�ca 10 najlepszych wynik�w wczytanych z pliku
nazwaPlikuWejsciowego - nazwa pliku przechowuj�cego wyniki

*/
void wczytaj(struct zapis najlepsze[10],char* nazwaPlikuWejsciowego);

/*
Funkcja przesuwa kursor w konsoli na podane wsp�rz�dne.

parametry funkcji :
-----------------------
x - wsp�rz�dna pionowa (licz�c od g�ry)
y - wsp�rz�dna pozioma (licz�c od lewej)


*/
void przesunKursor(int x, int y);

/*
Funkcja czy�ci konsol� a nast�pnie wypisuje ca�a plansz� wraz z informacjami o wyniku, nast�pnym klocku oraz tabele 10 najlepszych wynik�w.

parametry funkcji :
-----------------------
plansza - statyczna dwuwymiarowa tablica przechowuj�ca plansz� gry
wynik - zmienna przechowuje informacje o dotychczasowo uzyskanym przez gracza wyniku
nastepny - zmnienna przechowuje informacje jaki rodzaj klocka pojawi si� nast�pnie na planszy
najlepsze - statyczna 10 elementowa tablica przechowuj�ca 10 najlepszych wynik�w wczytanych z pliku

*/
void wypisaniePlanszy(char plansza[wysokoscPlanszy][szerokoscPlanszy], int wynik, int nastepny, struct zapis najlepsze[10]);

/*
Funkcja przesuwa klocek o jedn� kratk� w bok. W wypadku wykrycia kolizji klocek wraca na pocz�tkow� pozycj�.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj�ca plansz� gry
zmiana - zmienna przechowuj�ca informacje o tym czy na planszy nast�pi�a jaka� zmiana
obecny - wska�nik na struktur� przechowuj�c� obecne wsp�rz�dne klocka
n - zmienna definiuje czy przesuni�cie wyst�puje w prawo(1) czy w lewo(-1)

*/
void przesunWBok(char plansza[wysokoscPlanszy][szerokoscPlanszy], int *zmiana, struct klocek* obecny, int n);

/*
Funkcja przesuwa klocek o jedn� kratk� w d�. W wypadku wykrycia kolizii klocek wraca na pocz�tkow� pozycj�, zostaje unieruchomiony a funckja zapisuje informacje o tym �e powinien pojawi� si� nowy klocek.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj�ca plansz� gry
zmiana - zmienna przechowuj�ca informacje o tym czy na planszy nast�pi�a jaka� zmiana
obecny - wska�nik na struktur� przechowuj�c� obecne wsp�rz�dne klocka
nowy - zmienna przechowuj�ca informacje o tym czy na planszy powinien pojawi� si� nowy klocek

*/
void przesunWDol(char plansza[wysokoscPlanszy][szerokoscPlanszy], int *zmiana, struct klocek* obecny, int*nowy);

/*
Funkcja obraca klocek o 90 stopni zgodnie z ruchem wskaz�wek zegara. W wypadku wykrycia kolizii klocek wraca na pocz�tkow� pozycj�.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj�ca plansz� gry
zmiana - zmienna przechowuj�ca informacje o tym czy na planszy nast�pi�a jaka� zmiana
obecny - wska�nik na struktur� przechowuj�c� obecne wsp�rz�dne klocka

*/
void obroc(char plansza[wysokoscPlanszy][szerokoscPlanszy], int *zmiana, struct klocek* obecny);

/*
Funkcja, w zale�no�ci od wci�ni�tego przez u�ytkownika klawisza, wywo�uje ��dane funkcje.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj�ca plansz� gry
zmiana - zmienna przechowuj�ca informacje o tym czy na planszy nast�pi�a jaka� zmiana
obecny - wska�nik na struktur� przechowuj�c� obecne wsp�rz�dne klocka
nowy - zmienna przechowuj�ca informacje o tym czy na planszy powinien pojawi� si� nowy klocek
obrot - zmnienna przechowuj�ca informacje czy dany klocek si� obraca (kwadrat si� nie obraca)

*/
void reakcjaNaKlawisze(char plansza[wysokoscPlanszy][szerokoscPlanszy], int *zmiana, struct klocek* obecny, int* nowy, int obrot);

/*
Funkcja sprawdza czy na planszy znajduj� si� ca�kowicie wype�nione wiersze. Gdy je znajdzie usuwa je a nast�pnie obni�a wszystkie klocki znajduj�ce si� powy�ej o jeden w d�. W zale�no�ci od ilo�ci wyczyszczanych wierszy dodaje punkty do wyniku.
parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj�ca plansz� gry
wynik - zmienna przechowuje informacje o dotychczasowo uzyskanym przez gracza wyniku
najlepsze - statyczna 10 elementowa tablica przechowuj�ca 10 najlepszych wynik�w wczytanych z pliku
nastepny - zmnienna przechowuje informacje jaki rodzaj klocka pojawi si� nast�pnie na planszy

*/
void usunWiersz(char plansza[wysokoscPlanszy][szerokoscPlanszy], int* wynik, struct zapis najlepsze[10], int nastepny);

/*
Funkcja ustawia plansz� oraz zmienne do startowych warto��i.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj�ca plansz� gry
najlepsze - statyczna 10 elementowa tablica przechowuj�ca 10 najlepszych wynik�w wczytanych z pliku
hOut - uchwyt na wyj�cie konsoli
test - wska�nik na strukture przechowuj�c� imi� oraz wynik gracza

*/
void poczatekGry(char plansza[wysokoscPlanszy][szerokoscPlanszy], struct zapis najlepsze[10], HANDLE* hOut, struct zapis* test);

/*
Funkcja jest odpowiedzialna za pojawienie sie na planszy nowego klocka. W wypadku wystapienia kolizji wywo�ywana jest funkcja KoniecGry.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj�ca plansz� gry
tablica - statyczna dwuwymiarowa tablica przechowuj�ca pocz�tkowe wsp�rz�dne klock�w
obecny - wska�nik na struktur� przechowuj�c� obecne wsp�rz�dne klocka
losowa - zmienna przechowuje informacje o typie klocka kt�ry powinien pojawi� si� na planszy
najlepsze - statyczna 10 elementowa tablica przechowuj�ca 10 najlepszych wynik�w wczytanych z pliku
hOut - uchwyt na wyj�cie konsoli
test - wska�nik na strukture przechowuj�c� imi� oraz wynik gracza
wynik - zmienna przechowuje informacje o dotychczasowo uzyskanym przez gracza wyniku
nazwaPlikuWejsciowego - nazwa pliku przechowuj�cego wyniki


wartosc zwracana :
--------------------
0 - u�ytkownik zdecydowa� si� na wy��czenie gry
1 - u�ytkownik zdecydowa� si� na rozpocz�cie gry od nowa
2 - gra jeszcze si� nie zako�czy�a
*/
int nowyKlocek(char plansza[wysokoscPlanszy][szerokoscPlanszy], int tablica[7][8], struct klocek* obecny, int losowa, struct zapis najlepsze[10], HANDLE* hOut, struct zapis* test, int wynik, char* nazwaPlikuWejsciowego);

/*
Funkcja wyswietla ekran koncowy, czeka na decyzje uzytkownika. Wywoluje rowniez funkcje odpowiedzialna za zapisanie wyniku do pliku.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj�ca plansz� gry
najlepsze - statyczna 10 elementowa tablica przechowuj�ca 10 najlepszych wynik�w wczytanych z pliku
hOut - uchwyt na wyj�cie konsoli
test - wska�nik na strukture przechowuj�c� imi� oraz wynik gracza
obecny - wska�nik na struktur� przechowuj�c� obecne wsp�rz�dne klocka
wynik - zmienna przechowuje informacje o dotychczasowo uzyskanym przez gracza wyniku
nazwaPlikuWejsciowego - nazwa pliku przechowuj�cego wyniki

wartosc zwracana :
--------------------
0 - u�ytkownik zdecydowa� si� na wy��czenie gry
1 - u�ytkownik zdecydowa� si� na rozpocz�cie gry od nowa

*/
int KoniecGry(char plansza[wysokoscPlanszy][szerokoscPlanszy], struct zapis najlepsze[10], HANDLE* hOut, struct zapis* test, struct klocek* obecny, int wynik, char* nazwaPlikuWejsciowego);

/*
Funkcja zachowuje sterowanie tak d�ugo a� u�ytkownik nie wci�nie klawisza odpowiedzialnego za wy��czenie pauzy.

*/
void pauza();

/*
Funkcja odczytuje argumenty podane przez u�ytkownika w wierszu polece�. Wczytuje nazw� pliku podan� po prze��czniku -i.

parametry funkcji :
---------------------- -
argc - ilo�� argument�w wczytanych z wiersza polece�
argv - tablica przechowuj�ca argumenty
nazwaPlikuWejsciowego - nazwa pliku przechowuj�cego wyniki

wartosc zwracana :
--------------------
0 - uda�o si� wczyta� nazw� pliku wej�ciowego
1 - nazwy pliku nie uda�o si� wczyta�

*/
int czytajArgumentyWierszaPolecen(int argc, char** argv, char** nazwaPlikuWejsciowego);

#endif