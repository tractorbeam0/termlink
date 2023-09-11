/* COPYRIGHT NOTICE
	intro     - A not-so-vital piece of the termlink program
	termlink  - A recreation of the terminal hacking minigame from the
							Fallout series, with a sizable portion of personal
							touches

	Copyright (C) 2023  Gavin Mitchell

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <cmath>
#include <unistd.h>
#include <sys/ioctl.h>

#include "termfunk.h"

using namespace std;

//If I could do the startup flash without nesting so many for loops it'd be 100x more readable. *sigh*...

void Intro() {

	term.cursorHide();
	usleep(2401000); //Dramatic pause...
	
	//Startup
	for (int i = 0; i < 4; i++) {
		for (int i = 0; i < 7; i++) {
			int linecoord = rand()%term.TermSize.ws_col;
			for (int i = 0; i < term.TermSize.ws_col; i++) {
				term.setCursorPos(i, linecoord);
				cout << "█";
			}
		}
		usleep(30000);
	}
	usleep(30000);
	
	//White screen
	term.setCursorPos(0,0);
	for (int i = 0; i < term.TermSize.ws_row * term.TermSize.ws_col; i++) {
		cout << "█";
	}
	cout << flush;
	usleep(100000);
	
	//Vertical lines
	term.clearScreen();
	for (int i = 0; i < term.TermSize.ws_col; i+=2) {
		for (int j = 0; j < term.TermSize.ws_row; j++) {
			term.setCursorPos(i,j);
			cout << " │";
		}
		cout << flush;
		usleep(2000);
	}
	usleep(100000);
	
	//Grid
	term.setCursorPos(0,0);
	for (int i = 0; i < term.TermSize.ws_row; i++) {
		for (int j = 0; j < term.TermSize.ws_col; j+=2) {
			term.setCursorPos(j,i);
			cout << "─┼";
		}
		cout << flush;
		usleep(2000);
	}
	usleep(100000);

	//Horizontal lines
	for (int i = 0; i < term.TermSize.ws_col; i+=2) {
		for (int j = 0; j < term.TermSize.ws_row; j++) {
			term.setCursorPos(i,j);
			cout << "──";
		}
		cout << flush;
		usleep(2000);
	}
	usleep(120000);

	term.setCursorPos(0,0);
	for (int i = 0; i < term.TermSize.ws_row; i++) {
		for (int i = 0; i < term.TermSize.ws_col; i++) {
			cout << " ";
		}
		cout << flush;
		usleep(2000);
	}
	
	//Wait Screen
	term.clearScreen();
	usleep(1000000);
	cout << "PLEASE WAIT..." << flush;
	usleep(2000000);
	
	//Wait Screen, post ascii init
	term.clearScreen();
	cout << "Please Wait..." << flush;
	usleep(2300000);
 
	//Term OK screen
	term.clearScreen();
 
	usleep(200000);  
	term.setCursorPos(0, round(term.TermSize.ws_row/2) - 1);
	cout << '\7';
	cout << term.center("┏━━━━━━━━━━━━━━━━━━┓") << '\n';
	cout << term.center("┃    RT-1200 OK    ┃") << '\n';
	cout << term.center("┗━━━━━━━━━━━━━━━━━━┛") << '\n';

	//1/4 up from the bottom of the screen.
	term.setCursorPos(0, floor(round(term.TermSize.ws_row/2) + round(term.TermSize.ws_row/2)/2));
	cout << term.center("Firmware and Termlink Copyright (C) 2065,75") << "\n\n" << flush;
	
	//Loading Lines
	cout << term.center("ROBCO Industries (TM)") << "\n\n" << flush;
	usleep(600000);
	cout << term.center("Loading Termlink interface...") << flush;
	usleep(1400000);
	term.clearLine();
	cout << term.center("Looking for Host...") << flush;
	usleep(700000);
	term.clearLine();
	cout << term.center("Host Found!") << flush;
	usleep(300000);
	term.clearLine();
	cout << term.center("Handshake Complete") << flush;
	usleep(500000);
	cout << "\n" << term.center("Connected at 600 bits/s") << "\x1b[A" << flush; //last ascii code is essentially a reverse newline
	usleep(400000);
	term.clearLine();
	cout << term.center("Host is finishing up...") << flush;
	usleep(1100000);

	term.cursorShow();
}