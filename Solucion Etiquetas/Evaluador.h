/* 
 * File:   Evaluador.h
 * Author: Alan
 *
 * Created on 29 de agosto de 2014, 01:11 PM
 */

#ifndef EVALUADOR_H
#define	EVALUADOR_H
#include <string>
#include <memory>
#include <stack> 

#include "Mapeo.h"


using namespace std;


class Evaluador {
    
public:
    Evaluador(); 
    virtual ~Evaluador();
    
    void aPosfija(Mapeo& mapa,string& lineat);
private:
    
};

#endif	/* EVALUADOR_H */

