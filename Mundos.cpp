/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mundos.cpp
 * Author: marcoduarte
 * 
 * Created on 21 de Novembro de 2017, 22:43
 */

#include <iostream>
#include <time.h>
#include <random>
#include <ncurses.h>
#include "Mundos.h"
#include "Interface.h"
#include "Ninhos.h"
#include "Comunidades.h"
#include "Posicao.h"
#include "Migalhas.h"
#include "Formigas.h"

using namespace std;

Mundos::Mundos() {
}
Mundos::Mundos(Mundos *mundo) {
    
}
Mundos::Mundos(const Mundos& orig) {
    *this = orig;
}
Mundos & Mundos::operator=(const Mundos& outro){
    if(this == &outro)
        return *this;
    
    for(unsigned int i = 0; i < comunidades.size(); i++)
        delete comunidades[i];
    comunidades.clear();
    
    for(unsigned int i = 0; i < outro.comunidades.size(); i++)
        comunidades.push_back(outro.comunidades[i]->duplica());
    
    for(unsigned int i = 0; i < migalhas.size(); i++)
        delete migalhas[i];
    migalhas.clear();
    
    for(unsigned int i = 0; i < outro.migalhas.size(); i++)
        migalhas.push_back(outro.migalhas[i]->duplica());
    
    nome = outro.nome;
    tamLado = outro.tamLado;
    
    return *this;
}
Mundos::~Mundos() {
    int i;
    for(i = 0; i < comunidades.size(); i++)
        delete comunidades[i];
    comunidades.clear();
    
    for(i = 0; i < migalhas.size(); i++)
        delete migalhas[i];
    migalhas.clear();
}

void Mundos::setLado(int tLado){
    tamLado = tLado;
}

int Mundos::getLado()const{
    return tamLado;
}

void Mundos::adicionaComunidade(int energ,int enTransf, int enCF, int cX, int cY, WINDOW *m){
    int x, y;
    
    Comunidades * nova = new Comunidades(energ, enTransf, enCF, cX, cY);
    comunidades.push_back(nova);
}

void Mundos::criaMundo(WINDOW *m){
    int a, y, x, num1, num2, cont = 0;
    Interface mundo;
    start_color();
    
    y = (18 + getLado()/2);
    x = (60 + getLado()/2);
    wmove(m,y,x);
    num1 = 9;
    for(a=0;a<getLado();a++){
        mvwprintw(m,y,x,"_");
        mvwprintw(m,y-getLado()-1,x,"_");
        if(cont == 10){
            num1 = 9;
            cont = 0;
        }
        //mvwprintw(m,y-getLado()-3,x,"%d", num1);
        mvwprintw(m,y-getLado()-2,x - 1,"%d", num1--);
        cont++;
        x--;
        wmove(m,y+getLado(),x);
    }
    num1 = getLado();
    for(a=0;a<getLado()+1;a++){
        mvwprintw(m,y,x-1,"|");
        mvwprintw(m,y,x-3,"%d", num1--);
        mvwprintw(m,y,x+getLado()+1,"|");
        y--;
        wmove(m,y,x-getLado());
    }

    wrefresh(m);
}

void Mundos::desenhaMundo(Mundos* mundo, WINDOW *m){
    int i, x, y;
    Ninhos *n;
    werase(m);
    criaMundo(m);

    x = (60 - getLado()/2);
    y = (18 - getLado()/2);
    wmove(m,y,x);
    
    for(i = 0; i < migalhas.size(); i++){
        mvwprintw(m, y + migalhas[i]->getPosY(), x + migalhas[i]->getPosX(), "*");
        wrefresh(m);
    }
    for(i = 0; i < comunidades.size(); i++){
        comunidades[i]->percorreFormigas(mundo,m, 1, 0, 0);
    }
    for(i = 0; i < comunidades.size(); i++){
        n = comunidades[i]->getNinho();
        mvwprintw(m, y + n->getCoordY(), x + n->getCoordX(), "#");
        wrefresh(m);
    }
    wrefresh(m);
}

