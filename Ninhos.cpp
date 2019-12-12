/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ninhos.cpp
 * Author: marcoduarte
 * 
 * Created on 22 de Novembro de 2017, 15:07
 */

#include "Ninhos.h"
#include "Mundos.h"
#include "Formigas.h"

int Ninhos::ID_counter = 0;

Ninhos::Ninhos(){
}
Ninhos::Ninhos(const Ninhos& orig) {
    *this = orig;
}
Ninhos & Ninhos::operator=(const Ninhos& outro){
    if(this == &outro)
        return *this;
    
    ID = outro.ID;
    ID_counter = outro.ID_counter;
    coordX = outro.coordX;
    coordY = outro.coordY;
    energia = outro.energia;
    energ_transf = outro.energ_transf;
    energ_cf = outro.energ_cf;
    energia_inicial = outro.energia_inicial;
    
    return *this;
}
Ninhos * Ninhos::duplica() const{
    return new Ninhos(*this);
}
Ninhos::~Ninhos() {
}

void Ninhos::setEnergia(int energ){
    energia = energ;
}
void Ninhos::setEnergiaInicial(int energ){
    energia_inicial = energ;
}
void Ninhos::setEnCriaFormiga(int valor){
    energ_cf = valor;
}

void Ninhos::setEnergTransf(int etransf){
    energ_transf = etransf;
}

int Ninhos::getEnergia(){
    return energia;
}

int Ninhos::getEnergiaInicial(){
    return energia_inicial;
}
int Ninhos::getEnergTransf()const{
    return energ_transf;
}

int Ninhos::getEnCriaFormiga()const{
    return energ_cf;
}

int Ninhos::getID(){
    return ID;
}

Ninhos::Ninhos(int energ, int enTransf, int enCF, int cX, int cY){
    ID += ID_counter++;
    energia = energ;
    energia_inicial = energ;
    energ_transf = enTransf;
    energ_cf = enCF;
    coordX = cX;
    coordY = cY;
}

void Ninhos::setCoordX(int x){
    coordX = x;
}

int Ninhos::getCoordX()const{
    return coordX;
}

void Ninhos::setCoordY(int y){
    coordY = y;
}

int Ninhos::getCoordY()const{
    return coordY;
}
void Ninhos::listaInformacao(WINDOW *d){
    
    int y, x;
    
    getyx(d,y,x);
    
    mvwprintw(d, y++, 1, "-> Ninhos:\n");
    mvwprintw(d, y++, 1, "ID: %d | Energia: %d\n", getID(),
            getEnergia());
    mvwprintw(d, y++, 1, "EnTransf: %d | EnCriaForm: %d\n", getEnergTransf(),
            getEnCriaFormiga());
    
    wrefresh(d);
}

void Ninhos::criaFormigas(Mundos *mundo){
    char tf;
    string tipo;
    stringstream iss;
    if(this->getEnergia() >= this->getEnergiaInicial() + (this->getEnergiaInicial() * (this->getEnCriaFormiga() * 0.01))){
        if(mundo->verificaFormigasCFN(this) == 0){
            tf = randomTipoFormiga();
            iss << tf;
            iss >> tipo;
            mundo->acaoCF(tipo,this->getID(),1,this->getCoordX(), this->getCoordY(), mundo);
            if(tipo.compare("C") == 0)
                this->setEnergia(this->getEnergia() - 100);
            if(tipo.compare("V") == 0)
                this->setEnergia(this->getEnergia() - 150);
            if(tipo.compare("A") == 0)
                this->setEnergia(this->getEnergia() - 80);
            if(tipo.compare("E") == 0)
                this->setEnergia(this->getEnergia() - 200);
            if(tipo.compare("S") == 0)
                this->setEnergia(this->getEnergia() - 50);
        }
    }
}

char Ninhos::randomTipoFormiga(){
    int tf;
    
    tf = rand() % 5 + 1;
    
    if(tf == 1)
        return 'C';
    if(tf == 2)
        return 'V';
    if(tf == 3)
        return 'A';
    if(tf == 4)
        return 'E';
    if(tf == 5)
        return 'S';
    return 'X';
}

void Ninhos::verificaSaidaNinho(Formigas *f){
    if(f->getInNinho() == true){
        if(f->getTipo() == 'C'){
            if(f->getEnergia() < 100 && f->getEnergia() > 50)
                f->setInNinho(false);
            if(this->getEnergia() == 1 && f->getEnergia() < 50)
                f->setInNinho(false);
        }
        if(f->getTipo() == 'V'){
            if(f->getEnergia() < 150 && f->getEnergia() > 75)
                f->setInNinho(false);
            if(this->getEnergia() == 1 && f->getEnergia() < 75)
                f->setInNinho(false);
        }
        if(f->getTipo() == 'A'){
            if(f->getEnergia() < 80 && f->getEnergia() > 40)
                f->setInNinho(false);
            if(this->getEnergia() == 1 && f->getEnergia() < 40)
                f->setInNinho(false);
        }
        if(f->getTipo() == 'E'){
            if(f->getEnergia() < 200 && f->getEnergia() > 100)
                f->setInNinho(false);
            if(this->getEnergia() == 1 && f->getEnergia() < 100)
                f->setInNinho(false);
        }
        if(f->getTipo() == 'S'){
            if(f->getEnergia() < 50 && f->getEnergia() > 25)
                f->setInNinho(false);
            if(this->getEnergia() == 1 && f->getEnergia() < 25)
                f->setInNinho(false);
        }        
    }
}