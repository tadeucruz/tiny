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

#include "../include/ExpBinaria.h"

ExpBinaria::ExpBinaria(string operador, Expressao* exp1s, Expressao* exp2s){
    op = operador;
    exp1 = exp1s;
    exp2 = exp2s;
}

double ExpBinaria::avalia(void) {
    double v2 = exp1->avalia();
    double v1 = exp2->avalia();
    double volta = 0;
    if (op.compare("+") == 0) {
        volta = v1 + v2;
    } else if (op.compare("-") == 0) {
        volta = v1 - v2;
    } else if (op.compare("*") == 0) {
        volta = v1 * v2;
    } else if (op.compare("/") == 0) {
        volta = v1 / v2;
    } else if (op.compare("=") == 0) {
        if (v1 == v2) {
            volta = 0;
        } else {
            volta = 1;
        }
    } else if (op.compare("<") == 0) {
        if (v1 < v2) {
            volta = 0;
        } else {
            volta = 1;
        }
    } else if (op.compare(">") == 0) {
        if (v1 > v2) {
            volta = 0;
        } else {
            volta = 1;
        }
    } else if (op.compare(">=") == 0) {
        if (v1 >= v2) {
            volta = 0;
        } else {
            volta = 1;
        }
    } else if (op.compare("<=") == 0) {
        if (v1 <= v2) {
            volta = 0;
        } else {
            volta = 1;
        }
    } else if (op.compare("<>") == 0) {
        if (v1 != v2) {
            volta = 0;
        } else {
            volta = 1;
        }
    } else if (op.compare("or") == 0) {
        if ((int) (v1) == 0 || (int) (v2) == 0) {
            volta = 0;
        } else {
            volta = 1;
        }
    } else if (op.compare("and") == 0) {
        if ((int) (v1) == 0 && (int) (v2) == 0) {
            volta = 0;
        } else {
            volta = 1;
        }
    } else {
        volta = (float) sqrt(v2);
    }

    return volta;
}