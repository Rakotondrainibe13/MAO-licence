#include"stdio.h"
#include"math.h"
float f(float x);
float f1(float x);
void displayResult(float a,float b,float eps,float ksi);
float newtonpentefixe(float a,float b,float eps);
int main(){
	printf("Trouver xi si tel que f(xi)=0\n");
	///entrée des données
		float a=1.01,b=5;     //l'intervalle [a;b]
		float xi=333;      //Racine
		float eps=1e-6;    //Epsilone    
	///Traitement:Methode de Newton pentefixe
	    xi=newtonpentefixe(a,b,eps);
	///sortie des résultats
	    displayResult(a,b,eps,xi);
return 0;
}
float f(float x){
	return x-2-log(x);
}
void displayResult(float a,float b,float eps,float xi){
	printf("La racine de f dans [%g ;%g ] a epsilon=%g\n",a,b,eps);
	printf("\est %g \n",xi);
}
float newtonpentefixe(float a,float b,float eps)
{
	float xo=a;
	float p=(f(b)-f(a))/(b-a);
	float x1=a-(f(a)/p);
	if((x1-a)*(x1-b)>0) {
	    xo=b;
		x1=b-(f(b)/p);
	}
	while(fabs(x1-xo)>eps){
	     xo=x1;
	     x1=xo-(f(xo)/p);
	}
	return x1;
