#include <stdio.h>
#include <math.h>

float f(float x);
float calculerH(float a, float b, float n);

int main() {
	printf("Calcul de l'intervalle de la fonction f sur [a,b] par la methode de Simpson\n");
	
// Entrees des donnees
	float a = 0, b = 2.356; 	// les bornes de l'intervalle
	float fDeA = 1;				// image de a par f
	float fDeB = 1;				// image de b par f
	float premierSomme = 1;		// premier boucle
	float deuxiemeSomme = 1;	// deuxieme boucle
	float aire = 1;				// l'integrale a calculer
	int n = 100;				// nombre de sous-intervalles
	float h = 1;				// distance entre xi et xi+1;
	float xiMilieu = 1;			// le premier milieu entre a et x1
	float xi = 1;				// xi
	
// Traitement : Methode de Simpson
	h = calculerH(a, b, n);
	xi = a + h;
	fDeA = f(a);
	fDeB = f(b);
	
// premier boucle pour la somme des f(xi)
	for(int i = 1; i < n-1; i++) {
		premierSomme += f(xi);
		xi += h;
	}
	
// deuxieme boucle pour la somme des f(xi+1/2)
	xiMilieu = a + (h / 2);
	for(int i = 0; i < n-1; i++) {
		deuxiemeSomme += f(xiMilieu);
		xiMilieu += h;	
	}
	
	aire = fDeA + fDeB + 2 * premierSomme + 4 * deuxiemeSomme;
	aire = aire * (h / 6);
	
// Sortie des resultats
	printf("Aire = %f\n", aire);
	
// Retour de la fonction main()
	return 0;
}

float f(float x) {
	return sin(x);
}

float calculerH(float a, float b, float n) {
	float h = (b - a) / n;
	return h;
}
