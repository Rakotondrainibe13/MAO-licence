#include"stdio.h"
#include"math.h"
float f(float x);
float f1(float x);
void displayResult(float a,float b,float eps,float ksi);
float newton(float a,float b,float eps);
int main(){
	printf("Trouver xi si tel que f(xi)=0\n");
	///entrée des données
		float a=0,b=1;     //l'intervalle [a;b]
		float xi=333;      //Racine
		float eps=1e-5;    //Epsilone    
	///Traitement:Methode de Newton
	    xi=newton(a,b,eps);
	///sortie des résultats
	    displayResult(a,b,eps,xi);
return 0;
}
float f(float x){
	return exp(-x)-x;
}
float f1(float x){
	return -exp(-x)-1;
}
void displayResult(float a,float b,float eps,float xi){
	printf("La racine de f dans [%g ;%g ] a epsilon=%g\n",a,b,eps);
	printf("\est %g \n",xi);
}
float newton(float a,float b,float eps)
{
	float xo=a;
	float x1=a-(f(a)/f1(a));
	if((x1-a)*(x1-b)>0) {
	    xo=b;
		x1=b-(f(b)/f1(b));
	}
	while(fabs(x1-xo)>eps){
	     xo=x1;
	     x1=xo-(f(xo)/f1(xo));
	}
	return x1;
}
