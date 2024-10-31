#include <stdio.h>
#include <math.h>

// Prototypes
float fonction(float x);
float dichotomie(float a, float b, float epsilon);
void afficherResultat(float a, float b, float ksi, float epsilon);

// Main
int main() {	
	printf("Resolution de f(x) = 0 dans l' intervalle [a ; b]\n");
	
// Entree des donnees
	float epsilon = pow(10, -6);										// precision 
	float a = 0;														// borne gauche de l' intervalle
	float b = 5;														// borne droite de l' intervalle
	float ksi = 0;														// solution de la f dans [a ; b]	
	
// Traitement : methode de Dichotomie
	ksi = dichotomie(a , b, epsilon);

// Sortie des resultats
	afficherResultat(a, b, ksi, epsilon);
	
	return 0;
}

float fonction(float x) {
// f(x) = x - 2 - log(x)
	float result = 0;
	result = x - 2 - log(x);
	return result;
}

float dichotomie(float a, float b, float epsilon) {
	float x = 0;														// milieu de a et b
	
	while(fabs(b - a) > epsilon) {
		x = (a + b) / 2;
		if(fonction(a) * fonction(x) <= 0) {
			b = x;
		} else {
			a = x;
		}
	}
	
	return x;
}

void afficherResultat(float a, float b, float ksi, float epsilon) {
	printf("La racine de f dans l' intervalle [%f ; %f] est egale a %f a %f pres\n", a, b, ksi, epsilon);
}

