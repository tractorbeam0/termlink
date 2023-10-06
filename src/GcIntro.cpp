/* COPYRIGHT NOTICE

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

#ifdef linux
	#include <unistd.h>
#endif

#include <iostream>
#include <cmath>

#include "GcTerminal.h"
#include "GcIntro.h"

using namespace GameComponents::Terminal;
using namespace GameComponents;
using namespace std;

//If I could do the startup flash without nesting so many for loops it'd be 100x more readable. *sigh*...

void GameComponents::Intro() {

	cursorHide();
	timer(2401000); //Dramatic pause...
	
	//Startup
	for (int i = 0; i < 4; i++) {
		for (int i = 0; i < 7; i++) {
			int linecoord = rand()%Size.ws_col;
			for (int i = 0; i < Size.ws_col; i++) {
				setCursorPos(i, linecoord);
				cout << "█";
			}
			cout << flush;
		}
		timer(30000);
	}
	timer(30000);
	
	//White screen
	setCursorPos(0,0);
	for (int i = 0; i < Size.ws_row * Size.ws_col; i++) {
		cout << "█";
	}
	cout << flush;
	timer(100000);
	
	//Vertical lines
	clearScreen();
	for (int i = 0; i < Size.ws_col - 1; i+=2) {
		for (int j = 0; j < Size.ws_row; j++) {
			setCursorPos(i,j);
			cout << " │";
		}
		cout << flush;
		timer(2000);
	}
	timer(100000);
	
	//Grid
	setCursorPos(0,0);
	for (int i = 0; i < Size.ws_row; i++) {
		for (int j = 0; j < Size.ws_col; j+=2) {
			setCursorPos(j,i);
			cout << "─┼";
		}
		cout << flush;
		timer(2000);
	}
	timer(100000);

	//Horizontal lines
	for (int i = 0; i < Size.ws_col; i+=2) {
		for (int j = 0; j < Size.ws_row; j++) {
			setCursorPos(i,j);
			cout << "──";
		}
		cout << flush;
		timer(2000);
	}
	timer(120000);

	setCursorPos(0,0);
	for (int i = 0; i < Size.ws_row; i++) {
		for (int i = 0; i < Size.ws_col - 1; i++) {
			cout << " ";
		}
		cout << flush;
		timer(2000);
	}
	
	//Wait Screen
	clearScreen();
	timer(1000000);
	cout << "PLEASE WAIT..." << flush;
	timer(2000000);
	
	//Wait Screen, post ascii init
	clearScreen();
	cout << "Please Wait..." << flush;
	timer(2300000);
 
	//Term OK screen
	clearScreen();
 
	timer(200000);  
	setCursorPos(0, round(Size.ws_row/2) - 1);
	cout << '\7';
	cout << center("┏━━━━━━━━━━━━━━━━━━┓") << '\n';
	cout << center("┃    RT-1200 OK    ┃") << '\n';
	cout << center("┗━━━━━━━━━━━━━━━━━━┛") << '\n';

	//1/4 up from the bottom of the screen.
	setCursorPos(0, floor(round(Size.ws_row/2) + round(Size.ws_row/2)/2));
	cout << center("Firmware and Termlink Copyright (C) 2065,75") << "\n\n" << flush;
	
	//Loading Lines
	cout << center("ROBCO Industries (TM)") << "\n\n" << flush;
	timer(600000);
	cout << center("Loading Termlink interface...") << flush;
	timer(1400000);
	clearLine();
	cout << center("Looking for Host...") << flush;
	timer(700000);
	clearLine();
	cout << center("Host Found!") << flush;
	timer(300000);
	clearLine();
	cout << center("Handshake Complete") << flush;
	timer(500000);
	cout << "\n" << center("Connected at 600 bits/s") << "\x1b[A" << flush; //last ascii code is essentially a reverse newline
	timer(400000);
	clearLine();
	cout << center("Host is finishing up...") << flush;
	timer(1100000);

	//Fancily scrolling the text up and off the screen...
	for (int i = 0; i <= Size.ws_row; i++) {
		cout << "\n" << flush;
		timer(16666);
	}
	setCursorPos(0,0);
	cursorShow();

	timer(3000000);
	slowPrint("Welcome to ROBCO Industries (TM) Termlink\n");
	slowPrint("**LOGIN SCRIPT ACTIVE**\n\n");
	timer(150000);
	slowPrint("TERMINAL SET TO MAINTANANCE MODE - Contact your administrator.\n");
	slowPrint("\n00> ");
	timer(100000);
	slowPrint("((HOOKED))\n?\n00> OPN MEM 00,7D\n");
	slowPrint("00> OPN MEM E1,FF\n");
	slowPrint("E1> INS MEM 69, 00 5F 4B D8 A7 01\n");
	timer(150000);
	slowPrint("\nUNAUTHORIZED ACCESS TO KERNEL MEMORY DETECTED\n");
	slowPrint("CUTTING CONNECTION...\n\n");
	slowPrint("((IGNORE THAT))\n");
	slowPrint("E2> INS MEM 6A, FF 4D 0A AA 6B 4F\n");
	slowPrint("E3> INS MEM 6B, 07 55 7C 3E D1 1F\n");
	slowPrint("((CODE INJECTION COMPLETE))\n");
	slowPrint("E4> RUN E1\n");
	timer(520000);
}
