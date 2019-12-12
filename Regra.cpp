/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Regra.cpp
 * Author: marcoduarte
 * 
 * Created on 4 de Janeiro de 2018, 13:56
 */

#include "Regra.h"
#include "Mundos.h"
#include "Formigas.h"
#include "Posicao.h"
#include "Ninhos.h"
#include "Migalhas.h"

Regra::Regra() {
}

Regra::Regra(const Regra& orig) {
    *this = orig;
}
Regra & Regra::operator =(const Regra& outro){
    if(this == &outro)
        return *this;
    
    return *this;
}
Regra::~Regra() {
}

//#########################################################
//****Secção do código referente à RegraFoge****
//#########################################################

bool RegraFoge::condicao(Mundos* mundo, Formigas* f, WINDOW *m){
    Formigas *inim = mundo->getInimiga(f, 1);
    if(inim != nullptr)
        return true;
    else
        return false;
}

void RegraFoge::agir(Mundos* mundo, Formigas* f, WINDOW *m){
    int x, y, xi, yi, x1, y1, cX, cY;
    Posicao *pos;
    
        
    if(condicao(mundo, f, m) == true){
        Formigas *inim = mundo->getInimiga(f, 1);
        x = f->getPosX();
        y = f->getPosY();
        xi = inim->getPosX();
        yi = inim->getPosY();

        if(x < xi && y < yi){
            do{
                x1 = pos->setCoordX(mundo->getLado());
                y1 = pos->setCoordY(mundo->getLado());
            }while(max(abs(x - x1), abs(y - y1)) > f->getRaioMov() || x1 > x || y1 > y);
            f->setX(x1);
            f->setY(y1);
            f->setEnergia(f->getEnergia() - (1 + abs(x - x1) + abs(y - y1)));
        }
        if(x > xi && y > yi){
            do{
                x1 = pos->setCoordX(mundo->getLado());
                y1 = pos->setCoordY(mundo->getLado());
            }while(max(abs(x - x1), abs(y - y1)) > f->getRaioMov() || x1 < x || y1 < y);
            f->setX(x1);
            f->setY(y1);
            f->setEnergia(f->getEnergia() - (1 + abs(x - x1) + abs(y - y1)));
        }
        if(x > xi && y < yi){
            do{
                x1 = pos->setCoordX(mundo->getLado());
                y1 = pos->setCoordY(mundo->getLado());
            }while(max(abs(x - x1), abs(y - y1)) > f->getRaioMov() || x1 < x || y1 > y);
            f->setX(x1);
            f->setY(y1);
            f->setEnergia(f->getEnergia() - (1 + abs(x - x1) + abs(y - y1)));
        }
        if(x < xi && y > yi){
            do{
                x1 = pos->setCoordX(mundo->getLado());
                y1 = pos->setCoordY(mundo->getLado());
            }while(max(abs(x - x1), abs(y - y1)) > f->getRaioMov() || x1 > x || y1 < y);
            f->setX(x1);
            f->setY(y1);
            f->setEnergia(f->getEnergia() - (1 + abs(x - x1) + abs(y - y1)));
        }
    }  
}

//#########################################################
//****Secção do código referente à RegraPersegue****
//#########################################################

bool RegraPersegue::condicao(Mundos* mundo, Formigas* f, WINDOW *m){
    Formigas *inim = mundo->getInimiga(f, 3);
    if(inim != nullptr)
        return true;
    else
        return false;
}

void RegraPersegue::agir(Mundos* mundo, Formigas* f, WINDOW *m){
    int x, y;
    Posicao *pos;
    
    if(condicao(mundo, f, m) == true){
        Formigas *inim = mundo->getInimiga(f, 3);
        do{
            x = pos->setCoordX(mundo->getLado());
            y = pos->setCoordY(mundo->getLado());
        }while(abs(x - f->getPosX()) + abs(y - f->getPosY()) < f->getRaioMov() ||
                abs(x - f->getPosX()) + abs(y - f->getPosY()) > f->getRaioMov() || abs(x - inim->getPosX()) +
                abs(y - inim->getPosY()) >= abs(f->getPosX() - inim->getPosX()) + abs(f->getPosY() - inim->getPosY()));
        f->setEnergia(f->getEnergia() - (1 + abs(f->getPosX() - x) + abs(f->getPosY() - y)));
        f->setX(x);
        f->setY(y);
    }
}

//#########################################################
//****Secção do código referente à RegraAssalta****
//#########################################################

bool RegraAssalta::condicao(Mundos* mundo, Formigas* f, WINDOW *m){
    Formigas *inim = mundo->getInimiga(f, 2);
    if(inim != nullptr)
        return true;
    else
        return false;
}

void RegraAssalta::agir(Mundos* mundo, Formigas* f, WINDOW *m){
    if(condicao(mundo, f, m) == true){
       Formigas *inim = mundo->getInimiga(f, 2);
       f->setEnergia(f->getEnergia() + inim->getEnergia()/2);
       inim->setEnergia(inim->getEnergia()/2);
    }
}

