/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Simulacao.cpp
 * Author: marcoduarte
 * 
 * Created on 11 de Dezembro de 2017, 18:37
 */

#include "Simulacao.h"
#include "Interface.h"
#include "Mundos.h"
#include "Ninhos.h"
#include "Migalhas.h"
#include "Posicao.h"
#include "Formigas.h"
#include "Comunidades.h"
#include "Configuracao.h"

Simulacao::Simulacao() {
}

Simulacao::Simulacao(const Simulacao& orig) {
}

Simulacao::~Simulacao() {
}


void Simulacao::leComandos(Mundos *mundo, Ninhos *ninho, Migalhas *migalha){
    
    string token;
    char buffer[100];
    int yc, xc, yd, xd, *coord, it = 0, linFoco = mundo->getLado()/2, colFoco = mundo->getLado()/2;
    WINDOW * c, * m, * d;
    Interface simulacao;
    Ninhos *novo;
    Comunidades *comun;
    Posicao *pos = new Posicao;
    
    m = simulacao.setWSimulacao(0);
    c = simulacao.setWSimulacao(1);
    d = simulacao.setWSimulacao(2);
    if(mundo->getLado() <= 30)
        mundo->criaMundo(m);
    else
        mundo->focaMundo(linFoco, colFoco, mundo, m);
    mundo->adicionaMigalhas(0, 0, 0, migalha->getEnerg(), migalha->getPerc(), migalha->getMax(), mundo, pos, m, c, d);
    guardaMundo(&mundo, "default");
    while(1){
        if(mundo->getLado() <= 30)
            mundo->desenhaMundo(mundo, m);
        else
            mundo->focaMundo(linFoco, colFoco, mundo, m);
        
        getyx(c,yc,xc);
        getyx(d,yd,xd);
        mvwprintw(c, yc++, 1, "> ");
        wgetstr(c, buffer);
        wrefresh(c);
        getyx(c,yc,xc);
        
        istringstream iss(buffer);
        iss >> token;
        
        if(token.compare("ninho") == 0){
            int lin, col;
            
                iss >> token;
                if(!iss)
                    mvwprintw(c, yc++, 1, "Faltam ambas as coordenadas!\n");
                else{
                    lin = stoi(token);
                    iss >> token;
                    if(!iss)
                        mvwprintw(c, yc++, 1, "Falta uma das coordenadas!\n");
                    else{
                    col = stoi(token);
                    iss >> token;
                    if(lin > mundo->getLado() || col > mundo->getLado())
                        mvwprintw(c, yc++, 1, "Coordenadas excedem o limite do mundo!\n");
                    else{
                        mundo->adicionaComunidade(ninho->getEnergia(), ninho->getEnergTransf(),
                                ninho->getEnCriaFormiga(), lin, col, m);
                        mvwprintw(d, yd++, 1, "Ninho adicionado com sucesso!\n");
                    }
                    }
                }
        }
        else if(token.compare("criaf") == 0){ 

            int nF,idN, i, a = 0, flagN = 0;
            string tF;
            
            iss >> token;
            if(!iss)
                mvwprintw(c, yc++, 1, "Faltam todos os parametros!\n");
            else{
                nF = stoi(token);
                iss >> token;
                if(!iss)
                    mvwprintw(c, yc++, 1, "Falta o tipo de formiga!\n");
                else{
                    tF = token;
                    iss >> token;
                    if(!iss)
                        mvwprintw(c, yc++, 1, "Falta o ID do ninho!\n");
                    else{
                        idN = stoi(token);
                        flagN = mundo->acaoCF(tF, idN, nF, 0, 0, mundo); 

                        if(flagN == 1)
                           mvwprintw(d, yd++, 1, "Formigas adicionadas com sucesso!\n");
                        if(flagN == 0)
                           mvwprintw(c, yc++, 1, "Ninho inexistente!\n");
                    }
                }       
                
            }
        }
        else if(token.compare("cria1") == 0){
            string tF;
            int idN, lin, col, flagN = 0;
            iss >> token;
            if(!iss)
                mvwprintw(c, yc++, 1, "Faltam os argumentos todos!\n");
            else{
                tF = token;
                iss >> token;
                if(!iss)
                    mvwprintw(c, yc++, 1, "Falta o ID do ninho!\n");
                else{
                    idN = stoi(token);
                    iss >> token;
                    if(!iss)
                        mvwprintw(c, yc++, 1, "Falta os valores das coordenadas!\n");
                    else{
                        lin = stoi(token);
                        iss >> token;
                        if(!iss)
                            mvwprintw(c, yc++, 1, "Falta o ultimo valor das coordenadas!\n");
                        else{
                            col = stoi(token);
                            flagN = mundo->acaoCF(tF, idN, 1, col, lin, mundo); 

                            if(flagN == 1)
                                mvwprintw(d, yd++, 1, "Formigas adicionadas com sucesso!\n");
                            if(flagN == 0)
                                mvwprintw(c, yc++, 1, "Ninho inexistente!\n");
                        }
                    }
                }
            }
        }
        else if(token.compare("migalha") == 0){
            int col, lin;
            iss >> token;
            if(!iss)
                mvwprintw(c, yc++, 1, "Faltam ambos os valores da coordenada!\n");
            else{
                lin = stoi(token);
                iss >> token;
                if(!iss)
                    mvwprintw(c, yc++, 1, "Falta o segundo valor da coordenada!\n");
                else{
                    col = stoi(token);
                    mundo->adicionaMigalhas(1, col, lin, migalha->getEnerg(), migalha->getPerc(),
                            migalha->getMax(), mundo, pos, m, c, d);
                }
            }
        }
        else if(token.compare("foca") == 0){
            iss >> token;
            if(!iss)
                mvwprintw(c, yd++, 1, "Falta a coordenada!\n");
            else{
                linFoco = stoi(token);
                iss >> token;
                if(!iss)
                    mvwprintw(c, yd++, 1, "Falta um valor da coordenada!\n");
                else{
                    colFoco = stoi(token);
                    mundo->focaMundo(linFoco, colFoco, mundo, m);
                }
            }
        }
        else if(token.compare("tempo") == 0){
            int i, n;
            iss >> token;
            
            if(!iss){
                mundo->acaoMF(mundo, m);
                mundo->trataMigalhas(migalha->getEnerg(), migalha->getMax(), mundo, pos, m);
                mundo->trataNinhos(mundo);
                mundo->trataFormigasNinho();
                it++;
            }
            else{
                n = stoi(token);
                for(i = 0; i < n; i++){
                    mundo->acaoMF(mundo, m);
                    mundo->trataMigalhas(migalha->getEnerg(), migalha->getMax(), mundo, pos, m);
                    mundo->trataNinhos(mundo);
                    mundo->trataFormigasNinho();
                    it++;
                }
            }
            mvwprintw(d, yd++, 1, "Iteracao %d!\n", it);
        }
        else if(token.compare("energninho") == 0){
            int idN, energ;
            iss >> token;
            if(!iss)
                mvwprintw(c, yc++, 1, "Faltam ambos os parametros!\n");
            else{
                idN = stoi(token);
                iss >> token;
                if(!iss)
                    mvwprintw(c, yc++, 1, "Falta a energia a acrescentar ao ninho!\n");
                else{
                    energ = stoi(token);
                    mundo->acaoTEN(idN, energ, c, d);
                }
            }
        }
        else if(token.compare("energformiga") == 0){
            int lin, col, energ;
            
            iss >> token;
            if(!iss)
                mvwprintw(c, yc++, 1, "Faltam todos os parametros!\n");
            else{
                lin = stoi(token);
                iss >> token;
                if(!iss)
                    mvwprintw(c, yc++, 1, "Falta um valor da coordenada e a energia!\n");
                else{
                    col = stoi(token);
                    iss >> token;
                    if(!iss)
                        mvwprintw(c, yc++, 1, "Falta a energia!\n");
                    else{
                        energ = stoi(token);
                        mundo->acaoTEF(lin, col, energ, c, d);
                    }
                }
            }
        }
        else if(token.compare("mata") == 0){
            int col, lin;
            iss >> token;
            if(!iss)
                mvwprintw(c, yc++, 1, "Faltam os valores da coordenada!\n");
            else{
                lin = stoi(token);
                iss >> token;
                if(!iss)
                    mvwprintw(c, yc++, 1, "Falta um valor da coordenada!\n");
                else{
                    col = stoi(token);
                    mundo->acaomataF(lin, col, mundo, m, c, d);
                }
            }
        }
        else if(token.compare("inseticida") == 0){
            int idN;
            iss >> token;
            if(!iss)
                mvwprintw(c, yc++, 1, "Falta o ID do ninho!\n");
            else{
                idN = stoi(token);
                mundo->acaoInseticida(idN, mundo, m, c, d);
            }
        }
        else if(strcmp(buffer, "listamundo") == 0){
            mvwprintw(d, yd++, 1, "*** Elementos no Mundo ***\n");
            mundo->acaoLCM(d);
        }
        else if(token.compare("listaninho") == 0){
            int i, a, id;
            iss >> token;
            if(!iss)
                mvwprintw(c, yc++, 1, "Falta ID do ninho!\n");
            else{
                id = stoi(token);
                mundo->acaoLCN(id, c, d);
            }           
        }
        else if(token.compare("listaposicao") == 0){
            int col, lin, i;
            iss >> token;
            if(!iss)
                mvwprintw(c, yc++, 1, "Faltam as coordenadas!\n");
            else{
                lin = stoi(token);
                iss >> token;
                if(!iss)
                    mvwprintw(c, yc++, 1, "Faltam uma das coordenadas!\n");
                col = stoi(token);
                mundo->acaoLPO(col, lin, d);        
            }
        }
        else if(token.compare("guarda") == 0){
            iss >> token;
            if(!iss)
                mvwprintw(c, yc++, 1, "Falta o nome do mundo a guardar!\n");
            else{
                if(token.compare("default") == 0)
                    mvwprintw(c, yc++, 1, "O nome default e invalido!\n");
                else{
                    guardaMundo(&mundo, token);
                    mvwprintw(d, yd++, 1, "Mundo guardado com sucesso!");
                }
            }
        }
        else if(token.compare("muda") == 0){
            iss >> token;
            if(!iss)
                mvwprintw(c, yc++, 1, "Falta o nome do mundo a carregar!\n");
            else{
                mudaMundo(&mundo,token);
            }
        }
        else if(token.compare("apaga") == 0){
            int a;
            iss >> token;
            if(!iss)
                mvwprintw(c, yc++, 1, "Falta o nome do mundo a apagar!\n");
            else{
                a = apagaMundo(token);
                if(token.compare("default") == 0){
                    WINDOW *config;
                    Configuracao *con;
                    wclear(m);
                    wclear(c);
                    wclear(d);
                    delwin(m);
                    delwin(c);
                    delwin(d);
                    config = simulacao.setWindows();
                    con->leComando(config, mundo, ninho, migalha);
                }    
                if(a == 1)
                    mvwprintw(d, yd++, 1, "Mundo apagado com sucesso!\n");
                else
                    mvwprintw(c, yc++, 1, "Mundo inexistente!\n");
            }
        }
        else if(strcmp(buffer, "sair") == 0)
            return;
            //exit(0);
        else
            mvwprintw(c, yc++, 1, "Comando invalido!\n");
        wborder(d,0,0,0,0,0,0,0,0);
        wrefresh(d);
        wrefresh(c);
    }
    
    
}

void Simulacao::guardaMundo(Mundos **mundo, string nome){
    
    Mundos *novo = new Mundos(**mundo);
    copiasMundos.push_back(novo);
    novo->setNome(nome);
}

void Simulacao::mudaMundo(Mundos **atual, string nome){
    int i;
    
    for(i = 0; i < copiasMundos.size(); i++){
        if(copiasMundos[i]->getNome() == nome){
            delete *atual;
            *atual = nullptr;
            *atual = new Mundos(*copiasMundos[i]);
        }
    }
}

int Simulacao::apagaMundo(string nome){
    int i;
    
    for(i = 0; i < copiasMundos.size(); i++){
        if(copiasMundos[i]->getNome() == nome){
            delete (copiasMundos[i]);
            copiasMundos.erase(copiasMundos.begin() + i);
            return 1;
        }
    }
    return 0;
}