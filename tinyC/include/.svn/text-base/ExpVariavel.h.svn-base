/* 
 * File:   ExpVariavel.h
 * Author: tadeucruz
 *
 * Created on 19 de Outubro de 2008, 02:53
 */




#ifndef _EXPVARIAVEL_H
#define	_EXPVARIAVEL_H
#include "Expressao.h"
#include "Memoria.h"

class ExpVariavel: public Expressao {
public:
    ExpVariavel(string nome, Memoria* mem);
    double avalia(void);
private:
    Memoria* mem;
    char nomevar;
};

#endif	/* _EXPVARIAVEL_H */

