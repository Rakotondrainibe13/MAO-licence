#include <stdio.h>
#include <stdlib.h>
#include <math.h>
float** newMat(int dim);
void getData(int *dim,float ***A,float **b,int**p,float **x);
void displayResult(int dim,float **A,float *b,int*p,float *x);
float* newMat1(int dim);
float** newMat2(int dim);
float** triangularisation(int dim,float** A,int*p,float *B);
void solveTriangleInf(int dim,float**A,float*B,int*p,float*x);
void gauss(int dim,float** A,float *B,int *p,float*x);
void problem(char* message);
int* newInvect(int dim);
int main(){
	printf("Resolution d'un systeme d'equation lineaire par la meth de Gauss\n");
///Entree des donnees
	int dim; //dimension matrice
	float **A = NULL; // adresse la matrice du probleme
	float *b = NULL; //adresse le second membre
	float *x = NULL; //adresse la solution a trouver
	int*p=NULL;      //tableau de pointeur de ligne
	int i,j;
	getData(&dim,&A,&b,&p,&x);
	
///traitement des donnees
	gauss(dim,A,b,p,x);
///sortie des resultats
	displayResult(dim,A,b,p,x);
	free(b);
	free(x);
	for(int i=0;i<dim;i++)
	   free(A[i]);
    free(A);
    free(p);
	return 0;
}


void getData(int *dim,float ***A,float **b,int**p,float **x){
	FILE *file = NULL;
	int * pp=NULL;
	file = fopen("donnes.txt","r");
	if(file != NULL){
		int taille;
		fscanf(file,"%d",&taille);         //récuperer la taille
		float** M = newMat2(taille);       //alloue de la place pour la matrice
		int i,j;
		for(i=0;i<taille;i++){
			for(j=0;j<taille;j++){
				fscanf(file,"%f",&M[i][j]); //lit les données ligne par ligne
			}
		}
		float *vecteur = newMat1(taille);	//alloue de la place pour le second membre
		float *solution = newMat1(taille);	//alloue de la place pour la solution
		pp=newInvect(taille);				//alloue de la place pour le pointeur de ligne
		for(i=0;i<taille;i++){
			fscanf(file,"%f",&vecteur[i]);
			pp[i]=i;
		}
		*dim = taille;
		*A = M;
		*b = vecteur;
		*x = solution;
		*p= pp;
		fclose(file);
	}else{
		problem("Can't open file\n");
		exit(2);
	}
}

float* newMat1(int dim){
	float *A = NULL;
	A = malloc(dim*sizeof(float));
	return A;
}
int* newInvect(int dim){
	int *A = NULL;
	A = malloc(dim*sizeof(int));
	return A;
}
float** newMat2(int dim){
	float **A = NULL;
	A = malloc(dim*sizeof(float *));
	int i;
	for(i=0;i<dim;i++){
		A[i] = malloc(dim*sizeof(float));
	}
	return A;
}
void displayResult(int dim,float **A,float *b,int*p,float *x){
	printf("La matrice du probleme\n");
	int i,j;
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			printf("%g\t",A[p[i]][j]);
		}
		printf("\n");
	}
	printf("Les second membres :\n");
	for(i=0;i<dim;i++){
		printf("%g\n",b[i]);
	}
		printf("La solution :\n");
	for(i=0;i<dim;i++){
		printf("%g\n",x[i]);
	}
}
void gauss(int dim,float** A,float *B,int *p,float*x)
{
	float piv=0;
	int lpiv=0;
/// Triangularisation
	for(int k=0;k<=dim-2;k++)
	{
///chercher le plus grand pivot
  lpiv=p[k];
  piv=fabs(A[p[k]][k]); 
  for(int i=k+1;i<dim;i++){
	  if(fabs(A[p[i]][k])> piv){
		  lpiv=p[i];
		  piv =fabs(A[p[i]][k]);
		  }
	  }
/// permuter les lignes k et lpiv
   int t=0;
   t=p[k];
   p[k]=p[lpiv];
   p[lpiv]=t;
///Elimination

		for(int i=k+1;i<=dim-1;i++)
		{
			for(int j=k+1;j<=dim-1;j++)
			{
				A[p[i]][j]=A[p[i]][j]-(A[p[i]][k]/A[p[k]][k])*A[p[k]][j];
			}c
			B[p[i]] -=(A[p[i]][k]/A[p[k]][k])*B[p[k]];
			A[p[i]][k]=0;
		}
	}
	/// Résolution du systéme triangulaire
	solveTriangle(dim, A, B,p, x);
}
void solveTriangleInf(int dim,float**A,float*B,int*p,float*x)
{
	float s=0;
	for(int i=0;i<=dim-1;i++){
		s=0;
		for(int j=i+1;j<dim; j++)
			s += A[p[i]][j]*x[j];
		x[i]=(B[p[i]]-s)/A[p[i]][i];
		}
	}
float** triangularisation(int dim,float** A,int*p,float *B)
{
	for(int k=0;k<=dim-2;k++)
	{
		for(int i=k+1;i<=dim-1;i++)
		{
			for(int j=k+1;j<=dim-1;j++)
			{
				A[p[i]][j]=A[p[i]][j]-(A[p[i]][k]/A[p[k]][k])*A[p[k]][j];
			}
			B[p[i]]=B[p[i]]-(A[p[i]][k]/A[p[k]][k])*B[p[k]];
			A[p[i]][k]=0;
		}
	}
	return A;
}
void problem(char* message){
	printf("%s\n",message);
	exit(2);
	}
/*float* resolution(int dim,float **matrice,float *vecteur){
	float *solution = malloc(dim*sizeof(float));
	int i;
	for(i=0;i<dim;i++){
		solution[dim-1] = (1/matrice[dim-1][dim-1])*();
	}
}*/
