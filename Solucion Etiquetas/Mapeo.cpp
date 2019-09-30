

#include <map>

#include "Mapeo.h"

Mapeo::Mapeo() {
    
}

Mapeo::~Mapeo() {
}

int Mapeo::tamanioMap() {
    int tamanio=EtiqMap.size();
    return tamanio;
      
}


void Mapeo::enviarEtiqueta(buzon &bu, int tipo) { //se envian las etiquetas a un buzon específico con un tipo
    string resultado="";
    
    map<string, int>::iterator pos;
    etiquetasfull eti;
    
    string etiqueta;
    int veces;
    
    int i=0;
    for (pos = EtiqMap.begin(); pos != EtiqMap.end(); ++pos) {//envia las etiquetas del map
        veces=pos->second;
        etiqueta=pos->first;
        char *etiqu = (char *)etiqueta.c_str();
        stringstream ss;
        ss << veces;
        string str = ss.str();
        char *vecesu=(char *)str.c_str(); 
        bu.Enviar(vecesu,etiqu,tipo);
        
        
    }
    etiqueta="fin del mundo";//etiqueta final que termina la busqueda
    char *etiqu = (char *)etiqueta.c_str();
        
    bu.Enviar(etiqu,etiqu,tipo);
        
    
    
}




void Mapeo::addEtiqueta(const string& nombre) { //agrega las etiquetas con al map, si no esta lo crea, si esta le agrega 1
    map<string, int>::iterator p = EtiqMap.find(nombre);
    
    if(p != EtiqMap.end()){
        int prueba=p->second;
        prueba=prueba+1;
        p->second = prueba;
    }else{
        EtiqMap.insert(pair<string, int> (nombre, 1));
    }
    
    
}

string Mapeo::imprimirEtiqueta() {// imprime las etiquetas del map
    string resultado="";
    map<string, int>::iterator pos;
    
    string number;          
    
    for (pos = EtiqMap.begin(); pos != EtiqMap.end(); ++pos) {
        int a=pos->second;
        number="";
        number=std::to_string(a);
        resultado= resultado + pos->first +": "+number+'\n';
        
    }
    
    return resultado;
    
}

