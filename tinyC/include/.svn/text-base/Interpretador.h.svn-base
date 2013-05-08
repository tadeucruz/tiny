/*
This file is part of tinyC.

tinyC is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

tinyC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ProjectRisc.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2008 tadeucruz<contato@tadeucruz.com>
 */

#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H
#include "ArquivoFonte.h"
#include "Memoria.h"
#include "ComandoEndp.h"
#include "ComandoWrite.h"
#include "ComandoWriteln.h"
#include "Comandoread.h"
#include "ComandowriteVar.h"
#include "ComandoAtrib.h"
#include "ComandoIf.h"
#include "ComandoFor.h"
#include "ComandoWhile.h"
#include "Expressao.h"
#include "ExpBinaria.h"
#include "ExpConstante.h"
#include "ExpVariavel.h"
#include <vector>
#include <stack>
#include <stdlib.h> 
#include <iostream>
using namespace std;

class Interpretador {
public:
    Interpretador(string nome);
    void listaArquivo();
    void leArquivo();
    void executa();
private:
    ArquivoFonte* arq;
    Memoria* memoria;
    vector<Comando*> comandos;
    string palavraAtual;
    stack<Expressao*> pilha;
    int linhaIF;
    void trataComandoEndp(int linha);
    void trataComandowriteStr(int linha);
    void trataComandowriteln(int linha);
    void trataComandoread(int linha);
    void trataComandowriteVar(int linha);
    void trataExp(string comandoAtual, int linha);
    void tratarIf(void);
    bool trataElse(void);
    void tratarFor(void);
    void tratarWhile(void);
    Expressao* trataExpressao(void);
    Expressao* trataExpressaoIf(void);
    Expressao* trataExpressaoFor(void);
    Expressao* trataExpressaoWhile(void);
    void expressao(void);
    void fator(void);
    void termo(void);
    void corrigirBugs(void);
};

#endif // INTERPRETADOR_H
