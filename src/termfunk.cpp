/* COPYRIGHT NOTICE
	termfunk    - A library used to do funky terminal shenanigans without
				relying on something with massive overhead like ncurses

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
#include <sys/ioctl.h>  //funkInit(), to grab terminal size
#include <cmath>        //center()

#include "termfunk.h"

size_t termfunk::strlen_utf8(const std::string& str) {
	size_t length = 0;
	for (char c : str) {
		if ((c & 0xC0) != 0x80)
			++length;
	}
	return length;
}

//Public functions

//Performs all the actions required to help the functions... y'know, function.
termfunk::termfunk() {
	//Establishes the size of the terminal.
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &TermSize);
}

//Cleans up and prepares the terminal to be used by regular programs again.
termfunk::~termfunk() {
	cursorShow();
}

// It clears the screen.
void termfunk::clearScreen() {
	for (int i=0; i < TermSize.ws_row; i++)
		std::cout << std::endl;
	setCursorPos(0,0);
}

// It clears the line the cursor is on.
void termfunk::clearLine() {
	std::cout << "\r";
	for (int i=0; i < TermSize.ws_col; i++) {
		std::cout << " ";
	}
	std::cout << "\r" << std::flush;
}

// It hides the cursor.
void termfunk::cursorHide() {
	std::cout << "\e[?25l" << std::flush;
}

// It shows the cursor.
void termfunk::cursorShow() {
	std::cout << "\e[?25h" << std::flush;
}

// Uses an ansi code to change the cursor position in the terminal.
// The terminal location values start at 1,1 not 0,0 so for simplicity it increments them by one so you can input 0,0 for the top-left.
void termfunk::setCursorPos(unsigned short col, unsigned short row) {
	printf("\033[%d;%dH",++row,++col);
}

//Usage: slowPrint("Hello, World!")
void termfunk::slowPrint(std::string input) {
	for (char c : input) {
		#ifdef NDEBUG
		usleep(16666);
		#endif
		std::cout << std::string(1, c) << std::flush;
	}
}

//Usage: cout << center("Hello World!");
// Returns the string with the proper number of whitespace to appear at the center of the screen when printed.
std::string termfunk::center(std::string input) {
	int x = round(( TermSize.ws_col - strlen_utf8(input) )/2);
	return std::string(x, ' ') + input;
}

termfunk term;