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
	std::vector<std::string> keyTable;
	std::vector<std::string> outputTable;
	std::vector<bool> passInUse;

	void openFile(std::string input) {
		std::ifstream fileStream(input);
		std::stringstream FileData;

		if (!fileStream.is_open()) {
			throw 1001;
		}
		FileData << fileStream.rdbuf();
		fileStream.close();

		//Table is space delimited, will include special characters so be careful.
		std::string tempString;
		for (char c : FileData.str()) {
			if (c == ' ') {
				keyTable.push_back(tempString);
				passInUse.push_back(false);
				tempString = "";
				continue;
			}
			tempString += c;
		}

		if (tempString != "")
			keyTable.push_back(tempString);
			passInUse.push_back(false);
	}

	void shuffleKeys() {
		std::vector<std::string> tempTable;
		tempTable.resize(keyTable.size());

		for (int i = 0; i < keyTable.size(); i++) {
			int random = floor (rand() % keyTable.size());
			if (!passInUse[random]) {
				tempTable[i] = keyTable[random];
				passInUse[random] = true;
			} else
				i--;
		}

		keyTable = tempTable;
	}

	std::string generateSegment(std::string key, size_t size) {
		if (key.length() > size)
			throw 1002;
		
		std::string output;

		//Fill segment with garble
		for (int i = 0; i < size; i++) {
			output += garble[rand() % garble.size()];
		}
		
		//Overwrite a random portion of the segment with the key
		int randomcoord = rand() % (size - key.length());
		for (char c : key) {
			output[randomcoord] = c;
			randomcoord++;
		}

		return output;
	}

	void generateTable() {
		//Find the size a segment would be
		size_t segmentSize = tableArea / keyTable.size();

		//Generate the table
		std::string tableString;
		for (std::string s : keyTable) {
			tableString += generateSegment(s, segmentSize);
		}

		std::string tmp;
		for (char c : tableString) {
			tmp += c;
			if (tmp.length() == tableSize.ws_col) {
				outputTable.push_back(tmp);
				tmp = "";
			}
		}

		if (tmp != "")
			outputTable.push_back(tmp);
	}

public:
	SingletonTable(std::string file) {
		openFile(file);
		shuffleKeys();
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
	term.cursorHide();
	//Fancily scrolling the text up and off the screen...
	for (int i = 0; i <= term.TermSize.ws_row; i++) {
		std::cout << "\n" << std::flush;
		usleep(16666);
	}
	term.setCursorPos(0,0);
	term.cursorShow();

	usleep(3000000);
	term.slowPrint("Welcome to ROBCO Industries (TM) Termlink\n");
	#ifdef NDEBUG
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
	#endif
	termClear();
	term.slowPrint("Password Required\n\n");
	usleep(200000);
	term.slowPrint("Starting Debugger...");
	usleep(400000);
	term.clearLine();
	term.slowPrint("Please wait...\n");
	
	SingletonTable tableone("passwords.txt");

	tableone.printTable(1, 5);
}