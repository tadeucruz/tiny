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

package br.pucminas.inf.principal;

import java.util.Stack;
import java.util.Vector;

import lp.ArquivoFonte;
import br.pucminas.inf.ex.ExpBinaria;
import br.pucminas.inf.ex.ExpConstante;
import br.pucminas.inf.ex.ExpVariavel;
import br.pucminas.inf.ex.Expressao;
import br.pucminas.inf.tiny.controlecomandos.Comando;
import br.pucminas.inf.tiny.controlecomandos.ComandoAtrib;
import br.pucminas.inf.tiny.controlecomandos.ComandoCall;
import br.pucminas.inf.tiny.controlecomandos.ComandoEndp;
import br.pucminas.inf.tiny.controlecomandos.ComandoFor;
import br.pucminas.inf.tiny.controlecomandos.ComandoIf;
import br.pucminas.inf.tiny.controlecomandos.ComandoProc;
import br.pucminas.inf.tiny.controlecomandos.ComandoReader;
import br.pucminas.inf.tiny.controlecomandos.ComandoWhile;
import br.pucminas.inf.tiny.controlecomandos.ComandoWrite;
import br.pucminas.inf.tiny.controlecomandos.ComandoWriteVar;
import br.pucminas.inf.tiny.controlecomandos.ComandoWriteln;

public class Interpretador {

	private ArquivoFonte arq;

	private Vector comandos;

	public static Vector comandosGeral;
	public static char varGlobal;
	public static float valorGlobal;

	private Memoria memoria;

	private Stack pilha;

	private String palavraAtual;

	private int linhaIF;

	public Interpretador(String nome) {
		arq = new ArquivoFonte(nome);
		comandos = new Vector();
		memoria = new Memoria();
	}

	public Interpretador(ArquivoFonte arq) {
		this.arq = arq;
		comandos = new Vector();
		memoria = new Memoria();
	}

	public Vector getComandos() {
		return comandos;
	}

	public Memoria getMemoria() {
		return memoria;
	}

	public void listaArquivo() {
		String palavra;

		do {
			palavra = arq.proximaPalavra();
			System.out.println("Palavra: " + palavra);
		} while (!palavra.equals("EOF"));
	}

	public void leArquivo() {

		String comandoAtual;
		int linha = 0;
		do {
			comandoAtual = arq.proximaPalavra();
			if (comandoAtual.equals("endp")) {
				trataComandoEndp(linha);
				linha++;
			} else if (comandoAtual.equals("writeStr")) {
				trataComandoWrite(linha);
				linha++;
			} else if (comandoAtual.equals("read")) {
				trataComandoReader(linha);
				linha++;
			} else if (comandoAtual.equals("writeln")) {
				trataComandoWriteln(linha);
				linha++;
			} else if (comandoAtual.equals("writeVar")) {
				trataComandoWriteVar(linha);
				linha++;
			} else if (comandoAtual.matches("[a-z]")) {
				trataExp(comandoAtual, linha);
				linha++;
			} else if (comandoAtual.equals("if")) {
				linhaIF = linha;
				tratarIf();
				corrigirBugs();
				linhaIF++;
				linha = linhaIF;
			} else if (comandoAtual.equals("for")) {
				linhaIF = linha;
				tratarFor();
				corrigirBugs();
				linhaIF++;
				linha = linhaIF;
			} else if (comandoAtual.equals("while")) {
				linhaIF = linha;
				tratarWhile();
				corrigirBugs();
				linhaIF++;
				linha = linhaIF;
			} else if (comandoAtual.equals("proc")) {
				tratarProc();
			} else if (comandoAtual.equals("call")) {
				tratarCall(linha);
				linha++;
			} else if (comandoAtual.equals("local")) {
				tratarLocal();
				// linha++;
			} else if (comandoAtual.equals("global")) {
				tratarGlobal();
				// linha++;
			} else if (comandoAtual.equals("endproc")) {
				comandoAtual = "endp";
				trataComandoEndp(linha);
			} else if (comandoAtual.equals("EOF")) {
				comandoAtual = "endp";
				trataComandoEndp(linha);
			}
		} while (!comandoAtual.equals("endp"));
		tratarMain();
	}

