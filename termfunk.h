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

#include <iostream>
#include <unistd.h>
#include <cmath>
#include <string>
#include <sys/ioctl.h>

struct termfunk {
  winsize TermSize;
  winsize TermPos;

  termfunk();
  ~termfunk();
  void clearScreen();
  void clearLine();
  static void cursorHide();
  static void cursorShow();
  void setCursorPos(unsigned short x, unsigned short y);
  void slowPrint(std::string input);
  std::string center(std::string input);

private:
  void termf_cout(std::string input);
  void updatePos(unsigned short &ws_col, unsigned short &ws_row);
  size_t strlen_utf8(const std::string& str);
};

extern termfunk term;