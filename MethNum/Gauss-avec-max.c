#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Prototypes de fonctions
void displayResult(int dim, float** A, float* b,  int* p, float* x);
void problem(char* erreur);
float** newMat(int dim);
float* newVect(int dim);
int* newIVect(int dim);
void getData(int* dim, float*** A, float** b, int** p, float** x);
void gauss(int dim, float** A, float*b, int* p, float* x);
void solveTriangSup(int dim, float** A, float*b, int* p, float* x);

// Main
int main() {
	printf("Resolution de A.x = b par la methode de Gauss\n");

// Donnees
	int dim = 3;														// dimension de la matrice	
	float** A = newMat(dim);											// matrice du probleme
	float* b = newVect(dim);											// second membre
	float* x = newVect(dim);
	int* p = NULL;														// tableau de pointeur de ligne 
	getData(&dim, &A, &b, &p, &x);					
			
// Traitement: methode de Gauss
	gauss(dim, A, b, p, x);

// Affichage des resultats
	printf("Le systeme: \n");
	displayResult(dim, A, b, p, x);
	
// Liberation de memoires
	free(x);
	free(b);
	for(int i = 0; i < dim; i++) {
		free(A[i]);
	}
	free(A);
	
	return 0;
	
}

// Definitions de fonctions
void displayResult(int dim, float** A, float* b, int* p, float* x) {
	for(int i = 0; i < dim; i++) {
		for(int j = 0; j < dim; j++) {
			printf("%gx%i\t", A[i][j], j+1);
		}
		printf(" = %g\n", b[p[i]]);
	}
}

float** newMat(int dim) {
	float** mat = malloc(dim * sizeof(float*));
	for(int i = 0; i < dim; i++) {
		mat[i] = malloc(dim * sizeof(float));
	}
	return mat;
}

float* newVect(int dim) {
	float* vect = malloc(dim * sizeof(float));
	return vect;
}

int* newIVect(int dim) {
	int* ivect = malloc(dim * sizeof(int));
	return ivect;
}

void problem(char* erreur) {
	printf("%s\n", erreur);
	exit(2);
}

void getData(int* dim, float*** A, float** b, int** p, float** x) {
	float** M = NULL, *v = NULL, *sol = NULL;
	FILE *pf = NULL;
	int* pp = NULL;
	
	pf = fopen("data3.txt", "r");
	if (pf != NULL) {
		fscanf(pf, "%d", dim);											// recuperation de la dimension
		M = newMat(*dim);												// allocation de la matrice
		v = newVect(*dim);												// allocation du vecteur second membre
		sol = newVect(*dim);											// allocation du vecteur solution
		pp = newIVect(*dim);											// allocation du pointeur de ligne
		for(int i = 0; i < *dim; i++) {
			for(int j = 0; j < *dim; j++) {
				fscanf(pf, "%f", &M[i][j]);								
			}
		}
		for(int i = 0; i < *dim; i++) {
			fscanf(pf, "%f", &v[i]);
		}
		fclose(pf);
		for(int i = 0; i < *dim; i++) {
			sol[i] = 0;													// initialisation du vecteur solution
		}
		for(int i = 0; i < *dim; i++) {
			pp[i] = i;													// initialisation du vecteur pointeur de ligne
		}
		*A = M;
		*b = v;
		*x = sol;
		*p = pp;
	}
	else {
		problem("Ouverture du fichier impossible");
		exit(2);
	}
}

void gauss(int dim, float** A, float*b, int* p, float* x) {
	float piv = 0;
	int lpiv = 0;
	
//Triangularisation de A
	for(int k = 0; k < dim - 1; k++) {
	
// Chercher le plus grand pivot
	lpiv = p[k];
	piv = fabs(A[p[k]][k]);
	for(int i = k+1; i < dim; i++) {
		if(fabs(A[p[i]][k]) > piv) {
			lpiv = p[i];
			piv = fabs(A[p[i]][k]);
		}
	}

// Permuter les lignes k et lpiv
		for(int i = k+1; i < dim; i++) {
			for(int j = k+1; j < dim; j++) {
				A[p[i]][j] = (A[p[i]][k] / A[p[k]][k] * A[p[k]][j]);
			}
			b[p[i]] = b[p[i]] - (A[p[i]][k] / A[p[k]][k] * b[p[k]]);
			A[p[i]][k] = 0;
		}
	}
// Resolution du systeme triangulaire
	solveTriangSup(dim, A, b, p, x);
}

void solveTriangSup(int dim, float** A, float* b, int* p, float* x) {
	float s = 0;
	for(int i = dim-1; i >= 0; i--) {
		for(int j = i + 1; j < dim - 1; j++) {
			s += A[p[i]][j] * x[j];
		}
		x[i] = (1 / A[p[i]][i]) * (A[p[i]][i] - s);
		s = 0;
	}
}
