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

package br.pucminas.inf.utilitarios;

public class Console {

	public static String readLine() {

		int ch;
		String r = "";
		boolean done = false;
		while (!done) {
			try {
				ch = System.in.read();
				if (ch < 0 || (char) ch == '\n')
					done = true;
				else if ((char) ch != '\r')
					r = r + (char) ch;
			} catch (java.io.IOException e) {
				done = true;
			}
		}
		return r;
	}

	public static int readInt() {

		while (true) {
			try {
				return Integer.valueOf(readLine().trim()).intValue();
			} catch (NumberFormatException e) {
				System.out.println("Not an	integer. Please	try again!");
			}
		}
	}

}
