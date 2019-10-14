#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include "synchPT.h"
#include <array>
#include <algorithm>
#include <thread>
#include <unistd.h>
using namespace std;


Mutex mutex;



Semaphore s1(0);
Semaphore s2(0);
Semaphore s3(0);


int semillas = 0, abono = 0, agua = 0, stashabono=500, stashsemillas=500, stashagua=500, stashtotal=1500;
int dealercont=0;
bool sem1=false,sem2=false,sem3=false;

void sembrador1 () {//le hace falta abono
    int contador=0;
   while(stashabono>=0){

        s1.Wait();
        mutex.Lock();
        abono--;
        dealercont--;
        cout << "El sembrador 1 esta plantando!"<< endl;
        contador++;
        cout << "Sembrador 1: "<<contador<< endl;

        mutex.Unlock();
    }

    exit(0);


}

void sembrador2 () {//le hace falta semillas
    int contador=0;
    while(stashsemillas>=0){

        s2.Wait();
        mutex.Lock();
        semillas--;
        dealercont--;
        cout << "El sembrador 2 esta plantando!"<< endl;
        contador++;
        cout << "Sembrador 2: "<<contador<< endl;
        mutex.Unlock();
    }

    exit(0);

}

void sembrador3 () {//le hace falta agua
    int contador=0;
    while(stashagua>=0){

        s3.Wait();
        mutex.Lock();
        agua--;
        dealercont--;
        cout << "El sembrador 3 esta plantando!"<< endl;
        contador++;
        cout << "Sembrador 3: "<<contador<< endl;
        mutex.Unlock();
    }

    exit(0);

}

void dealer () {


   bool solouno=false;
   while(solouno==false){

        if(dealercont<2){
            int a[3]={1,2,3};
            random_shuffle(std::begin(a), std::end(a));

            if(stashtotal>1){
                int b=a[0];
                switch (b) {
                    case 1: if(stashabono>0){
                        mutex.Lock();
                        abono++;
                        stashabono--;
                        stashtotal--;
                        dealercont++;
                        cout << "Hay abono disponible!" << endl;
                        mutex.Unlock();
                        s1.Signal();



                    };break;
                    case 2: if(stashsemillas>0){
                        mutex.Lock();

                        semillas++;
                        stashsemillas--;
                        stashtotal--;
                        dealercont++;
                        cout << "Hay semillas disponibles!" <<  endl;
                        mutex.Unlock();
                        s2.Signal();

                    };break;
                    case 3: if(stashagua>0){
                        mutex.Lock();
                        agua++;
                        stashagua--;
                        stashtotal--;
                        dealercont++;
                        cout << "Hay agua disponible!" << endl;
                        mutex.Unlock();
                        s3.Signal();

                    };break;
                }


            }else{
                while(solouno==false){
                    if(stashabono>0){
                        mutex.Lock();
                        abono++;
                        stashabono--;
                        stashtotal--;
                        dealercont++;
                        cout << "Hay abono disponible!" << endl;
                        solouno=true;
                        mutex.Unlock();
                        s1.Signal();

                    }else if(stashsemillas>0){
                        mutex.Lock();
                        semillas++;
                        stashsemillas--;
                        stashtotal--;
                        dealercont++;
                        cout << "Hay semillas disponibles!" <<  endl;
                        solouno=true;
                        mutex.Unlock();
                        s2.Signal();




                    }else{

                        mutex.Lock();
                        agua++;
                        stashagua--;
                        stashtotal--;
                        dealercont++;
                        cout << "Hay agua disponible!" << endl;
                        solouno=true;
                        mutex.Unlock();
                        s3.Signal();


                    }
                }
            }
        }
   }

  exit( 0 );// Finish this thread

}







int main () {



  thread deal (dealer);
  thread semb1 (sembrador1);
  thread semb2 (sembrador2);
  thread semb3 (sembrador3);


    deal.join();
    semb1.join();
    semb2.join();
    semb3.join();

  cout << "\n";
  cout << "  Hemos terminado.\n";

  return 0;
}



