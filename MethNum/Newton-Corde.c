#include <stdio.h>
#include <math.h>

// Prototypes
float fonction(float x);
float newton(float a, float b, float epsilon);

// Main
int main() {

// Entree des donnees
	float a = -5, b = 12;													// bornes de l'intervalle				
	float epsilon = pow(10, -6);										// precision
	float ksi = 999;													// la racine a trouver														
	
// Traitement: methode de Newton (methode des cordes)
	ksi = newton(a, b, epsilon);
	printf("la racine de f dans [%f, %f] est %f\n", a, b, ksi);
	return 0;
}

// Definitions de fonction

float fonction(float x) {
// f(x) = Expo(-x) - x
	float result = 0;
	result = exp(-x) - x;
	return result;
}

float newton(float a, float b, float epsilon) {
	float x0 = 0, x1 = 0;
	
	x0 = a;
	x1 = a - ( fonction(a)*(b - a) /  (fonction(b) -fonction(a)) );
	
	if(fonction(x1) * fonction(a) < 0) {
		b = x1;
	} 
	
	else {
		a = x1;
	}
	
	while(fabs(x0 - x1) > epsilon) {
		x0 = x1;
		x1 = a - ( fonction(a)*(b - a) /  (fonction(b) -fonction(a)) );
	
		if(fonction(x1) * fonction(a) < 0) b = x1;
	
		else a = x1;
	}
	
	return x1;
}
