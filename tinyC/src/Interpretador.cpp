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

#include <string>
#include <string>
#include "../include/Interpretador.h"

Interpretador::Interpretador(string nome) {
    memoria = new Memoria();
    arq = new ArquivoFonte(nome);
}

void Interpretador::listaArquivo() {
    string linha;
    do {
        linha = arq->proximaPalavra();
        for (int i = 0; i < linha.length(); i++) {
            char c = linha.at(i);
            cout << c;
        }
        cout << endl;
    } while (linha.compare("EOF") != 0);
    arq->zerar();

}

void Interpretador::leArquivo() {
    string comandoAtual;
    int linha = 0;
    do {
        comandoAtual = arq->proximaPalavra();
        //cout << comandoAtual[0] << endl;
        if (comandoAtual.compare("endp") == 0) {
            trataComandoEndp(linha);
            linha++;
        }else if (comandoAtual.compare("writeStr") == 0) {
            trataComandowriteStr(linha);
            linha++;
        }else if (comandoAtual.compare("writeln") == 0) {
            trataComandowriteln(linha);
            linha++;
        }else if (comandoAtual.compare("read") == 0) {
            trataComandoread(linha);
            linha++;
        }else if (comandoAtual.compare("writeVar") == 0) {
            trataComandowriteVar(linha);
            linha++;
        }else if (comandoAtual.length() == 1) {
            if (((comandoAtual[0] - 97) >= 0) && ((comandoAtual[0] - 97) <= 25)) {
                trataExp(comandoAtual, linha);
                linha++;
            }
        }else if (comandoAtual.compare("if") == 0) {
            linhaIF = linha;
            tratarIf();
            corrigirBugs();
            linhaIF++;
            linha = linhaIF;
        }else if (comandoAtual.compare("for") == 0) {
            linhaIF = linha;
            tratarFor();
            corrigirBugs();
            linhaIF++;
            linha = linhaIF;
        }else if (comandoAtual.compare("while") == 0) {
            linhaIF = linha;
            tratarWhile();
            corrigirBugs();
            linhaIF++;
            linha = linhaIF;
        }
    } while (comandoAtual.compare("endp") != 0);
}