	private void tratarMain() {
		for (int i = 0; i < comandos.size(); i++) {
			if (comandos.elementAt(i) instanceof ComandoProc) {
				/*
				 * for (int t =
				 * 0;t<((ComandoProc)comandos.elementAt(i)).getComandos
				 * ().size();t++){ if
				 * (((ComandoProc)comandos.elementAt(i)).getComandos
				 * ().elementAt(t) instanceof ComandoCall){
				 * ((ComandoCall)((ComandoProc
				 * )comandos.elementAt(i)).getComandos
				 * ().elementAt(t)).setComandos(comandos); } }
				 */
				if (((ComandoProc) comandos.elementAt(i)).getNome().equals(
						"main")) {
					Comando temp = (Comando) comandos.remove(0);
					Comando main = (Comando) comandos.remove(i - 1);
					comandos.insertElementAt(main, 0);
					comandos.add(temp);
				}
			}
		}
		comandosGeral = comandos;
	}

	private void tratarLocal() {
		String a = arq.proximaPalavra();
		String controle = a;
		while (!a.equals(";")) {
			a = arq.proximaPalavra();
		}
	}

	private void tratarGlobal() {
		Interpretador.varGlobal = arq.proximaPalavra().toCharArray()[0];
		Interpretador.valorGlobal = 0;
	}

	private void tratarCall(int linha) {
		String nome = arq.proximaPalavra();
		Expressao ex = trataExpressao();
		Vector<Expressao> vex = new Vector<Expressao>();
		vex.add(ex);
		while (palavraAtual.equals(",")) {
			ex = trataExpressaoCall();
			vex.add(ex);
		}
		palavraAtual = arq.proximaPalavra();
		ComandoCall c = new ComandoCall(nome, vex, memoria, linha);
		comandos.add(c);
	}

	private void tratarProc() {
		String nome = arq.proximaPalavra();
		arq.proximaPalavra();
		String listapar = "";
		String controle = arq.proximaPalavra();
		while (!controle.equals(")")) {
			listapar = listapar + controle;
			controle = arq.proximaPalavra();
		}
		Interpretador i = new Interpretador(arq);
		i.leArquivo();
		ComandoProc c = new ComandoProc(i.getComandos(), i.getMemoria(), nome,
				listapar);
		comandos.add(c);
	}

