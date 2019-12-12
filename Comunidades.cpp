/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Comunidades.cpp
 * Author: marcoduarte
 * 
 * Created on 22 de Novembro de 2017, 14:59
 */

#include "Comunidades.h"
#include "Formigas.h"
#include "Ninhos.h"
#include "Mundos.h"

int Comunidades::ID_counter = 0;

Comunidades::Comunidades(int energ,int enTransf, int enCF, int cX, int cY){
    ID += ID_counter++;
    ninho = new Ninhos(energ, enTransf, enCF, cX, cY);
}

Comunidades::Comunidades(const Comunidades& orig) {
    ninho = nullptr;
    *this = orig;
}

Comunidades & Comunidades::operator=(const Comunidades& outro){
    if(this == &outro)
        return *this;
    
    for(unsigned int i = 0; i < formigas.size(); i++)
        delete formigas[i];
    formigas.clear();
    
    for(unsigned int i = 0; i < outro.formigas.size(); i++)
        formigas.push_back(outro.formigas[i]->duplica());
    
    delete ninho;
    
    ninho = outro.ninho->duplica();
    ID = outro.ID;
    ID_counter = outro.ID_counter;
    
    return *this;
}
Comunidades * Comunidades::duplica() const{
    return new Comunidades(*this);
} 
Comunidades::~Comunidades() {
    int i;
    for(i = 0; i < formigas.size(); i++)
        delete formigas[i];
    formigas.clear();
    delete ninho;
}


int Comunidades::getID(){
    return ID;
}

Ninhos * Comunidades::getNinho(){
    return ninho;
}
void Comunidades::adicionaFormigas(string tipof, int num, int l, int c, Mundos *mundo){
    int i, cX, cY;
    Formigas * nova;
    

    for(i = 0; i < num; i++){
        if(c != 0 && l != 0){
            if(tipof.compare("E") == 0)
                nova = new Exploradora(c, l);
            if(tipof.compare("C") == 0)
                nova = new Cuidadora(c, l);
            if(tipof.compare("V") == 0)
                nova = new Vigilante(c, l);
            if(tipof.compare("A") == 0)
                nova = new Assaltante(c, l);
            if(tipof.compare("S") == 0)
                nova = new Surpresa(c, l);
            if(tipof.compare("D") == 0)
                nova = new Defesa(c, l);
        }
        else{
            if(tipof.compare("E") == 0)
                nova = new Exploradora(mundo);
            if(tipof.compare("C") == 0)
                nova = new Cuidadora(mundo);
            if(tipof.compare("V") == 0)
                nova = new Vigilante(mundo);
            if(tipof.compare("A") == 0)
                nova = new Assaltante(mundo);
            if(tipof.compare("S") == 0)
                nova = new Surpresa(mundo);
            if(tipof.compare("D") == 0)
                nova = new Defesa(mundo);
            }
        
        formigas.push_back(nova);

    }
}

void Comunidades::acaoCF(string tipof, int id, int num, int l, int c, Mundos *mundo){
    int i;
    
    if(ninho->getID() == id){
         adicionaFormigas(tipof, num, l, c, mundo);   
    }
}

void Comunidades::acaoMF(Mundos *mundo, WINDOW *m){
    int i;
    
        for(i = 0; i < formigas.size(); i++){
            formigas[i]->percorreRegras(mundo, m);
            formigas[i]->setIter(formigas[i]->getIter() + 1);
        }
}
int Comunidades::acaoTEF(int lin, int col, int energ, WINDOW *d){
    int i, yd, xd;
    
    getyx(d, yd, xd);
    wmove(d, yd, xd);
    
    for(i = 0; i < formigas.size(); i++){
        if(lin == formigas[i]->getPosY() && col == formigas[i]->getPosX()){
            formigas[i]->setEnergia(formigas[i]->getEnergia() + energ);
            mvwprintw(d, yd++, 1, "Energ transf para formiga com sucesso!\n");
            wrefresh(d);
            return 1;
        }
    }
    
    return 0;
}
int Comunidades::transfEnergNinho(int id, int energ, WINDOW *d){
    int  yd, xd;
    if(ninho->getID() == id){
        ninho->setEnergia(ninho->getEnergia() + energ);
        getyx(d, yd, xd);
        wmove(d, yd, xd);
        mvwprintw(d, yd++, 1, "Transf de energ executada com sucesso!\n");
        wrefresh(d);
        return 1;
    }
    else
        return 0;
}

void Comunidades::listaComunidadeM(WINDOW *d){
    
    int yd, xd;
    getyx(d,yd,xd);
    mvwprintw(d, yd++, 1, "-> Ninho %d:\n", ninho->getID());
    mvwprintw(d, yd++, 1, "Energia: %d | EnTrasf: %d |\n", ninho->getEnergia(), ninho->getEnergTransf());
    mvwprintw(d, yd++, 1, "EnCriaForm: %d", ninho->getEnCriaFormiga());
    mvwprintw(d, yd++, 1, "Numero de Formigas: %d\n", formigas.size());
    
    wrefresh(d);
}