void Interpretador::tratarIf(void) {
    int linhaPosIf = linhaIF + 1;
    int linhaEndIf = 0;
    int linhaElse = 0;
    bool controle = false;
    Expressao* ex = trataExpressaoIf();
    ComandoIf* c = new ComandoIf(ex);
    comandos.push_back(c);
    int comandoMod = comandos.size() - 1;
    int comandoElse = 0;
    string comandoAtual;
    do {
        comandoAtual = arq->proximaPalavra();
        if (comandoAtual.compare("writeStr") == 0) {
            trataComandowriteStr(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("read") == 0) {
            trataComandoread(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("writeln") == 0) {
            trataComandowriteln(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("writeVar") == 0) {
            trataComandowriteVar(linhaIF);
            linhaIF++;
        } else if (comandoAtual.length() == 1) {
            if (((comandoAtual[0] - 97) >= 0) && ((comandoAtual[0] - 97) <= 25)) {
                trataExp(comandoAtual, linhaIF);
                linhaIF++;
            }
        } else if (comandoAtual.compare("if") == 0) {
            linhaIF++;
            tratarIf();
        } else if (comandoAtual.compare("else") == 0) {
            linhaElse = linhaIF;
            comandoElse = comandos.size() - 1;
            controle = trataElse();
            if (controle == true) {
                comandoAtual = "endif";
            }
        } else if (comandoAtual.compare("for") == 0) {
            linhaIF++;
            tratarFor();
        } else if (comandoAtual.compare("while") == 0) {
            linhaIF++;
            tratarWhile();
        } else if (comandoAtual.compare("call") == 0) {
            //tratarCall(linhaIF);
            //linhaIF++;
        } else if (comandoAtual.compare("local") == 0) {
            //tratarLocal();
        }
    } while (!comandoAtual.compare("endif") == 0);
    linhaEndIf = linhaIF;
    if (comandoElse == 0) {
        int x = linhaEndIf + 1;
        Comando* a = (Comando*) comandos.at(comandos.size() - 1);
        if (a->isAlterado() == false) {
            a->setLinha(x);
            a->setAlterado(true);
        }
    } else {
        int x = linhaEndIf + 1;
        Comando* a = (Comando*) comandos.at(comandoElse);
        if (a->isAlterado() == false) {
            a->setLinha(x);
            a->setAlterado(true);
        }
    }
    c = (ComandoIf*) comandos.at(comandoMod);
    c->setLinhaEndIf(linhaEndIf);
    c->setLinhaPosIf(linhaPosIf);
    c->setLinhaElse(linhaElse);
}

bool Interpretador::trataElse(void) {
    string comandoAtual;
    bool controle = false;
    do {
        comandoAtual = arq->proximaPalavra();
        if (comandoAtual.compare("writeStr") == 0) {
            trataComandowriteStr(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("read") == 0) {
            trataComandoread(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("writeln") == 0) {
            trataComandowriteln(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("writeVar") == 0) {
            trataComandowriteVar(linhaIF);
            linhaIF++;
        } else if (comandoAtual.length() == 1) {
            if (((comandoAtual[0] - 97) >= 0) && ((comandoAtual[0] - 97) <= 25)) {
                trataExp(comandoAtual, linhaIF);
                linhaIF++;
            }
        } else if (comandoAtual.compare("if") == 0) {
            linhaIF++;
            tratarIf();
        } else if (comandoAtual.compare("else") == 0) {
            controle = trataElse();
            if (controle == true) {
                comandoAtual = "endif";
            }
        } else if (comandoAtual.compare("for") == 0) {
            linhaIF++;
            //tratarFor();
        } else if (comandoAtual.compare("while") == 0) {
            linhaIF++;
            tratarWhile();
        } else if (comandoAtual.compare("call") == 0) {
            //tratarCall(linhaIF);
            //linhaIF++;
        } else if (comandoAtual.compare("local") == 0) {
            //tratarLocal();
        }
    } while (!comandoAtual.compare("endif") == 0);
    return true;
}

void Interpretador::tratarFor(void) {
    string var, varOq, varvalor, metodo;
    var = arq->proximaPalavra();
    varOq = arq->proximaPalavra();
    varvalor = arq->proximaPalavra();
    metodo = arq->proximaPalavra();
    Expressao* ate = trataExpressaoFor();
    string comandoAtual;
    ComandoFor* c = new ComandoFor(var, varOq, varvalor, metodo, ate, memoria);
    comandos.push_back(c);
    int comandoMod = comandos.size() - 1;
    do {
        comandoAtual = arq->proximaPalavra();
        if (comandoAtual.compare("endp") == 0) {
            trataComandoEndp(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("writeStr") == 0) {
            trataComandowriteStr(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("read") == 0) {
            trataComandoread(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("writeln") == 0) {
            trataComandowriteln(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("writeVar") == 0) {
            trataComandowriteVar(linhaIF);
            linhaIF++;
        } else if (comandoAtual.length() == 1) {
            if (((comandoAtual[0] - 97) >= 0) && ((comandoAtual[0] - 97) <= 25)) {
                trataExp(comandoAtual, linhaIF);
                linhaIF++;
            }
        } else if (comandoAtual.compare("if") == 0) {
            linhaIF++;
            tratarIf();
        } else if (comandoAtual.compare("for") == 0) {
            linhaIF++;
            tratarFor();
        } else if (comandoAtual.compare("while") == 0) {
            linhaIF++;
            tratarWhile();
        } else if (comandoAtual.compare("call") == 0) {
            //tratarCall(linhaIF);
            //linhaIF++;
        } else if (comandoAtual.compare("local") == 0) {
            //tratarLocal();
        }
    } while (!comandoAtual.compare("endfor") == 0);
    c = (ComandoFor*) comandos.at(comandoMod);
    c->setUltimaLinha(linhaIF + 1);
    c->setPosFor(comandoMod + 1);
    Comando* a = (Comando*) comandos.at(linhaIF);
    if (a->isAlterado() == false) {
        a->setLinha(comandoMod);
        a->setAlterado(true);
    }
}

void Interpretador::tratarWhile() {
    Expressao* ex = trataExpressaoWhile();
    ComandoWhile* c = new ComandoWhile(ex);
    comandos.push_back(c);
    int comandoMod = comandos.size() - 1;
    string comandoAtual;
    do {
        comandoAtual = arq->proximaPalavra();
        if (comandoAtual.compare("writeStr") == 0) {
            trataComandowriteStr(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("read") == 0) {
            trataComandoread(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("writeln") == 0) {
            trataComandowriteln(linhaIF);
            linhaIF++;
        } else if (comandoAtual.compare("writeVar") == 0) {
            trataComandowriteVar(linhaIF);
            linhaIF++;
        } else if (comandoAtual.length() == 1) {
            if (((comandoAtual[0] - 97) >= 0) && ((comandoAtual[0] - 97) <= 25)) {
                trataExp(comandoAtual, linhaIF);
                linhaIF++;
            }
        } else if (comandoAtual.compare("if") == 0) {
            linhaIF++;
            tratarIf();
        } else if (comandoAtual.compare("for") == 0) {
            linhaIF++;
            tratarFor();
        } else if (comandoAtual.compare("while") == 0) {
            linhaIF++;
            tratarWhile();
        } else if (comandoAtual.compare("call") == 0) {
            //tratarCall(linhaIF);
            //linhaIF++;
        } else if (comandoAtual.compare("local") == 0) {
            //tratarLocal();
        }
    } while (!comandoAtual.compare("endw") == 0);
    c = (ComandoWhile*) comandos.at(comandoMod);
    c->setUltimaLinha(linhaIF + 1);
    c->setPosWhile(comandoMod + 1);
    Comando* a = (Comando*) comandos.at(linhaIF);
    if (a->isAlterado() == false) {
        a->setLinha(comandoMod);
        a->setAlterado(true);
    }
}

void Interpretador::trataExp(string comandoAtual, int linha) {
    Expressao* ex = trataExpressao();
    ComandoAtrib* c = new ComandoAtrib(linha, ex, comandoAtual, memoria);
    comandos.push_back(c);
}

void Interpretador::trataComandowriteVar(int linha) {
    arq->proximaPalavra();
    string smemoria = arq->proximaPalavra();
    ComandowriteVar* c = new ComandowriteVar(linha, memoria, smemoria);
    comandos.push_back(c);
}

void Interpretador::trataComandoread(int linha) {
    arq->proximaPalavra();
    string smemoria = arq->proximaPalavra();
    Comandoread* c = new Comandoread(linha, memoria, smemoria);
    comandos.push_back(c);
}

void Interpretador::trataComandowriteln(int linha) {
    ComandoWriteln* c = new ComandoWriteln(linha);
    comandos.push_back(c);
}

void Interpretador::trataComandoEndp(int linha) {
    ComandoEndp* c = new ComandoEndp(linha);
    comandos.push_back(c);
}

void Interpretador::trataComandowriteStr(int linha) {
    string frase;
    arq->proximaPalavra();
    frase = arq->proximaPalavra();
    ComandoWrite* c = new ComandoWrite(linha, frase);
    comandos.push_back(c);
}

Expressao* Interpretador::trataExpressao(void) {
    arq->proximaPalavra();
    palavraAtual = arq->proximaPalavra();
    expressao();
    Expressao* raizArvoreExpressao = (Expressao*) pilha.top();
    pilha.pop();
    return raizArvoreExpressao;
}

Expressao* Interpretador::trataExpressaoIf(void) {
    palavraAtual = arq->proximaPalavra();
    expressao();
    Expressao* raizArvoreExpressao = (Expressao*) pilha.top();
    pilha.pop();
    return raizArvoreExpressao;
}

Expressao* Interpretador::trataExpressaoFor() {
    palavraAtual = arq->proximaPalavra();
    expressao();
    Expressao* raizArvoreExpressao = (Expressao*) pilha.top();
    pilha.pop();
    return raizArvoreExpressao;
}

Expressao* Interpretador::trataExpressaoWhile() {
    palavraAtual = arq->proximaPalavra();
    string parte1 = palavraAtual;
    palavraAtual = arq->proximaPalavra();
    string op = palavraAtual;
    palavraAtual = arq->proximaPalavra();
    expressao();
    Expressao* exp1 = (Expressao*) pilha.top();
    pilha.pop();
    pilha.push(new ExpVariavel(parte1, memoria));
    Expressao* exp2 = (Expressao*) pilha.top();
    pilha.pop();
    pilha.push(new ExpBinaria(op, exp1, exp2));
    Expressao* raizArvoreExpressao = (Expressao*) pilha.top();
    pilha.pop();
    return raizArvoreExpressao;
}

void Interpretador::expressao(void) {
    termo();
    while (palavraAtual.compare("+") == 0 || palavraAtual.compare("-") == 0
            || palavraAtual.compare("sqrt") == 0 || palavraAtual.compare("=") == 0
            || palavraAtual.compare(">") == 0 || palavraAtual.compare("<") == 0
            || palavraAtual.compare("<=") == 0 || palavraAtual.compare(">=") == 0
            || palavraAtual.compare("<>") == 0) {
        string op = palavraAtual;
        palavraAtual = arq->proximaPalavra();
        termo();
        Expressao* exp1 = (Expressao*) pilha.top();
        pilha.pop();
        Expressao* exp2 = (Expressao*) pilha.top();
        pilha.pop();
        ExpBinaria* ex = new ExpBinaria(op, exp1, exp2);
        pilha.push(ex);
    }
}

void Interpretador::termo(void) {
    fator();
    while (palavraAtual.compare("*") == 0 || palavraAtual.compare("/") == 0
            || palavraAtual.compare("and") == 0 || palavraAtual.compare("or") == 0
            || palavraAtual.compare("sqrt") == 0) {
        string op = palavraAtual;
        palavraAtual = arq->proximaPalavra();
        fator();
        if (op.compare("sqrt") == 0) {
            Expressao* exp1 = (Expressao*) pilha.top();
            pilha.pop();
            ExpConstante* exp2 = new ExpConstante(0);
            ExpBinaria* ex = new ExpBinaria(op, exp1, exp2);
            pilha.push(ex);
        } else {
            Expressao* exp1 = (Expressao*) pilha.top();
            pilha.pop();
            Expressao* exp2 = (Expressao*) pilha.top();
            pilha.pop();
            ExpBinaria* ex = new ExpBinaria(op, exp1, exp2);
            pilha.push(ex);
        }
    }
}

void Interpretador::fator(void) {
    if (palavraAtual.length() == 1) {
        if (((palavraAtual[0] - 97) >= 0) && ((palavraAtual[0] - 97) <= 25)) {
            ExpVariavel* ex = new ExpVariavel(palavraAtual, memoria);
            pilha.push(ex);
            palavraAtual = arq->proximaPalavra();
        }else if (((palavraAtual[0] - 48) >= 0) && ((palavraAtual[0] - 48) <= 9)) {
            double n;
            n = atoi(palavraAtual.c_str());
            ExpConstante* ex = new ExpConstante(n);
            pilha.push(ex);
            palavraAtual = arq->proximaPalavra();
        }
    }
    if (palavraAtual.compare("(") == 0) {
        palavraAtual = arq->proximaPalavra();
        expressao();
        if (palavraAtual.compare(")") == 0) {
            palavraAtual = arq->proximaPalavra();
        }
    }
}

void Interpretador::corrigirBugs(void) {
    for (int i = 0; i < comandos.size(); i++) {
        Comando* c = (Comando*) comandos.at(i);
        if (c->getLinha() == i) {
            int t = c->getLinha() + 1;
            c->setLinha(t);
        }
    }
}

void Interpretador::executa(void) {
    Comando* cmd;
    int pc = 0;
    do {
        cmd = comandos[pc];
        pc = cmd->executa();
    } while (pc != -1);
}