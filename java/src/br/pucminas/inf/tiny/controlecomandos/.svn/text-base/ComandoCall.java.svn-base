/*
This file is part of tiny-java.

tiny-java is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

tiny-java is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ProjectRisc.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2008 tadeucruz<contato@tadeucruz.com>
 */

package br.pucminas.inf.tiny.controlecomandos;

import java.util.Vector;

import br.pucminas.inf.ex.Expressao;
import br.pucminas.inf.principal.Interpretador;
import br.pucminas.inf.principal.Memoria;

public class ComandoCall extends Comando {

	private Vector comandos;
	private String nome;
	private Vector<Expressao> listapar = new Vector<Expressao>();
	private Memoria memoria;

	public ComandoCall(String nome, Vector<Expressao> ex, Memoria memoria,
			int linha) {
		this.nome = nome;
		this.listapar = ex;
		this.memoria = memoria;
		this.linha = linha + 1;
	}

	public int executa() {
		for (int i = 0; i < Interpretador.comandosGeral.size(); i++) {
			if (Interpretador.comandosGeral.elementAt(i) instanceof ComandoProc) {
				if (((ComandoProc) Interpretador.comandosGeral.elementAt(i))
						.getNome().equals(nome)) {
					((ComandoProc) Interpretador.comandosGeral.elementAt(i))
							.SetValorPar(listapar);
					Comando cmd = (Comando) Interpretador.comandosGeral
							.elementAt(i);
					cmd.executa();
					return linha;
				}
			}
		}
		return -1;
	}

}
