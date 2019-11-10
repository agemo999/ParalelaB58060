#include <iostream>
#include <chrono>
#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>
#include "synchPT.h"
#include <array>
#include <algorithm>
#include <thread>
#include <unistd.h>

#define BLACK "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
using namespace std;
using namespace std::chrono;


using namespace std;


struct elevadorevent {
    int   start_floor;
    int   target_floor;
    double arrival_time;
    bool direccion;
    int Persona;
};


struct pisoevent {
    int genteentrasubiendo;
    int genteentrabajando;
    int gentesale;
};


Semaphore pe1(0),pe2(0),pe3(0),pe4(0),pe5(0),pe6(0),pe7(0),pe8(0),pe9(0),pe10(0),pe11(0),pe12(0),pe13(0),pe14(0),pe15(0),pe16(0);
Semaphore ps1(0),ps2(0),ps3(0),ps4(0),ps5(0),ps6(0),ps7(0),ps8(0),ps9(0),ps10(0),ps11(0),ps12(0),ps13(0),ps14(0),ps15(0),ps16(0);
Semaphore inicioelev(0);
elevadorevent cola[1024];
pisoevent pisos[16];
int pisometa=0;//determina el piso meta antes de cambiar direccion
int ping=0;
int pisoactual=1;
Mutex mutexsalida, mutexdir,mutexpasaj,mutexcola;
int memoriaelevador=0;
int pasajeros=0;
int personatotal=0;
bool direccion=true;
int gente;
void entradapersona(int entrada, bool direccionper, int salida, int colaper, int numpersona){
    bool enter=false;
    mutexdir.Lock();
    if(direccionper==false){
        pisos[entrada-1].genteentrabajando++;
    }else{
        pisos[entrada-1].genteentrasubiendo++;
    }
    mutexdir.Unlock();
    while(enter==false){
        switch (entrada) {
            case 1: {
                pe1.Wait();
                };break;
            case 2: {
                pe2.Wait();
            };break;
            case 3: {
                pe3.Wait();
            };break;
            case 4: {
                pe4.Wait();
            };break;
            case 5: {
                pe5.Wait();
            };break;
            case 6: {
                pe6.Wait();
            };break;
            case 7: {
                pe7.Wait();
            };break;
            case 8: {
                cout << "Persona espera en piso 8" << endl;

                pe8.Wait();
            };break;
            case 9: {
                pe9.Wait();
            };break;
            case 10: {
                pe10.Wait();
            };break;
            case 11: {
                pe11.Wait();
            };break;
            case 12: {
                pe12.Wait();
            };break;
            case 13: {
                pe13.Wait();
            };break;
            case 14: {
                pe14.Wait();
            };break;
            case 15: {
                pe15.Wait();
            };break;
            case 16: {
                pe16.Wait();
            };break;

        }


        mutexpasaj.Lock();
        if(pasajeros<8){
            if(direccionper==false){
                pisos[entrada-1].genteentrabajando--;
            }else{
                pisos[entrada-1].genteentrasubiendo--;
            }
            pasajeros++;
            enter=true;
            mutexdir.Lock();
            pisos[salida-1].gentesale++;
            mutexdir.Unlock();
            cout << "Persona: " <<numpersona<<" ha entrado al elevador, hay "<<pasajeros<<" pasajeroes en el elevador, quedan " <<8-pasajeros<<" espacios" << endl;
            mutexpasaj.Unlock();
            mutexsalida.Lock();
            if(direccion==false){
                if(salida<pisometa){
                    pisometa=salida;
                }
            }else{
                if(salida>pisometa){
                    pisometa=salida;
                }
            }
            mutexsalida.Unlock();
            inicioelev.Signal();

        }else{

            mutexpasaj.Unlock();
            inicioelev.Signal();

        }


    }

    inicioelev.Signal();
    switch (salida) {
        case 1: {
            ps1.Wait();
            };break;
        case 2: {
            ps2.Wait();
        };break;
        case 3: {
            ps3.Wait();
        };break;
        case 4: {
            ps4.Wait();
        };break;
        case 5: {
            ps5.Wait();
        };break;
        case 6: {
            ps6.Wait();
        };break;
        case 7: {
            cout << "Persona espera al piso 7" << endl;

            ps7.Wait();
        };break;
        case 8: {
            ps8.Wait();
        };break;
        case 9: {
            ps9.Wait();
        };break;
        case 10: {
            ps10.Wait();
        };break;
        case 11: {
            ps11.Wait();
        };break;
        case 12: {
            ps12.Wait();
        };break;
        case 13: {
            ps13.Wait();
        };break;
        case 14: {
            ps14.Wait();
        };break;
        case 15: {
            ps15.Wait();
        };break;
        case 16: {
            ps16.Wait();
        };break;
    }
    cout << "disminuyo pasajeros" << endl;
    mutexpasaj.Lock();
    pasajeros--;
    cout << "Persona:" <<numpersona<<" ha salido del elevador, hay "<<pasajeros<<" pasajeroes en el elevador, quedan" <<8-pasajeros<<" espacios" << endl;
    pisos[salida-1].gentesale--;
    mutexpasaj.Unlock();
    mutexcola.Lock();
    cola[colaper].arrival_time=0;
    cola[colaper].Persona=0;
    cola[colaper].start_floor=0;
    cola[colaper].target_floor=0;
    mutexcola.Unlock();
    inicioelev.Signal();



}

