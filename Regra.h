/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Regra.h
 * Author: marcoduarte
 *
 * Created on 4 de Janeiro de 2018, 13:56
 */

#ifndef REGRA_H
#define REGRA_H

#include <ncurses.h>

class Mundos;
class Formigas;

class Regra {
public:
    virtual bool condicao(Mundos *mundo, Formigas *f, WINDOW *m) = 0;
    virtual void agir(Mundos *mundo, Formigas *f, WINDOW *m) = 0;
    Regra &operator=(const Regra& outro);
    virtual Regra * duplica()const = 0;
    Regra();
    Regra(const Regra& orig);
    virtual ~Regra();
private:

};

class RegraFoge : public Regra{
public:
    RegraFoge() : Regra(){}
    RegraFoge(const RegraFoge& orig){*this = orig;}
    ~RegraFoge(){}
    bool condicao(Mundos *mundo, Formigas *f, WINDOW *m);
    void agir(Mundos *mundo, Formigas *f, WINDOW *m);
    Regra * duplica()const{return new RegraFoge(*this);}
private:

};

class RegraPersegue : public Regra{
public:
    RegraPersegue() : Regra(){}
    RegraPersegue(const RegraPersegue& orig){*this = orig;}
    ~RegraPersegue(){}
    bool condicao(Mundos *mundo, Formigas *f, WINDOW *m);
    void agir(Mundos *mundo, Formigas *f, WINDOW *m);
    Regra * duplica()const{return new RegraPersegue(*this);}
private:

};

class RegraAssalta : public Regra{
public:
    RegraAssalta() : Regra(){}
    RegraAssalta(const RegraAssalta& orig){*this = orig;}
    ~RegraAssalta(){}
    bool condicao(Mundos *mundo, Formigas *f, WINDOW *m);
    void agir(Mundos *mundo, Formigas *f, WINDOW *m);
    Regra * duplica()const{return new RegraAssalta(*this);}
private:

};

class RegraAssaltaNinho : public Regra{
public:
    RegraAssaltaNinho() : Regra(){}
    RegraAssaltaNinho(const RegraAssalta& orig){*this = orig;}
    ~RegraAssaltaNinho(){}
    bool condicao(Mundos *mundo, Formigas *f, WINDOW *m);
    void agir(Mundos *mundo, Formigas *f, WINDOW *m);
    Regra * duplica()const{return new RegraAssaltaNinho(*this);}
private:

};

class RegraProtege : public Regra{
public:
    RegraProtege() : Regra(){}
    RegraProtege(const RegraProtege& orig){*this = orig;}
    ~RegraProtege(){}
    bool condicao(Mundos *mundo, Formigas *f, WINDOW *m);
    void agir(Mundos *mundo, Formigas *f, WINDOW *m);
    Regra * duplica()const{return new RegraProtege(*this);}
private:

};

class RegraProcuraMigalha: public Regra{
public:
    RegraProcuraMigalha() : Regra(){}
    RegraProcuraMigalha(const RegraProcuraMigalha& orig){*this = orig;}
    ~RegraProcuraMigalha(){}
    bool condicao(Mundos *mundo, Formigas *f, WINDOW *m);
    void agir(Mundos *mundo, Formigas *f, WINDOW *m);
    Regra * duplica()const{return new RegraProcuraMigalha(*this);}
private:

};

class RegraComeMigalha : public Regra{
public:
    RegraComeMigalha() : Regra(){}
    RegraComeMigalha(const RegraComeMigalha& orig){*this = orig;}
    ~RegraComeMigalha(){}
    bool condicao(Mundos *mundo, Formigas *f, WINDOW *m);
    void agir(Mundos *mundo, Formigas *f, WINDOW *m);
    Regra * duplica()const{return new RegraComeMigalha(*this);}
private:

};

class RegraVaiParaNinho : public Regra{
public:
    RegraVaiParaNinho() : Regra(){}
    RegraVaiParaNinho(const RegraVaiParaNinho& orig){*this = orig;}
    ~RegraVaiParaNinho(){}
    bool condicao(Mundos *mundo, Formigas *f, WINDOW *m);
    void agir(Mundos *mundo, Formigas *f, WINDOW *m);
    Regra * duplica()const{return new RegraVaiParaNinho(*this);}
private:

};

class RegraPasseia : public Regra{
public:
    RegraPasseia() : Regra(){}
    RegraPasseia(const RegraPasseia& orig){*this = orig;}
    ~RegraPasseia(){}
    bool condicao(Mundos *mundo, Formigas *f, WINDOW *m);
    void agir(Mundos *mundo, Formigas *f, WINDOW *m);
    Regra * duplica()const{return new RegraPasseia(*this);}
private:

};
#endif /* REGRA_H */

