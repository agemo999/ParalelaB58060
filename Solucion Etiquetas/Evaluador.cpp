
#include "Evaluador.h"

Evaluador::Evaluador(){ 
}

Evaluador::~Evaluador() {
}


void Evaluador::aPosfija(Mapeo& mapa,string& lineat){ //lee las etiquetas, utiliza la pila y guarda en un map
    std::stack<string> pilastring;
    std::stack<string> pilaetiqueta;
    int p1=0;
    string texto="";
    string etiqueta="";
    string inter="";
    string primerlineab="";
    bool busqueda=false;
    bool finbusqueda=true;
    while (p1 < lineat.length()) {
        inter= lineat.substr(p1,1);
        primerlineab=lineat.substr(0,5);
        if(inter.compare("<") == 0){
            p1=p1+1;
            busqueda=true;
            finbusqueda=false;
        }else{
            if(busqueda==true){
                if(inter.compare(" ") == 0 || inter.compare(">")==0){
                    p1=p1+1;
                    busqueda=false;
                    while (!pilaetiqueta.empty()){
                        etiqueta=pilaetiqueta.top()+etiqueta;
                        pilaetiqueta.pop();
                    }
                    mapa.addEtiqueta(etiqueta);
                    etiqueta="";
                    if(inter.compare(">")==0){
                        finbusqueda=true;
                    }
                }else{
                    pilaetiqueta.push(inter);
                    p1=p1+1;
                }
            }else{
                p1=p1+1;
                if(finbusqueda==true){
                    pilastring.push(inter);
                }else if(inter.compare(">")==0){
                    finbusqueda=true;
                }
                               
            }
        }
        
    }
    
    while (!pilastring.empty()){
        texto=pilastring.top()+texto;
        pilastring.pop();
    }
        
        
    
    lineat=texto;
    
}


