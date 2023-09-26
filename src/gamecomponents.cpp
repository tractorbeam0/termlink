#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "gamecomponents.h"

using namespace std;
using namespace GameComponents;

void TableManager::openFile(string input) {
	ifstream fileStream(input);
	stringstream FileData;

	if (!fileStream.is_open()) {
		throw 1001;
	}
	FileData << fileStream.rdbuf();
	fileStream.close();

	//Table is delimited with newline's, spaces, or carriage returns
	//doesn't filter ascii codes so be careful.
	string tempString;
	for (char c : FileData.str()) {
		if (isspace(c)) {
			keyTable.push_back((Key){tempString, false});
			tempString.clear();
			continue;
		}
		tempString += c;
	}

	if (tempString.empty() == false) {
		keyTable.push_back((Key){tempString, false});
	}
}

vector<string> TableManager::shuffledKeys() {
	vector<string> tempTable;

	//Check all of the keys to see if there are any left to use
	//Also see if there are enough to generate a corresponding segment
	size_t keysRemaining;
	for (Key p : keyTable) {
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
		int random = floor (rand() % keyTable.size());
		if (!keyTable[random].isUsed) {
			tempTable[i] = keyTable[random].ID;
			keyTable[random].isUsed = true;
		} else
			i--;
	}

	return tempTable;
}

string TableManager::generateSegment(string key, size_t size) {
	if (key.length() >= size) {
		#ifndef NDEBUG
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

void TableManager::sortSegments(vector<string> keyTable) {
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

TableManager::TableManager(string file) {
	openFile(file);
	generateTable();
}

void TableManager::generateTable() {
	outputTable.clear();
	sortSegments(shuffledKeys());
}

char TableManager::getRandomChar() {
	return garble[rand() % garble.size()];
}

void TableManager::printTable(unsigned x, unsigned y) {
	//Print the table
	for (int i = 0; i < outputTable.size(); i++) {
		term.setCursorPos(x, y + i);
		term.slowPrint(outputTable[i]);
	}
}