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

#include <sys/ioctl.h>  //funkInit(), to grab terminal size
#include <iostream>
#include <unistd.h>
#include <cmath>        //center()

#include "GcTerminal.h"

using namespace std;

void GameComponents::Terminal::Init() {
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &Size);
}

size_t GameComponents::Terminal::strlen_utf8(const std::string& str) {
	size_t length = 0;
	for (char c : str)
		if ((c & 0xC0) != 0x80) ++length;
	return length;
}

// It clears the screen.
void GameComponents::Terminal::clearScreen() {
	for (int i=0; i < Size.ws_row * 2; i++)
		std::cout << std::endl;
	setCursorPos(0,0);
}

// It clears the line the cursor is on.
void GameComponents::Terminal::clearLine() {
	std::cout << "\r";
	for (int i=0; i < Size.ws_col; i++) {
		std::cout << " ";
	}
	std::cout << "\r" << std::flush;
}

// It hides the cursor.
void GameComponents::Terminal::cursorHide() {
	std::cout << "\033[?25l" << std::flush;
}

// It shows the cursor.
void GameComponents::Terminal::cursorShow() {
	std::cout << "\033[?25h" << std::flush;
}

// Uses an ansi code to change the cursor position in the terminal.
// The terminal location values start at 1,1 not 0,0 so for simplicity it increments them by one so you can input 0,0 for the top-left.
void GameComponents::Terminal::setCursorPos(unsigned short col, unsigned short row) {
	printf("\033[%d;%dH",++row,++col);
}

//Usage: slowPrint("Hello, World!")
void GameComponents::Terminal::slowPrint(std::string input) {
	for (char c : input) {
		#ifdef NDEBUG
		usleep(16666);
		#endif
		std::cout << std::string(1, c) << std::flush;
	}
}

//Usage: cout << center("Hello World!");
// Returns the string with the proper number of whitespace to appear at the center of the screen when printed.
std::string GameComponents::Terminal::center(std::string input) {
	int x = floor(( Size.ws_col - strlen_utf8(input) )/2);
	return std::string(x, ' ') + input;
}