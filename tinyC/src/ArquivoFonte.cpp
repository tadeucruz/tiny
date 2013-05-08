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
#include <vector>
#include "../include/ArquivoFonte.h"

ArquivoFonte::ArquivoFonte(string name) {
    cont = 0;
    inFile.open(name.c_str());

    arrumarPalavras();
    palavras.push_back("EOF");
}

ArquivoFonte::~ArquivoFonte() {
    inFile.close();
}

void ArquivoFonte::arrumarPalavras() {
    string s;
    char * cstr;
    while (inFile >> s) {
        string final;
        cstr = new char [s.size() + 1];
        strcpy(cstr, s.c_str());
        for (int i = 0; i < s.length(); i++) {
            if (cstr[i] == ':') {
                palavras.push_back(final);
                final = "";
                palavras.push_back(":=");
                i++;
                tratamentoAtrib(s, i);
            }
            if (cstr[i] == '(') {
                if (final != "") {
                    palavras.push_back(final);
                }
                palavras.push_back("(");
                final = "";
            }else if (cstr[i] == '"') {
                tratamento(s, i + 1);
                i = s.length();
                final = "";
            }else if (cstr[i] == ')') {
                if (final[0] == '(') {
                    int temp = final.size() - 1;
                    char t = final[temp];
                    final = "";
                    final = final + t;
                    palavras.push_back(final);
                    palavras.push_back(")");
                    final = "";
                }else {
                    palavras.push_back(final);
                    palavras.push_back(")");
                    final = "";
                }
            }else if (cstr[i] == ';') {
                if (final[0] == ';') {
                    string ajuda;
                    for (int y = 1; y < final.size(); y++) {
                        ajuda = ajuda + final[y];
                    }
                    final = "";
                    final = ajuda;
                    i++;
                }else if (final[0] == ')') {
                    string ajuda;
                    for (int y = 1; y < final.size(); y++) {
                        ajuda = ajuda + final[y];
                    }
                    if (ajuda.size() != 0) {
                        final = "";
                        final = ajuda;
                    }else {
                        final = ";";
                    }
                }
                if (final != ";") {
                    palavras.push_back(final);
                }
                palavras.push_back(";");
                final = "";
            }
            //cout << (int)cstr[i] <<  " - " << cstr[i] <<endl;
            final = final + cstr[i];
        }
        if (final.compare("endp") == 0) {
            palavras.push_back(final);
            final = "";
        }
        if (final.compare("if") == 0) {
            palavras.push_back("if");
            tratarmentoIf();
            final = "";
        }
        if (final.compare("else") == 0) {
            palavras.push_back("else");
            final = "";
        }
        if (final.compare("for") == 0) {
            palavras.push_back("for");
            tratarmentoFor();
            final = "";
        }
        if (final.compare("while") == 0) {
            palavras.push_back("while");
            tratarmentoWhile();
            final = "";
        }
        if (final == ";") {
            final = "";
        }
        if (final.length() > 1) {
            palavras.push_back(final);
        }
    }
}

void ArquivoFonte::tratarmentoWhile(){
    string s;
    char * cstr;
    while (inFile >> s) {
        string final;
        cstr = new char [s.size() + 1];
        strcpy(cstr, s.c_str());
        for (int i = 0; i < s.length(); i++) {
            if(s[i] == '<' && s[i+1] == '=') {
                palavras.push_back("<=");
                break;
            }
            if(s[i] == 'd' && s[i + 1] == 'o'){
                palavras.push_back("do");
                return;
            }
            string a;
            a = a + s[i];
            palavras.push_back(a);
        }
    }
}

