/* COPYRIGHT NOTICE
  termfunk  - A library used to do funky terminal shenanigans without
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

#define BEEP    '\7'
#define NULCHAR '\0'
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>  //funkInit(), to grab terminal size
#include <sstream>      //slowPrint(), center()
#include <cmath>        //center()
using namespace std;



//**LOCAL (Only used in this source)

extern struct winsize w; //Used specifically for window sizes since ioctl unfortunately won't output to anything but a struct.

//Copy & Pasted from cplusplus.com because standard functions don't recognize UTF-8 chars as just 1 character, need it for box drawing, thanks Peter87 (10193)!
size_t strlen_utf8(const string& str) {
  size_t length = 0;
  for (char c : str) {
    if ((c & 0xC0) != 0x80) {
      ++length;
    }
  }
  return length;
}


//**PUBLIC (Declared in the header to be used elsewhere)

//Usage: int main() {funkInit(); ...}
// Performs all the actions required to help the functions... y'know, function.
void funkInit() {
  //Establishes the size of the terminal.
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
}

// It hides the cursor. 
void cursorHide() {
  cout << "\e[?25l" << flush;
}

// It shows the cursor.
void cursorShow() {
  cout << "\e[?25h" << flush;
}

// Uses an ansi code to change the cursor position in the terminal.
// The terminal location values start at 1,1 not 0,0 so for simplicity it increments them by one so you can input 0,0 for the top-left.
void setCursorPos(int col, int row) {
  printf("\033[%d;%dH",++row,++col);
}

//...
void clearScreen() {
  for (int i=0; i < w.ws_row; i++) {cout << endl;}
  setCursorPos(0,0); 
}

//Usage: slowPrint(0, 0, "Hello, World!")
// Prints things like an old terminal at 600 baud, requires coordinates because there is no way to tell where the cursor started (the only downside to not using ncurses...)
// Change the usleep down there if you want it to be faster, but be prepared to do the math.
void slowPrint(int x, int y, string input) {
  y++;
  for (int i=0; input[i] !=NULCHAR; i++) {
    setCursorPos(++x,y);
    cout << "\033[" << y << ";" << x << "H" << input[i] << flush;
    usleep(16666);
  }
} 

//Usage: cout << center("Hello World!");
// Returns a string with the proper number of spaces to appear at the center of the screen when printed.
string center(string input) {
  stringstream output;
  for (int i = 0; i < round(round(w.ws_col/2) - strlen_utf8(input) / 2); i++) {
    output << " ";
  }
  output << input;
  return output.str();
}

void clearLine() {
  cout << "\r" << flush;
  for (int i = 0; i < w.ws_col; i++) {
    cout << " ";
  }
  cout << "\r" << flush;
}

void termClear() {
  setCursorPos(0,1);
  for (int i = 2;  i < w.ws_row; i++) {
    clearLine();
    cout << '\n' << flush;
    usleep(16666);
  }
  setCursorPos(0,1);
}

void funkClose() {
  cout << "\e[0m" << flush;
}