void Mundos::focaMundo(int lin, int col, Mundos* mundo, WINDOW *m){

    int a, y, x, num1, num2, cont = 0, i;
    Ninhos *n;      
    werase(m);
    y = (18 + 30/2);
    x = (60 + 30/2);
    wmove(m,y,x);
    num1 = 9;
    for(a=0;a<30;a++){
        mvwprintw(m,y,x,"_");
        mvwprintw(m,y-30-1,x,"_");
        if(cont == 10){
            num1 = 9;
            cont = 0;
        }
        mvwprintw(m,y-30-2,x - 1,"%d", num1--);
        cont++;
        x--;
        wmove(m,y+30,x);
    }
    num1 = 30;
    for(a=0;a<30+1;a++){
        mvwprintw(m,y,x-1,"|");
        mvwprintw(m,y,x-3,"%d", num1--);
        mvwprintw(m,y,x+30+1,"|");
        y--;
        wmove(m,y,x-30);
    }
    
    y = (18 - lin);
    x = (60 - col);
    wmove(m,y,x);
    for(i = 0; i < migalhas.size(); i++){
        if(migalhas[i]->getPosX() > col + 15 || migalhas[i]->getPosX() < col - 15 ||
                migalhas[i]->getPosY() > lin + 15 || migalhas[i]->getPosY() < lin - 15)
            continue;
        else{
            mvwprintw(m, y + migalhas[i]->getPosY(), x + migalhas[i]->getPosX(), "*");
            wrefresh(m);
        }
    }
    for(i = 0; i < comunidades.size(); i++){
        comunidades[i]->percorreFormigas(mundo,m, 2, lin, col);
    }
    for(i = 0; i < comunidades.size(); i++){
        n = comunidades[i]->getNinho();
        if(n->getCoordX() > col + 15 || n->getCoordX() < col - 15 || n->getCoordY() > lin + 15 || n->getCoordY() < lin - 15)
            continue;
        else{
            mvwprintw(m, y + n->getCoordY(), x + n->getCoordX(), "#");
            wrefresh(m);
        }
    }
    
    wrefresh(m);
}

int Mundos::acaoCF(string tipof, int id, int num, int l, int c, Mundos *mundo){
    int i;
    
    if (comunidades.size() == 0)
        return 0;
    else{
        for(i = 0; i < comunidades.size(); i++){
            comunidades[i]->acaoCF(tipof, id, num, l, c, mundo);
        }
    }
    return 1;
}

void Mundos::acaoMF(Mundos *mundo, WINDOW *m){
    int i;
    
    for(i = 0; i < comunidades.size(); i++){
        comunidades[i]->acaoMF(mundo, m);
        comunidades[i]->verificaFormigas(mundo, m);
    }
}

