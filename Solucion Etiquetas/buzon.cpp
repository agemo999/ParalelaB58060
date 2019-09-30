
#include "buzon.h"
#include <iostream>
using namespace std;


buzon::buzon() {
    id=msgget(KEY,IPC_CREAT| 0600);
    if(-1==id){
        perror("Buzon::Buzon");
        exit(7);
    }
}

//Se encarga de enviar un mensaje al buzon
int buzon::Enviar(char * veces, char * etiqueta, int tipo ){
    size_t len=sizeof(A)-sizeof(long);
    A.mtype=tipo;
    
    strncpy(A.etiq,etiqueta,64);
    strncpy(A.veces,veces,64);
    
    st=msgsnd(id,&A,len,0);
    
    if(-1==st){
        perror("Buzon::Enviar");
        exit(9);
    }
    return st;
}
//se encarga de recibir un mensaje del buzon de un tipo especifico
int buzon::Recibir(char * etiqueta,char * veces, int tipo){
    st=msgrcv(id,&A,sizeof(A),tipo,0);
    
    int len=64;
    
    if(-1==st){
        perror("Buzon::Recibir");
        exit(10);
        
    }else{
        strncpy(etiqueta, A.etiq,len);
        strncpy(veces, A.veces,len);
    
    }
    
    
    
    
    return 0;
}

buzon::~buzon() {
    st=msgctl(id,IPC_RMID,0);
    if(-1==st){
        
        perror("buzon::~buzon");
        exit(8);
    }
}