void elevadorpiso(int piso){
    int iteracionentra=0;
    mutexpasaj.Lock();
    int iteracionsale=pisos[piso-1].gentesale;
    if(direccion==false){//verifica la cola pertinente
        iteracionentra=pisos[piso-1].genteentrabajando;

    }else{
        iteracionentra=pisos[piso-1].genteentrasubiendo;
    }
    mutexpasaj.Unlock();
    if(iteracionsale>0){//personas entra
        for(int i=0;i<iteracionsale;i++){

            switch (piso) {
                    case 1: {
                        ps1.Signal();
                    };break;
                    case 2: {
                        ps2.Signal();
                        inicioelev.Wait();
                    };break;
                    case 3: {
                        ps3.Signal();
                        inicioelev.Wait();
                    };break;
                    case 4: {
                        ps4.Signal();
                        inicioelev.Wait();
                    };break;
                    case 5: {
                        ps5.Signal();
                        inicioelev.Wait();
                    };break;
                    case 6: {
                        ps6.Signal();
                        inicioelev.Wait();
                    };break;
                    case 7: {
                        ps7.Signal();
                        inicioelev.Wait();
                    };break;
                    case 8: {
                        ps8.Signal();
                        inicioelev.Wait();
                    };break;
                    case 9: {
                        ps9.Signal();
                        inicioelev.Wait();
                    };break;
                    case 10: {
                        ps10.Signal();
                        inicioelev.Wait();
                    };break;
                    case 11: {
                        ps11.Signal();
                        inicioelev.Wait();
                    };break;
                    case 12: {
                        ps12.Signal();
                        inicioelev.Wait();
                    };break;
                    case 13: {
                        ps13.Signal();
                        inicioelev.Wait();
                    };break;
                    case 14: {
                        ps14.Signal();
                        inicioelev.Wait();
                    };break;
                    case 15: {
                        ps15.Signal();
                        inicioelev.Wait();
                    };break;
                    case 16: {
                        ps16.Signal();
                        inicioelev.Wait();
                    };break;
            }
        }
    }
    if(iteracionentra>0){ //entra persona
        for(int i=0;i<iteracionentra;i++){

            switch (piso) {
                    case 1: {
                        pe1.Signal();
                        inicioelev.Wait();
                    };break;
                    case 2: {
                        pe2.Signal();
                        inicioelev.Wait();
                    };break;
                    case 3: {
                        pe3.Signal();
                        inicioelev.Wait();
                    };break;
                    case 4: {
                        pe4.Signal();
                        inicioelev.Wait();
                    };break;
                    case 5: {
                        pe5.Signal();
                        inicioelev.Wait();
                    };break;
                    case 6: {
                        pe6.Signal();
                        inicioelev.Wait();
                    };break;
                    case 7: {
                        pe7.Signal();
                        inicioelev.Wait();
                    };break;
                    case 8: {
                        pe8.Signal();
                        inicioelev.Wait();
                    };break;
                    case 9: {
                        pe9.Signal();
                        inicioelev.Wait();
                    };break;
                    case 10: {
                        pe10.Signal();
                        inicioelev.Wait();
                    };break;
                    case 11: {
                        pe11.Signal();
                        inicioelev.Wait();
                    };break;
                    case 12: {
                        pe12.Signal();
                        inicioelev.Wait();
                    };break;
                    case 13: {
                        pe13.Signal();
                        inicioelev.Wait();
                    };break;
                    case 14: {
                        pe14.Signal();
                        inicioelev.Wait();
                    };break;
                    case 15: {
                        pe15.Signal();
                        inicioelev.Wait();
                    };break;
                    case 16: {
                        pe16.Signal();
                        inicioelev.Wait();
                    };break;

            }

        }

    }
    usleep(5);

    if(piso==pisometa){

          0

    }


}

