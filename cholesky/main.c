#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void displayResult2(int dim,float** a,float* b,int *p,float* x);
float **newMat(int dim);
float *newVect(int dim);
int *newIvect(int dim);
void problem(char* message);
void myData(int *dim,float***a, float**b,int **p,float** x);
void solveTriangleSup(int dim,float **a, float* b,float*x);
void solveTriangleInf(int dim,float **a, float* b,float*x);
void cholesky(int dim,float** a,float* b,float* x);
float** transposition(int dim,float** a);
void factorisationCholesky(int dim,float ** a);
int main()
{
	printf("CHERCHER LE VECTEUR X TEL QUE A * X = B \n");

	//DONNEES
	int dim = 69; 								// la dimension de la matrice

	float *b=NULL; 								// la matrice du second membre
	float *x=NULL; 								// la matrice a trouver
	float **a=NULL;								// la matrice principale
	int *p=NULL;								// tableau de pointeur de ligne

	//accessFichier(&dim, &a, &b, &x);
	//getData(&dim, &a, &b, &x);
	myData(&dim, &a, &b ,&p, &x);





/*	float* pa=NULL;								// pointeur de float pour se deplacer dans a */

	//TRAITEMENT


	/*atri=malloc(dim*sizeof(float*));
	for(int i=0;i<dim;i++)
	{
		atri[i]=malloc(dim*sizeof(float));
	}
	for(int j1=0;j1<dim;j1++)
	{
		for(int j2=0;j2<dim;j2++)
		{
			atri[j1][j2]=a[j1][j2];
		}
	}*/

	//gauss(&dim, &a, &b, &x);
	//gauss2(dim, a, b, p, x);


	cholesky(dim,a,b,x);


	//SORTIE DE RESULTAT
	//pa=&a[0][0];
	displayResult2(dim,a,b,p,x);

	free(x);
	free(b);
	for(int i=0;i<dim;i++)
	{
		free(a[p[i]]);
	}
	free(a);
	free(p);

	return 0;
}
void displayResult2(int dim,float** a,float* b,int *p,float* x)
{
	printf("La matrice a \n");


	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			printf("%g\t",a[p[i]][j]);
		}
		printf("\n");
	}

	printf("Le second membre \n");
	for(int i=0;i<dim;i++)
	{
			printf("%g\t",b[p[i]]);

	}
	printf("\n");
	printf("La solution \n");
	for(int i=0;i<dim;i++)
	{
			printf("%g\t",x[i]);

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
void myData(int *dim,float***a, float**b,int **p,float** x)
{
	float** M=NULL, *v=NULL, *sol=NULL;
	FILE *pf=NULL;
	int* pp=NULL;

	pf=fopen("data.txt","r");
	if(pf!=NULL)
{
		fscanf(pf,"%d",dim);				//recupere la dimension
		M=newMat(*dim);						// alloue la place pour la matrice
		v=newVect(*dim);					//alloue de la place pour le second membre
		sol=newVect(*dim);					// alloue de la place pour la solution
		pp=newIvect(*dim);					// alloue de la place pour le pointeur de ligne

	for(int i=0;i<*dim;i++)
	{
		for(int j=0;j<*dim;j++)
		{
			fscanf(pf,"%f", &M[i][j]); 		// lit les données ligne par ligne
		}
	}
	for(int i=0;i<*dim;i++)
	{
		fscanf(pf,"%f",&v[i]);
	}
	fclose(pf);
	for(int i=0;i< *dim;i++)
	{
		sol[i]=0;							// initialise le vecteur solution
	}
	for(int i=0;i< *dim;i++)
	{
		pp[i]=i;							// initialise le vecteur pointeur de ligne
	}
}
	else{
			problem("Il y a des problemes");
			exit(2);
	}

// Renvoie les adresses des contenus vers main
	a[0]=M;
	b[0]=v;
	x[0]=sol;
	p[0]=pp;
}
void problem(char* message)
{
	printf("%s\n",message);
	exit(2);
}
float *newVect(int dim)
{
	float *v=NULL;
	v=malloc(dim*sizeof(float));
	if(v==NULL) problem("Ne peut pas allouer un vecteur de float");
	return v;
}
int *newIvect(int dim)
{
	int *v=NULL;
	v=malloc(dim*sizeof(int));
	if(v==NULL) problem("Ne peut pas allouer un vecteur d'entier");
	return v;
}
float **newMat(int dim)
{
	float **M=NULL;
	M=malloc(dim*sizeof(float*));
	if(M==NULL) problem("Ne peut pas allouer une matrice");
	for(int i=0;i<dim;i++)
	{
		M[i]=malloc(dim*sizeof(float));
	}
	return M;
}
