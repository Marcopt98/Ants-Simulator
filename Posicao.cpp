/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Posicao.cpp
 * Author: marcoduarte
 * 
 * Created on 15 de Dezembro de 2017, 22:28
 */

#include "Posicao.h"
#include "Mundos.h"
#include "Ninhos.h"
#include "Comunidades.h"
#include "Formigas.h"
#include <iostream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <time.h>

using namespace std;

Posicao::Posicao() {
}

Posicao::Posicao(const Posicao& orig) {
    *this = orig;
}
Posicao & Posicao::operator =(const Posicao& outro){
    if(this == &outro)
        return *this;
    
    return *this;
}
Posicao * Posicao::duplica() const{
    return new Posicao(*this);
}
Posicao::~Posicao() {
}

int Posicao::setCoordX(int tLado){
    int x;
    
    x = rand() % tLado;
    
    return x;
}
int Posicao::setCoordY(int tLado){
    int y;
    
    y = rand() % tLado;
    
    return y;
}
