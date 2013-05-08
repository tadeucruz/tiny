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

#ifndef ARQUIVOFONTE_H
#define ARQUIVOFONTE_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

class ArquivoFonte
{
    private:
        ifstream inFile;
        vector<string> palavras;
        void arrumarPalavras();
        void tratamento(string palavra, int pos);
        void tratamentoAtrib(string palavra, int pos);
        void tratarmentoIf();
        void tratarmentoFor();
        void tratarmentoWhile();
        bool procurar(string oque,string frase);
        int cont;
    public:
        ArquivoFonte(string name);
        virtual ~ArquivoFonte();
        string proximaPalavra();
        void zerar();
};

#endif // ARQUIVOFONTE_H