void Mundos::acaoLCM(WINDOW *d){
    int i;
    
    for(i = 0; i < comunidades.size(); i++){
        comunidades[i]->listaComunidadeM(d);
    }
}
void Mundos::acaoLCN(int id, WINDOW *c, WINDOW *d){
    int i, flag = 0, yc, xc;
    
    getyx(c, yc, xc);
    wmove(c, yc, xc);
    
    for(i = 0; i < comunidades.size(); i++){
        flag = comunidades[i]->listaComunidadeN(id,d);
        if(flag == 1)
            break;
    }
    if(flag == 0)
        mvwprintw(c, yc++, 1, "Ninho inexistente!\n");
}
void Mundos::acaoLPO(int x, int y, WINDOW *d){
    int i, yd, xd;
    getyx(d,yd,xd);
    mvwprintw(d, yd++, 1, "*** Elementos na Posicao ***\n");
    for(i = 0; i < comunidades.size(); i++){
        comunidades[i]->procuraObjeto(x, y, d);
    }

    for(i = 0; i < migalhas.size(); i++){
        if(x == migalhas[i]->getPosX() && y == migalhas[i]->getPosY())
            migalhas[i]->listaInformacao(d);
    }
    wrefresh(d);
}
void Mundos::acaoTEN(int id, int energ, WINDOW *c, WINDOW *d){
    int i, yc, xc, flag;
    
    for(i = 0; i < comunidades.size(); i++){
        flag = comunidades[i]->transfEnergNinho(id, energ, d);
        if(flag == 1)
            break;
    }
    if(flag == 0){
        getyx(c, yc, xc);
        wmove(c, yc, xc);
        mvwprintw(c, yc++, 1, "Ninho inexistente!\n");
        wrefresh(c);
    }
}
void Mundos::acaoTEF(int lin, int col, int energ, WINDOW *c, WINDOW *d){
    int i, flag, yc, xc;
    
    for(i = 0; i < comunidades.size(); i++){
        flag = comunidades[i]->acaoTEF(lin, col, energ, d);
    }
    if(flag == 0){
        getyx(c, yc, xc);
        wmove(c, yc, xc);
        mvwprintw(c, yc++, 1, "Formigas nao encontradas na posicao!\n");
        wrefresh(c);
    }
}
void Mundos::acaomataF(int lin, int col, Mundos *mundo, WINDOW *m, WINDOW *c, WINDOW *d){
    int i;
    
    for(i = 0; i < comunidades.size(); i++){
        comunidades[i]->mataFormiga(lin, col, mundo, m, c, d);
    }
}
void Mundos::acaoInseticida(int id, Mundos *mundo, WINDOW* m, WINDOW* c, WINDOW* d){
    int i, flag, yd, xd, yc, xc;
    
    getyx(d, yd, xd);
    wmove(d, yd, xd);
    getyx(c, yc, xc);
    wmove(c, yc, xc);
    
    for(i = 0; i < comunidades.size(); i++){
        flag = comunidades[i]->inseticida(id, mundo, m);
        if(flag == 1){
            delete(comunidades[i]);
            comunidades.erase(comunidades.begin() + i);
            break;
        }
    }
    if(flag == 0){
        mvwprintw(c, yc++, 1, "Ninho inexistente!\n");
        wrefresh(c);
    }
    if(flag == 1){
        mvwprintw(d, yd++, 1, "Comunidade extinta com sucesso!\n");
        wrefresh(d);
    }
}
void Mundos::adicionaMigalhas(int flag, int col, int lin, int energ, int perc, int max, Mundos *mundo, Posicao *pos, WINDOW *m, WINDOW *c, WINDOW *d){
    int i, a, cY, cX, y, x, yc, xc, yd, xd;
    
    cX = pos->setCoordX(tamLado);
    cY = pos->setCoordY(tamLado);
    if(flag == 0){
        for(i = 0; i < (tamLado * tamLado)*(perc * 0.01); i++){

            for(a = 0; a < migalhas.size(); a++){
                do{
                    cX = pos->setCoordX(tamLado);
                    cY = pos->setCoordY(tamLado);
                }while(cX == migalhas[a]->getPosX() && cY == migalhas[a]->getPosY());
            }
            Migalhas * nova = new Migalhas(energ, cX, cY);
            migalhas.push_back(nova);

        }
    }
    if(flag == 1){
        getyx(c, yc, xc);
        wmove(c, yc, xc);
        getyx(d, yd, xd);
        wmove(d, yd, xd);
        for(a = 0; a < migalhas.size(); a++){
            if(col == migalhas[a]->getPosX() && lin == migalhas[a]->getPosY())
                mvwprintw(c, yc++, 1, "Posicao ocupada por outra migalha!\n");   
        }
        Migalhas * nova = new Migalhas(energ, col, lin);
        migalhas.push_back(nova);

        mvwprintw(d, yd++, 1, "Migalha adicionada com sucesso!\n");

        wrefresh(d);
    }
}

void Mundos::trataMigalhas(int energ, int max, Mundos *mundo, Posicao *pos, WINDOW *m){
    int num, cX, cY, i, a, x, y;

    
    for(a = 0; a < migalhas.size(); a++){
        migalhas[a]->setEnerg(migalhas[a]->getEnerg() - 1);
        if(migalhas[a]->getEnerg() < (energ * 0.1)){
            delete(migalhas[a]);
            migalhas.erase(migalhas.begin() + a);
        }
    }
    
    num = rand() % max;
    
    for(i = 0; i < num; i++){
        
        for(a = 0; a < migalhas.size(); a++){
            do{
                cX = pos->setCoordX(tamLado);
                cY = pos->setCoordY(tamLado);
            }while(cX == migalhas[a]->getPosX() && cY == migalhas[a]->getPosY());
        }
        Migalhas * nova = new Migalhas(energ, cX, cY);
        migalhas.push_back(nova);
    } 
}

