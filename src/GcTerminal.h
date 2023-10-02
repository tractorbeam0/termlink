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
#include <unistd.h>
#include <string>
#pragma once

namespace GameComponents {
  namespace Terminal
  {
    const winsize Size = { [] {
      winsize temp;
      ioctl(STDOUT_FILENO, TIOCGWINSZ, &temp);
      return temp;
    } () };
    static bool initialized = false;

    void Init();
    size_t strlen_utf8(const std::string& str);
    void cursorHide();
    void cursorShow();
    void clearScreen();
    void clearLine();
    void setCursorPos(unsigned short x, unsigned short y);
    void slowPrint(std::string input);
    std::string center(std::string input);
  };
}