/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Semaforo.h
 * Author: osboxes
 *
 * Created on September 5, 2018, 4:24 PM
 */

#ifndef SEMAFORO_H
#define SEMAFORO_H
#define KEY 0xB58060

class Semaforo {
public:
    Semaforo(int v=0);
    Semaforo(const Semaforo& orig);
    virtual ~Semaforo();
    int Wait();
    int Signal();
private:
    
    int id;
    int st;
};

#endif /* SEMAFORO_H */

