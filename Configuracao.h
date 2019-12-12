/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Configuracao.h
 * Author: marcoduarte
 *
 * Created on 26 de Dezembro de 2017, 21:28
 */

#ifndef CONFIGURACAO_H
#define CONFIGURACAO_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ncurses.h>

class Ninhos;
class Mundos;
class Migalhas;

using namespace std;

class Configuracao {
public:
    Configuracao();
    Configuracao(const Configuracao& orig);
    virtual ~Configuracao();
    void configSimulacao(string comando, int *flag, WINDOW *comand, Mundos *m, Ninhos *n, Migalhas *mi);
    void leFicheiro(string nomeTXT, int *flag, WINDOW *comand, Mundos *m, Ninhos *n, Migalhas *mi);
    void leComando(WINDOW *comando, Mundos *m, Ninhos *n, Migalhas *mi);
private:

};

#endif /* CONFIGURACAO_H */

