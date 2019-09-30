/* 
 * File:   Mapeo.h
 * Author: Alan
 *
 * Created on 29 de agosto de 2014, 01:22 PM
 */

#ifndef MAPEO_H
#define	MAPEO_H

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <cstring>
#include <string>
#include "buzon.h"

using namespace std;

class Mapeo {
public:
    Mapeo();
    virtual ~Mapeo();
    
    void addEtiqueta(const string& nombre);
    
    int tamanioMap();
    struct etiquetasfull {
          int veces;
          string etiq;
          
    };
    
    struct etiquetaspaso {
          int veces;
          char etiq[128];
          
    };
    void enviarEtiqueta(buzon &bu, int tipo);
    
    string imprimirEtiqueta();
    
private:
    typedef std::map< string, int > EtiqMapT ;
    EtiqMapT EtiqMap;
    
    
};

#endif	/* MAPEO_H */

