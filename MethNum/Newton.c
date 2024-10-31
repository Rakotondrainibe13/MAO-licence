#include <stdio.h>
#include <math.h>


// Prototypes
float fonction(float x);
float derive(float x);
float newton(float a, float b, float epsilon);

// Main
int main() {
	printf("Soit a trouver ksi tel que f(ksi) = 0 sur l'intervalle [a ; b]\n");

// Entree des donnees
	float a = 0, b = 1;												// bornes de l'intervalle [a; b] 
	float ksi = 0;														// la solution a trouver					
	float epsilon = pow(10, -6);										// precision														
	
// Traitement: par la methode de Newton
	ksi = newton(a, b, epsilon);
	
// Sortie des resultats
	printf("la solution de f en [%f ; %f] en est %f", a, b, ksi);
	return 0;
}

// Definitions de fonction
float fonction(float x) {
// f(x) = Expo(-x) - x
	float result = 0;
	result = exp(-x) - x;
	return result;
}

float derive(float x) {
// f'(x) = -Expo(-x) - 1
	float result = 0;
	result = - exp(-x) - 1;
	return result;
}

float newton(float a, float b, float epsilon) {
	float ksi = 0;
	float x0 = 0, x1 = 0;
	int operation = 1;
	
	x0 = a;
	x1 = x0 - (fonction(x0) / derive(x0));
	
	if((x1 - a) * (x1 - b) > 0) {
		x0 = b;
		x1 = x0 - (fonction(x0) / derive(x0));
	}
	
	while (fabs(x1 - x0) > epsilon) {
		x0 = x1;
		x1 = x0 - (fonction(x0) / derive(x0));
		ksi = x1;
		operation++;
		printf("Nombre d'operation: %i\n", operation);
	}
	return ksi;
}
