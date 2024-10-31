#include<stdio.h>
#include<stdlib.h>
void allouerMatriceCarre(float**A,int dim);
void displayResult1(float*pA,float*b,float*x,int dim);
void displayResult2(float**A,float*b,float*x,int dim);
void getdata(float*A,int dim,float*pA);
int main(){
	printf("Resolution de A.x=b par la meth. de Gauss\n");
///entrée des données
	   int dim=3;    
	   float**A=NULL;
	   float**d=NULL;
	   float d[3][3]={{4,8,12},{3,8,13},{2,9,18}}; // la matrice adj pb
	   //float b[3]={4,5,11};         			   //le second membre
	   //float x[3]={87,654,0.555};   			   //la solution à trouver
	   float* pA=NULL;                			   //pointeur de float pour se déplacer dans A
	   pA=&d;
	   float *b=NULL,*x=NULL;
	   b=malloc(dim*sizeof(float));
	   x=malloc(dim*sizeof(float)); 
	   b[0]=4;b[1]=5;b[2]=11;
	   x[0]=87;x[1]=654;x[2]=0.555;
       getdata(A,dim,pA);
///Traitement:Méthode de Gauss
	  //Triangularisation
  
	  //Résolution

///sortie des résultats
	pA=&A[0][0];
	displayResult1(pA,b,x,dim);
return 0;
}
void displayResult1(float*pA,float*b,float*x,int dim){
		printf("La matrice A \n");
		int k=-1;
		for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			  k++;
			//printf("%g\t",*(pA+k));
			  printf("%g\t",pA[k]);
			}
			printf("\n");
		}
		printf("Le second membre \n");
		for(int i=0;i<dim;i++)
		printf("%g\n",b[i]);
		printf("La solution \n");
		for(int i=0;i<dim;i++)
		printf("%g\n",x[i]);
	}
void displayResult2(float**A,float*b,float*x,int dim){
		printf("La matrice A \n");
		for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			 printf("%g\t",A[i][j]);
			}
			printf("\n");
		}
		printf("Le second membre \n");
		for(int i=0;i<dim;i++)
		printf("%g\n",b[i]);
		printf("La solution \n");
		for(int i=0;i<dim;i++)
		printf("%g\n",x[i]);
	}
void allouerMatriceCarre(float**A,int dim){
		A=malloc(dim*sizeof(float*));
		for(int i=0;i<dim;i++)
		{
			A[i]=malloc(dim*sizeof(float));
		}
	}
void getData(int *dim,float ***A,float **b,float **x){
		float * sol=NULL;
	     FILE *pf=NULL;
	     pf=fopen("donnees.txt","r");
	     if(pf!=NULL){
			fscanf(pf,"%d",dim);   				//récuperer la dimension
			 M=newMat(*dim);					//alloue de la place pour la matrice
			 v=newVect(*dim);					//alloue de la place pour le second membre
			 sol = newVect(*dim);   			//alloue de la place pour la solution 
			 for(int i=0;i< *dim;i++)			
			      fscanf(pf,"%f",&v[i]);		//lit les données ligne par ligne
			fclose(pf);
			for(int i=0;i< *dim ;i++) sol[i]=0; //initialise le vecteur solution
			 }
			 else{
				 problem("Can't open file");
				 exit(2);
			 }
	}
