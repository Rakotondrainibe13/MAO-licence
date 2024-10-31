#include <stdio.h>
#include <stdlib.h>

void displayResult1(int dim,float* pA,float *B,float *x);
void displayResult2(int dim,float** A,float *B,float *x);
float** triangularisation(int dim,float** A,float *B);
float* gauss(int dim,float** A,float *B);
int main(){
	
	printf("Resolution de Ax=B par la methode de Gauss\n");
	
//Entree des donnees
	int dim=3;
	//float A[3][3]={{4,8,12},{3,8,13},{2,9,18}}; //la matrice
	//float B[3]={4,5,11}; 						//le second membre
	//float x[3]={343,0,434};					//la solution a trouver
	//float* pA=NULL;						//Pointeur de float pour se deplacer dans A
	
	float *b=NULL, *X=NULL;
	b=malloc(dim*sizeof(float));
	X=malloc(dim*sizeof(float));
	b[0]=4;b[1]=5;b[2]=11;
	X[0]=545;X[1]=55;X[2]=45;
	
	float **A=NULL;
	float **aTriangularise=NULL;
	A=malloc(dim*sizeof(float*));
	for(int i=0;i<dim;i++)
	{
		A[i]=malloc(dim*sizeof(float));
	}
	A[0][0]=4;A[0][1]=8;A[0][2]=12;
	A[1][0]=3;A[1][1]=8;A[1][2]=13;
	A[2][0]=2;A[2][1]=9;A[2][2]=18;
	
//Traitement : Methode de Gauss
	aTriangularise=triangularisation(dim,A,b);
	X=gauss(dim,aTriangularise,b);
	
//Sortie de resultat
	//pA=&A[0][0];
	displayResult2(dim,A,b,X);
	
	return 0;
}
float* gauss(int dim,float** A,float *B)
{
	float* x=malloc(dim*sizeof(float));
	float somme=0;
	for(int i=dim-1;i>=0;i--)
	{
		for(int j=i+1;j<dim;j++)
		{
			somme += A[i][j]*x[j];
		}
		x[i]=(1/A[i][i])*(B[i]-somme);
		somme=0;
	}
	return x;
}
float** triangularisation(int dim,float** A,float *B)
{
	for(int k=0;k<=dim-2;k++)
	{
		for(int i=k+1;i<=dim-1;i++)
		{
			for(int j=k+1;j<=dim-1;j++)
			{
				A[i][j]=A[i][j]-(A[i][k]/A[k][k])*A[k][j];
			}
			B[i]=B[i]-(A[i][k]/A[k][k])*B[k];
			A[i][k]=0;
		}
	}
	return A;
}
void displayResult2(int dim,float** A,float *B,float *x)
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
	printf("Le second membre\n");
	for(int i=0;i<dim;i++)
	{
		printf("%g\n",B[i]);
	}
	printf("La solution:\n");
	for(int i=0;i<dim;i++)
	{
		printf("%g\n",x[i]);
	}
}
void displayResult1(int dim,float *pA,float *B,float *x)
{
	printf("La matrice A du probleme:\n");
	int k=-1;
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			//printf("%g\t",A[i][j]);
			k++;
			printf("%g\t",pA[k]);
		}
		printf("\n");
	}
	printf("Le second membre\n");
	for(int i=0;i<dim;i++)
	{
		printf("%g\n",B[i]);
	}
	printf("La solution:\n");
	for(int i=0;i<dim;i++)
	{
		printf("%g\n",x[i]);
	}
}
