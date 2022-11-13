
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define N 4
/******La fonction ercriturePereFils permet au père de communiquer simultanement une information à tous ses fils *******/
void ercriturePereFils(int* tab_pipes_pere_fils[N],int A){
	for(int i=1 ;i<N+1; i++){
		close(tab_pipes_pere_fils[i][0]);
		write(tab_pipes_pere_fils[i][1],&A,sizeof(A));
		printf("Le père a envoyé la valeur %d au fils numero %d\n",A,i);
		close(tab_pipes_pere_fils[i][1]);
 	}
}
/***La fonction enfantParleAuPere permet au fils(joueur actuel) d'envoyer une information à son père et à son frère(processus suivant) ***/
void enfantParleAuPere(int* tab_pipes_pere_fils[N],int *tab_pipes[N],int* p1){
	void* A; 
	for(int i=1 ;i<N+1; i++){
		
     	close(tab_pipes_pere_fils[i][1]);
     	int nb_lu;
     	nb_lu = read(tab_pipes_pere_fils[i][0], &A, sizeof(A)); 
      	
        printf("Le fils numero %d  a reçu la valeur %d du père\n",i,-1*(int)nb_lu);
     	close(tab_pipes_pere_fils[i][0]);
		if(-1*(int)nb_lu == i){
/******************les commandes ci dessous dans le if sont executées que par le fils qui joue********************/
		    srand( time( NULL ) );
            int B=rand()%6+1;
            printf("La valeur aleatoire du dé que doit jouer le fils numero %d  est : %d\n",i,B);
            if(B==6){
                int reponse;
                printf("Entrer 1 si vous souhaiter sortir un pion 0 sinon\n");
                scanf("%d",&reponse);
            }
           /**********************Communication avec le frère********************/
		    close(tab_pipes[i+1][0]);
			write(tab_pipes[i+1][1],&B,sizeof(i));
			printf("Le fils numero %d a envoyé la valeur %d au fils numero  %d\n",i,B,i+1); 
	        close(tab_pipes[i+1][1]);
	       /**********************Communication avec le père********************/
	        close(p1[0]);
			write(p1[1],&i,sizeof(i));
			printf("Le fils numero %d a envoyé la valeur %d au processus père \n",i,i);
	        close(p1[1]);
	        
	        
	        
		}
 	}
	

}

/**************************************************LA FONCTION PRINCIPALE*********************************************/
int main(){
     
    int A = 1;
    int p1[2];
    int* tab_pipes[N];
    int* tab_pipes_pere_fils[N];
   /*pipe p1 permettant de transferer les informations du fils vers le père(utilisé par tous les fils)*/
    pipe(p1);

 /*Création des N pipes reliant un fils à son frère stockés dans le tableau  tab_pipes(pipe unique entre deux frères successifs).
 Création des N pipes reliant un fils à son père stockés dans le tableau  tab_pipes_pere_fils(pipe unique entre chaque fils et son père)
 */ 
 	printf("\n************************CREATION DES PIPES************************\n");   
    for(int i =1;i<N+1;i++){
        int p[2];
        pipe(p);
        
        tab_pipes[i]=p;
        tab_pipes_pere_fils[i]=p;
        
        printf("pipe numero %d créé\n",i);
        
    }
    printf("\n");
    
 /****************** Création des N processus fils*****************************/ 
    for (int i=1;i<N+1;i++){
        switch(fork()){
            case -1:
                fprintf(stderr,"erreur de fork\n");
                exit(-1);
            case 0:  
            		printf("creation du fils numero %d, dont le pid du pere est %d\n", i,getppid());
            	
                exit(0);
            default:
                close(p1[1]);
                close(tab_pipes_pere_fils[i][0]);	 
                      
               
        }
        
        
    }
    printf("***************************DEBUT DU JEU************************\n");  
    ercriturePereFils(tab_pipes_pere_fils,A);
    enfantParleAuPere (tab_pipes_pere_fils,tab_pipes,p1);
    
    
  	
	
	return 0;
}
