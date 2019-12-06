#include <stdio.h>
#include <string.h>  /* For strlen             */
#include <mpi.h>     /* For MPI functions, etc */
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <array>
#include <algorithm>
#include <unistd.h>

#define BLACK "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"

//////////

using namespace std;




int Collatz(int numero){//calcula el collatz usando un entero
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


  int mysize=0;
  int myrank=0;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &mysize);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);


  int num=100;
  int numerosglob[num];
  int vecesfinalglob[num];

  int distrib=0;
  if(num%mysize==0){

    distrib=num/mysize;//distribuye si es divisible de manera exacta

  }else{
    distrib=num/mysize+1;//hace que se pueda usar cualquier numero para la distribucion

  }
  int datoslocales[distrib];



  if (myrank == 0) {
    srand( time(0) );

    for (int i=0; i<num; i++){
        numerosglob[i] = rand()%1000+1;
    }



  }

  MPI_Scatter(numerosglob, distrib, MPI_INT, &datoslocales, distrib, MPI_INT, 0, MPI_COMM_WORLD);//distribuye datoslocales entre los procesos

//
  for (int i=0; i<distrib; i++){//imprime que le toca a cada numero
    if(datoslocales[i]!=0){
        cout<<"El proceso "<<BLUE<< myrank<<BLACK<<": tiene en la cola "<<RED<<i+1<<BLACK<<" el numero: "<<CYAN<<datoslocales[i]<<BLACK<<endl;

    }


  }

  MPI_Barrier(MPI_COMM_WORLD);//evita un poco el caos con los prints

  for (int i = 0; i < distrib; i++) {//trabaja cada uno

      if(datoslocales[i]!=0){
        int veces=Collatz(datoslocales[i]);

        datoslocales[i]=veces;

      }


  }

  MPI_Barrier(MPI_COMM_WORLD);//espera a que todos terminen

  MPI_Gather(&datoslocales, distrib, MPI_INT, vecesfinalglob, distrib, MPI_INT, 0, MPI_COMM_WORLD);//padre obtiene todos los numeros

  MPI_Barrier(MPI_COMM_WORLD);

  if (myrank == 0) {

    for (int i=0; i<num; i++){//imprime las veces que se trabajo cada uno
      if(numerosglob[i]!=0){
          cout<<"El numero "<<GREEN<<numerosglob[i]<<BLACK<<" se iteró "<<RED<<vecesfinalglob[i]<<BLACK<<" veces"<<endl;
      }


    }
  }


  MPI_Finalize();
  return 0;
}

  /* main */
