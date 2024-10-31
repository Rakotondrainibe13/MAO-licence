#include<stdio.h>
#include<math.h>
float f(float x);
void displayResult(float a,float b,int n,float aire);
float trapezes(float a,float b,int n);
int main()
{
	printf("calcul de l'integrale de f dans [a; b]\n ");
	//entree des donnees
      
	float a=0, b=2.35619;					   //BORNE DE L'INTEGRALE	                    
	float aireN1=555,aireN2=888;						   //l'intégr. à clalculer							
	int n=12;              				   // le nb sous-int de 
	float ep=10e-5;				
   
	//traitement:methode des trapèzes
	while(1) {
	  aireN1 = trapezes(a,b,n);
	  aireN2 = trapezes(a,b,n+10);
      float difference= aireN1-aireN2;
	//sortie des resultats
	 

	 if(fabs(difference)<ep)
	 {
		 displayResult(a,b,n,aireN1);
		 break;
	 }
	 n +=10;
  }
	return 0;
}

float trapezes(float a,float b,int n){
float aire=999;			//l'intégrale à calculer	
float h=1;				//pas de discrétisation
float s=0,xi=a;
h=(b-a)/n;
s=0;
for(int i=0;i<n;i++){
	xi += h;
	s += f(xi);
	}
	aire=h/2.*(f(a)+2*s+f(b));
return aire;
}
void displayResult(float a,float b,int n,float aire)
{
	printf("Intég. de f dans [%g ;%g ]=%g\n",a,b,aire);
	printf("\ten utilisant %d sous-interv.\n",n);
}
float f(float x)
{
	return sin(x);
}