//#########################################################
//****Secção do código referente à RegraAssaltaNinho****
//#########################################################

bool RegraAssaltaNinho::condicao(Mundos* mundo, Formigas* f, WINDOW *m){
    Ninhos *inim = mundo->getNinho(f, 2);
    if(inim != nullptr){
        if(inim->getEnergia() > inim->getEnergiaInicial()/2){
            return true;
        }
    }
    
    return false;
}

void RegraAssaltaNinho::agir(Mundos* mundo, Formigas* f, WINDOW *m){
    int x, y;
    Posicao *pos;
    if(condicao(mundo, f, m) == true){
       Ninhos *inim = mundo->getNinho(f, 2);
       if(max(abs(f->getPosX() - inim->getCoordX()), abs(f->getPosY() - inim->getCoordY())) <= f->getRaioMov()){
           f->setEnergia(f->getEnergia() + inim->getEnergia()/4);
           inim->setEnergia( inim->getEnergia() - (inim->getEnergia()/4));
       }
       else{
           do{
               x = pos->setCoordX(mundo->getLado());
               y = pos->setCoordY(mundo->getLado());
           }while((abs(x - inim->getCoordX()) + abs(y - inim->getCoordY())) > abs(f->getPosX() - inim->getCoordX()) + abs(f->getPosY() - inim->getCoordY()));
           f->setEnergia(f->getEnergia() - (1 + abs(f->getPosX() - x) + abs(f->getPosY() - y)));
           f->setX(x);
           f->setY(y);
       }
    }
}

//#########################################################
//****Secção do código referente à RegraProtege****
//#########################################################

bool RegraProtege::condicao(Mundos* mundo, Formigas* f, WINDOW *m){
    Formigas *inim = mundo->getInimiga(f, 1);
    Formigas *aliada = mundo->getAliada(f);
    if(aliada != nullptr && inim != nullptr){
        return true;
    }
    return false;
}

void RegraProtege::agir(Mundos* mundo, Formigas* f, WINDOW *m){
    int y,x;
    Posicao *pos;
    if(condicao(mundo, f, m) == true){
        Formigas *inim = mundo->getInimiga(f, 1);
        Formigas *aliada = mundo->getAliada(f);
        y = (aliada->getPosY() + inim->getPosY())/2;
        x = (aliada->getPosX() + inim->getPosX())/2;
        if(max(abs(f->getPosX() - x), abs(f->getPosY() - y)) <= f->getRaioMov()){
            f->setEnergia(f->getEnergia() - (1 + abs(f->getPosX() - x) + abs(f->getPosY() - y)));
            f->setX(x);
            f->setY(y);
        }
        else{
            do{
                x = pos->setCoordX(mundo->getLado());
                y = pos->setCoordY(mundo->getLado());
            }while(abs(x - inim->getPosX()) + abs(y - inim->getPosY())
                    >= abs(f->getPosX() - inim->getPosX()) + abs(f->getPosY() - inim->getPosY()) ||
                    abs(x - aliada->getPosX()) + abs(y - aliada->getPosY())
                    >= abs(f->getPosX() - aliada->getPosX()) + abs(f->getPosY() - aliada->getPosY()) ||
                    abs(x - f->getPosX()) + abs(y - f->getPosY())
                    > f->getRaioMov());
            f->setEnergia(f->getEnergia() - (1 + abs(x - f->getPosX()) + abs(y - f->getPosY())));
            f->setX(x);
            f->setY(y);
        }
    }
}

//#########################################################
//****Secção do código referente à RegraProcuraMigalha****
//#########################################################

bool RegraProcuraMigalha::condicao(Mundos* mundo, Formigas* f, WINDOW *m){
    Migalhas *mig = mundo->getMigalha(f, 2);
    if(mig != nullptr)
        return true;
    return false;
}

void RegraProcuraMigalha::agir(Mundos* mundo, Formigas* f, WINDOW *m){
    int x, y;
    Posicao *pos;
    if(condicao(mundo, f, m) == true){
        Migalhas *mig = mundo->getMigalha(f, 2);
        
        do{
            x = pos->setCoordX(mundo->getLado());
            y = pos->setCoordY(mundo->getLado());
        }while(abs(x - mig->getPosX()) + abs(y - mig->getPosY()) >=
                abs(f->getPosX() - mig->getPosX()) + abs(f->getPosY() - mig->getPosY()));
        
        f->setEnergia(f->getEnergia() - (1 + abs(x - f->getPosX()) + abs(y - f->getPosY())));
        f->setX(x);
        f->setY(y);
    }
}
//#########################################################
//****Secção do código referente à RegraComeMigalha****
//#########################################################

