/*
@Author : Jolivé Hodehou
@Email : jolivehodehou7@gmail.com
*/
#include <sys/shm.h>
#include <sys/wait.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include <math.h>


#define N 4

typedef struct matrixstruct {
    int C[N][N];
} matstr;

matstr *Cms; /* pointer to output matrix C */
int Cid;     /* segment id for output matrix C */
int base_pid, status, pid;

int main()
{
    int i,j;
    int rank, chunk, u, t;
    // Obtenez la taille du travail que chaque processus devra effectuer.
    chunk = N / sqrt(4);

    /*
    *
    * ÉTAPE 1: créer le segment partagé
    */
    if ((Cid = shmget(IPC_PRIVATE, sizeof(matstr), IPC_CREAT | 0666)) < 0)
    {
        perror("smget returned -1\n");
        error(-1, errno, " ");
        exit(-1);
    }
    printf("Allocated %d, at id %d\n", (int) sizeof(matstr), Cid);

 
    /*
    *
    * ÉTAPE 2: bifurquer les processus enfants
    */
    base_pid = getpid();
    for(i=1; i<N; i++) {
        if (getpid()==base_pid)
            pid = fork();
        else
            break;
    }

    /*
    *
    * ÉTAPE 3: chaque processus enfant attache le segment
    */
    if ((Cms = (matstr *) shmat(Cid, NULL, 0)) == (matstr *) -1){
        perror("Process shmat returned NULL\n");
        error(-1, errno, " ");
    }
    else
        printf("Processus %d attacher au segment %d\n", getpid(), Cid);


    /*
    *
    *
    *
    * ÉTAPE 4: utilisez le segment partagé 
    *
    *
    *
    */

    // Get the process id
    rank = getpid()-base_pid;

    // Calculate the offsets for the result matrix
    u = (rank % (N/chunk)) * chunk;
    t = floor((rank * chunk) / N) * chunk;

    // Loop over the matrix chunk for this process
    for (i=u;i<(u+chunk);i++) {
        for (j=t;j<(t+chunk);j++) {
            Cms->C[i][j] = rank;
        }
    }

    /*
    *
    * ÉTAPE 5: chaque processus enfant détache le segment
    */
    if (shmdt(Cms) == -1){
        perror("shmdt returned -1\n");
        error(-1, errno, " ");
    }else
        printf("Processus %d detacher du segment %d\n", getpid(), Cid);

    /*
    *
    * ÉTAPE 6: chaque processus enfant se termine et le parent se joint
    */
    if (getpid()==base_pid)
        for(i=1; i<N; i++) {
            wait(NULL);
        }
    else
        exit(0);

    // Print out the matrix
    Cms = (matstr *) shmat(Cid, NULL, 0);
    for (i=0;i<N;i++) {
            printf("[");
        for (j=0;j<N;j++) {
            printf("%d ", Cms->C[i][j]);
        }
        printf("]\n");
    }
    printf("\n\n");

    /*
    *
    * ÉTAPE 7: le processus de base supprime le segment
    */
    if (shmctl(Cid,IPC_RMID,NULL) == -1){
        perror("shmctl returned -1\n");
        error(-1, errno, " ");
    }


    return 0;
}