	private void tratarWhile() {
		Expressao ex = trataExpressaoWhile();
		ComandoWhile c = new ComandoWhile(ex);

		comandos.add(c);
		int comandoMod = comandos.size() - 1;
		String comandoAtual;
		do {
			comandoAtual = arq.proximaPalavra();
			if (comandoAtual.equals("writeStr")) {
				trataComandoWrite(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("read")) {
				trataComandoReader(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("writeln")) {
				trataComandoWriteln(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("writeVar")) {
				trataComandoWriteVar(linhaIF);
				linhaIF++;
			} else if (comandoAtual.matches("[a-z]")) {
				trataExp(comandoAtual, linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("if")) {
				linhaIF++;
				tratarIf();
			} else if (comandoAtual.equals("for")) {
				linhaIF++;
				tratarFor();
			} else if (comandoAtual.equals("while")) {
				linhaIF++;
				tratarWhile();
			} else if (comandoAtual.equals("call")) {
				tratarCall(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("local")) {
				tratarLocal();
			}
		} while (!comandoAtual.equals("endw"));
		c = (ComandoWhile) comandos.elementAt(comandoMod);
		c.setUltimaLinha(linhaIF + 1);
		c.setPosWhile(comandoMod + 1);
		Comando a = (Comando) comandos.elementAt(linhaIF);
		if (a.isAlterado() == false) {
			a.setLinha(comandoMod);
			a.setAlterado(true);
		}
	}

	private void tratarFor() {
		String var, varOq, varvalor, metodo;
		var = arq.proximaPalavra();
		varOq = arq.proximaPalavra();
		varvalor = arq.proximaPalavra();
		metodo = arq.proximaPalavra();
		Expressao ate = trataExpressaoFor();
		String comandoAtual;
		ComandoFor c = new ComandoFor(var, varOq, varvalor, metodo, ate,
				memoria);
		comandos.add(c);
		int comandoMod = comandos.size() - 1;
		do {
			comandoAtual = arq.proximaPalavra();
			if (comandoAtual.equals("endp")) {
				trataComandoEndp(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("writeStr")) {
				trataComandoWrite(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("read")) {
				trataComandoReader(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("writeln")) {
				trataComandoWriteln(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("writeVar")) {
				trataComandoWriteVar(linhaIF);
				linhaIF++;
			} else if (comandoAtual.matches("[a-z]")) {
				trataExp(comandoAtual, linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("if")) {
				linhaIF++;
				tratarIf();
			} else if (comandoAtual.equals("for")) {
				linhaIF++;
				tratarFor();
			} else if (comandoAtual.equals("while")) {
				linhaIF++;
				tratarWhile();
			} else if (comandoAtual.equals("call")) {
				tratarCall(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("local")) {
				tratarLocal();
			}
		} while (!comandoAtual.equals("endfor"));
		c = (ComandoFor) comandos.elementAt(comandoMod);
		c.setUltimaLinha(linhaIF + 1);
		c.setPosFor(comandoMod + 1);
		Comando a = (Comando) comandos.elementAt(linhaIF);
		if (a.isAlterado() == false) {
			a.setLinha(comandoMod);
			a.setAlterado(true);
		}
	}

	private void tratarIf() {
		int linhaPosIf = linhaIF + 1;
		int linhaEndIf = 0;
		int linhaElse = 0;
		boolean controle = false;
		Expressao ex = trataExpressaoIf();
		ComandoIf c = new ComandoIf(ex);
		comandos.add(c);
		int comandoMod = comandos.size() - 1;
		int comandoElse = 0;
		String comandoAtual;
		do {
			comandoAtual = arq.proximaPalavra();
			if (comandoAtual.equals("writeStr")) {
				trataComandoWrite(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("read")) {
				trataComandoReader(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("writeln")) {
				trataComandoWriteln(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("writeVar")) {
				trataComandoWriteVar(linhaIF);
				linhaIF++;
			} else if (comandoAtual.matches("[a-z]")) {
				trataExp(comandoAtual, linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("if")) {
				linhaIF++;
				tratarIf();
			} else if (comandoAtual.equals("else")) {
				linhaElse = linhaIF;
				comandoElse = comandos.size() - 1;
				controle = trataElse();
				if (controle == true) {
					comandoAtual = "endif";
				}
			} else if (comandoAtual.equals("for")) {
				linhaIF++;
				tratarFor();
			} else if (comandoAtual.equals("while")) {
				linhaIF++;
				tratarWhile();
			} else if (comandoAtual.equals("call")) {
				tratarCall(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("local")) {
				tratarLocal();
			}
		} while (!comandoAtual.equals("endif"));
		linhaEndIf = linhaIF;
		if (comandoElse == 0) {
			int x = linhaEndIf + 1;
			Comando a = (Comando) comandos.elementAt(comandos.size() - 1);
			if (a.isAlterado() == false) {
				a.setLinha(x);
				a.setAlterado(true);
			}
		} else {
			int x = linhaEndIf + 1;
			Comando a = (Comando) comandos.elementAt(comandoElse);
			if (a.isAlterado() == false) {
				a.setLinha(x);
				a.setAlterado(true);
			}
		}
		c = (ComandoIf) comandos.elementAt(comandoMod);
		c.setLinhaEndIf(linhaEndIf);
		c.setLinhaPosIf(linhaPosIf);
		c.setLinhaElse(linhaElse);
		// comandos.add(comandoMod, c);
	}

	private void corrigirBugs() {
		for (int i = 0; i < comandos.size(); i++) {
			Comando a = (Comando) comandos.elementAt(i);
			if (a.getLinha() == i) {
				a.setLinha(a.getLinha() + 1);
			}
		}
	}

	private boolean trataElse() {
		String comandoAtual;
		boolean controle = false;
		do {
			comandoAtual = arq.proximaPalavra();
			if (comandoAtual.equals("writeStr")) {
				trataComandoWrite(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("read")) {
				trataComandoReader(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("writeln")) {
				trataComandoWriteln(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("writeVar")) {
				trataComandoWriteVar(linhaIF);
				linhaIF++;
			} else if (comandoAtual.matches("[a-z]")) {
				trataExp(comandoAtual, linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("if")) {
				linhaIF++;
				tratarIf();
			} else if (comandoAtual.equals("else")) {
				controle = trataElse();
				if (controle == true) {
					comandoAtual = "endif";
				}
			} else if (comandoAtual.equals("for")) {
				linhaIF++;
				tratarFor();
			} else if (comandoAtual.equals("while")) {
				linhaIF++;
				tratarWhile();
			} else if (comandoAtual.equals("call")) {
				tratarCall(linhaIF);
				linhaIF++;
			} else if (comandoAtual.equals("local")) {
				tratarLocal();
			}
		} while (!comandoAtual.equals("endif"));
		return true;
	}

	private void trataExp(String comandoAtual, int linha) {
		String frase = "";
		Expressao ex = trataExpressao();
		ComandoAtrib c = new ComandoAtrib(linha, ex, comandoAtual, memoria);
		comandos.addElement(c);
	}

	private void trataComandoWriteVar(int linha) {
		String frase = "";
		arq.proximaPalavra();
		frase = arq.proximaPalavra();
		ComandoWriteVar c = new ComandoWriteVar(linha, frase, memoria);
		comandos.addElement(c);
	}

	private void trataComandoWriteln(int linha) {
		ComandoWriteln c = new ComandoWriteln(linha);
		comandos.addElement(c);
	}

	private void trataComandoReader(int linha) {
		String frase = "";
		arq.proximaPalavra();
		frase = arq.proximaPalavra();
		ComandoReader c = new ComandoReader(linha, frase, memoria);
		comandos.addElement(c);
	}

	private void trataComandoWrite(int linha) {
		String frase = "";
		arq.proximaPalavra();
		frase = arq.proximaPalavra();
		ComandoWrite c = new ComandoWrite(linha, frase);
		comandos.addElement(c);
	}

	private void trataComandoEndp(int lin) {
		ComandoEndp c = new ComandoEndp(lin);
		comandos.addElement(c);
	}

	private Expressao trataExpressao() {
		arq.proximaPalavra();
		palavraAtual = arq.proximaPalavra();
		pilha = new Stack();
		expressao();
		Expressao raizArvoreExpressao = (Expressao) pilha.pop();
		return raizArvoreExpressao;
	}

	private Expressao trataExpressaoCall() {
		palavraAtual = arq.proximaPalavra();
		pilha = new Stack();
		expressao();
		Expressao raizArvoreExpressao = (Expressao) pilha.pop();
		return raizArvoreExpressao;
	}

	private Expressao trataExpressaoFor() {
		palavraAtual = arq.proximaPalavra();
		pilha = new Stack();
		expressao();
		Expressao raizArvoreExpressao = (Expressao) pilha.pop();
		return raizArvoreExpressao;
	}

	private Expressao trataExpressaoIf() {
		palavraAtual = arq.proximaPalavra();
		pilha = new Stack();
		expressao();
		Expressao raizArvoreExpressao = (Expressao) pilha.pop();
		return raizArvoreExpressao;
	}

	private Expressao trataExpressaoWhile() {
		palavraAtual = arq.proximaPalavra();
		pilha = new Stack();
		String parte1 = palavraAtual;
		palavraAtual = arq.proximaPalavra();
		String op = palavraAtual;
		palavraAtual = arq.proximaPalavra();
		expressao();
		Expressao exp1 = (Expressao) pilha.pop();
		pilha.push(new ExpVariavel(parte1, memoria));
		Expressao exp2 = (Expressao) pilha.pop();
		pilha.push(new ExpBinaria(op, exp1, exp2));
		Expressao raizArvoreExpressao = (Expressao) pilha.pop();
		return raizArvoreExpressao;
	}

	private void expressao() {
		termo();
		while (palavraAtual.equals("+") || palavraAtual.equals("-")
				|| palavraAtual.equals("sqrt") || palavraAtual.equals("=")
				|| palavraAtual.equals(">") || palavraAtual.equals("<")
				|| palavraAtual.equals("<=") || palavraAtual.equals(">=")
				|| palavraAtual.equals("<>")) {
			String op = palavraAtual;
			palavraAtual = arq.proximaPalavra();
			termo();
			Expressao exp1 = (Expressao) pilha.pop();
			Expressao exp2 = (Expressao) pilha.pop();
			pilha.push(new ExpBinaria(op, exp1, exp2));
		}
	}

	private void termo() {
		fator();
		while (palavraAtual.equals("*") || palavraAtual.equals("/")
				|| palavraAtual.equals("and") || palavraAtual.equals("or")
				|| palavraAtual.equals("sqrt")) {
			String op = palavraAtual;
			palavraAtual = arq.proximaPalavra();
			fator();
			if (op.equals("sqrt")) {
				Expressao exp1 = (Expressao) pilha.pop();
				Expressao exp2 = new ExpConstante(0);
				pilha.push(new ExpBinaria(op, exp1, exp2));
			} else {
				Expressao exp1 = (Expressao) pilha.pop();
				Expressao exp2 = (Expressao) pilha.pop();
				pilha.push(new ExpBinaria(op, exp1, exp2));
			}
		}
	}

	private void fator() {
		if (palavraAtual.matches("[a-z]")) {
			pilha.push(new ExpVariavel(palavraAtual, memoria));
			palavraAtual = arq.proximaPalavra();

		} else if (palavraAtual.matches("[0-9]")) {
			pilha.push(new ExpConstante(Long.valueOf(palavraAtual)));
			palavraAtual = arq.proximaPalavra();
		} else if (palavraAtual.equals("(")) {
			palavraAtual = arq.proximaPalavra();
			expressao();
			if (palavraAtual.equals(")")) {
				palavraAtual = arq.proximaPalavra();
			}
		}
	}

	public void executa() {

		Comando cmd;
		int pc = 0;
		do {
			cmd = (Comando) comandos.elementAt(pc);
			pc = cmd.executa();
		} while (pc != -1);
	}
}