int Comunidades::listaComunidadeN(int id, WINDOW *d){
    int yd, xd, i;
    getyx(d,yd,xd);
    if(id == ninho->getID()){
        mvwprintw(d, yd++, 1, "-> Informacao do Ninho:\n");
        mvwprintw(d, yd++, 1, "ID: %d | posX: %d | posY: %d \n", ninho->getID(), ninho->getCoordX(),
                ninho->getCoordY());
        mvwprintw(d, yd++, 1, "Formigas do ninho:\n");
        for(i = 0; i < formigas.size(); i++){
            mvwprintw(d, yd++, 1, "ID: %d | Energia: %d | Tipo: %c\n", formigas[i]->getID(), formigas[i]->getEnergia(),
                    formigas[i]->getTipo());
            mvwprintw(d, yd++, 1, "posX: %d | posY: %d\n", formigas[i]->getPosX(), formigas[i]->getPosY());
        }
        wrefresh(d);
        return 1;
    }
    return 0;
}

void Comunidades::procuraObjeto(int x, int y, WINDOW *d){
    int i;
    
    if(ninho->getCoordX() == x && ninho->getCoordY() == y)
        ninho->listaInformacao(d);
    for(i = 0; i < formigas.size(); i++){
        if(formigas[i]->getPosX() == x && formigas[i]->getPosY() == y)
            formigas[i]->listaInformacao(d);
    }
}

void Comunidades::mataFormiga(int lin, int col, Mundos *mundo, WINDOW *m, WINDOW *c, WINDOW *d){
    int i, y, x, yd, xd, yc, xc;

    getyx(d, yd, xd);
    wmove(d, yd, xd);
    getyx(c, yc, xc);
    wmove(c, yc, xc);
    for(i = 0; i < formigas.size(); i++){
        if(lin == formigas[i]->getPosY() && col == formigas[i]->getPosX()){

            delete(formigas[i]);
            formigas.erase(formigas.begin() + i);
            mvwprintw(d, yd++, 1, "Formiga eliminada com sucesso!\n");
            wrefresh(d);
            return;
        }
    }
    mvwprintw(c, yc++, 1, "Formiga inexistente na posicao!\n");
    wrefresh(c);
}
int Comunidades::inseticida(int id, Mundos *mundo, WINDOW *m){
    int i, x, y;
    
    if(id == ninho->getID()){

        for(vector<Formigas *>::iterator it = formigas.begin(); it != formigas.end();){
            delete(*it);
            it = formigas.erase(it);
        }

        delete(ninho);
        return 1;
    }
    return 0;
}

void Comunidades::verificaFormigas(Mundos* mundo, WINDOW* m){
    int i, x, y;

    for(vector<Formigas *>::iterator it = formigas.begin(); it != formigas.end();){
        if(!(*it)->isViva()){
            delete(*it);
            it = formigas.erase(it);
        }
        else
            ++it;
    }
}

int Comunidades::verificaComunidadeFormiga(Formigas *f){
    int i;
    
    for(i = 0; i < formigas.size(); i++){
        if(formigas[i]->getID() == f->getID())
            return 0;
    }
    return 1;
}

Formigas * Comunidades::calculaDistanciaForm(Formigas *f, int flag){
    int i, x, y, x1, y1, s = 0;
    Formigas * sol, *best_sol;
    sol = new Formigas();
    best_sol = new Formigas();
    
    x = f->getPosX();
    y = f->getPosY();
    if(flag == 1){
        for(i = 0; i < formigas.size(); i++){
            x1 = formigas[i]->getPosX();
            y1 = formigas[i]->getPosY();
            if(max(abs(x - x1), abs(y - y1)) <= f->getRaioVisao()){
                return formigas[i];
            }
        }
    }
    if(flag == 2){
        for(i = 0; i < formigas.size(); i++){
            x1 = formigas[i]->getPosX();
            y1 = formigas[i]->getPosY();
            if(max(abs(x - x1), abs(y - y1)) <= f->getRaioMov()){
                sol = formigas[i];
                if(sol->getEnergia() > best_sol->getEnergia()){
                    best_sol = sol;
                    s = 1;
                }
            }
        }
        if(s == 1)
            return best_sol;
    }
    if(flag == 3){
        for(i = 0; i < formigas.size(); i++){
            x1 = formigas[i]->getPosX();
            y1 = formigas[i]->getPosY();
            if(max(abs(x - x1), abs(y - y1)) <= f->getRaioVisao()){
                sol = formigas[i];
                if(sol->getEnergia() > best_sol->getEnergia()){
                    best_sol = sol;
                    s = 1;
                }
            }
        }
        if(s == 1)
            return best_sol;
    }

    return nullptr;
}

