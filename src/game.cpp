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
#include <fstream>
#include <sstream>
#include <math.h>
#include <string>
#include <vector>

#include "termfunk.h"

//Clears everything on the screen *except* the "Welcome to ROBCO..." in an animated manor.
void termClear() {
	term.setCursorPos(0,1);
	for (int i = 2; i < term.TermSize.ws_row; i++) {
		term.clearLine();
		std::cout << '\n' << std::flush;
		usleep(16666);
	}
	term.setCursorPos(0,2);
}

class SingletonTable {
	const winsize tableSize = {12, 15};
	const size_t tableArea = tableSize.ws_row * tableSize.ws_col;
	const std::string garble = "!@#$%^&*()_+-=[]{};':\",./<>?`~\\|";
	std::vector<std::string> passTable;
	std::vector<std::string> outputTable;

	void openFile(std::string input) {
		std::ifstream fileStream(input);
		if (!fileStream.is_open()) throw 1001;
		std::stringstream fStreamToStringBuffer;
		std::string FileData;

		fStreamToStringBuffer << fileStream.rdbuf();
		fileStream.close();

		FileData = fStreamToStringBuffer.str();

		std::string translationBuffer;
		//Table is space delimited, will include special characters so be careful.
		for (int i = 0; i < FileData.length(); i++) {
			if (FileData[i] == ' ') {
				passTable.push_back(translationBuffer);
				translationBuffer = "";
				continue;
			}
			translationBuffer += FileData[i];
		}
	}

	void shufflePasswords() {
		std::vector<std::string> tempTable;

		for (int i = 0; i < passTable.size(); i++) {
			int random = rand() % passTable.size();
			tempTable.push_back(passTable[random]);
		}
		passTable = tempTable;
	}

	void generateTable() {
		std::string tableString;
		int i = 0;

		//Fill the table with garbage
		for (int i = 0; i < tableArea; i++) {
			tableString += garble[rand() % garble.length()];
		}

		size_t segmentSize = tableArea / passTable.size();

		for (int i = 0; i < passTable.size(); i++) {
			int currentSegmentCoord = i * segmentSize;
			int effectiveSegmentSize = segmentSize - passTable[i].length();
			if (effectiveSegmentSize < 0) throw 1002;
			
			currentSegmentCoord += floor( rand() % effectiveSegmentSize );
			for (char c : passTable[i]) {
				tableString[currentSegmentCoord] = c;
				currentSegmentCoord++;
			}
		}
		
		for (int i = 0; i < tableString.size(); i++) {
			if (i % tableSize.ws_col == 0) {
				outputTable.push_back("");
			}
			outputTable.back() += tableString[i];
		}
	}

public:
	SingletonTable() {
		openFile("./PasswordTable.txt");
		shufflePasswords();
		generateTable();
	}

	void printTable(unsigned x, unsigned y) {
		//Print the table
		for (int i = 0; i < outputTable.size(); i++) {
			term.setCursorPos(x, y + i);
			term.slowPrint(outputTable[i]);
		}
	}
};

void Game() {
	#ifdef DEBUG
	term.cursorHide(); //Debug builds skip the intro, so this is needed to make the cursorShow down there not redundant. No, I don't care whether it matters.
	#endif
	//Fancily scrolling the text up and off the screen...
	for (int i = 0; i <= term.TermSize.ws_row; i++) {
		std::cout << "\n" << std::flush;
		usleep(16666);
	}
	term.setCursorPos(0,0);
	term.cursorShow();

	usleep(3000000);
	term.slowPrint("Welcome to ROBCO Industries (TM) Termlink\n");
	term.slowPrint("**LOGIN SCRIPT ACTIVE**\n\n");
	usleep(150000);
	term.slowPrint("TERMINAL SET TO MAINTANANCE MODE - Contact your administrator.\n");
	term.slowPrint("((HOOKED!))\n");
	usleep(50000);
	term.slowPrint("00> LOD 00,7D\n");
	term.slowPrint("70> LOD E1,FF\n");
	term.slowPrint("78> INS 69, 00 5F 4B D8 A7 01\n");
	term.slowPrint("79> INS 6A, FF 4D 0A AA 6B 4F\n");
	term.slowPrint("7A> INS 6B, 07 55 7C 3E D1 1F\n");
	term.slowPrint("7B> //CODE INJECTION COMPLETE\n");
	term.slowPrint("7B> RUN E1\n");
	usleep(520000);  
	termClear();
	term.slowPrint("Password Required\n\n");
	usleep(200000);
	term.slowPrint("Please wait...");
	usleep(400000);
	term.clearLine();
	term.slowPrint("Starting Debugger...\n");
	
	SingletonTable tableOne;
	SingletonTable tableTwo;

	tableOne.printTable(1, 5);
	tableTwo.printTable(17, 5);
}