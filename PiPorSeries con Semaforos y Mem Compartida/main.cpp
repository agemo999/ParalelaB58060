/*
  Calcula el numero PI utilizando una serie "infinita"
  Debe recibir la cantidad de iteraciones como parametro

  pi = (-1)^i x 4/(2xi + 1)

*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Semaforo.h"
#include <sys/shm.h>
#include <iostream>

/*
   Realiza la acumulacion de terminos desde una posicion inicial hasta un termino final
*/
double calcularSumaParcialPi( double Pi[], int proceso, long inicial, long terminos ) {
   double casiPi = 0;
   double alterna = 4;
   long divisor = 0;
   long termino;
   
   for ( termino = inicial; termino < terminos; termino++ ) {
      divisor = termino + termino + 1;		// 2 x termino + 1
      casiPi += alterna/divisor;		// 4 / (2xi + 1)
      alterna *= -1;				// Pasa de 4 a -4 y viceversa, para realizar la aproximacion de los terminos
   }
   Pi[ proceso ] = casiPi;			// Guarda el resultado en el vector y finaliza
   
   return 0;
}


int main( int argc, char ** argv ) {
   long terminos, inicio, fin;
   int proceso;
   int pid;
   double casiPi[ 10 ] = { 0 };
   Semaforo s(1);
   int id = shmget(0xB58060, 1024, 0700 | IPC_CREAT); //para crear la memoria compartida
   double * area = (double *) shmat(id, NULL, 0); //declaro el tipo que se va a guardar en la memoria compartida
   area[0]=0; //inicializa la memoria compartida en 0  
   terminos = atol( argv[ 1 ] );
   
   for ( proceso = 0; proceso < 10; proceso++ ) {
      inicio = proceso * terminos/10;
      fin = (proceso + 1) * terminos/10;
      pid = fork();
      
      if ( ! pid ) { //proceso hijo hace el calculo, pide permiso para usar el semaforo, hace la suma y lo guarda en el espacio de la memoria compartida y da signal
          
          calcularSumaParcialPi( casiPi, proceso, inicio, fin );
          s.Wait();
          double midnum=area[0];
          midnum=midnum+casiPi[proceso];
          area[0]=midnum;
          s.Signal();
          exit( 0 );
          
      } else {
                    
         printf("Creating process %d: starting value %ld, finish at %ld\n", pid, inicio, fin ); 
         
         
      }
   }

   for ( proceso = 0; proceso < 10; proceso++ ) { //espera a que terminen todos los procesos
      int status;
      pid_t pid = wait( &status );
   }

   
   printf( "Valor calculado de Pi es %g con %ld terminos\n", area[ 0 ], terminos ); //imprime el valor final en la memoria compartida cuando todos los hijos han terminado
   shmdt(area); //elimina area de memoria compartida
   shmctl(id, IPC_RMID, NULL); //borro el segmento asignado 
   s.~Semaforo(); //elimina el semaforo

}