/*
@Author : Jolivé Hodehou
@Email : jolivehodehou7@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

static struct {
   int value;
} *total;
int k=0;
static void process1(void) { 
   // int k = 0;  
   while (k < 100) {  
      k++;  
      __sync_fetch_and_add(&total->value, 1);  
    }  
    printf("From process 1 = %d\n", total->value);
}

static void process2(void) { 
  // int k = 0;
   while (k < 100) {  
      k++;  
      __sync_fetch_and_add(&total->value, 1);  
   }  
   printf("From process 2 = %d\n", total->value);
}

static void process3(void) { 
   // int k = 0;  
   while (k < 100) {  
      k++;  
      __sync_fetch_and_add(&total->value, 1);  
    }  
    printf("From process 3 = %d\n", total->value);
}

int main(void) {
   int   shmid;
   int   pid1;
   int   pid2;
   int   pid3;
   int   status;

   /* Create and connect to a shared memory segment */


   if ((shmid = shmget(1234, sizeof *total, IPC_CREAT|0666)) < 0) {
      perror ("shmget");
      exit (1);
   }
   if ((total = shmat(shmid, 0, 0)) == (void *)-1) {
      perror("shmat");
      exit (0);
   }
   total->value = 0; // not necessary in Linux if IPC_CREAT invoked

   if (!(pid1 = fork()))
      process1();
   else if (!(pid2 = fork()))
      process2();
   else if (!(pid3 = fork()))
      process3();
   else {
      wait(&status);
      wait(&status);
      wait(&status);
      if ((shmctl(shmid, IPC_RMID, (struct shmid_ds *) 0)) == -1) {
         perror("shmctl");
         exit (-1);
      }
      printf("\t\t  End of Program.\n");
   }
   return 0;
}

