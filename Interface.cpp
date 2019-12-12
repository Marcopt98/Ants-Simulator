/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interface.cpp
 * Author: marcoduarte
 * 
 * Created on 11 de Dezembro de 2017, 15:30
 */

#include "Interface.h"

Interface::Interface() {
}

Interface::Interface(const Interface& orig) {
}

Interface::~Interface() {
}

WINDOW * Interface::setWindows(){
    
    initscr(); //Inicializa o ecrã.
    wborder(stdscr,0,0,0,0,0,0,0,0);

    start_color();
    WINDOW *comand = newwin(20,120,18,20);
    wmove(comand,2,2);
    wborder(comand,0,0,0,0,0,0,0,0);
    scrollok(comand, TRUE);
    //mousemask(ALL_MOUSE_EVENTS, NULL);
    
    init_pair(1,COLOR_BLUE,COLOR_WHITE);
    init_pair(2,COLOR_BLACK,COLOR_WHITE);
    //move(3, 25);
    bkgd(COLOR_PAIR(1));
    
    mvprintw(2,40,"================================================================================");
    mvprintw(3,40,"||---------------------------Simulacao Formigueiros---------------------------||");
    mvprintw(4,40,"================================================================================");
    wbkgd(comand,COLOR_PAIR(2));
    //bkgd(COLOR_PAIR(2));

    refresh();
    wrefresh(comand);
    
    return comand;
}

WINDOW * Interface::setWSimulacao(int flag){
    
    initscr();
    start_color();
    WINDOW *m = newwin(36,120,0,0);
    WINDOW *c = newwin(12,160,36,0);
    WINDOW *d = newwin(36,40,0,120);

    wmove(c,0,1);
    wmove(d,1,1);
    wmove(m,18,60);
    wborder(d,0,0,0,0,0,0,0,0);
    //idlok(c, TRUE);
    scrollok(c, TRUE);
    scrollok(d, TRUE);
    
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    wbkgd(m,COLOR_PAIR(1));
    wbkgd(c,COLOR_PAIR(2));
    wbkgd(d,COLOR_PAIR(2));
    
    wrefresh(m);
    wrefresh(c);
    wrefresh(d);
    if(flag == 0)
        return m;
    if(flag == 1)
        return c;
    if(flag == 2)
        return d;
    
    return 0;
}

WINDOW * Interface::closeWindow(WINDOW * w){
    
    werase(w);
    delwin(w);

    return 0;
}