/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: marcoduarte
 *
 * Created on 14 de Novembro de 2017, 16:21
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ncurses.h>
#include <time.h>
#include "Comunidades.h"
#include "Mundos.h"
#include "Ninhos.h"
#include "Interface.h"
#include "Simulacao.h"
#include "Migalhas.h"
#include "Configuracao.h"

using namespace std;

/*
 * 
 */


int main(int argc, char** argv) {
    
    WINDOW *c;
    Interface *principal = new Interface;
    Configuracao *config = new Configuracao;
    Mundos *m = new Mundos;
    Ninhos *n = new Ninhos;
    Migalhas *mi = new Migalhas;
    srand(time(NULL));
    
    c = principal->setWindows();
    config->leComando(c,m,n,mi);

    delete(principal);
    delete(config);
    delete(m);
    delete(n);
    delete(mi);
    endwin();
    return 0;
}

