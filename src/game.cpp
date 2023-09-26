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

#include <iostream>
#include <unistd.h>
#include <sstream>
#include <math.h>
#include <string>
#include "termfunk.h"
#include "gamecomponents.h"

using namespace std;
using namespace GameComponents;

//Clears everything on the screen *except* the "Welcome to ROBCO..." in an animated manor.
void termClearDontClearTitle() {
	term.setCursorPos(0,1);
	for (int i = 2; i < term.TermSize.ws_row; i++) {
		term.clearLine();
		cout << '\n' << flush;
		usleep(16666);
	}
	term.setCursorPos(0,2);
}

void Game() {
	termClearDontClearTitle();
	term.slowPrint("Password Required\n\n");
	usleep(200000);
	term.slowPrint("Starting Debugger...");
	usleep(700000);
	term.clearLine();
	term.slowPrint("Please wait...\n\n");
	
	//Any number within the 16-bit integer range, minus the number of lines in both the tables.
	uint16_t random = rand() % (65535 - 24);
	stringstream output;
	for (int i = 0; i < 24; i++)
	{
		if (i < 12)
			term.setCursorPos(0, 6 + i);
		else
			term.setCursorPos(23, 6 + i - 12);
		
		output << hex << uppercase << random + i << nouppercase << dec;

		stringstream tmp;
		if (output.str().length() < 4) {
			for (int i = 0; i < 4 - output.str().length(); i++)
				tmp << "0";
		}

		tmp << output.rdbuf();
		output = move(tmp);
		
		term.slowPrint("0x" + output.str());
		output.str("");
	}

	term.setCursorPos(0, 4);
	term.clearLine();
	term.slowPrint("Reading from memory...\n\n");
	TableManager table("passwords.txt");

	table.printTable(7, 6);
	table.generateTable();
	table.printTable(30, 6);
}