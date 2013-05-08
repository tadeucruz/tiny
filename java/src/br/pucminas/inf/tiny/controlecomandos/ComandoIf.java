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

import br.pucminas.inf.ex.Expressao;

public class ComandoIf extends Comando {

	private int linhaPosIf;
	private int linhaEndIf;
	private int linhaElse;
	private Expressao ex;

	public int getLinhaElse() {
		return linhaElse;
	}

	public void setLinhaElse(int linhaElse) {
		if (linhaElse != 0) {
			this.linhaElse = ++linhaElse;
		}
	}

	public int getLinhaPosIf() {
		return linhaPosIf;
	}

	public void setLinhaPosIf(int linhaPosIf) {
		this.linhaPosIf = linhaPosIf;
	}

	public int getLinhaEndIf() {
		return linhaEndIf;
	}

	public void setLinhaEndIf(int linhaEndIf) {
		this.linhaEndIf = ++linhaEndIf;
	}

	public Expressao getEx() {
		return ex;
	}

	public void setEx(Expressao ex) {
		this.ex = ex;
	}

	public ComandoIf(Expressao ex) {
		this.ex = ex;
	}

	public int executa() {
		float volta = ex.avalia();
		int v;
		if (volta == 0) {
			v = linhaPosIf;
		} else if (linhaElse != 0) {
			v = linhaElse;
		} else {
			v = linhaEndIf;
		}
		return v;
	}

}
