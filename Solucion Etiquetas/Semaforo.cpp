
#include "Semaforo.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;


union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
};


Semaforo::Semaforo(int v) {//crea un semáforo en un número especifico

    id= semget(KEY,1,IPC_CREAT | 0600); 
    if(-1==id){
        perror("Semaforo::Semaforo");
        exit(2);
    }
    union semun a;
    a.val=v;
    st=semctl(id,0,SETVAL,a);
    if(-1==id){
        perror("Semaforo::Semaforo");
        exit(3);
    }
    
}

int Semaforo::Wait() {//hace que se espere al reducir el sem.op en uno, basicamente detiene el funcionamiento si el semaforo esta en 0 o menos
    struct sembuf s;
    s.sem_num=0;
    s.sem_op=-1;
    s.sem_flg=0;
    st= semop(id,&s,1);
    if(-1==id){
        perror("Semaforo::Wait");
        exit(5);
    }
    
    return st;
    
}

int Semaforo::Signal() {// aumenta el sem.op en uno, esto activa los procesos que esten en wait() para que continuen su funcionamiento
    struct sembuf s;
    s.sem_num=0;
    s.sem_op=+1;
    s.sem_flg=0;
    st= semop(id,&s,1);
    if(-1==id){
        perror("Semaforo::Signal");
        exit(6);
    }
    
    return st;
    
}
Semaforo::Semaforo(const Semaforo& orig) {
}

Semaforo::~Semaforo() {//destruye el semáforo
    st=semctl(id,0,IPC_RMID);
    if(-1==id){
        perror("Semaforo::~Semaforo");
        exit(4);
    }
}

