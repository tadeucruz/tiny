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

package br.pucminas.inf.ex;

public class ExpBinaria extends Expressao {

	Expressao exp1;
	Expressao exp2;
	String op;

	public ExpBinaria(String operador, Expressao exp1, Expressao exp2) {
		this.exp1 = exp1;
		this.exp2 = exp2;
		this.op = operador;
	}

	public float avalia() {
		float v2 = exp1.avalia();
		float v1 = exp2.avalia();
		float volta = 0;
		if (op.equals("+")) {
			volta = v1 + v2;
		} else if (op.equals("-")) {
			volta = v1 - v2;
		} else if (op.equals("*")) {
			volta = v1 * v2;
		} else if (op.equals("/")) {
			volta = v1 / v2;
		} else if (op.equals("=")) {
			if (v1 == v2) {
				volta = 0;
			} else {
				volta = 1;
			}
		} else if (op.equals("<")) {
			if (v1 < v2) {
				volta = 0;
			} else {
				volta = 1;
			}
		} else if (op.equals(">")) {
			if (v1 > v2) {
				volta = 0;
			} else {
				volta = 1;
			}
		} else if (op.equals(">=")) {
			if (v1 >= v2) {
				volta = 0;
			} else {
				volta = 1;
			}
		} else if (op.equals("<=")) {
			if (v1 <= v2) {
				volta = 0;
			} else {
				volta = 1;
			}
		} else if (op.equals("<>")) {
			if (v1 != v2) {
				volta = 0;
			} else {
				volta = 1;
			}
		} else if (op.equals("or")) {
			if ((int) (v1) == 0 || (int) (v2) == 0) {
				volta = 0;
			} else {
				volta = 1;
			}
		} else if (op.equals("and")) {
			if ((int) (v1) == 0 && (int) (v2) == 0) {
				volta = 0;
			} else {
				volta = 1;
			}
		} else {
			volta = (float) Math.sqrt(v1);
		}

		return volta;
	}

}
