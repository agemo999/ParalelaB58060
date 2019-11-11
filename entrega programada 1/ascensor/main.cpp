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

Semaphore ae1(0),ae2(0),ae3(0),ae4(0),ae5(0),ae6(0),ae7(0),ae8(0),ae9(0),ae10(0),ae11(0),ae12(0),ae13(0),ae14(0),ae15(0),ae16(0);
Semaphore as1(0),as2(0),as3(0),as4(0),as5(0),as6(0),as7(0),as8(0),as9(0),as10(0),as11(0),as12(0),as13(0),as14(0),as15(0),as16(0);
int personaselev[8];
Semaphore inicioelev(0);
elevadorevent cola[256];
pisoevent pisos[16];
bool elev=true;
int pisometa=0;//determina el piso meta antes de cambiar direccion
int ping=0;
int pisoactual=1;
Mutex mutexsalida, mutexdir,mutexpasaj,mutexcola;
int memoriaelevador=0;
int pasajeros=0;
int personatotal=0;
bool direccion=true;
int gente;

void AscenHold(bool status,int modo, int piso){ //status mide entrada y modo mide si espera o da signal

    if(status==true && modo==0){
        switch (piso) {
            case 1: {
                ae1.Wait();
                };break;
            case 2: {
                ae2.Wait();
            };break;
            case 3: {
                ae3.Wait();
            };break;
            case 4: {
                ae4.Wait();
            };break;
            case 5: {
                ae5.Wait();
            };break;
            case 6: {
                ae6.Wait();
            };break;
            case 7: {
                ae7.Wait();
            };break;
            case 8: {
                ae8.Wait();
            };break;
            case 9: {
                ae9.Wait();
            };break;
            case 10: {
                ae10.Wait();
            };break;
            case 11: {
                ae11.Wait();
            };break;
            case 12: {
                ae12.Wait();
            };break;
            case 13: {
                ae13.Wait();
            };break;
            case 14: {
                ae14.Wait();
            };break;
            case 15: {
                ae15.Wait();
            };break;
            case 16: {
                ae16.Wait();
            };break;

        }






    }

    if(status==true && modo==1){
        cout <<BLUE<<  "Ascensor"<< BLACK<< ": Cierro Puertas" << endl;

        switch (piso) {
            case 1: {
                ae1.Signal();
                };break;
            case 2: {
                ae2.Signal();
            };break;
            case 3: {
                ae3.Signal();
            };break;
            case 4: {
                ae4.Signal();
            };break;
            case 5: {
                ae5.Signal();
            };break;
            case 6: {
                ae6.Signal();
            };break;
            case 7: {
                ae7.Signal();
            };break;
            case 8: {
                ae8.Signal();
            };break;
            case 9: {
                ae9.Signal();
            };break;
            case 10: {
                ae10.Signal();
            };break;
            case 11: {
                ae11.Signal();
            };break;
            case 12: {
                ae12.Signal();
            };break;
            case 13: {
                ae13.Signal();
            };break;
            case 14: {
                ae14.Signal();
            };break;
            case 15: {
                ae15.Signal();
            };break;
            case 16: {
                ae16.Signal();
            };break;

        }

    }



     if(status==false && modo==0){


        switch (piso) {
            case 1: {
                as1.Wait();
                };break;
            case 2: {
                as2.Wait();
            };break;
            case 3: {
                as3.Wait();
            };break;
            case 4: {
                as4.Wait();
            };break;
            case 5: {
                as5.Wait();
            };break;
            case 6: {
                as6.Wait();
            };break;
            case 7: {
                as7.Wait();
            };break;
            case 8: {
                as8.Wait();
            };break;
            case 9: {
                as9.Wait();
            };break;
            case 10: {
                as10.Wait();
            };break;
            case 11: {
                as11.Wait();
            };break;
            case 12: {
                as12.Wait();
            };break;
            case 13: {
                as13.Wait();
            };break;
            case 14: {
                as14.Wait();
            };break;
            case 15: {
                as15.Wait();
            };break;
            case 16: {
                as16.Wait();
            };break;

        }






    }

    if(status==false && modo==1){
        cout <<BLUE<<  "Ascensor"<< BLACK<< "Cierro Puertas" << endl;

        switch (piso) {
            case 1: {
                as1.Signal();
                };break;
            case 2: {
                as2.Signal();
            };break;
            case 3: {
                as3.Signal();
            };break;
            case 4: {
                as4.Signal();
            };break;
            case 5: {
                as5.Signal();
            };break;
            case 6: {
                as6.Signal();
            };break;
            case 7: {
                as7.Signal();
            };break;
            case 8: {
                as8.Signal();
            };break;
            case 9: {
                as9.Signal();
            };break;
            case 10: {
                as10.Signal();
            };break;
            case 11: {
                as11.Signal();
            };break;
            case 12: {
                as12.Signal();
            };break;
            case 13: {
                as13.Signal();
            };break;
            case 14: {
                as14.Signal();
            };break;
            case 15: {
                as15.Signal();
            };break;
            case 16: {
                as16.Signal();
            };break;

        }

    }

}
void entradapersona(int entrada, bool direccionper, int salida, int colaper, int numpersona){//determina una persona entra
    bool enter=false;
    mutexdir.Lock();
    if(direccionper==false){
        pisos[entrada-1].genteentrabajando++;
    }else if(direccionper==true){
        pisos[entrada-1].genteentrasubiendo++;
    }
    mutexdir.Unlock();
    while(enter==false){// trata de entrar al elevador en un piso, si el elevador no esta o esta lleno no entra y se queda esperando
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

            cout <<BLUE <<"Ascensor "<<BLACK<<": Aumento pasajeros" << endl;
            bool listo=false;
            int counterpelev=0;
            while(listo==false){
                if(personaselev[counterpelev]==0){

                    personaselev[counterpelev]=numpersona;
                    listo=true;

                }
                counterpelev++;
            }

            cout <<RED<< "Persona" <<BLACK <<": "<<numpersona<<" ha entrado al elevador, hay "<<pasajeros<<" pasajeros en el elevador, quedan " <<8-pasajeros<<" espacios" << endl;
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
            AscenHold(true,1,entrada);

        }else{

            mutexpasaj.Unlock();
            AscenHold(true,1, entrada);

        }


    }


    switch (salida) {// espera para poder salir en el piso
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
    cout <<BLUE<< "Ascensor"<<BLACK<<": Disminuyo pasajeros" << endl;//la persona sale
    mutexpasaj.Lock();
    pasajeros--;
    cout <<RED<< "Persona" <<BLACK <<": "<<numpersona<<" ha salido del elevador, hay "<<pasajeros<<" pasajero(s) en el elevador, quedan " <<8-pasajeros<<" espacios" << endl;
    pisos[salida-1].gentesale--;
    bool listo=false;
    int counterpelev=0;
    while(listo==false){//la remueve del array de personas en el elevador
        if(personaselev[counterpelev]==numpersona){

            personaselev[counterpelev]=0;
            listo=true;

        }
        counterpelev++;
    }

    mutexpasaj.Unlock();
    mutexcola.Lock();
    cola[colaper].arrival_time=0;
    cola[colaper].Persona=0;
    cola[colaper].start_floor=0;
    cola[colaper].target_floor=0;
    AscenHold(false,1,salida);
    mutexcola.Unlock();


}

