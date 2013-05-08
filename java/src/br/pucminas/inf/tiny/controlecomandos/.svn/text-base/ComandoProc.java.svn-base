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
import br.pucminas.inf.principal.Memoria;

public class ComandoProc extends Comando {

	private Vector comandos;

	private Memoria memoria;

	private String nome;

	private String listapar;

	public ComandoProc(Vector comandos, Memoria memoria, String nome,
			String listapar) {
		this.comandos = comandos;
		this.memoria = memoria;
		this.nome = nome;
		this.listapar = listapar;
	}

	public String getNome() {
		return nome;
	}

	public Vector getComandos() {
		return comandos;
	}

	public void SetValorPar(Vector<Expressao> vex) {
		String[] vars = listapar.split(",");
		for (int i = 0; i < vex.size(); i++) {
			memoria.setMemoria(vars[i].toCharArray()[0], vex.elementAt(i)
					.avalia());
		}
	}

	public int executa() {
		Comando cmd;
		int pc = 0;
		do {
			cmd = (Comando) comandos.elementAt(pc);
			pc = cmd.executa();
		} while (pc != -1);
		return -1;
	}

}
