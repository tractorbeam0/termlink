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

#include <sys/ioctl.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include "GameComponents.h"

using namespace std;

void Gc::Table::openFile(string input) {
	ifstream fileStream(input);
	stringstream FileData;

	if (!fileStream.is_open()) {
		throw 1001;
	}
	FileData << fileStream.rdbuf();
	fileStream.close();

	//Gc::Table is delimited with newline's, spaces, or carriage returns
	//doesn't filter ascii codes so be careful.
	string tempString;
	for (char c : FileData.str()) {
		if (isspace(c)) {
			keys.push_back((Key){tempString, false});
			tempString.clear();
			continue;
		}
		tempString += c;
	}

	if (tempString.empty() == false) {
		keys.push_back((Key){tempString, false});
	}
}

vector<string> Gc::Table::shuffledKeys() {
	vector<string> tempTable;

	//Check all of the keys to see if there are any left to use
	//Also see if there are enough to generate a corresponding segment
	size_t keysRemaining;
	for (Key p : keys) {
		if (!p.isUsed)
			keysRemaining++;
	}

	size_t numKeys = floor(rand() % 3 + 5);
	tempTable.resize(numKeys);

	if (keysRemaining < numKeys) {
		#ifndef NDEBUG
		printf("Need to return %ld keys, but there were only %ld left.\n", numKeys, keysRemaining);
		#endif

		throw 1003;
	}

	for (int i = 0; i < numKeys; i++) {
		int random = floor (rand() % keys.size());
		if (!keys[random].isUsed) {
			tempTable[i] = keys[random].ID;
			keys[random].isUsed = true;
		} else
			i--;
	}

	return tempTable;
}

string Gc::Table::generateSegment(string key, size_t size) {
	if (key.length() >= size) {
		#ifndef NDEBUG
		Term.setCursorPos(0, Term.Size.ws_row);
		printf("Key: %s\n", key.c_str());
		printf("Size: %ld\n", size);
		#endif

		throw 1002;
	}
		
	string output;

	//Fill segment with garble
	for (int i = 0; i < size; i++) {
		output += getRandomChar();
	}

	//Overwrite a random portion of the segment with the key
	int randomcoord = rand() % (size - key.length());
	for (char c : key) {
		output[randomcoord] = c;
		randomcoord++;
	}

	return output;
}

void Gc::Table::sortSegments(vector<string> keyTable) {
	//Find the size a segment would be
	size_t segmentSize = tableArea / keyTable.size();

	//Generate the table
	string tableString;
	for (string s : keyTable) {
		tableString += generateSegment(s, segmentSize);
	}

	while (tableString.length() < tableArea) {
		tableString += garble[rand() % garble.size()];
	}

	string tmp;
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

Gc::Table::Table(string file) {
	openFile(file);
	Generate();
}

void Gc::Table::Generate() {
	outputTable.clear();
	sortSegments(shuffledKeys());
}

char Gc::Table::getRandomChar() {
	return garble[rand() % garble.size()];
}

void Gc::Table::Print(unsigned x, unsigned y) {
	//Print the table
	for (int i = 0; i < outputTable.size(); i++) {
		Term.setCursorPos(x, y + i);
		Term.slowPrint(outputTable[i]);
	}
}