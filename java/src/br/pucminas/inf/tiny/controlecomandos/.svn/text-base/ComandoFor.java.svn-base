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
import br.pucminas.inf.principal.Memoria;

public class ComandoFor extends Comando {

	private String var, metodo;
	private Memoria m;
	public boolean controle = false;
	private Expressao ate;

	private float ultimaLinha, varvalor, posFor;

	public float getPosFor() {
		return posFor;
	}

	public void setPosFor(float posFor) {
		this.posFor = posFor;
	}

	public float getUltimaLinha() {
		return ultimaLinha;
	}

	public void setUltimaLinha(int ultimaLinha) {
		this.ultimaLinha = ultimaLinha;
	}

	public ComandoFor(String var, String varOq, String varvalor, String metodo,
			Expressao ate, Memoria m) {
		this.var = var;
		this.varvalor = Float.valueOf(varvalor);
		this.metodo = metodo;
		this.ate = ate;
		this.m = m;
		char[] vc = this.var.toCharArray();
		if (varOq.equals(":="))
			this.m.setMemoria(vc[0], this.varvalor);
	}

	public int executa() {
		char[] vc = var.toCharArray();
		if (controle == true) {
			float valor = m.getMemoria()[vc[0] - 97];
			if (metodo.equals("to")) {
				if (valor >= ate.avalia()) {
					controle = false;
					return (int) ultimaLinha;
				} else {
					m.setMemoria(vc[0], ++m.getMemoria()[vc[0] - 97]);
					return (int) posFor;
				}
			} else {
				if (valor <= ate.avalia()) {
					controle = false;
					return (int) ultimaLinha;
				} else {
					m.setMemoria(vc[0], --m.getMemoria()[vc[0] - 97]);
					return (int) posFor;
				}
			}
		} else if (ate.avalia() == 0) {
			return (int) ultimaLinha;
		} else {
			controle = true;
			this.m.setMemoria(vc[0], this.varvalor);
			return (int) posFor;
		}
	}

}
