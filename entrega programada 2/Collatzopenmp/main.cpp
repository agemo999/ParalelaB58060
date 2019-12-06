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


#define BLACK "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"

//////

using namespace std;




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



  int num=1000; 
  int numerosglob[num];
  int vecesfinalglob[num];
  srand( time(0) );

  #pragma omp parallel for schedule(dynamic)//paralelizamos el guardar los rands
  for (int i=0; i<num; i++){
      numerosglob[i] = rand()%1000+1;
  }


  #pragma omp parallel for schedule(dynamic)//paralelizamos el calcular el collatz
  for (int i=0; i<num; i++){
      vecesfinalglob[i]=Collatz(numerosglob[i]);

  }


//





  for (int i=0; i<num; i++){//imprime los numeros de veces finales
      cout<<"El numero "<<GREEN<<numerosglob[i]<<BLACK<<" se iteró "<<RED<<vecesfinalglob[i]<<BLACK<<" veces"<<endl;
  }




  return 0;
}

  /* main */
