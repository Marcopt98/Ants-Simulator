/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Migalhas.cpp
 * Author: Marco
 * 
 * Created on 13 de Dezembro de 2017, 0:38
 */

#include "Migalhas.h"

Migalhas::Migalhas() {
}
Migalhas::Migalhas(const Migalhas& orig) {
    *this = orig;
}
Migalhas & Migalhas::operator =(const Migalhas& outro){
    if(this == &outro)
        return *this;
    
    energia = outro.energia;
    max_migalhas = outro.max_migalhas;
    percentagem = outro.percentagem;
    posX = outro.posX;
    posY = outro.posY;
    
    return *this;
}
Migalhas * Migalhas::duplica() const{
    return new Migalhas(*this);
}

Migalhas::~Migalhas(){}

void Migalhas::setPerc(int perc){
    percentagem = perc;
}

void Migalhas::setQuant(int max){
    max_migalhas = max;
}

int Migalhas::getPosX(){
    return posX;
}
int Migalhas::getPosY(){
    return posY;
}
void Migalhas::setEnerg(int energ){
    energia = energ;
}
Migalhas::Migalhas(int energ, int x, int y){
    energia = energ;
    posX = x;
    posY = y;
}

int Migalhas::getEnerg(){
    return energia;
}
int Migalhas::getPerc(){
    return percentagem;
}
int Migalhas::getMax(){
    return max_migalhas;
}
void Migalhas::listaInformacao(WINDOW *d){
    int yd, xd;
    
    getyx(d, yd, xd);
    wmove(d, yd, xd);
    mvwprintw(d, yd++, 1, "->Migalhas:\n");
    mvwprintw(d, yd++, 1, "Energia: %d | PosX: %d | PosY: %d\n", getEnerg(), getPosX(), getPosY());
    wrefresh(d);
}
