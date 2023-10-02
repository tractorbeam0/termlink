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

#include <iostream>
#include <unistd.h>
#include <sstream>
#include <math.h>
#include <string>

#include "GcGame.h"
#include "GcTerminal.h"
#include "GcTable.h"

using namespace GameComponents::Terminal;
using namespace GameComponents;
using namespace std;

//Clears everything on the screen *except* the "Welcome to ROBCO..." in an animated manor.
void termClearEverythingButTitle() {
	setCursorPos(0,1);
	for (int i = 2; i < Size.ws_row; i++) {
		clearLine();
		cout << endl;
		usleep(16666);
	}
	setCursorPos(0,2);
}

void GameComponents::Game() {
	termClearEverythingButTitle();
	slowPrint("Password Required\n\n");
	usleep(200000);
	slowPrint("Starting Debugger...");
	usleep(700000);
	clearLine();
	slowPrint("Please wait...\n\n");
	
	//Any number within the 16-bit integer range, minus the number of lines in both the tables.
	uint16_t random = rand() % (65535 - 24);
	stringstream output;
	for (int i = 0; i < 24; i++)
	{
		if (i < 12)
			setCursorPos(0, 6 + i);
		else
			setCursorPos(23, 6 + i - 12);
		
		output << hex << uppercase << random + i << nouppercase << dec;

		stringstream tmp;
		if (output.str().length() < 4) {
			for (int i = 0; i < 4 - output.str().length(); i++)
				tmp << "0";
		}

		tmp << output.rdbuf();
		output = std::move(tmp);
		
		slowPrint("0x" + output.str());
		output.str("");
	}

	setCursorPos(0, 4);
	clearLine();
	slowPrint("Reading from memory...\n\n");
	Table table("passwords.txt");

	table.Print(7, 6);
	table.Generate();
	table.Print(30, 6);
}