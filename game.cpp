/* COPYRIGHT NOTICE
	game      - The vast majority of the termlink program
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

#include "termfunk.hpp"
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
using namespace std;

//Clears everything on the screen *except* the "Welcome to ROBCO..." in an animated manor.
void termClear() {
	setCursorPos(0,1);
	for (int i = 2;  i < w.ws_row; i++) {
		clearLine();
		cout << '\n' << flush;
		usleep(16666);
	}
	setCursorPos(0,1);
}


void Game() {
	//Smaller Intro with the actual interface.

	//Loading debugger's physical RAM viewer, loading the Login program, editing the debugger to display section of RAM with potential password over login program. 
	//  ^^^Obviously this is fake, it's just that it'll seem even faker if it doesn't sound at least plausible in concept.
	usleep(3000000);
	slowPrint(0, 0, "Welcome to ROBCO Industries (TM) Termlink");
	slowPrint(0, 1, "**LOGIN SCRIPT ACTIVE**\n\n");
	usleep(150000);
	slowPrint(0, 3, "TERMINAL SET TO MAINTANANCE MODE - Please contact your administrator.\n");
	usleep(50000);
	slowPrint(0, 4, "00> LOD 00,7D\n");
	slowPrint(0, 5, "70> LOD E1,FF\n");
	slowPrint(0, 6, "78> INS 69, 00 5F 4B D8 A7 01\n");
	slowPrint(0, 7, "79> INS 6A, FF 4D 0A AA 6B 4F\n");
	slowPrint(0, 8, "7A> INS 6B, 07 55 7C 3E D1 1F\n");
	slowPrint(0, 9, "7B> //CODE INJECTION COMPLETE\n");
	slowPrint(0,10, "7B> RUN E1\n");
	usleep(520000);  
	termClear();
	slowPrint(0, 2, "Password Required\n\n");
	usleep(200000);
	slowPrint(0, 4, "Starting Debugger...");
	usleep(400000);
	slowPrint(0, 4, "Please wait...\n");

	//These are all the random characters that can appear in-game
	char garbleTable[24] = {
		'$','?','_','/','%',
		'(',')','{','}','[',
		']','*',':','!','@',
		'#','`','"',',','.',
		'<','>',':','\''
	};

	//CHANGE ME: These are only for debugging purposes, obviously
	string passwordTable[9] = {
		"ONE", "TWO", "THREE",
		"FOUR", "FIVE", "SIX",
		"SEVEN", "EIGHT", "NINE"
	};

	//2 Windows of 12x16 characters, resulting in 192 characters per window, 384 total.
	//Both windows are generated independently to prevent passwords leaking from one window to the other
	stringstream tableOne, tableTwo;

	//TODO: choose a random number of passwords, and make a for loop that adds a random password to a random place in either of the streams until both of them have reached 192 characters.
}