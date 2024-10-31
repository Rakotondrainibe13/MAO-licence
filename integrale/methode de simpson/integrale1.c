#include <stdio.h>
#include <math.h>

float f(float x);
void displayResult(float a,float b,int n,float aire);
float simpson(float a,float b,float n);
int main()
{
	printf("calcul integrale de f dans [a;b]\n");
	///Les donnees
		// les bornes d'integrales
		               float a=0,b=2.356194;
		//l'integrale a calculer   
		               float aire=0;   
		//le nombre de sous intervalles   
		               int n=131;          
	
	///traitement:Methode de Simpson
		while(1)
		{
			printf("Entrer n: ");
			scanf("%d",&n);
			if(n<=0 ) break;
			aire = simpson(a,b,n);
	
	///sortie de resultat
		displayResult(a,b,n,aire);
	}	
	return 0;
	
	
}

float simpson(float a,float b,float n){
	float aire=10.02;
	float h=1;
	float si=0,si2=0,xi2=444,xi=a;

	h=((b-a)/n);
     xi2=a-(h/2);
	for(int i=1;i<n;i++)
	{
		xi +=h;
		si +=f(xi);	
	}
	for(int a=0;a<n;a++)
	{
		xi2 +=h;
		si2 +=f(xi2);	
	}
	aire=((h/6)*(f(a)+2*si+f(b)+4*si2));
	return aire;
}
void displayResult(float a,float b,int n,float aire)
{
	
	printf("Integrale de f dans [%g; %g]= %g\n ",a,b,aire);
	printf("\t en utilisant %d sous-interv.\n",n);
}
float f(float x)
{
	return sin(x);
}
