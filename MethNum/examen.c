#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// pow(a, b) = 'a' a la puissance 'b'

// Prototypes des fonctions
float fonction(float* coeffs, int degre, float x);
float horner(float* coeffs, int degre, float x);

int main() {
	printf("\n");

// Entree des donnees


// Traitement


// Sortie des resultats
int degre = 1;
float* coeffs = malloc((degre+1) * sizeof(float));
coeffs[0] = 1;
coeffs[1] = 1;
float x = 2;
float val = horner(coeffs, degre, x);
printf("val = %f\n", val);

// Retour de la fonction main()
	return 0;
}

float fonction(float* coeffs, int degre, float x) {
	int nombreDOperation = degre + 1;
	float result = 0;
	
	for(int i = nombreDOperation; i >= 0; i--){
		result += coeffs[i] * pow(x, i);
	}
	
	return result;																	
}

float horner(float* coeffs, int degre, float x) {
	float result = coeffs[0];
	
	if(degre == 0) {
		return result;
	}
	
	else {
		for(int i = 1; i <= degre; i++) {
			result = (result * x) + coeffs[i];
		}
	}
	
	return result;
}
