/* 
 * File:   Memoria.h
 * Author: tadeucruz
 *
 * Created on 4 de Outubro de 2008, 14:01
 */

#ifndef _MEMORIA_H
#define	_MEMORIA_H

class Memoria{
private:
    double memoria[26];
public:
    Memoria();
    void setMemoria(char codmemoria, double valor);
    double getMemoria(char codmemoria);
};

#endif	/* _MEMORIA_H */

