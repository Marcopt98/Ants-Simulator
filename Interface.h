/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interface.h
 * Author: marcoduarte
 *
 * Created on 11 de Dezembro de 2017, 15:30
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>

class Interface {
public:
    Interface();
    Interface(const Interface& orig);
    virtual ~Interface();
    WINDOW * setWindows();
    WINDOW * setWSimulacao(int flag);
    WINDOW * closeWindow(WINDOW * w);
private:

};

#endif /* INTERFACE_H */

