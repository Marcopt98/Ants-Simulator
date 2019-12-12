/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Comunidades.h
 * Author: marcoduarte
 *
 * Created on 22 de Novembro de 2017, 14:59
 */

#ifndef COMUNIDADES_H
#define COMUNIDADES_H

#include <vector>
#include <ncurses.h>

using namespace std;

class Ninhos;
class Formigas;
class Mundos;

class Comunidades {
    int ID = 1;
    static int ID_counter;
    Ninhos *ninho;
    vector <Formigas *> formigas;
    
public:
    
    Comunidades(int energ,int enTransf, int enCF, int cX, int cY);
    Comunidades(const Comunidades& orig);
    Comunidades &operator=(const Comunidades& outro);
    virtual Comunidades * duplica()const;
    bool acrescentaNinho(Ninhos * ninho);
    virtual ~Comunidades();
    void adicionaFormigas(string tipof, int num, int l, int c, Mundos *mundo);
    int getID();
    Ninhos * getNinho();
    void acaoCF(string tipof, int id, int num, int l, int c, Mundos *mundo);
    void acaoMF(Mundos *mundo, WINDOW *m);
    int acaoTEF(int lin, int col, int energ, WINDOW *d);
    int transfEnergNinho(int id, int energ, WINDOW *d);
    void listaComunidadeM(WINDOW *d);
    int listaComunidadeN(int id, WINDOW *d);
    void procuraObjeto(int x, int y, WINDOW *d);
    void mataFormiga(int lin, int col, Mundos *mundo, WINDOW *m, WINDOW *c, WINDOW *d);
    int inseticida(int id, Mundos *mundo, WINDOW *m);
    void verificaFormigas(Mundos *mundo, WINDOW *m);
    int verificaComunidadeFormiga(Formigas *f);
    void percorreFormigas(Mundos *mundo, WINDOW *m, int flag, int lin, int col);
    int percorreFormigasCFN();
    void transfereEnergia(Ninhos *n);
    Formigas * calculaDistanciaForm(Formigas *f, int flag);
    Ninhos * calculaDistanciaNinho(Formigas *f);
private:

};

#endif /* COMUNIDADES_H */

