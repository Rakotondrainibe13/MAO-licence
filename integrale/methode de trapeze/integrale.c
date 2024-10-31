#include <stdio.h>
#include <math.h>

float f(float x);
void displayResult(float a,float b,int n,float aire);
float trapezes(float a,float b,float n);
int main()
{
	printf("calcul integrale de f dans [a;b]\n");
	///Les donnees
	float a=0,b=2.356194; // les bornes d'integrales
	float aire=0; //l'integrale a calculer
	int n=20; //le nombre de sous intervalles
	
	///traitement:Methode de trapezes
	while(1)
	{
		printf("Entrer n: ");
		scanf("%d",&n);
		///n +=10;
		if(n<=0 ) break;
		aire = trapezes(a,b,n);
	
		///sortie de resultat
		displayResult(a,b,n,aire);
	}	
	return 0;
	
	
}
float trapezes(float a,float b,float n){
	float aire=10.02;
	float h=1;
	float s=0,xi=a;

	h=((b-a)/n);

	for(int i=1;i<n;i++)
	{
		xi +=h;
		s +=f(xi);	
	}
	aire=((h/2)*(f(a)+2*s+f(b)));
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