bool RegraComeMigalha::condicao(Mundos* mundo, Formigas* f, WINDOW *m){
    Migalhas *mig = mundo->getMigalha(f, 1);
    if(mig != nullptr)
        return true;
    return false;
}

void RegraComeMigalha::agir(Mundos* mundo, Formigas* f, WINDOW *m){
    if(condicao(mundo, f, m) == true){
        Migalhas *mig = mundo->getMigalha(f, 1);
        
        if(f->getTipo() == 'C'){
            f->setEnergia(f->getEnergia() + mig->getEnerg()/2);
            mig->setEnerg(mig->getEnerg()/2);
        }
        if(f->getTipo() == 'V'){
            f->setEnergia(f->getEnergia() + mig->getEnerg()*0.75);
            mig->setEnerg(mig->getEnerg()*0.25);
        }
        if(f->getTipo() == 'A'){
            f->setEnergia(f->getEnergia() + mig->getEnerg()*0.25);
            mig->setEnerg(mig->getEnerg()+0.75);
        }
        if(f->getTipo() == 'E'){
            f->setEnergia(f->getEnergia() + mig->getEnerg());
            mig->setEnerg(0);
        }
        if(f->getTipo() == 'S'){
            f->setEnergia(f->getEnergia() + mig->getEnerg());
            mig->setEnerg(0);
        }
    }
}

//#########################################################
//****Secção do código referente à RegraVaiParaNinho****
//#########################################################

bool RegraVaiParaNinho::condicao(Mundos* mundo, Formigas* f, WINDOW *m){
    Ninhos *n = mundo->getNinho(f, 1);
    if(f->getTipo() == 'C'){
        if(f->getEnergia() > 100 || f->getEnergia() < 50){
            if(n != nullptr){
                if(f->getIter() > 10)
                    return true;
            }
            
        }
        return false;
    }
    if(f->getTipo() == 'V'){
        if(f->getEnergia() > 150 || f->getEnergia() < 75){
            if(n != nullptr){
                if(f->getIter() > 10)
                    return true;
            }
            
        }
        return false;
    }
    if(f->getTipo() == 'A'){
        if(f->getEnergia() > 80 || f->getEnergia() < 40){
            if(n != nullptr){
                if(f->getIter() > 10)
                    return true;
            }
            
        }
        return false;
    }
    if(f->getTipo() == 'E'){
        if(f->getEnergia() > 200 || f->getEnergia() < 100){
            if(n != nullptr){
                if(f->getIter() > 10)
                    return true;
            }
            
        }
        return false;
    }
    if(f->getTipo() == 'S'){
        if(f->getEnergia() > 200 || f->getEnergia() < 100){
            if(n != nullptr){
                if(f->getIter() > 10)
                    return true;
            }
            
        }
        return false;
    }
    return false;
}

void RegraVaiParaNinho::agir(Mundos* mundo, Formigas* f, WINDOW *m){
    int x, y;
    Posicao *pos;
    if(condicao(mundo, f, m) == true){
        Ninhos *n = mundo->getNinho(f, 1);
        if(max(abs(f->getPosX() - n->getCoordX()), abs(f->getPosY() - n->getCoordY())) <= f->getRaioMov()){
            f->setEnergia(f->getEnergia() - (1 + abs(f->getPosX() - n->getCoordX()) + abs(f->getPosY() - n->getCoordY())));
            f->setX(n->getCoordX());
            f->setY(n->getCoordY());
            f->setIter(0);
            f->setInNinho(true);
        }
        else{
            do{
                x = pos->setCoordX(mundo->getLado());
                y = pos->setCoordY(mundo->getLado());
            }while((abs(x - n->getCoordX()) + abs(y - n->getCoordY())) > 
            (abs(f->getPosX() - n->getCoordX()) + abs(f->getPosY() - n->getCoordY())));
            f->setEnergia(f->getEnergia() - (1 + abs(f->getPosX() - x) + abs(f->getPosY() - y)));
            f->setX(x);
            f->setY(y);
            f->setInNinho(true);
        }
    }
}

//#########################################################
//****Secção do código referente à RegraPasseia****
//#########################################################

bool RegraPasseia::condicao(Mundos* mundo, Formigas* f, WINDOW *m){
    return true;
}

void RegraPasseia::agir(Mundos* mundo, Formigas* f, WINDOW *m){
    
    if(condicao(mundo, f, m) == true){
        int cX, cY, pX1, pY1, pX, pY;
        Posicao *pos;

        pX = f->getPosX();
        pY = f->getPosY();

        do{
            pX1 = pos->setCoordX(mundo->getLado());
            pY1 = pos->setCoordY(mundo->getLado());
        }while(max(abs(pX - pX1), abs(pY - pY1)) > f->getRaioMov());

        if(f->getInNinho() == false){
            f->setX(pX1);
            f->setY(pY1);
            f->setEnergia(f->getEnergia() - (1 + abs(pX - pX1) + abs(pY - pY1)));
        }
        else
            return;
    }
}