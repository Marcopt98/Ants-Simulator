/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Formigas.h
 * Author: marcoduarte
 *
 * Created on 22 de Novembro de 2017, 15:07
 */

#ifndef FORMIGAS_H
#define FORMIGAS_H

#include <string>
#include <sstream>
#include <ncurses.h>
#include <vector>

using namespace std;

class Posicao;
class Mundos;
class Comunidades;
class Regra;

class Formigas {

    int ID = 1, energia, posX, posY,raioM, raioV, iter;
    static int ID_counter;
    bool ninho;
    char tipo;
    Posicao *pos;
    vector <Regra *> regras;
public:
    Formigas();
    Formigas(const Formigas& orig);
    Formigas &operator=(const Formigas& outro);
    Formigas(int energ, int rM, int rV, char tp, int c, int l);
    Formigas(Mundos *m, int energ, int rM, int rV, char tp);
    virtual Formigas * duplica()const{return nullptr;};
    virtual ~Formigas();
    
    bool getInNinho();
    void setInNinho(bool condicao);
    bool isViva()const;
    int getPosY();
    int getPosX();
    int getRaioMov();
    int getRaioVisao();
    int getID();
    int getEnergia();
    void setEnergia(int energ);
    int getIter();
    void setIter(int iteracao);
    char getTipo();
    void moveFormiga(Mundos *mundo, WINDOW *m);
    void listaInformacao(WINDOW *d);
    void defineRegras(int flag);
    void setX(int x);
    void setY(int y);
    void percorreRegras(Mundos *mundo, WINDOW *m);
private:

};

    class Exploradora : public Formigas{
public:
    Exploradora(Mundos *m) : Formigas(m,200, 8, 10, 'E'){defineRegras(4);}
    Exploradora(int c, int l) : Formigas(200, 8, 10, 'E', c, l){defineRegras(4);}
    Exploradora(const Exploradora& orig){*this = orig;}
    Formigas * duplica()const{return new Exploradora(*this);}
    ~Exploradora(){}
private:

};

class Cuidadora : public Formigas {
public:
    Cuidadora(Mundos *m) : Formigas(m,100, 3, 5, 'C'){defineRegras(1);}
    Cuidadora(int c, int l) : Formigas(100, 3, 5, 'C', c, l){defineRegras(1);}
    Cuidadora(const Cuidadora& orig){*this = orig;}
    Formigas * duplica()const{return new Cuidadora(*this);}
    ~Cuidadora(){}
private:

};

class Vigilante : public Formigas{
public:
    Vigilante(Mundos *m) : Formigas(m,150, 5, 7, 'V'){defineRegras(2);}
    Vigilante(int c, int l) : Formigas(150, 5, 7, 'V', c, l){defineRegras(2);}
    Vigilante(const Vigilante& orig){*this = orig;}
    Formigas * duplica()const{return new Vigilante(*this);}
    ~Vigilante(){}
private:

};

class Assaltante : public Formigas{
public:
    Assaltante(Mundos *m) : Formigas(m,80, 4, 8, 'A'){defineRegras(3);}
    Assaltante(int c, int l) : Formigas(80, 4, 8, 'A', c, l){defineRegras(3);}
    Assaltante(const Assaltante& orig){*this = orig;}
    Formigas * duplica()const{return new Assaltante(*this);}
    ~Assaltante(){}
private:

};

class Surpresa : public Formigas{
public:
    Surpresa(Mundos *m) : Formigas(m,50, 3, 5, 'S'){defineRegras(5);}
    Surpresa(int c, int l) : Formigas(50, 3, 5, 'S', c, l){defineRegras(5);}
    Surpresa(const Surpresa& orig){*this = orig;}
    Formigas * duplica()const{return new Surpresa(*this);}
    ~Surpresa(){}
private:
    
};
    
class Defesa : public Formigas{
public:
    Defesa(Mundos *m) : Formigas(m,150, 5, 7, 'D'){defineRegras(6);}
    Defesa(int c, int l) : Formigas(150, 5, 7, 'D', c, l){defineRegras(6);}
    Defesa(const Defesa& orig){*this = orig;}
    Formigas * duplica()const{return new Defesa(*this);}
    ~Defesa(){}
private:



};
#endif /* FORMIGAS_H */

