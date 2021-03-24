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
Funkcja dopisuje wynik i imiê gracza na koniec pliku binarnego przechowuj¹cego wszystkie wyniki.

parametry funkcji :
-----------------------
rekord - wskaŸnik na strukture przechowuj¹c¹ imiê oraz wynik gracza we w³aœnie zakoñczonej rozgrywce
nazwaPlikuWejsciowego - nazwa pliku przechowuj¹cego wyniki

*/
void zapisz(struct zapis* rekord, char* nazwaPlikuWejsciowego);

/*
Funkcja wczytuje wszystkie wyniki z pliku do pamiêci, nastêpnie zachowuje 10 najlepszych wyników w statycznej tablicy a zalokowan¹ wczeœniej pamiêc zwalnia.

parametry funkcji :
---------------------- -
najlepsze - statyczna 10 elementowa tablica przechowuj¹ca 10 najlepszych wyników wczytanych z pliku
nazwaPlikuWejsciowego - nazwa pliku przechowuj¹cego wyniki

*/
void wczytaj(struct zapis najlepsze[10],char* nazwaPlikuWejsciowego);

/*
Funkcja przesuwa kursor w konsoli na podane wspó³rzêdne.

parametry funkcji :
-----------------------
x - wspó³rzêdna pionowa (licz¹c od góry)
y - wspó³rzêdna pozioma (licz¹c od lewej)


*/
void przesunKursor(int x, int y);

/*
Funkcja czyœci konsolê a nastêpnie wypisuje ca³a planszê wraz z informacjami o wyniku, nastêpnym klocku oraz tabele 10 najlepszych wyników.

parametry funkcji :
-----------------------
plansza - statyczna dwuwymiarowa tablica przechowuj¹ca planszê gry
wynik - zmienna przechowuje informacje o dotychczasowo uzyskanym przez gracza wyniku
nastepny - zmnienna przechowuje informacje jaki rodzaj klocka pojawi siê nastêpnie na planszy
najlepsze - statyczna 10 elementowa tablica przechowuj¹ca 10 najlepszych wyników wczytanych z pliku

*/
void wypisaniePlanszy(char plansza[wysokoscPlanszy][szerokoscPlanszy], int wynik, int nastepny, struct zapis najlepsze[10]);

/*
Funkcja przesuwa klocek o jedn¹ kratkê w bok. W wypadku wykrycia kolizji klocek wraca na pocz¹tkow¹ pozycjê.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj¹ca planszê gry
zmiana - zmienna przechowuj¹ca informacje o tym czy na planszy nast¹pi³a jakaœ zmiana
obecny - wskaŸnik na strukturê przechowuj¹c¹ obecne wspó³rzêdne klocka
n - zmienna definiuje czy przesuniêcie wystêpuje w prawo(1) czy w lewo(-1)

*/
void przesunWBok(char plansza[wysokoscPlanszy][szerokoscPlanszy], int *zmiana, struct klocek* obecny, int n);

/*
Funkcja przesuwa klocek o jedn¹ kratkê w dó³. W wypadku wykrycia kolizii klocek wraca na pocz¹tkow¹ pozycjê, zostaje unieruchomiony a funckja zapisuje informacje o tym ¿e powinien pojawiæ siê nowy klocek.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj¹ca planszê gry
zmiana - zmienna przechowuj¹ca informacje o tym czy na planszy nast¹pi³a jakaœ zmiana
obecny - wskaŸnik na strukturê przechowuj¹c¹ obecne wspó³rzêdne klocka
nowy - zmienna przechowuj¹ca informacje o tym czy na planszy powinien pojawiæ siê nowy klocek

*/
void przesunWDol(char plansza[wysokoscPlanszy][szerokoscPlanszy], int *zmiana, struct klocek* obecny, int*nowy);

/*
Funkcja obraca klocek o 90 stopni zgodnie z ruchem wskazówek zegara. W wypadku wykrycia kolizii klocek wraca na pocz¹tkow¹ pozycjê.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj¹ca planszê gry
zmiana - zmienna przechowuj¹ca informacje o tym czy na planszy nast¹pi³a jakaœ zmiana
obecny - wskaŸnik na strukturê przechowuj¹c¹ obecne wspó³rzêdne klocka

*/
void obroc(char plansza[wysokoscPlanszy][szerokoscPlanszy], int *zmiana, struct klocek* obecny);

/*
Funkcja, w zale¿noœci od wciœniêtego przez u¿ytkownika klawisza, wywo³uje ¿¹dane funkcje.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj¹ca planszê gry
zmiana - zmienna przechowuj¹ca informacje o tym czy na planszy nast¹pi³a jakaœ zmiana
obecny - wskaŸnik na strukturê przechowuj¹c¹ obecne wspó³rzêdne klocka
nowy - zmienna przechowuj¹ca informacje o tym czy na planszy powinien pojawiæ siê nowy klocek
obrot - zmnienna przechowuj¹ca informacje czy dany klocek siê obraca (kwadrat siê nie obraca)

*/
void reakcjaNaKlawisze(char plansza[wysokoscPlanszy][szerokoscPlanszy], int *zmiana, struct klocek* obecny, int* nowy, int obrot);

