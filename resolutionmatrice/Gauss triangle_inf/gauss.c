#include "stdio.h"
#include "stdlib.h"

float** newMat(int dim);
void getData(int *dim, float ***A, float **b, int**p, float **x);
void displayResult(int dim,float **A,float *b, int*p, float *x);
float* newMat1(int dim);
float** newMat2(int dim);
void calculerB(int dim, float** A, float* b, float* x);
solveTriangleSup(int dim,float **a, float* b,float*x)
void gauss(int dim,float** A,float*x, float *B);
void affiche(float* tab, int taille);
void problem(char* message);
void solveTriangleInf(int dim,float** A, float*x, float *B);
void cholesky(int dim, float** A, float* b, float* x);

int main(){
	printf("Resolution de A.x=b pour A triang.inferieur\n");

///Entree des donnees
	int dim; 			// dimension matrice
	float **A = NULL; 	// la matrice du probleme
	float *b = NULL; 	// le second membre
	float *x = NULL; 	// la solution a trouver
	float *y = NULL; 	// la solution a trouver
	int* p = NULL;		// tableau de pointeur de ligne
	
	getData(&dim,&A,&b,&p, &x);
	
///traitement des donnees
	//A=triangularisation(dim,A,p,b);
	//gauss(dim,A,x,b);
	cholesky(dim, A, b, x);
///sortie des resultats
	displayResult(dim,A,b,p,x);
	
	free(x);
	free(b);
	
	return 0;
}


void getData(int *dim,float ***A,float **b, int**p, float **x){
	FILE *file = NULL;
	file = fopen("data.txt","r");
	
	if(file != NULL){
		int taille;
		fscanf(file,"%d",&taille);				// recupere la dimension
		float** M = newMat2(taille);			// alloue de la place pour la matrice
		
		for(int i=0;i<taille;i++){
			for(int j=0;j<taille;j++){
				fscanf(file,"%f",&M[i][j]);		// lit les données ligne par ligne
			}
		}
		
		float *vecteur = newMat1(taille);		// alloue de la place pour le second membre
		float *solution = newMat1(taille);		// alloue de la place pour la solution
		
		for(int i=0;i<taille;i++){
			fscanf(file,"%f",&vecteur[i]);
		}
		
		for(int i=0; i<taille; i++){
			solution[i] = 0;					// initialise le vecteur solution
		}
				
		*dim = taille;
		*A = M;
		*b = vecteur;
		*x = solution;
		
		fclose(file);
	}
	else{
		problem("Can't open file");
	}
}
void solveTriangleSup(int dim,float **a, float* b,float*x)
{
	float somme = 0;
	for(int i=dim-1;i>=0;i--)
	{
		for(int j=i+1;j<dim;j++)
		{
			somme += a[i][j]*x[j];

		}
		x[i]=(1/a[i][i])*(b[i]-somme);
		somme=0;
	}
}
void solveTriangleInf(int dim,float **a,float* b,float*x)
{
	float somme = 0;
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			somme += a[i][j]*x[j];

		}
		x[i]=(1/a[i][i])*(b[i]-somme);
		somme=0;
	}
}
float** transposition(int dim,float** a)
{
	float** bt = newMat(dim);
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			bt[i][j] = a[i][j];
		}
	}

	for(int i=0;i<dim;i++)
	{
		for(int j=i;j<dim;j++)
		{
			float temp = bt[i][j];
			bt[i][j] = bt[j][i];
			bt[j][i] = temp;
		}
	}
	return bt;
}
void factorisationCholesky(int dim, float **a)
{
	float somme = 0;
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			if(j<=i)
			{
				if(i!=j)
				{
					for(int k=0;k<j;k++)
					{
						somme +=a[i][k]*a[j][k];
					}
					a[i][j] = (1/a[j][j]) * (a[i][j] - somme);
				}
				else
				{
					for(int k=0;k<i;k++)
					{
						somme +=pow(a[i][k],2);
					}
					a[i][j] = sqrt(a[i][j] - somme);
				}
				somme = 0;
			}
			else
			{
				a[i][j] = 0;
			}


		}
	}
}
void cholesky(int dim,float** a,float* b,float* x)
{
	factorisationCholesky(dim,a);

	float** bt = transposition(dim,a);
	// Resolution de B.y = b
	solveTriangleInf(dim,a,b,x);
	// Resolution de Bt.x = ys
	solveTriangleSup(dim,bt,x,x);





}	
float* newMat1(int dim){
	float *A = NULL;
	A = malloc(dim*sizeof(float));
	return A;
}

float** newMat2(int dim){
	float **A = NULL;
	A = malloc(dim*sizeof(float *));
	
	if(A == NULL){
		problem("Ne peut pas allouer la Matrice");
	}
	
	int i;
	for(i=0;i<dim;i++){
		A[i] = malloc(dim*sizeof(float));
	}
	return A;
}

void displayResult(int dim,float** A,float *B, int*p, float *x)
{
	printf("La matrice A du probleme:\n");
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			printf("%g\t",A[i][j]);
		}
		printf("\n");
	}
	
	printf("\nLe second membre\n");
	affiche(B, dim);
	
	printf("\nLa solution:\n");
	affiche(x, dim);
}/*
void solveTriangleSup(int dim,float **a, float* b,float*x)
{
	float somme = 0;
	for(int i=dim-1;i>=0;i--)
	{
		for(int j=i+1;j<dim;j++)
		{
			somme += a[i][j]*x[j];

		}
		x[i]=(1/a[i][i])*(b[i]-somme);
		somme=0;
	}
}*//*
void solveTriangleSup(int dim,float** A, float*x, float *B)
{
	float s = 0;
	for(int i=dim-1;i>=0;i--)
	{
		for(int j=i+1;j<dim;j++)
		{
			s += A[i][j]*x[j];
		}
		x[i] = (B[i] - s) / A[i][i];
		s = 0;
	}
}*/
/*void solveTriangleInf(int dim,float** A, float*x, float *B)
{
	float s = 0;
	for(int i=dim-1;i>=0;i--)
	{
		for(int j=0;j<i-1;j++)
		{
			s += A[i][j]*x[j];
		}
		x[i] = (B[i] - s) / A[i][i];
		s = 0;
	}
}

void solveTriangleInf(int dim,float **a,float* x,float*b)
{
	float somme = 0;
	for(int i=0;i<dim;i++)
	{
				somme=0;
		for(int j=0;j<dim;j++)
		{
			somme += a[i][j]*x[j];

		}
		x[i]=(1/a[i][i])*(b[i]-somme);
	}
}*/
void gauss(int dim,float** A, float*x, float *B)
{
	for(int k=0;k<=dim-2;k++)
	{
		for(int i=k+1;i<=dim-1;i++)
		{
			for(int j=k+1;j<=dim-1;j++)
			{
				A[i][j]=A[i][j]-(A[i][k]/A[k][k])*A[k][j];
			}
			B[i] -= (A[i][k]/A[k][k])*B[k];
			A[i][k]=0;
		}
	}
	solveTriangleSup(dim,A,x,B);
}

void affiche(float* tab, int taille){
	for(int i=0;i<taille;i++)
	{
		printf("%g\n",tab[i]);
	}
}

void problem(char* message){
	printf("%s\n", message);
	exit(3);
}
