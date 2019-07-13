/*
@Author : Jolivé Hodehou
@Email : jolivehodehou7@gmail.com
*/
#include <unistd.h>
#include <stdio.h>

int main() {

                                     
    pid_t pid1 = fork();             
    if (pid1 == 0) {                 
        printf("Je suis le premier fils || Mon pid est : (%d)\n", getpid());
        return 0;                    
    }                                
                                     
    pid_t pid2 = fork();             
    if (pid2 == 0) {                 
        printf("Je suis le second fils || Mon pid est : (%d)\n", getpid());
        return 0;                    
    }   
       

    pid_t pid3 = fork();             
    if (pid3 == 0) {                 
        printf("Je suis le troisieme fils || Mon pid est :  (%d)\n", getpid());
        return 0;                    
    }                          

                                     
    return 0;                        
}