void Persona(int entrada, int salida, int personatot){
    mutexcola.Lock();
    if(memoriaelevador==1023){
        memoriaelevador=0;
    }
    cola[memoriaelevador].arrival_time=memoriaelevador;
    if((entrada-salida)<0){
        cola[memoriaelevador].direccion=true;

    }else{
        cola[memoriaelevador].direccion=false;

    }
    cola[memoriaelevador].Persona=personatot;
    cola[memoriaelevador].start_floor=entrada;
    cola[memoriaelevador].target_floor=salida;
    int ubicacionpersona=memoriaelevador;
    int numpersona=personatot;
    memoriaelevador++;
    bool direcpersona=cola[memoriaelevador].direccion;
    cout << "Persona:" <<numpersona<<" espera en el piso "<<entrada<<" y va al piso " <<salida << endl;
    mutexcola.Unlock();
    entradapersona(entrada,direcpersona,salida, ubicacionpersona,numpersona);


}


void Ascensor(){
    inicioelev.Wait();
    usleep(5);
    ping=cola[0].start_floor;
    pisometa=cola[0].target_floor;
    direccion=cola[0].direccion;
    cout << "Ascensor: Subo inicialmente al piso "<<ping << endl;
    pisoactual=ping;
    elevadorpiso(pisoactual);
    bool elev=true;

    while(elev==true){

        for(int i=0;i<personatotal;i++){

            if(cola[i].start_floor!=0){
                if(cola[i].direccion==direccion){
                    if(direccion==true){
                        if(ping<cola[i].start_floor){
                            ping=cola[i].start_floor;
                        }
                    }else{

                        if(ping>cola[i].start_floor){
                            ping=cola[i].start_floor;
                        }
                    }
                 }
            }
        }
        cout << "Ascensor: Estoy en el piso "<<pisoactual << endl;
        if(pisoactual<pisometa){
            pisoactual++;
            cout << "Ascensor: Subo al piso "<<pisoactual << endl;
            elevadorpiso(pisoactual);

        }else if(pisoactual>pisometa){
            pisoactual--;
            cout << "Ascensor: Bajo al piso "<<pisoactual << endl;
            elevadorpiso(pisoactual);


        }






    }
}


int main()
{
    thread personastotals[8];
    for (int i=0;i<8;i++){
        int entrada=rand()%16+1;
        int salida=rand()%16+1;
        personatotal++;
        personastotals[i]=thread(Persona,entrada,salida,personatotal);
        if(i==0){
            inicioelev.Signal();

        }
        if(i==7){
            usleep(10);
            Ascensor();
        }
    }


    for (int i = 0; i < 8; i++)   //crea todos los hijos
    {

        personastotals[i].join();

    }

    cout << "hola" << endl;
    return 0;
}
