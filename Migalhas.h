/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Migalhas.h
 * Author: Marco
 *
 * Created on 13 de Dezembro de 2017, 0:38
 */

#ifndef MIGALHAS_H
#define MIGALHAS_H

#include <ncurses.h>

class Migalhas {
    int energia, posX, posY, percentagem, max_migalhas;
public:
    Migalhas();
    Migalhas(const Migalhas& orig);
    Migalhas &operator=(const Migalhas& outro);
    virtual Migalhas * duplica()const;
    virtual ~Migalhas();
    int getPosX();
    int getPosY();
    void setPerc(int perc);
    void setQuant(int max);
    void setEnerg(int energ);
    Migalhas(int energ, int x, int y);
    int getEnerg();
    int getPerc();
    int getMax();
    void listaInformacao(WINDOW *d);
    
};

#endif /* MIGALHAS_H */

