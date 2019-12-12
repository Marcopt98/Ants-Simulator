/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Configuracao.cpp
 * Author: marcoduarte
 * 
 * Created on 26 de Dezembro de 2017, 21:28
 */

#include "Configuracao.h"
#include "Comunidades.h"
#include "Mundos.h"
#include "Ninhos.h"
#include "Interface.h"
#include "Simulacao.h"
#include "Migalhas.h"

Configuracao::Configuracao() {
}

Configuracao::Configuracao(const Configuracao& orig) {
}

Configuracao::~Configuracao() {
}

void Configuracao::leFicheiro(string nomeTXT, int *flag, WINDOW *comand, Mundos *m, Ninhos *n, Migalhas *mi){
    ifstream nomeFich;
    string comando;
    int f;
    
    nomeFich.open(nomeTXT, ios::in);
     
    if(nomeFich.is_open()){
        while(!nomeFich.eof()){
            getline(nomeFich,comando);
            configSimulacao(comando, &f, comand, m, n, mi);
            *flag = f;
        
        }
        nomeFich.close();
    }
    else
        wprintw(comand,"Erro a abrir o ficheiro!\n");
    
}

void Configuracao::configSimulacao(string comando, int *flag, WINDOW *comand, Mundos *m, Ninhos *n, Migalhas *mi){
    string token;
    int parametro;

    
    istringstream iss(comando);

    
    iss >> token;
    //cout << "\n" << token;
    if(token.compare("defmundo") == 0){
        iss >> token;
        parametro = stoi(token);
        if(parametro >= 10){    
            m->setLado(parametro);
            (*flag)++;
        }
        else
            wprintw(comand,"Tamanho lateral do mundo demasiado pequeno!\n");
    }
    if(token.compare("defen") == 0){
        iss >> token;
        parametro = stoi(token);
        n->setEnergia(parametro);
        n->setEnergiaInicial(parametro);
        (*flag)++;
    }
    if(token.compare("defpc") == 0){
        iss >> token;
        parametro = stoi(token);
        
        if(parametro >= 0 || parametro <= 0){
            n->setEnCriaFormiga(parametro);
            (*flag)++;
        }
        else
            wprintw(comand,"FORMIGAS::Percentagem invalida!\n");
            
    }
    if(token.compare("defvt") == 0){
        iss >> token;
        parametro = stoi(token);
        if(parametro < n->getEnergia()){
            n->setEnergTransf(parametro);
            (*flag)++;
        }
        else
            wprintw(comand,"Transferencia superior a energia inicial do ninho!\n");
    }
    if(token.compare("defmi") == 0){
        iss >> token;
        parametro = stoi(token);
        if(parametro >= 0 || parametro <= 100){
            mi->setPerc(parametro);
            (*flag)++;
        }
        else
            wprintw(comand,"MIGALHAS::Percentagem invalida!\n");
    }
    if(token.compare("defme") == 0){
        iss >> token;
        parametro = stoi(token);
        mi->setEnerg(parametro);
        (*flag)++;
    }
    if(token.compare("defnm") == 0){
        iss >> token;
        parametro = stoi(token);
        mi->setQuant(parametro);
        (*flag)++;
    }
    
    wrefresh(comand);
}
void Configuracao::leComando(WINDOW *comando, Mundos *m, Ninhos *n, Migalhas *mi){

    string token;
    char buffer[100];
    int x, y, flag = 0;
    Simulacao *sim = new Simulacao;
    WINDOW *wsim;

    while(1){
        
        getyx(comando, y, x);
        mvwprintw(comando, y++, 2,"Introduza o comando: ");
        wgetstr(comando,buffer);
        
        wrefresh(comando);
        
        getyx(comando, y, x); //corrige bug do fim de janela.
        istringstream iss(buffer);
        iss >> token;

        if(token.compare("executa") == 0){
            while(iss){
                iss >> token;
                if(!iss)
                    mvwprintw(comando, y++,2,"Falta nome do ficheiro!\n");
                else
                    leFicheiro(token,&flag,comando, m, n, mi);
                //mvwprintw(comando, y++, 2,"%d\n",flag);
                iss >> token;
            };
            y++;
        }
        else if(strcmp(buffer,"inicio") == 0){
            if(flag == 7){
                clear();
                wclear(comando);
                refresh();
                wrefresh(comando);
    
                delwin(comando);
                
                sim->leComandos(m,n,mi);

                break;
            }  
            else
                mvwprintw(comando, y++, 2,"A simulacao ainda nao foi configurada!\n");
        }
        else if(token.compare("defmundo") == 0){
            configSimulacao(buffer, &flag, comando, m, n, mi);
            if(flag == 1)
                mvwprintw(comando, y++, 2,"Tamanho lateral do mundo configurado!\n");
        }
        else if(token.compare("defen") == 0){
            configSimulacao(buffer, &flag, comando, m, n, mi);
            if(flag == 2)
                mvwprintw(comando, y++, 2,"Energia do ninho configurada!\n");
        }
        else if(token.compare("defpc") == 0){
            configSimulacao(buffer, &flag, comando, m, n, mi);
            if(flag == 3)
                mvwprintw(comando, y++, 2,"Percentagem dos ninhos configurada!\n");
        }
        else if(token.compare("defvt") == 0){
            configSimulacao(buffer, &flag, comando, m, n, mi);
            if(flag == 4)
                mvwprintw(comando, y++, 2,"Transferencia de energia configurada!\n");
        }
        else if(token.compare("defmi") == 0){
            configSimulacao(buffer, &flag, comando, m, n, mi);
            if(flag == 5)
                mvwprintw(comando, y++, 2,"Percentagem das migalhas configurada!\n");
        }
        else if(token.compare("defme") == 0){
            configSimulacao(buffer, &flag, comando, m, n, mi);
            if(flag == 6)
                mvwprintw(comando, y++, 2,"Energia das migalhas configurada!\n");
        } 
        else if(token.compare("defnm") == 0){
            configSimulacao(buffer, &flag, comando, m, n, mi);
            if(flag == 7)
                mvwprintw(comando, y++, 2,"Migalhas por instante configurado!\n");
        }
        else if(strcmp(buffer,"sair") == 0)
            return;
        else{
            mvwprintw(comando, y++, 2, "Comando invalido!\n");
        }
        wborder(comando,0,0,0,0,0,0,0,0);
        wrefresh(comando);
        
    }
}