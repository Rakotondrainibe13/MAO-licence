#include <stdio.h>
#include <stdlib.h>

// Prototypes de fonctions
void displayResult(int dim, float** A, float* b, float* x);
void problem(char* erreur);
float** newMat(int dim);
float* newVect(int dim);
void getData(int* dim, float*** A, float** b, float** x);
void calculerB(int dim, float** A, float* b, float* x);
void solveTriangSup(int dim, float** A, float* b, float* x);
void solveTriangInf(int dim, float** A, float* b, float* x);
void gauss(int dim, float** A, float*b, float* x);
void cholesky(int dim, float** A, float* b, float* x);
void displayResultCholesky(int dim, float** A, float* b, float* x);

// Main
int main() {
	printf("Resolution de A.x = b par la methode de Gauss\n");

// Donnees
	int dim = 3;														// dimension de la matrice	
	float** A = newMat(dim);											// matrice du probleme
	float* b = newVect(dim);											// second membre
	float* x = newVect(dim);											// pointeur pour se deplacer dans A 
	getData(&dim, &A, &b, &x);											// imporatation des données depuis nos fichiers				
			
// Traitement: methode de Gauss
	//gauss(dim, A, b, x);
	cholesky(dim, A, b, x);

// Affichage des resultats
	printf("Le systeme: \n");
	displayResult(dim, A, b, x);
	
// Liberation de la memoire
	free(x);
	free(b);
	for(int i = 0; i < dim; i++)
		free(A[i]);
	free(A);
	
	return 0;
}

// Definitions de fonctions
void displayResult(int dim,float **matrice,float *b,float *x) {
	printf("La matrice du probleme\n");
	int i,j;
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			printf("%g\t",matrice[i][j]);
		}
		printf("\n");
	}
	printf("Les second membres :\n");
	for(i=0;i<dim;i++){
		printf("%g\n",b[i]);
	}
	printf("La solution x :\n");
	for(i = 0;i<dim;i++){
		printf("%g\n",x[i]);
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

void problem(char* erreur) {
	printf("%s\n", erreur);
	exit(2);
}

void getData(int* dim, float*** A, float** b, float** x) {
	float** M = NULL, *v = NULL, *sol = NULL;
	FILE *pf = NULL;
	
	pf = fopen("data3.txt", "r");
	if (pf != NULL) {
		fscanf(pf, "%d", dim);											// recuperation de la dimension
		M = newMat(*dim);												// allocation de la matrice
		v = newVect(*dim);												// allocation du vecteur second membre
		sol = newVect(*dim);											// allocation du vecteur solution
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
		*A = M;
		*b = v;
		*x = sol;
	}
	else {
		problem("Ouverture du fichier impossible");
		exit(2);
	}
}

void gauss(int dim, float** A, float*b, float* x) {
//Triangularisation de A
	for(int k = 0; k < dim - 1; k++) {
		for(int i = k + 1; i < dim; i++) {
			for(int j = k + 1; j < dim; j++) {
				A[i][j] -= ((A[i][k] / A[k][k]) * A[k][j]);
			}
			b[i] -= ((A[i][k] / A[k][k]) * b[k]);
			A[i][k] = 0;
		}
	}
	
//Resolution du systeme triangulaire
	solveTriangSup(dim, A, b, x);
}

void calculerB(int dim, float** A, float* b, float* x) {
	float s = 0;
	for(int i = 0; i < dim; i++) { 
		for(int j = 0; j < dim; j++) { 
			s = 0;
			
			for(int k = 0; k < j; k++) {
				s += A[i][k] * A[j][k];
			}

			if(i == j) {
				A[i][j] = sqrt(A[i][j] - s);
			} else if(j < i) {
				A[i][j] = (A[i][j] - s) / A[j][j];
			} else {
				A[i][j] = 0;
			}
		}
	}
}	

void solveTriangSup(int dim, float** A, float* b, float* x) {
	float s = 0;
	for(int i = dim - 1; i >= 0; i--) {
		s = 0;
		for(int j = i + 1; j < dim; j++) {
			s += A[i][j] * x[j];
		}
		x[i] = (b[i] - s) / A[i][i];
	}
}

void solveTriangInf(int dim, float** A, float* b, float* x) {
	float s = 0;
	for(int i = 0; i < dim; i++) {
		s = 0;
		for(int j = 0; j < i; j++) {
			s += A[i][j] * x[j];
		}
		x[i] = (b[i] - s) / A[i][i];
	}
}

void transpose(int dim, float** matrix) {
	for(int i = 0; i < dim; i++) {
		for(int j = 0; j < dim; j++) {
			matrix[i][j] = matrix[j][i];
		}
	}
}

void cholesky(int dim, float** A, float* b, float* x) {
	calculerB(dim, A, b, x);
	solveTriangInf(dim, A, b, x);
	transpose(dim, A);
	solveTriangSup(dim, A, x, x);
}

void displayResultCholesky(int dim, float** A, float* b, float* x) {

}