void elevadorpiso(int piso){//determina en el piso que hacer, mete personas si puede o deja personas si estan listas
    int iteracionentra=0;
    mutexpasaj.Lock();
    int iteracionsale=pisos[piso-1].gentesale;
    if(direccion==false){//verifica la cola pertinente de subir y bajar
        iteracionentra=pisos[piso-1].genteentrabajando;

    }else{
        iteracionentra=pisos[piso-1].genteentrasubiendo;
    }
    int pasajnoentra=pasajeros;
    mutexpasaj.Unlock();
    if(iteracionsale>0){//personas salen
        for(int i=0;i<iteracionsale;i++){

            switch (piso) {
                    case 1: {
                        ps1.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 2: {
                        ps2.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 3: {
                        ps3.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 4: {
                        ps4.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 5: {
                        ps5.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 6: {
                        ps6.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 7: {
                        ps7.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 8: {
                        ps8.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 9: {
                        ps9.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 10: {
                        ps10.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 11: {
                        ps11.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 12: {
                        ps12.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 13: {
                        ps13.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 14: {
                        ps14.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 15: {
                        ps15.Signal();
                        AscenHold(false,0,piso);
                    };break;
                    case 16: {
                        ps16.Signal();
                        AscenHold(false,0,piso);
                    };break;
            }
        }
    }
    if(iteracionentra>0 && pasajnoentra!=8){ //entra persona
        for(int i=0;i<iteracionentra;i++){

            switch (piso) {
                    case 1: {
                        pe1.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 2: {
                        pe2.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 3: {
                        pe3.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 4: {
                        pe4.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 5: {
                        pe5.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 6: {
                        pe6.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 7: {
                        pe7.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 8: {
                        pe8.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 9: {
                        pe9.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 10: {
                        pe10.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 11: {
                        pe11.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 12: {
                        pe12.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 13: {
                        pe13.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 14: {
                        pe14.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 15: {
                        pe15.Signal();
                        AscenHold(true,0,piso);
                    };break;
                    case 16: {
                        pe16.Signal();
                        AscenHold(true,0,piso);
                    };break;

            }

        }

    }


}

void Persona(int entrada, int salida, int personatot){//agrega la informacion a la memoria de la cola
    mutexcola.Lock();
    if(memoriaelevador==255){
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
    bool direcpersona=cola[memoriaelevador].direccion;
    memoriaelevador++;
    cout <<RED<< "Persona" <<BLACK <<": "<<numpersona<<" espera en el piso "<<entrada<<" y va al piso " <<salida << endl;
    mutexcola.Unlock();
    entradapersona(entrada,direcpersona,salida, ubicacionpersona,numpersona);


}


void Ascensor(){//corre el elevador
    inicioelev.Wait();
    usleep(5);
    ping=cola[0].start_floor;
    pisometa=cola[0].target_floor;
    direccion=cola[0].direccion;
    cout <<BLUE<< "Ascensor"<<BLACK<<": Subo inicialmente al piso "<<ping << endl;
    pisoactual=ping;
    elevadorpiso(pisoactual);


    while(elev==true){
        usleep(10);

        if(pisoactual<pisometa){
            cout <<BLUE<< "Ascensor"<<BLACK<<": Estoy en el piso "<<pisoactual << endl;
            pisoactual++;
            cout <<BLUE <<"Ascensor"<<BLACK<<": Subo al piso "<<pisoactual << endl;
            elevadorpiso(pisoactual);

        }else if(pisoactual>pisometa){
            cout <<BLUE<< "Ascensor"<<BLACK<<": Estoy en el piso "<<pisoactual << endl;
            pisoactual--;
            cout <<BLUE<< "Ascensor"<<BLACK<<": Bajo al piso "<<pisoactual << endl;
            elevadorpiso(pisoactual);


        }else{

            mutexcola.Lock();
            if(pisoactual==pisometa){
                int pingant=ping;
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
                if(pingant==ping){
                    bool siguiente=false;
                    int contador=0;

                    if(pasajeros==8){
                        bool listo8=false;
                        int cont8=0;
                        while(listo8==false){
                            int a[8]={1,2,3,4,5,6,7,8};

                            random_shuffle(std::begin(a), std::end(a));
                            cont8=a[0];
                            if(personaselev[cont8]!=0){
                                pisometa=cola[personaselev[cont8]-1].target_floor;
                                direccion=cola[personaselev[cont8]-1].direccion;
                                elevadorpiso(pisoactual);

                                listo8=true;

                            }

                            cont8++;

                        }

                    }else{
                        while(siguiente==false){

                            if(cola[contador].start_floor==0){
                                contador++;
                                if(contador==personatotal){

                                    elev=false;
                                    siguiente=true;
                                }

                            }else{
                                siguiente=true;
                                bool c[2]={true,false};

                                random_shuffle(std::begin(c), std::end(c));
                                if(c[0]==true){
                                    pisometa=cola[contador].start_floor;
                                }else{
                                    pisometa=cola[contador].target_floor;
                                }
                                direccion=cola[contador].direccion;
                                elevadorpiso(pisoactual);


                            }

                        }

                    }




                }

            }

            mutexcola.Unlock();



        }

    }
}


int main()
{
    int totales=100;
    int a[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

    random_shuffle(std::begin(a), std::end(a));
    thread personastotals[totales];
    for (int i=0;i<totales;i++){ //crea todos los hijos
        int a[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};//genera randoms mas precisos que rand()

        random_shuffle(std::begin(a), std::end(a));

        int entrada=a[0];
        int b[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

        random_shuffle(std::begin(b), std::end(b));
        bool verif=false;
        while(verif==false){
            if(a[0]==b[0]){

                random_shuffle(std::begin(b), std::end(b));

            }else{
                verif=true;
            }

        }
        int salida=b[0];
        personatotal++;
        personastotals[i]=thread(Persona,entrada,salida,personatotal);
        if(i==0){
            inicioelev.Signal();

        }
        if(i==totales-1){
            usleep(10);
            Ascensor();
        }
    }


    for (int i = 0; i < totales; i++)   //espera todos los hijos
    {

        personastotals[i].join();

    }
    _exit(0);

    return 0;
}
