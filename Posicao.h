/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Posicao.h
 * Author: marcoduarte
 *
 * Created on 15 de Dezembro de 2017, 22:28
 */

#ifndef POSICAO_H
#define POSICAO_H

#include <ncurses.h>

class Mundos;
class Posicao {
public:
    Posicao();
    Posicao(const Posicao& orig);
    Posicao &operator=(const Posicao& outro);
    virtual Posicao * duplica()const;
    virtual ~Posicao();
    int setCoordX(int tLado);
    int setCoordY(int tLado);
private:

};

#endif /* POSICAO_H */

