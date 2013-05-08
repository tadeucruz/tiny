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

#include "../include/ComandoAtrib.h"

ComandoAtrib::ComandoAtrib(int lin, Expressao* exs, string smemorias, Memoria* memorias){
    ex = exs;
    memoria = smemorias[0];
    mem = memorias;
    this->linha = ++lin;
}

int ComandoAtrib::executa(void){
    double valor = ex->avalia();
    mem->setMemoria(memoria,valor);
    return linha;
}