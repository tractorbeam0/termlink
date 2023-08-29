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

#pragma once

#define BEEP    '\7' //It's hard to see '\7' as a beep, but...
#define NULCHAR '\0' //it's not as hard to see '\0' as nullchar, this definition might be redundant, *shrug*

#include <string>
#include <sys/ioctl.h> //Required to properly declare the w struct.

extern struct winsize w;

//Simple functions (they do a thing, nothing more)

void clearLine();
void cursorHide();
void cursorShow();
void funkClose();
void funkInit();
void clearScreen();

//Complex functions (they require input and can do different things)

void setCursorPos(int x, int y);
void slowPrint(int x, int y, std::string input);
std::string center(std::string input);