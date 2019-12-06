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
#include <omp.h>
#include <ctime>
#include <openacc.h>
#include <iostream>
//#include <accelmath.h>


#if defined(_WIN32) || defined(_WIN64)
#include <sys/timeb.h>
#define gettime(a) _ftime(a)
#define usec(t1,t2) ((((t2).time-(t1).time)*1000+((t2).millitm-(t1).millitm))*100)
typedef struct _timeb timestruct;
#else
#include <sys/time.h>
#define gettime(a) gettimeofday(a,NULL)
#define usec(t1,t2) (((t2).tv_sec-(t1).tv_sec)*1000000+((t2).tv_usec-(t1).tv_usec))
typedef struct timeval timestruct;
#endif


#define BLACK "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"

using namespace std;
/*
   Realiza la acumulacion de terminos desde una posicion inicial hasta un termino final
*/

double calcularSumaParcialPiserial(long inicial, long terminos ) {
   double alterna=4;
   long divisor = 0;
   long termino;
   double Pifinal;


   for ( termino = inicial; termino < terminos; termino++ ) {
      divisor = termino + termino + 1;		// 2 x termino + 1
      Pifinal+= alterna/divisor;		// 4 / (2xi + 1)


      alterna *= -1;				// Pasa de 4 a -4 y viceversa, para realizar la aproximacion de los terminos
   }
   return Pifinal;
   //exit( 0 );
}
int main( int argc, char ** argv ) {
   long terminos,terminos2, inicio, fin;
   double Pi=0;
   double Pi2=0;
   terminos = 1000000;
   terminos2= terminos;
   timestruct t1, t2, t3;
   long long cgpu, chost;
   double casiPi[terminos];

   int division=1000;
   if ( argc > 1 ) {
      terminos = atol( argv[ 1 ] );
   }
   inicio=0;
   #pragma acc data copy(casiPi[0:terminos])
   gettime( &t1 );

   #pragma acc parallel loop collapse(1)

   for (int i=0;i<terminos/division;i++){
        int inic=i*division;
        int fin2=inic+(division-1);
        double alterna = 4;
        long divisor = 0;
        long termino;

        for ( termino = inic; termino < fin2; termino++ ) {
           if(termino%2==0 || termino==0){
             alterna=4;
           }else{
             alterna=-4;
           }
           divisor = termino + termino + 1;		// 2 x termino + 1
           Pi+= alterna/divisor;


                        // Pasa de 4 a -4 y viceversa, para realizar la aproximacion de los terminos
        }



   }
   gettime( &t2 );

   cgpu = usec(t1,t2);

   Pi2=calcularSumaParcialPiserial(0,terminos2);
   gettime( &t3 );
   chost = usec(t2,t3);



   cout<<"El valor calculado de Pi acelerado es "<<GREEN<<Pi<<BLACK<<" con "<<RED<<terminos<<BLACK<<" terminos"<<endl;
   cout<<"El valor calculado de Pi serialmente es "<<GREEN<<Pi2<<BLACK<<" con "<<RED<<terminos<<BLACK<<" terminos"<<endl;
   printf( "%13ld microseconds on GPU\n", cgpu );
   printf( "%13ld microseconds on host\n", chost );


}
