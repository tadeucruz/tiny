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

public class ComandoWriteVar extends Comando {

	private String var;
	private Memoria memoria;

	public ComandoWriteVar(int lin, String frase, Memoria memoria) {
		linha = ++lin;
		this.var = frase;
		this.memoria = memoria;
	}

	public int executa() {
		char[] vc = this.var.toCharArray();
		if (vc[0] != Interpretador.varGlobal) {
			System.out.print(this.memoria.getMemoria()[vc[0] - 97]);
		} else {
			System.out.println(Interpretador.valorGlobal);
		}
		return linha;
	}

}
