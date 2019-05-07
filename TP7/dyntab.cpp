#include <iostream>
#include <cstdlib>
using namespace std;

struct vecteur {
    int n;
    int s;
    int *t;
};

vecteur *nouveau_vecteur() {
    vecteur *v = (vecteur*) malloc (sizeof(vecteur));
    v -> n = 0;
    v -> s = 10;
    v -> t = (int*) malloc (v -> s * sizeof(int));
    if (v -> t == NULL) {
        delete (v -> t);
        cout << "Erreur d'allocation" << endl;
        exit(1);
    }
    return v;
}

void liberer_vecteur(vecteur *v) {
    delete(v -> t);
    v -> s = 10;
    v -> n = 0;
}

void affiche_vecteur(vecteur *v) {
    for (int i = 0; i < v -> n; i++) {
        cout << v -> t[i] << ", ";
    }
    cout << endl;
}

void augmenter_taille(vecteur *v) {
    int *tmp;
    tmp = (int*) realloc (v -> t, v -> s * 2 * sizeof(int));
    if (tmp != NULL) {
        v -> t = tmp;
        v -> s *= 2;
    } else {
        delete(v -> t);
        cout << "Erreur réallocation" << endl;
        exit (1);
    }
}

void ajouter_en_queue(vecteur *v, int val) {
    if (v -> n < v -> s) {
        v -> t[v -> n] = val;
    } else {
        augmenter_taille(v);
        v -> t[v -> n] = val;
    }
    v -> n++;
}

void retirer_en_queue(vecteur *v) {
    v -> n--;
}

int taille_vecteur(vecteur *v) {
    return v -> n;
}

int lire_valeur(vecteur *v, int idx) {
    if (idx < v -> n) {
        return v -> t[idx];
    } else {
        return -1;
    }
}

void modifier_valeur(vecteur *v, int idx, int val) {
    if (idx < v -> n) {
        v -> t[idx] = val;
    }
}

int main() {
    vecteur *v = nouveau_vecteur();
    //liberer_vecteur(v);
    //augmenter_taille(v);
    for (int i = 0; i < 20; i++) {
        ajouter_en_queue(v, i);
    }
    ajouter_en_queue(v, 20);
    cout << v -> s << " " << v -> n << endl;
    affiche_vecteur(v);
    return 0;
}
