#include "header.hpp"

void tri_insertion(list *l) {
	list *t = new_list();
	while (l -> head != NULL) {
		int max = search_max(l);
		delete_val(l, max);
		add_head(t, max);
	}
	l -> head = t -> head;
	free(t);
}

int del_max(list *l) {
	node *n = l -> head;
	node *max = n;
	node *prevmax = n;
	int maxnb = n -> data;
	if (n == NULL) {
		return -1;
	}
	while(n -> next != NULL) {
		if (n -> next -> data > maxnb) {
			max = n -> next;
			prevmax = n;
			maxnb = n -> next -> data;
		}
		n = n -> next;
	}
	if (max != l->head) {
		prevmax -> next = max -> next;
	}
	else {
		l -> head = max -> next;
	}
		
	return maxnb;
}

void tri_insertion_rapide(list *l) {
	list *t = new_list();
	while (l -> head != NULL) {
		int max = del_max(l);
		add_head(t, max);
	}
	l -> head = t -> head;
	free(t);
}

int main() {
	srand(time(NULL));
	list *l = new_list();
	int taille = rand()%50;
	for (int i = 0; i < taille; i++) {
		add_head(l, rand()%100);
	}
	show_list(l);
	tri_insertion_rapide(l);
	show_list(l);
	return 0;
}