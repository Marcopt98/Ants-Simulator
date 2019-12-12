/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Simulacao.h
 * Author: marcoduarte
 *
 * Created on 11 de Dezembro de 2017, 18:37
 */

#ifndef SIMULACAO_H
#define SIMULACAO_H

#include <string>
#include <iostream>
#include <sstream>
#include <ncurses.h>
#include <vector>

class Mundos;
class Ninhos;
class Migalhas;

using namespace std;

class Simulacao {
    vector <Mundos *> copiasMundos;
public:
    Simulacao();
    Simulacao(const Simulacao& orig);
    virtual ~Simulacao();
    WINDOW * iniciaSimulacao();
    void leComandos(Mundos *mundo, Ninhos *ninho, Migalhas *migalha);
    void setNome(string n);
    string getNome();
    void guardaMundo(Mundos **mundo, string nome);
    void mudaMundo(Mundos **atual, string nome);
    int apagaMundo(string nome);
private:

};

#endif /* SIMULACAO_H */