/*
Funkcja sprawdza czy na planszy znajduj¹ siê ca³kowicie wype³nione wiersze. Gdy je znajdzie usuwa je a nastêpnie obni¿a wszystkie klocki znajduj¹ce siê powy¿ej o jeden w dó³. W zale¿noœci od iloœci wyczyszczanych wierszy dodaje punkty do wyniku.
parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj¹ca planszê gry
wynik - zmienna przechowuje informacje o dotychczasowo uzyskanym przez gracza wyniku
najlepsze - statyczna 10 elementowa tablica przechowuj¹ca 10 najlepszych wyników wczytanych z pliku
nastepny - zmnienna przechowuje informacje jaki rodzaj klocka pojawi siê nastêpnie na planszy

*/
void usunWiersz(char plansza[wysokoscPlanszy][szerokoscPlanszy], int* wynik, struct zapis najlepsze[10], int nastepny);

/*
Funkcja ustawia planszê oraz zmienne do startowych wartoœæi.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj¹ca planszê gry
najlepsze - statyczna 10 elementowa tablica przechowuj¹ca 10 najlepszych wyników wczytanych z pliku
hOut - uchwyt na wyjœcie konsoli
test - wskaŸnik na strukture przechowuj¹c¹ imiê oraz wynik gracza

*/
void poczatekGry(char plansza[wysokoscPlanszy][szerokoscPlanszy], struct zapis najlepsze[10], HANDLE* hOut, struct zapis* test);

/*
Funkcja jest odpowiedzialna za pojawienie sie na planszy nowego klocka. W wypadku wystapienia kolizji wywo³ywana jest funkcja KoniecGry.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj¹ca planszê gry
tablica - statyczna dwuwymiarowa tablica przechowuj¹ca pocz¹tkowe wspó³rzêdne klocków
obecny - wskaŸnik na strukturê przechowuj¹c¹ obecne wspó³rzêdne klocka
losowa - zmienna przechowuje informacje o typie klocka który powinien pojawiæ siê na planszy
najlepsze - statyczna 10 elementowa tablica przechowuj¹ca 10 najlepszych wyników wczytanych z pliku
hOut - uchwyt na wyjœcie konsoli
test - wskaŸnik na strukture przechowuj¹c¹ imiê oraz wynik gracza
wynik - zmienna przechowuje informacje o dotychczasowo uzyskanym przez gracza wyniku
nazwaPlikuWejsciowego - nazwa pliku przechowuj¹cego wyniki


wartosc zwracana :
--------------------
0 - u¿ytkownik zdecydowa³ siê na wy³¹czenie gry
1 - u¿ytkownik zdecydowa³ siê na rozpoczêcie gry od nowa
2 - gra jeszcze siê nie zakoñczy³a
*/
int nowyKlocek(char plansza[wysokoscPlanszy][szerokoscPlanszy], int tablica[7][8], struct klocek* obecny, int losowa, struct zapis najlepsze[10], HANDLE* hOut, struct zapis* test, int wynik, char* nazwaPlikuWejsciowego);

/*
Funkcja wyswietla ekran koncowy, czeka na decyzje uzytkownika. Wywoluje rowniez funkcje odpowiedzialna za zapisanie wyniku do pliku.

parametry funkcji :
---------------------- -
plansza - statyczna dwuwymiarowa tablica przechowuj¹ca planszê gry
najlepsze - statyczna 10 elementowa tablica przechowuj¹ca 10 najlepszych wyników wczytanych z pliku
hOut - uchwyt na wyjœcie konsoli
test - wskaŸnik na strukture przechowuj¹c¹ imiê oraz wynik gracza
obecny - wskaŸnik na strukturê przechowuj¹c¹ obecne wspó³rzêdne klocka
wynik - zmienna przechowuje informacje o dotychczasowo uzyskanym przez gracza wyniku
nazwaPlikuWejsciowego - nazwa pliku przechowuj¹cego wyniki

wartosc zwracana :
--------------------
0 - u¿ytkownik zdecydowa³ siê na wy³¹czenie gry
1 - u¿ytkownik zdecydowa³ siê na rozpoczêcie gry od nowa

*/
int KoniecGry(char plansza[wysokoscPlanszy][szerokoscPlanszy], struct zapis najlepsze[10], HANDLE* hOut, struct zapis* test, struct klocek* obecny, int wynik, char* nazwaPlikuWejsciowego);

/*
Funkcja zachowuje sterowanie tak d³ugo a¿ u¿ytkownik nie wciœnie klawisza odpowiedzialnego za wy³¹czenie pauzy.

*/
void pauza();

/*
Funkcja odczytuje argumenty podane przez u¿ytkownika w wierszu poleceñ. Wczytuje nazwê pliku podan¹ po prze³¹czniku -i.

parametry funkcji :
---------------------- -
argc - iloœæ argumentów wczytanych z wiersza poleceñ
argv - tablica przechowuj¹ca argumenty
nazwaPlikuWejsciowego - nazwa pliku przechowuj¹cego wyniki

wartosc zwracana :
--------------------
0 - uda³o siê wczytaæ nazwê pliku wejœciowego
1 - nazwy pliku nie uda³o siê wczytaæ

*/
int czytajArgumentyWierszaPolecen(int argc, char** argv, char** nazwaPlikuWejsciowego);

#endif