void ArquivoFonte::tratarmentoFor() {
    string s;
    char * cstr;
    while (inFile >> s) {
        string final;
        cstr = new char [s.size() + 1];
        strcpy(cstr, s.c_str());
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == 'd' && s[i + 1] == 'o' && s[i + 2] == 'w') {
                string a = "downto";
                palavras.push_back(a);
                i = i + 6;
                break;
            }else if (s[i] == 'd' && s[i + 1] == 'o') {
                string a = "do";
                palavras.push_back(a);
                i = i + 2;
                return;
            }else if (s[i] == 't' && s[i + 1] == 'o') {
                string a = "to";
                palavras.push_back(a);
                i = i + 2;
                break;
            }else if (s[i] == ':' && s[i + 1] == '=') {
                string a = ":=";
                palavras.push_back(a);
                i = i + 2;
                break;
            }else if (((s[i] - 48) >= 0) && ((s[i] - 48) <= 9)) {
                bool controle = true;
                string numero;
                while (controle) {
                    if (((s[i] - 48) >= 0) && ((s[i] - 48) <= 9)) {
                        numero = numero + s[i];
                        i++;
                    }else {
                        controle = false;
                    }
                }
                palavras.push_back(numero);
                if (i >= s.length()) break;
            }
            string a;
            a = a + s[i];
            palavras.push_back(a);
        }
    }
}

void ArquivoFonte::tratarmentoIf() {
    string s;
    char * cstr;
    while (inFile >> s) {
        string final;
        cstr = new char [s.size() + 1];
        strcpy(cstr, s.c_str());
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == 'a' && s[i + 1] == 'n' && s[i + 2] == 'd') {
                string a = "and";
                palavras.push_back(a);
                i = i + 3;
                break;
            }
            if (s[i] == 'o' && s[i + 1] == 'r') {
                string a = "or";
                palavras.push_back(a);
                i = i + 2;
                break;
            }
            if (s[i] == 't' && s[i + 1] == 'h' && s[i + 2] == 'e' && s[i + 3] == 'n') {
                string a = "then";
                palavras.push_back(a);
                return;
            }
            if (((s[i] - 48) >= 0) && ((s[i] - 48) <= 9)) {
                bool controle = true;
                string numero;
                while (controle) {
                    if (((s[i] - 48) >= 0) && ((s[i] - 48) <= 9)) {
                        numero = numero + s[i];
                        i++;
                    }else {
                        controle = false;
                    }
                }
                palavras.push_back(numero);
                break;
            }
            string a;
            a = a + s[i];
            if (a.compare(" ") == 0) {
                //cout << "teste" << endl;
            }
            palavras.push_back(a);
        }
    }
}

void ArquivoFonte::tratamentoAtrib(string palavra, int pos) {
    string s;
    char * cstr;
    while (inFile >> s) {
        string final;
        cstr = new char [s.size() + 1];
        strcpy(cstr, s.c_str());
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == ';') {
                palavras.push_back(";");
                return;
            }
            if (s[i] == 's' && s[i + 1] == 'q') {
                string a = "sqrt";
                palavras.push_back(a);
                i = i + 4;
            }
            string a;
            a = a + s[i];
            palavras.push_back(a);
        }
    }
}

void ArquivoFonte::tratamento(string palavra, int pos) {
    bool controle = true;
    string s, final, g;
    for (int i = pos; i < palavra.length(); i++) {
        if (palavra[i] == '"') {
            palavras.push_back(final);
            palavras.push_back(")");
            palavras.push_back(";");
            return;
        }
        if (palavra[i] == ')') {
            palavras.push_back(final);
            palavras.push_back(")");
            palavras.push_back(";");
            return;
        }
        final = final + palavra[i];
    }
    while (controle && inFile >> s) {
        final = final + " ";
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '"') {
                controle = false;
                palavras.push_back(final);
                final = "";
            }else if (controle == false) {
                g = g + s[i];
                palavras.push_back(g);
                g.clear();
            }else {
                final = final + s[i];
            }
        }
    }
}

bool ArquivoFonte::procurar(string oque, string frase) {
    size_t found;
    found = frase.find(oque);
    if (found != string::npos) return true;
    return false;
}

string ArquivoFonte::proximaPalavra() {
    return palavras[cont++];
}

void ArquivoFonte::zerar() {
    cont = 0;
}
