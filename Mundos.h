/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mundos.h
 * Author: marcoduarte
 *
 * Created on 21 de Novembro de 2017, 22:43
 */

#ifndef MUNDOS_H
#define MUNDOS_H

#include <vector>
#include <ncurses.h>
#include <string>

class Comunidades;
class Ninhos;
class Formigas;
class Migalhas;
class Interface;
class Posicao;

using namespace std;

class Mundos {
    
    int tamLado;
    string nome;
    vector <Comunidades *> comunidades;
    vector <Migalhas *> migalhas;

public:

    Mundos();
    Mundos(Mundos *mundo);
    Mundos(const Mundos& orig);
    Mundos & operator=(const Mundos& outro);
    virtual ~Mundos();
    int getCoordenadas(int x, int y, int tLado);
    void setLado(int tLado);
    int getLado()const;
    void criaMundo(WINDOW *m);
    void desenhaMundo(Mundos *mundo, WINDOW *m);
    void adicionaComunidade(int energ, int enTransf, int enCF, int cX, int cY, WINDOW *m);
    int acaoCF(string tipof, int id, int num, int c, int l, Mundos *mundo);
    void acaoMF(Mundos *mundo, WINDOW *m);
    void acaoLCM(WINDOW *d);
    void acaoLCN(int id, WINDOW *c, WINDOW *d);
    void acaoLPO(int x, int y, WINDOW *d);
    void acaoTEN(int id, int energ, WINDOW *c, WINDOW *d);
    void acaoTEF(int lin, int col, int energ, WINDOW *c, WINDOW *d);
    void acaomataF(int lin, int col, Mundos *mundo, WINDOW *m, WINDOW *c, WINDOW *d);
    void acaoInseticida(int id, Mundos *mundo, WINDOW *m, WINDOW *c, WINDOW *d);
    void adicionaMigalhas(int flag, int col, int lin, int energ, int perc, int max, Mundos *mundo, Posicao *pos, WINDOW *m, WINDOW *c, WINDOW *d);
    void trataMigalhas(int energ, int max, Mundos *mundo, Posicao *pos, WINDOW *m);
    Formigas * getInimiga(Formigas *f, int flag);
    Formigas * getAliada(Formigas *f);
    Ninhos * getNinho(Formigas *f, int flag);
    Migalhas * getMigalha(Formigas *f, int flag);
    void setNome(string n);
    string getNome();
    int verificaFormigasCFN(Ninhos *n);
    void trataNinhos(Mundos *mundo);
    void trataFormigasNinho();
    void focaMundo(int lin, int col, Mundos * mundo, WINDOW *m);
private:

};

#endif /* MUNDOS_H */

