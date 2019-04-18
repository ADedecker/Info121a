#include <cstdlib>
#include <iostream>

using namespace std;

struct branch {
	int data;
	branch *left;
	branch *right;
	int visited;
};

struct tree {
	branch *root;
};

branch *newBranch(int val) {
	branch *b = (branch*) malloc (sizeof(branch));
	b -> data = val;
	b -> visited = 0;
	b -> left = NULL;
	b -> right = NULL;
	return b;
}

void showRec(branch *b, int space) {
	for (int i = 0; i < space; i++) {
		if (i < space - 1)
			cout << "  ";
		else
			cout << "\u21B3 ";
	}
	cout << b -> data << endl;
	if (b -> left != NULL) {
		showRec(b -> left, space+1);
	}
	if (b -> right != NULL) {
		showRec(b -> right, space+1);
	}
}

void showTree(tree *t) {
	branch *b = t -> root;
	showRec(b, 0);
}

void addValIter(tree *t, int val) {
	cout << 1 << endl;
	if (t -> root == NULL) {
		t -> root = newBranch(val);
		return;
	}
	cout << 2 << endl;
	branch *b = t -> root;
	cout << 3 << endl;
	while(b != NULL) {
		if(val < b->data){
			if(b->left==NULL){
				b->left=newBranch(val);
				break;
			}else{
				b=b->left;
			}
		}
		else{
			if(b->right==NULL){
				b->right=newBranch(val);
				break;
			}else{
				b=b->right;
			}
		}
	}
}

void recAddVal(branch *b, int val) {
	if (val >= b -> data && b ->right != NULL)
		recAddVal(b -> right, val);
	else if (val < b -> data && b ->left != NULL)
		recAddVal(b -> left, val);
	if (b ->left == NULL || b ->right == NULL) {
		if (val >= b -> data) {
			b -> right = newBranch(val);
		} else {
			b -> left = newBranch(val);
		}
	}
}

void addValRec(tree *t, int val) {
	recAddVal(t -> root, val);
}

int searchMin(tree *t) {
	branch *b = t -> root;
	while (b -> left != NULL) {
		b = b -> left;
	}
	return b -> data;
}

int recDeepness(branch *b) {
	if (b -> left != NULL && b -> right != NULL) {
		return 1 + max(recDeepness(b -> left), recDeepness(b -> right));
	} else if (b -> right != NULL) {
		return 1 + recDeepness(b ->right);
	} else if (b -> left != NULL) {
		return 1 + recDeepness(b -> left);
	} else {
		return 1;
	}
}

int deepnessRec(tree *t) {
	return recDeepness(t -> root);
}

int deepnessIter(tree *t) {
	branch *b = t -> root;
	int max = 0;
	int nb = 0;
	while (b && !b -> visited) {
		if (b -> left && !b -> left->visited) {
			nb++;
			b = b -> left;
		} else if (b -> right && !b -> right->visited) {
			nb++;
			b = b -> right;
		} else {
			nb++;
			if (nb > max)
				max = nb;
			nb = 0;
			b -> visited = 1;
			b = t -> root;
		}
	}
	return max;
}

int recContains(branch *b, int val){
	if(b->data!=val){
			if (val < b -> data && b->left !=NULL){
				return (b->left, val);
			}

			else if (val < b -> data && b->right !=NULL){
					return (b->right, val);
			}
			else
				return 0;
	} else
	return 1;
}

int contains(tree *b, int val){
	return recContains(b -> root, val);
}

branch *findMin(branch *b) {
	while (b -> left != NULL) {
		b = b -> left;
	}
	return b;
}

branch* recDel(branch *b, int val) {
	if (b == NULL)
		return NULL;
	if (val < b -> data) {
		b->left = recDel(b->left, val);
	} else if (val > b->data) {
		b->right = recDel(b->right, val);
	} else {
		if (b->left == NULL && b->right == NULL) {
			delete(b);
			b = NULL;
		}
		else if (b->left == NULL) {
			branch *temp = b;
			b = b->right;
			delete temp;
		}
		else if (b->right == NULL) {
			branch *temp = b;
			b = b->left;
			delete temp;
		}
		else {
			branch *temp = findMin(b -> right);
			b->data = temp->data;
			b->right = recDel(b->right, temp->data);
		}
	}
	return b;
}

void del(tree *t, int val) {
	if(t -> root -> left == NULL){
		t ->root = t-> root -> right;
	}
	recDel(t -> root, val);
}

void sort(int tab[], int n){
	tree *t = (tree*) malloc (sizeof(tree));
	t -> root = newBranch(tab[0]);
	for(int i =1; i<n; i++){
		addValIter(t,tab[i]);
	}
	for(int i=0; i<n;i++){
		int min=searchMin(t);
		cout<<min<<" ";
		del(t, min);
	}
	cout << endl;
}

int main() {
	const int size=10;
	int tab1[size]={3,1,2,5,4,9,7,9,8,4};
	sort(tab1, size);
	int tab2[size]={3,1,2,5,4,10,7,7,10,4};
	sort(tab2, size);
	return 0;
}