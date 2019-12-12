/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Formigas.cpp
 * Author: marcoduarte
 * 
 * Created on 22 de Novembro de 2017, 15:07
 */

#include "Formigas.h"
#include "Posicao.h"
#include "Mundos.h"
#include "Comunidades.h"
#include "Regra.h"

int Formigas::ID_counter = 0;

Formigas::Formigas(){}
Formigas::Formigas(Mundos *m, int energ, int rM, int rV, char tp) {
    ID += ID_counter++;
    energia = energ;
    raioM = rM;
    raioV = rV;
    tipo = tp;
    iter = 0;
    ninho = false;
    posX = pos->setCoordX(m->getLado());
    posY = pos->setCoordY(m->getLado());
    
}

Formigas::Formigas(int energ, int rM, int rV, char tp, int c, int l){
    ID += ID_counter++;
    energia = energ;
    raioM = rM;
    raioV = rV;
    tipo = tp;
    iter = 0;
    ninho = false;
    posX = c;
    posY = l;
}
Formigas::Formigas(const Formigas& orig) {
    pos = nullptr;
    *this = orig;
}
Formigas & Formigas::operator=(const Formigas& outro){
    if(this == &outro)
        return *this;
    
    for(unsigned int i = 0; i < regras.size(); i++)
        delete regras[i];
    regras.clear();
    
    for(unsigned int i = 0; i < outro.regras.size(); i++)
        regras.push_back(outro.regras[i]->duplica());
    
    energia = outro.energia;
    iter = outro.iter;
    ninho = outro.ninho;
    posX = outro.posX;
    posY = outro.posY;
    raioM = outro.raioM;
    raioV = outro.raioV;
    tipo = outro.tipo;
    
    return *this;
}
Formigas::~Formigas() {
    int i;
    for(i = 0; i < regras.size(); i++)
        delete regras[i];
    regras.clear();
    
    delete pos;
}

bool Formigas::getInNinho(){
    return ninho;
}

void Formigas::setInNinho(bool condicao){
    ninho = condicao;
}
bool Formigas::isViva()const{
    return energia > 0;
}

int Formigas::getPosY(){
    return posY;
}

int Formigas::getPosX(){
    return posX;
}
int Formigas::getRaioMov(){
    return raioM;
}
int Formigas::getRaioVisao(){
    return raioV;
}
int Formigas::getID(){
    return ID;
}
int Formigas::getEnergia(){
    return energia;
}
char Formigas::getTipo(){
    return tipo;
}
void Formigas::setEnergia(int energ){
    energia = energ;
}
void Formigas::setIter(int iteracao){
    iter = iteracao;
}
int Formigas::getIter(){
    return iter;
}
void Formigas::setX(int x){
    posX = x;
}

void Formigas::setY(int y){
    posY = y;
}

void Formigas::listaInformacao(WINDOW *d){
    
    int y, x;
    
    getyx(d,y,x);
    
    mvwprintw(d, y++, 1, "-> Formigas:\n");
    mvwprintw(d, y++, 1, "ID: %d | Energia: %d | Tipo: %c", getID(),
            getEnergia(), getTipo());
    mvwprintw(d, y++, 1, "RaioM: %d | RaioV: %d\n", getRaioMov(), getRaioVisao());
    
    wrefresh(d);
}

void Formigas::defineRegras(int flag){
    Regra *nova;
    
    if(flag == 1){
        nova = new RegraFoge();
        regras.push_back(nova);
        nova = new RegraComeMigalha();
        regras.push_back(nova);
        nova = new RegraProcuraMigalha();
        regras.push_back(nova);
        nova = new RegraVaiParaNinho();
        regras.push_back(nova);
        nova = new RegraPasseia();
        regras.push_back(nova);
    }
    if(flag == 2){
        nova = new RegraProtege();
        regras.push_back(nova);
        nova = new RegraComeMigalha();
        regras.push_back(nova);
        nova = new RegraProcuraMigalha();
        regras.push_back(nova);
        nova = new RegraPasseia();
        regras.push_back(nova);
    }
    if(flag == 3){
        nova = new RegraAssalta();
        regras.push_back(nova);
        nova = new RegraPersegue();
        regras.push_back(nova);
        nova = new RegraComeMigalha();
        regras.push_back(nova);
        nova = new RegraProcuraMigalha();
        regras.push_back(nova);
        nova = new RegraPasseia();
        regras.push_back(nova);
    }
    if(flag == 4){
        nova = new RegraComeMigalha();
        regras.push_back(nova);
        nova = new RegraPasseia();
        regras.push_back(nova);
    }
    if(flag == 5){
        nova = new RegraAssaltaNinho();
        regras.push_back(nova);
        nova = new RegraComeMigalha();
        regras.push_back(nova);
        nova = new RegraPasseia();
        regras.push_back(nova);
    }
    if(flag == 6){
        nova = new RegraProcuraMigalha();
        regras.push_back(nova);
        nova = new RegraComeMigalha();
        regras.push_back(nova);
        nova = new RegraProtege();
        regras.push_back(nova);
    }
}

void Formigas::percorreRegras(Mundos* mundo, WINDOW* m){
    int i;
    if(this->getInNinho() == false){
        for(i = 0; i < regras.size(); i++){
            if(regras[i]->condicao(mundo, this, m) == true){
                regras[i]->agir(mundo, this, m);
                break;
            }
        }
    }
}
