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
#include <math.h>
#include <string>
#include <vector>

#include "termfunk.h"

//Clears everything on the screen *except* the "Welcome to ROBCO..." in an animated manor.
void termClear() {
	t.setCursorPos(0,1);
	for (int i = 2;  i < t.TermPos.ws_row; i++) {
		t.clearLine();
		std::cout << '\n' << std::flush;
		usleep(16666);
	}
	t.setCursorPos(0,1);
}

struct Singleton {
	std::vector<std::string> content;
	size_t population;
	bool* inUse;

	Singleton(std::vector<std::string> input) {
		inUse = new bool[input.size()];
		for (int i = 0; i < input.size(); i++) {
			inUse[i] = false;
		}
		population = input.size();
		content = input;
	}

	std::string getRandom() {
		unsigned r;
		while (true) {
			r = rand()%population;
			if (*(inUse + r) == true) continue;

			*(inUse + r) = true;
			return content[r];
		}
	}
};

//tableGenerate returns the wall of text that includes some potential passwords. Should return 180 characters, one for each individual table.
std::string tableGenerate() {
	std::string result;
	const size_t length = 15;
	const size_t height = 12;
	const size_t area = length * height;
	const std::string garble = "$?_/%(){}[]*:!@#`\"\\,.<>:'";

	Singleton password({"THERE","IS","NO","WAY","THAT","A","BEE","SHOULD","BE","ABLE","TO","FLY"});


	std::vector<std::string> passwordsInOrder;
	/*----Prepare the order of the passwords (Temporarily disabled)
	unsigned tmp;
	//Anywhere between 0 and half of password.population, as not to use all of the passwords *sometimes*.
	tmp  = round(password.population/2);
	tmp %= rand();
	tmp  = password.population - tmp;

	for (int i = 0; i < tmp; i++) {*/
	for (int i = 0; i < password.population; i++)
		passwordsInOrder.push_back(password.getRandom());

	//----And lay out the table for the passwords
	for (int i = 0; i < passwordsInOrder.size(); i++) {
		std::string password = passwordsInOrder[i];

		//I *eventually* came across the revelation that math
		//should be evaluated like this and not in a single line... eventually.
		unsigned charsBeforeNextPassword;
		float a;
		a  = area / passwordsInOrder.size();
		a *= i+1;
		a -= result.length();
		if (i+1 == passwordsInOrder.size())
			a -= password.length();
		else
			a -= (0.5 * password.length());
		//I'd like to see the terminal try to render half a character.
		charsBeforeNextPassword = floor(a);
		
		//Insert the garble...
		for (int i = 0; i < charsBeforeNextPassword; i++)
			result += garble[rand()%garble.length()];
		//...and insert the password
		result += password;
	}

	//Final check...
	if (result.size() != area)
		throw 1000;

	return result;
}

void Game() {
	#ifdef DEBUG
	cursorHide(); //Debug builds skip the intro, so this is needed to make the cursorShow down there not redundant. No, I don't care whether it matters.
	#endif
	//Fancily scrolling the text up and off the screen...
	for (int i = 0; i <= t.TermPos.ws_row; i++) {
		std::cout << "\n" << std::flush;
		usleep(16666);
	}
	t.setCursorPos(0,0);
	t.cursorShow();

	usleep(3000000);
	t.slowPrint(0, 0, "Welcome to ROBCO Industries (TM) Termlink");
	t.slowPrint(0, 1, "**LOGIN SCRIPT ACTIVE**\n\n");
	usleep(150000);
	t.slowPrint(0, 3, "TERMINAL SET TO MAINTANANCE MODE - Contact your administrator.\n");
	usleep(50000);
	t.slowPrint(0, 4, "00> LOD 00,7D\n");
	t.slowPrint(0, 5, "70> LOD E1,FF\n");
	t.slowPrint(0, 6, "78> INS 69, 00 5F 4B D8 A7 01\n");
	t.slowPrint(0, 7, "79> INS 6A, FF 4D 0A AA 6B 4F\n");
	t.slowPrint(0, 8, "7A> INS 6B, 07 55 7C 3E D1 1F\n");
	t.slowPrint(0, 9, "7B> //CODE INJECTION COMPLETE\n");
	t.slowPrint(0,10, "7B> RUN E1\n");
	usleep(520000);  
	termClear();
	t.slowPrint(0, 2, "Password Required\n\n");
	usleep(200000);
	t.slowPrint(0, 4, "Starting Debugger...");
	usleep(400000);
	t.clearLine();
	t.slowPrint(0, 4, "Please wait...\n");
	
	auto temporary = tableGenerate();
	printf("Table Size: %ld\n", temporary.size());
	printf("Table Contents: %s\n\n", temporary.c_str());
}