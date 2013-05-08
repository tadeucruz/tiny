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

#ifndef _COMANDOFOR_H
#define	_COMANDOFOR_H
#include "Comando.h"
#include "Expressao.h"
#include "Memoria.h"

class ComandoFor: public Comando {
private:
    Expressao* ate;
    bool controle;
    Memoria* m;
    float ultimaLinha, varvalor, posFor;
    string var, metodo;
public:
    ComandoFor(string vars, string varOqs, string varvalors, string metodos,Expressao* ates,Memoria* ms);
    int executa(void);
    float getPosFor(void);
    float getUltimaLinha(void);
    void setPosFor(float posFors);
    void setUltimaLinha(int ultimaLinhas);
};


#endif	/* _COMANDOFOR_H */