Ninhos * Comunidades::calculaDistanciaNinho(Formigas *f){
    int i, x, y, xN, yN;
    
    x = f->getPosX();
    y = f->getPosY();
    xN = ninho->getCoordX();
    yN = ninho->getCoordY();
    if(max(abs(x - xN), abs(y - yN)) <= f->getRaioVisao())
        return ninho;
    else
        return nullptr;
}

void Comunidades::percorreFormigas(Mundos *mundo, WINDOW *m, int flag, int lin, int col){
    int i, x, y;
    
    if(flag == 1){
        x = (60 - mundo->getLado()/2);
        y = (18 - mundo->getLado()/2);
        wmove(m,y,x);

        for(i = 0; i < formigas.size(); i++){
            mvwprintw(m, y + formigas[i]->getPosY(), x + formigas[i]->getPosX(), "%c", formigas[i]->getTipo());
            wrefresh(m);
        }
    }
    if(flag == 2){
        x = (60 - col);
        y = (18 - lin);
        wmove(m,y,x);

        for(i = 0; i < formigas.size(); i++){
            if(formigas[i]->getPosX() > col + 15 || formigas[i]->getPosX() < col - 15 ||
                    formigas[i]->getPosY() > lin + 15 || formigas[i]->getPosY() < lin - 15)
                continue;
            else{
                mvwprintw(m, y + formigas[i]->getPosY(), x + formigas[i]->getPosX(), "%c", formigas[i]->getTipo());
                wrefresh(m);
            }
        }
    }
}

int Comunidades::percorreFormigasCFN(){
    int i;
  
    for(i = 0; i < formigas.size(); i++){
        if(formigas[i]->getInNinho() == true)
            return 1;
    }
    return 0;
}

void Comunidades::transfereEnergia(Ninhos *n){
    int i;
  
    for(i = 0; i < formigas.size(); i++){
        n->verificaSaidaNinho(formigas[i]);
        if(formigas[i]->getInNinho() == true){ 
            if(formigas[i]->getTipo() == 'C'){
                if(formigas[i]->getEnergia() > 100){
                    formigas[i]->setEnergia(formigas[i]->getEnergia() - n->getEnergTransf());
                    n->setEnergia(n->getEnergia() + n->getEnergTransf());
                }
                if(formigas[i]->getEnergia() < 50){
                    formigas[i]->setEnergia(formigas[i]->getEnergia() + n->getEnergTransf());
                    n->setEnergia(n->getEnergia() - n->getEnergTransf());
                }
            }
            if(formigas[i]->getTipo() == 'V'){
                if(formigas[i]->getEnergia() > 150){
                    formigas[i]->setEnergia(formigas[i]->getEnergia() - n->getEnergTransf());
                    n->setEnergia(n->getEnergia() + n->getEnergTransf());
                }
                if(formigas[i]->getEnergia() < 75){
                    formigas[i]->setEnergia(formigas[i]->getEnergia() + n->getEnergTransf());
                    n->setEnergia(n->getEnergia() - n->getEnergTransf());
                }                
            }
            if(formigas[i]->getTipo() == 'A'){
                if(formigas[i]->getEnergia() > 80){
                    formigas[i]->setEnergia(formigas[i]->getEnergia() - n->getEnergTransf());
                    n->setEnergia(n->getEnergia() + n->getEnergTransf());
                }
                if(formigas[i]->getEnergia() < 40){
                    formigas[i]->setEnergia(formigas[i]->getEnergia() + n->getEnergTransf());
                    n->setEnergia(n->getEnergia() - n->getEnergTransf());
                }                
            }
            if(formigas[i]->getTipo() == 'E'){
                if(formigas[i]->getEnergia() > 200){
                    formigas[i]->setEnergia(formigas[i]->getEnergia() - n->getEnergTransf());
                    n->setEnergia(n->getEnergia() + n->getEnergTransf());
                }
                if(formigas[i]->getEnergia() < 100){
                    formigas[i]->setEnergia(formigas[i]->getEnergia() + n->getEnergTransf());
                    n->setEnergia(n->getEnergia() - n->getEnergTransf());
                }                
            }
            if(formigas[i]->getTipo() == 'S'){
                if(formigas[i]->getEnergia() > 50){
                    formigas[i]->setEnergia(formigas[i]->getEnergia() - n->getEnergTransf());
                    n->setEnergia(n->getEnergia() + n->getEnergTransf());
                }
                if(formigas[i]->getEnergia() < 25){
                    formigas[i]->setEnergia(formigas[i]->getEnergia() + n->getEnergTransf());
                    n->setEnergia(n->getEnergia() - n->getEnergTransf());
                }                
            }
        }
    }
}