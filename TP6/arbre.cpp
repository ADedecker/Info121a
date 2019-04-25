#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

const int TAILLE = 15;

int parent(int i) {
	return (i-1)/2;
}

int gauche(int i) {
	return 2*i+1;
}

int droite(int i) {
	return 2*i+2;
}

void affiche_tableau(int tab[]) {
	for (int i = 0; i < TAILLE; i++) 
		cout << tab[i] << " ";
	cout << endl;
}

void afficher_tas(int tab[], int n) {
	int tot = 0;
	int i = 0;
	if (n != 0)
		while(n >= tot + pow(2, i)) {
			tot += pow(2, i);
			i++;
		}
	for (int s = 0; s < i; s++)
		cout << " ";
	cout << tab[n] << endl;
	if ((n+1)*2-1 < TAILLE)
		afficher_tas(tab, gauche(n));
	if ((n+1)*2 < TAILLE)
		afficher_tas(tab, droite(n));
}

void echange(int tab[], int a, int b) {
	int tmp = tab[a];
	tab[a] = tab[b];
	tab[b] = tmp;
}

void tamiser(int tab[], int deb, int fin) {
	int k = deb;
	int j = 2*k;
	while (j <= fin) {
		if (j < fin && tab[j] < tab[j+1]) {
			j++;
		}
		if (tab[k] < tab[j]) {
			echange(tab, k, j);
			k = j;
			j = 2*k;
		} else {
			j = fin + 1;
		}
	}
}

void creer_tas(int tab[], int n) {
	for (int i = n / 2; i >= 0; i--)
		tamiser(tab,i,n);
}

void tri_par_tas (int tab[], int n) {
	if (n <= 1) 
		return;
	creer_tas(tab,n);
	for (int j = n-1; j >= 1; j--) {
		echange(tab,0,j);
		tamiser(tab,0,j-1);
	}
}

int main() {
	srand(time(NULL));
	int tab[TAILLE];
	for (int i = 0; i < TAILLE; i++) {
		tab[i] = rand()%10;
	}
	cout << "Tableau avant tri: ";
	affiche_tableau(tab);
	tri_par_tas(tab, TAILLE);
	cout << "Tableau après tri: ";
	affiche_tableau(tab);
	return 0;
}