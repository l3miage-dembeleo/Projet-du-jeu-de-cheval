#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define N 4

int main(){

    for (int i=1;i<N+1;i++){
         switch(fork()){
                case -1:
                    fprintf(stderr,"erreur de fork\n");
                    exit(-1);
                case 0:  // création des n-1 fils restants
                    printf("creation du fils numero %d, dont le pid du pere est %d\n", i,getppid());
                    exit(0);
                default:
                    printf("le fils %d est mort \n", wait(NULL));  
                        
                 }
            }
    return 0;

}
