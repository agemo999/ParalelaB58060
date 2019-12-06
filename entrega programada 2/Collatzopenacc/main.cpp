#include <stdio.h>
#include <string.h>  /* For strlen             */
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <array>
#include <algorithm>
#include <unistd.h>
#include <omp.h>
#include <ctime>
#include <openacc.h>
#include <accelmath.h>


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

//////

using namespace std;
//


int Collatz(int numero){
    int tempnum=numero;
    int veces=0;
    while(tempnum!=1){

        if(tempnum%2==0){
            tempnum=tempnum/2;
            veces++;

        }else{

            tempnum=3*tempnum+1;
            veces++;
        }


    }



return veces;

}





int main(void)
{



  int num=1000000;
  float *numerosglob;  /* the vector */
  float *restrict vecesfinalglob;  /* acc results */
  float *e;  /* no acc results */
  timestruct t1, t2, t3;
  long long cgpu, chost;

  srand( time(0) );

  numerosglob = (float*)malloc(num*sizeof(float));
  vecesfinalglob = (float*)malloc(num*sizeof(float));
  e = (float*)malloc(num*sizeof(float));



  for (int i=0; i<num; i++){
      numerosglob[i] = rand()%1000+1;
  }
#pragma acc data copy(numerosglob[0:num])//copia los datos a la tarjeta de video
gettime( &t1 );//mide tiempo 1

#pragma acc parallel loop //lo trabaja de manera paralela usando openaccc calcula collatz para todos los numeros
for (int i=0; i<num; i++){

    vecesfinalglob[i]=Collatz(numerosglob[i]);

}
gettime( &t2 );//mide tiempo 2

cgpu = usec(t1,t2);

#pragma omp parallel for schedule(dynamic) //usa openmp para comparar con openacc
for (int i=0; i<num; i++){
    e[i]=Collatz(numerosglob[i]);

}
gettime( &t3 );
chost = usec(t2,t3);





  for (int i=0; i<num; i++){
      cout<<"El numero "<<GREEN<<numerosglob[i]<<BLACK<<" se iteró "<<RED<<vecesfinalglob[i]<<BLACK<<" veces"<<endl;

  }
  printf( "%13ld microseconds on GPU\n", cgpu );
  printf( "%13ld microseconds on host\n", chost );




  return 0;
}

  /* main */
