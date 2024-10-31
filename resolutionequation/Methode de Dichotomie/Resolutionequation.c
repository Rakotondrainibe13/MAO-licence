#include<stdio.h>
#include<math.h>
float f(float x);
void displayResult(float a,float b,float e,float ksi);
float dichotomie(float a,float b,float e);
int main(){
	printf("Chercher la racine d'une equation f(x)=0 dans un intervalle [a;b]\n");
	///entrée des données
		float a=2.5,b=4;     //l'intervalle [a;b]
		float ksi=333;         //Racine
		float e=1e-6;     //Epsilone    
	///Traitement:Methode de Dichotomie
	 ksi=dichotomie(a,b,e);
	///sortie des résultats
	    displayResult(a,b,e,ksi);
	return 0;
	}
float f(float x){
	return x-2-log(x);
}
void displayResult(float a,float b,float e,float ksi){
	printf("La racine de f dans [%g ;%g ] a epsilon=%g\n",a,b,e);
	printf("\est %g \n",ksi);
}
float dichotomie(float a,float b,float e){
    float ksi=1234;
    float  dn=fabs(b-a);
    while(dn>e)
    {
		ksi=(a+b)/2;
		if(f(a)*f(ksi)<=0) b=ksi;
		else a=ksi;
		dn=fabs(b-a);
	}
	return ksi;
}
