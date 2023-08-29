/* COPYRIGHT NOTICE
  termfunk.h  - termfunk's associated header file
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

//Performs all the actions required to help the functions... y'know, function.
termfunk::termfunk() {
    //Establishes the size of the terminal.
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &this->TermSize);
    this->TermPos = TermSize;
}

//Cleans up and prepares the terminal to be used by regular programs again.
termfunk::~termfunk() {
    cursorShow();
    clearScreen();
}

// It clears the screen.
void termfunk::clearScreen() {
    for (int i=0; i < this->TermSize.ws_row; i++)
        std::cout << std::endl;
    setCursorPos(0,0);
}

// It clears the line the cursor is on.
void termfunk::clearLine() {
    for (int i=0; i < this->TermSize.ws_col; i++)
        std::cout << " ";
    setCursorPos(0,0);
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
void termfunk::setCursorPos(int col, int row) {
    printf("\033[%d;%dH",++row,++col);
}

//Usage: slowPrint(0, 0, "Hello, World!")
// Prints things like an old terminal at 600 baud, requires coordinates because there is no way to tell where the cursor started (the only downside to not using ncurses...)
// Change the usleep down there if you want it to be faster, but be prepared to do the math.
void termfunk::slowPrint(std::string input) {
    setCursorPos(this->TermPos.ws_col, this->TermPos.ws_row);
    for (int i = 0; i < input.length(); i++) {
        std::cout << input[i] << std::flush;
        usleep(10000);
    }
}

//Usage: cout << center("Hello World!");
// Returns the string with the proper number of whitespace to appear at the center of the screen when printed.
std::string termfunk::center(std::string input) {
    int x = round(( this->TermSize.ws_col - this->strlen_utf8(input) )/2);
    return std::string(x, ' ') + input;
}

void termf_cout(std::string input) {
    //If the string is too long to fit on the current line, move to the next line.
    if (strlen_utf8(this->TermPos.ws_col) + strlen_utf8(input) > strlen_utf8(this->TermSize.ws_col))
        

    std::cout << input << std::flush;
}

size_t strlen_utf8(const std::string& str) {
	size_t length = 0;
	for (char c : str) {
		if ((c & 0xC0) != 0x80)
			++length;
	}
	return length;
}

void termfunk::updatePos(unsigned short int &ws_col, unsigned short int &ws_row) {
    this->TermPos.ws_col = ws_col;
    this->TermPos.ws_row = ws_row;
}