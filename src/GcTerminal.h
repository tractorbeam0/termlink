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

#include <string>
#include <stdint.h>
#pragma once

#ifdef linux
  #include <unistd.h>
  #include <sys/ioctl.h>

#elif _WIN32
  #include <windows.h>

  struct winsize {
	  unsigned short ws_row;
	  unsigned short ws_col;
    unsigned short xpixel;
    unsigned short ypixel;
  };
#endif

void timer(uint64_t usec);

namespace GameComponents {
  namespace Terminal
  {
    #ifdef linux
      const winsize Size = { [] {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &Size);
        return Size;
      } () };
    #elif _WIN32
      //Writing code for compatibility is sooo fun.
      const winsize Size = { [] {
          SetConsoleOutputCP(CP_UTF8);  //Compatibility with all the box characters.
        	CONSOLE_SCREEN_BUFFER_INFO temp;
	        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &temp);
          return winsize {static_cast<unsigned short>(temp.srWindow.Bottom - temp.srWindow.Top + 1),
                          static_cast<unsigned short>(temp.srWindow.Right - temp.srWindow.Left + 1),
                          0, 0};
      } () };
    #endif

    size_t strlen_utf8(const std::string& str);
    void cursorHide();
    void cursorShow();
    void clearScreen();
    void clearLine();
    void setCursorPos(unsigned short x, unsigned short y);
    void slowPrint(std::string input);
    std::string center(std::string input);
  }
}
