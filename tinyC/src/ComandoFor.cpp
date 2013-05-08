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

#include <stdlib.h>

#include "../include/ComandoFor.h"

ComandoFor::ComandoFor(string vars, string varOqs, string varvalors, string metodos, Expressao* ates, Memoria* ms) {
    controle = false;
    var = vars;
    varvalor = atoi(varvalors.c_str());
    metodo = metodos;
    ate = ates;
    m = ms;
    m->setMemoria(var[0], varvalor);
}

int ComandoFor::executa(void) {
    char vc = var[0];
    if (controle == true) {
        float valor = m->getMemoria(vc);
        if (metodo.compare("to") == 0) {
            if (valor >= ate->avalia()) {
                controle = false;
                return (int) ultimaLinha;
            } else {
                double a = m->getMemoria(vc);
                a++;
                m->setMemoria(vc,a);
                return (int) posFor;
            }
        } else {
            if (valor <= ate->avalia()) {
                controle = false;
                return (int) ultimaLinha;
            } else {
                double a = m->getMemoria(vc);
                a--;
                m->setMemoria(vc, a);
                return (int) posFor;
            }
        }
    } else if (ate->avalia() == 0) {
        return (int) ultimaLinha;
    } else {
        controle = true;
        m->setMemoria(vc, varvalor);
        return (int) posFor;
    }
}

float ComandoFor::getPosFor(){
    return posFor;
}

float ComandoFor::getUltimaLinha(){
    return ultimaLinha;
}

void ComandoFor::setPosFor(float posFors){
    posFor = posFors;
}

void ComandoFor::setUltimaLinha(int ultimaLinhas){
    ultimaLinha = ultimaLinhas;
}