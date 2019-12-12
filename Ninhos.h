/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ninhos.h
 * Author: marcoduarte
 *
 * Created on 22 de Novembro de 2017, 15:07
 */

#ifndef NINHOS_H
#define NINHOS_H

#include <ncurses.h>
class Mundos;
class Formigas;

class Ninhos {
    int ID = 1, coordX, coordY, energia, energ_transf, energ_cf, energia_inicial;
    static int ID_counter;
public:
    Ninhos();
    virtual ~Ninhos();
    Ninhos(const Ninhos& orig);
    Ninhos &operator=(const Ninhos& outro);
    virtual Ninhos * duplica()const;
    void setEnergia(int energ);
    void setEnCriaFormiga(int valor);
    void setEnergTransf(int etransf);
    void setEnergiaInicial(int energ);
    int getEnergia();
    int getEnergiaInicial();
    int getEnergTransf()const;
    int getEnCriaFormiga()const;
    Ninhos(int energ, int enTransf, int enCF, int cX, int cY);
    void setCoordX(int x);
    int getCoordX()const;
    void setCoordY(int y);
    int getCoordY()const;
    int getID();
    void listaInformacao(WINDOW *d);
    void criaFormigas(Mundos *mundo);
    char randomTipoFormiga();
    void verificaSaidaNinho(Formigas *f);
private:

};

#endif /* NINHOS_H */

