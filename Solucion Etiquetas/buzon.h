/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   buzon.h
 * Author: osboxes
 *
 * Created on September 12, 2018, 2:47 PM
 */

#ifndef BUZON_H
#define BUZON_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <sys/msg.h>
#include <cstring>
#include <string>

#define KEY 0xB58060	// Valor de la llave del recurso

   class buzon {
      public: 
      buzon();
      ~buzon();
      int Enviar(char * veces, char * mensaje, int tipo );
      int Recibir( char* mensaje,char* veces, int tipo );   // len es el tamaño máximo que soporte la variable mensaje
     private:
      int id;		// Identificador del buzon
      int st;
      struct msgbuf {
          long mtype;
          char veces[64];
          char etiq[64];
          
      };
      struct msgbuf A;
    
   };

#endif /* BUZON_H */

