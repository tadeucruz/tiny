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

#include "../include/ComandoIf.h"

ComandoIf::ComandoIf(Expressao* exs) {
    ex = exs;
    linhaElse = 0;
}

int ComandoIf::executa(void) {
    double volta = ex->avalia();
    int v;
    if (volta == 0) {
        v = linhaPosIf;
    } else if (linhaElse != 0) {
        v = linhaElse;
    } else {
        v = linhaEndIf;
    }
    return v;
}

Expressao* ComandoIf::getEx(void) {
    return ex;
}

int ComandoIf::getLinhaElse(void) {
    return linhaElse;
}

int ComandoIf::getLinhaEndIf(void) {
    return linhaEndIf;
}

int ComandoIf::getLinhaPosIf(void) {
    return linhaPosIf;
}

void ComandoIf::setEx(Expressao* exs) {
    ex = exs;
}

void ComandoIf::setLinhaElse(int linhaElses) {
    if (linhaElses != 0) {
        linhaElse = ++linhaElses;
    }
}

void ComandoIf::setLinhaEndIf(int linhaEndIfs) {
    linhaEndIf = ++linhaEndIfs;
}

void ComandoIf::setLinhaPosIf(int linhaPosifs) {
    linhaPosIf = linhaPosifs;
}