void Mundos::trataNinhos(Mundos *mundo){
    int i;
    Ninhos *n;
    for (i = 0; i < comunidades.size(); i++){
        n = comunidades[i]->getNinho();
        n->criaFormigas(mundo);
    }
}
Formigas * Mundos::getInimiga(Formigas *f, int flag){
    int i, fl = 2, s = 0;
    Formigas *inim, *sol, *best_sol;
    sol = new Formigas();
    best_sol = new Formigas();

    for(i = 0; i < comunidades.size(); i++){
        fl = comunidades[i]->verificaComunidadeFormiga(f);   
        if(fl == 1){
            if(flag == 1){
                inim = comunidades[i]->calculaDistanciaForm(f,1);
                   return inim;
            }
            if(flag == 2){
                sol = comunidades[i]->calculaDistanciaForm(f,2);
                if(sol != nullptr){
                    if(sol->getEnergia() > best_sol->getEnergia()){
                        best_sol = sol;
                        s = 1;
                    }
                }
            }
            if(flag == 3){
                sol = comunidades[i]->calculaDistanciaForm(f,3);
                if(sol != nullptr){
                    if(sol->getEnergia() > best_sol->getEnergia()){
                        best_sol = sol;
                        s = 1;
                    }
                }
           }
        }
    }
    if(s == 1)
        return best_sol;

    return nullptr;
}
Formigas * Mundos::getAliada(Formigas* f){
    int i, flag;
    Formigas *aliada = new Formigas();
    for(i = 0; i < comunidades.size(); i++){
        flag = comunidades[i]->verificaComunidadeFormiga(f);
        if(flag == 0){
            aliada = comunidades[i]->calculaDistanciaForm(f, 1);
            return aliada;
        }
    }
    return nullptr;
}
Ninhos * Mundos::getNinho(Formigas *f, int flag){
    int i, fl;
    Ninhos *n;
    
    for(i = 0; i < comunidades.size(); i++){
        fl = comunidades[i]->verificaComunidadeFormiga(f);
        if(flag == 1){
            if(fl == 0){
                n = comunidades[i]->calculaDistanciaNinho(f);
                return n;
            }
        }
        if(flag == 2){
            if(fl == 1){
                n = comunidades[i]->calculaDistanciaNinho(f);
                return n;
            }
        }
    }
    return nullptr;
}

Migalhas * Mundos::getMigalha(Formigas* f, int flag){
    int i, s = 0;
    Migalhas *sol, *best_sol;
    sol = new Migalhas();
    best_sol = new Migalhas();
    
    if(flag == 1){
        for(i = 0; i < migalhas.size(); i++){
            if(max(abs(f->getPosX() - migalhas[i]->getPosX()), abs(f->getPosY() - migalhas[i]->getPosY())) <= 1){
                sol = migalhas[i];
                if(best_sol->getEnerg() < sol->getEnerg()){
                    best_sol = sol;
                    s = 1;
                }
            }
        }
        if(s == 1)
            return best_sol;
        else
            return nullptr;
    }
    if(flag == 2){
        for(i = 0; i < migalhas.size(); i++){
            if(max(abs(f->getPosX() - migalhas[i]->getPosX()), abs(f->getPosY() - migalhas[i]->getPosY())) <= f->getRaioVisao()){
                sol = migalhas[i];
                if(best_sol->getEnerg() < sol->getEnerg()){
                    best_sol = sol;
                    s = 1;
                }
            }
        }
        if(s == 1)
            return best_sol;
        else
            return nullptr;
    }
    return nullptr;
}

void Mundos::setNome(string n){
    nome = n;
}

string Mundos::getNome(){
    return nome;
}

int Mundos::verificaFormigasCFN(Ninhos *n){
    int i, f;
    Ninhos *temp;
    
    for(i = 0; i < comunidades.size(); i++){
        temp = comunidades[i]->getNinho();
        if(temp->getID() == n->getID()){
            f = comunidades[i]->percorreFormigasCFN();
            if(f == 1)
                return 1;
            else
                return 0;
        }
    }
    return 0;
}

void Mundos::trataFormigasNinho(){
    int i;
    Ninhos *n;
    for(i = 0; i < comunidades.size(); i++){
        n = comunidades[i]->getNinho();
        comunidades[i]->transfereEnergia(n);
    }
}