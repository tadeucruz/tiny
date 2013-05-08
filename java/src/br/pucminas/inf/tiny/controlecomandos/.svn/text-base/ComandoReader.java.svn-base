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

import br.pucminas.inf.principal.Interpretador;
import br.pucminas.inf.principal.Memoria;
import br.pucminas.inf.utilitarios.Console;

public class ComandoReader extends Comando {

	private String memoria;
	private Memoria m;

	public ComandoReader(int lin, String smemoria, Memoria memoria) {
		linha = ++lin;
		this.memoria = smemoria;
		this.m = memoria;
	}

	public int executa() {
		char[] vc = this.memoria.toCharArray();
		Console c = new Console();
		if (vc[0] != Interpretador.varGlobal) {
			this.m.setMemoria(vc[0], c.readInt());
		} else {
			Interpretador.valorGlobal = c.readInt();
		}
		return linha;
	}

}
