
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "Mapeo.h"
#include "Evaluador.h"
#include "buzon.h"
#include "Semaforo.h"
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include <string>
#include <wait.h>


using namespace std;
struct hijosinfo {
   int init;
   int fin;
   int max;
};
/*
 * 
 */


static void show_usage(std::string name) {
    std::cerr << "Usage: " << name << " <option(s)> SOURCES\n"
            << "\t-h\t\tShow this help message\n"
            << "\tfilename.txt \tText file with the names of the html(only 1 at the moment)"
            << std::endl;
}


//este programa funciona, solo que tiene una inconsistencia por parte del buzon cuando se trabajan muchas lineas, no puedo encontrar el factor de error, pero sucede
int main(int argc, char** argv) {


    if (argc < 2) { //para poder agregar los argumentos o el mensaje de ayuda
        show_usage(argv[0]);
        return 1;
    }
    string archivo = "";
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            show_usage(argv[0]);
            return 0;
        } else {
            archivo = argv[1];

        }
    }


    Mapeo mapa;
    Evaluador eva;
    buzon bu;
    int id = shmget(0xB58060, 1024, 0700 | IPC_CREAT);
    Mapeo::etiquetaspaso * area = (Mapeo::etiquetaspaso *) shmat(id, NULL, 0);
    int tipoinit;
    int tipohijo;
    tipoinit = 10;
    Semaforo s(1);
        
    
    string str1;
    
    ifstream filep(archivo);
    
    if(!filep) {//verifica que el archivo sea valido
        cout << "Exception opening/reading file: " <<archivo << " please check that the name and the file is present";
        exit(0);
    }
    
    
    int cantidadlineas=0;
    
    while (!filep.eof()) {//calcula la cantidad total de lineas
        getline(filep, str1);
        cantidadlineas++;        
    }
    filep.clear();
    filep.seekg(0, std::ios::beg); // reinicia el eof generado anteriormente
    int hijos=0;
    if(cantidadlineas<10){//crea hijos acorde al numero de lineas
        hijos=cantidadlineas/2;
    }else{
        hijos=10;
    }
    
    vector<int> tipos(hijos);//vector para los tipos para enviar al buzon
    
    
    hijosinfo informacionlinea[hijos];//array de struct para tener informacion basica para cada hijo
    
      for (int i = 0; i < hijos; i++) {//genera el vector de tipos para poder asignarlos a los hijos
        tipos[i] = tipoinit;
        tipoinit += 10;
  
      }
    bool redistribut=false;
    int contador=0;
    int vamos=1;
    while(redistribut==false){ //determina cuantas lineas van para cada hijo de manera equitativa
        
        for(int i=0; i<hijos;i++){
            
            informacionlinea[i].max=vamos;
            if(contador<cantidadlineas){
                contador++;
            }else{
                i=hijos;
                redistribut=true;
            }
            if(i==hijos-1){
                vamos++;
            }
                
        }
        
    }
  
   
    int contadorlin=0;
    for (int i = 0; i < hijos; i++) {//distribuye las lineas basandose en la informacion anterior
        if(i==0){
            informacionlinea[i].init=1;
            informacionlinea[i].fin=informacionlinea[i].max;
            contadorlin=informacionlinea[i].fin+1;
        }else{
            informacionlinea[i].init=contadorlin;
            informacionlinea[i].fin=contadorlin+informacionlinea[i].max-1;
            contadorlin=informacionlinea[i].fin+1;
        }
    }
    
    int contaju = 0;
    
    for (int i = 0; i < hijos; i++) { //crea todos los hijos

        tipohijo = tipos[i];
        
        
        
        pid_t hijo = fork();
        int contador=1;
        filep.clear();
        filep.seekg(0, std::ios::beg); // reinicia el eof generado anteriormente
    
        while(contador<informacionlinea[i].init){//posiciona en el archivo la linea pertinente al inicio de ese hijo y de ahi parte hasta el final asignado
            getline(filep, str1);
            
            contador++;
            
        
        }
        int conttotal=informacionlinea[i].fin-informacionlinea[i].init+1;
        int cont=1;
        
        if (hijo == 0) { //los hijos que envian los mensajes con un tipo definido al buzon despues de procesar los html

            Mapeo mapa;
            string str;
            while (cont<=conttotal) {
                getline(filep, str);
                eva.aPosfija(mapa, str);//saca las etiquetas de la linea y las guarda en un map
                cont++;
                
            }
          s.Wait();
            mapa.enviarEtiqueta(bu, tipohijo);//si se sobrecarga la cantidad de lineas aqui fallan algunos mensajes y el resultado no es el deseado, funciona pero a veces falla por algunas etiquetas
          s.Signal();
            _exit(0);
        }


    }

    char etiquetar[64];
    char veces[64];
    int vecesm;
    string etiquetam;

    vector<Mapeo::etiquetasfull> mensajes(hijos);
    Mapeo::etiquetaspaso etiquetaarea;
    bool finetiquetas = false;
    bool llenarvec = false;
    bool findmin = false;
    bool finddupes = false;
    int contmin = -1;
    int cont2 = -1;
    int contarea = 0;

    while (finetiquetas == false) {//se uso un vector de 10 para trabajar los hijos, cada hijo tiene un espacio que envio todas sus etiquetas y el papa las va recibiendo y ordenando alfabeticamente
        if (llenarvec == false) { // se llena el vector inicial
            for (int i = 0; i < hijos; i++) {
                bu.Recibir(etiquetar, veces, tipos[i]);
                etiquetam = (string) etiquetar;
                vecesm = atoi(veces);
                mensajes[i].etiq = etiquetam;
                mensajes[i].veces = vecesm;

            }
            llenarvec = true;
        }
        contmin = 0;
        cont2 = 1;
        while (findmin == false) {//Se busca el mínimo del vector, es un analísis que busca "fin del mundo" para determinar el fin de los mensajes de un hijo
        

            if (mensajes[contmin].etiq.compare("fin del mundo") == 0) {
                contmin = contmin + 1;
                if (contmin == (hijos)) {
                    finetiquetas = true;
                    findmin = true;
                } else if (contmin == cont2) {
                    cont2 = cont2 + 1;
                }

            } else if (contmin == (hijos - 1)) {
                findmin = true;
            } else if (cont2 >= (hijos)) {
                findmin = true;
            } else if (mensajes[cont2].etiq.compare("fin del mundo") == 0 && (cont2 < hijos)) {//esto significa que el hijo mando su ultimo mensaje

                cont2 = cont2 + 1;

            } else if (mensajes[contmin].etiq.compare(mensajes[cont2].etiq) < 0 && (cont2 < hijos)) {
                cont2 = cont2 + 1;
                if (cont2 >= (hijos)) {
                    findmin = true;
                }
            } else if (mensajes[contmin].etiq.compare(mensajes[cont2].etiq) > 0 && (cont2 < hijos)) {
                contmin = cont2;
                cont2 = cont2 + 1;
                if (cont2 >= (hijos)) {
                    findmin = true;
                }
            } else if (mensajes[contmin].etiq.compare(mensajes[cont2].etiq) == 0 && (cont2 < hijos)) {
                cont2 = cont2 + 1;
            }

        }
        cont2 = 0;
        while (finddupes == false && finetiquetas == false) {//despues de encontrar el mínimo se buscan duplicados reemplazandolos despues de procesar
        
            if (mensajes[contmin].etiq.compare(mensajes[cont2].etiq) == 0 && (cont2 < hijos) && contmin != cont2) {
                mensajes[contmin].veces = mensajes[contmin].veces + mensajes[cont2].veces;
                bu.Recibir(etiquetar, veces, tipos[cont2]);
                etiquetam = (string) etiquetar;
                vecesm = atoi(veces);
                mensajes[cont2].etiq = etiquetam;
                mensajes[cont2].veces = vecesm;
                cont2 = cont2 + 1;
                if (cont2 >= hijos) {
                    finddupes = true;
                }
            } else {
                cont2 = cont2 + 1;
                if (cont2 >= hijos) {
                    finddupes = true;
                }
            }

        }

        if (finetiquetas == false) { //aqui se agregan las etiquetas al area compartida despues de revisar los duplicados 
            Mapeo::etiquetaspaso etiquetaarea;
            memset(etiquetaarea.etiq, 0, 255);
            copy(mensajes[contmin].etiq.begin(), mensajes[contmin].etiq.end(), etiquetaarea.etiq);
            etiquetaarea.veces = mensajes[contmin].veces;
            
            area[contarea] = etiquetaarea;
            contarea = contarea + 1;
            bu.Recibir(etiquetar, veces, tipos[contmin]);
            etiquetam = (string) etiquetar;
            vecesm = atoi(veces);
            mensajes[contmin].etiq = etiquetam;
            mensajes[contmin].veces = vecesm;
            
        }

        if (finetiquetas == false) {
            finddupes = false;
            findmin = false;
        }


    }

//por ultimo se imprime el resultado obtenido por el proceso padre
    string resultado = "";
         string number = "";
         string etiquetafinal = "";
         int a;
         bool termine = false;
         int i = 0;
         while (termine == false) {
             etiquetafinal = string(area[i].etiq);

             if (etiquetafinal == "") {
                 termine = true;
                 cout << resultado;
             } else {
                 Mapeo::etiquetaspaso etiquetaf;
                 etiquetaf = area[i];

                 a = etiquetaf.veces;
                 etiquetafinal = string(etiquetaf.etiq);
                 number = std::to_string(a);
                 resultado = resultado + etiquetafinal + ": " + number + '\n';
             }
             i++;
         }


    

    printf("Fin del programa ... \n");
    //se encarga de destruir el area compartida, el buzon y el semaforo y se cierra el archivo
    bool finprog = true;
    if (finprog == true) {
        shmdt(area);
        shmctl(id, IPC_RMID, NULL);
        s.~Semaforo();
        bu.~buzon();
        filep.close();
        
        exit(0);
        
    }


    



    
}

