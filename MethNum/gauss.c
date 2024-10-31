#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float** newMat(int dim);
void getData(int *dim,float ***matrice,float **b,int** p,float **x);
void displayResult(int dim,float **matrice,float *b,int* p,float *x);
float* newVect(int dim);
int* newIVect(int dim);
float** newMat(int dim);
void gauss(int dim,float** A,float* b,int* p,float* x);
void solveTriangSup(int dim,float** A,float* b,int* p,float* x);

int main(){
	printf("Resolution de A.x=b par la meth. de Gauss :\n");
	///Entree des donnees
	int dim; 							//dimension matrice
	float **matrice = NULL; 			//la matrice du probleme
	float *b = NULL; 					//le second membre
	float *x = NULL; 					//la solution a trouver
	int* p = NULL;						//tableau de pointeur de ligne
	getData(&dim,&matrice,&b,&p,&x);		//donne a getData les adresses a utiliser
	
	///traitement des donnees
	gauss(dim,matrice,b,p,x);

	///sortie des resultats
	displayResult(dim,matrice,b,p,x);

	/*On libere la memoire du pointeur dernierement allouee d'abord et ainsi de suite*/
	free(x);
	free(b);
	for(int i = 0; i < dim; i++)
		free(matrice[p[i]]);
	free(matrice);
	free(p);
	return 0;
}

void solveTriangSup(int dim,float** A,float* b,int* p,float* x){
	float s = 0;
	for(int i = dim-1 ; i >= 0; i--){
		s = 0;
		for (int j = i+1; j < dim; ++j)
		{
			s += A[p[i]][j]*x[j];
		}
		x[i] = (b[p[i]] - s)/A[p[i]][i];
	}
}

void gauss(int dim,float** A,float* b,int* p,float* x)
{
	x[0] = 8;x[1] = 9;x[2] = 10;
	float piv = 0;
	int lpiv = 0;
	//Triangularisation de A
	for (int k = 0; k < dim-1; ++k)
	{
	//Chercher le plus grand pivot
	lpiv = p[k];
	piv = fabs(A[p[k]][k]);
	for(int i = k + 1; i < dim; i++)
	{
		if(fabs(A[p[i]][k])> piv){
			lpiv = p[i];
			piv = fabs(A[p[i]][k]);
		}
	}
	//Permuter les lignes k et lpiv
		int t = 0;
		t = p[k];
		p[k] = p[lpiv];
		p[lpiv] = t;
	
		for (int i = k+1; i < dim; ++i)
		{
			for(int j = k+1; j < dim; j++)
			{
				A[p[i]][j] -= (A[p[i]][k]/A[p[k]][k]*A[p[k]][j]);
			}
			b[p[i]] -= (A[p[i]][k]/A[p[k]][k]*b[p[k]]);
			A[p[i]][k] = 0;
		}
	}

	solveTriangSup(dim,A,b,p,x);
}


void getData(int *dim,float ***matrice,float **b,int** p,float **x){
	FILE *file = NULL;
	file = fopen("data2.txt","r");
	int* pp = NULL;
	if(file != NULL){
		fscanf(file,"%d",dim);							//recupere la dimension
		float** M = newMat(*dim);						//alloue la place pour la matrice
		int i,j;							
		for(i=0;i<*dim;i++){
			for(j=0;j<*dim;j++){
				fscanf(file,"%f",&M[i][j]);				//lit les donnees ligne par ligne
			}
		}
		float *vecteur = newVect(*dim);					//alloue la place pour le second membre
		float *solution = newVect(*dim);				//alloue la place pour la solution
		pp = newIVect(*dim);							//alloue la place pour le pointeur de ligne
		for(i=0;i<*dim;i++){
			fscanf(file,"%f",&vecteur[i]);
		}
		fclose(file);
		for(int i = 0; i < *dim; i++) solution[i] = 0; //initialise le vecteur solution
		for(int i = 0; i < *dim; i++) pp[i] = i; //initialise le vecteur solution

		//Renvoie les adresses des contenus vers main
		*matrice = M;
		*b = vecteur;
		*x = solution;
		*p = pp;
	}else{
		printf("File not found\n");
		exit(1);
	}
}

float* newVect(int dim){
	float *A = NULL;
	A = malloc(dim*sizeof(float));
	return A;
}

int* newIVect(int dim){
	int *A = NULL;
	A = malloc(dim*sizeof(int));
	return A;
}

float** newMat(int dim){
	float **A = NULL;
	A = malloc(dim*sizeof(float *));
	int i;
	for(i=0;i<dim;i++){
		A[i] = malloc(dim*sizeof(float));
	}
	return A;
}

void displayResult(int dim,float **matrice,float *b,int* p,float *x){
	printf("La matrice du probleme\n");
	int i,j;
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			printf("%g\t",matrice[p[i]][j]);
		}
		printf("\n");
	}
	printf("Les second membres :\n");
	for(i=0;i<dim;i++){
		printf("%g\n",b[p[i]]);
	}
	printf("La solution x :\n");
	for(i = 0;i<dim;i++){
		printf("%g\n",x[i]);
	}
}

void problem(char* message)
{
	printf("%s\n", message);
	exit(2);
}
