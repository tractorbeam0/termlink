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

#pragma once

#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>

namespace Gc
{

  class Terminal
  {
    private:

    size_t strlen_utf8(const std::string& str);

    public:

    winsize Size;

    static void cursorHide();
    static void cursorShow();
    void clearScreen();
    void clearLine();
    void setCursorPos(unsigned short x, unsigned short y);
    void slowPrint(std::string input);
    std::string center(std::string input);

    Terminal();
    ~Terminal();
  };


  class Table
  {
    private:

    struct Key {
      std::string ID;
      bool isUsed;
    };

    #ifdef NDEBUG
    const std::string garble = "\".!@#$%^&*()_+-=[]{};':,/<>?`~\\|";
    #else
    const std::string garble = ".";
    #endif

    const winsize tableSize = {12, 15};
    const size_t tableArea = tableSize.ws_row * tableSize.ws_col;
    std::vector<Key> keys;
    std::vector<std::string> outputTable;

    void openFile(std::string input);
    void sortSegments(std::vector<std::string> keyTable);
    std::string generateSegment(std::string key, size_t size);
    std::vector<std::string> shuffledKeys();
    
    public:

    void Generate();
    char getRandomChar();
    void Print(unsigned x, unsigned y);
    
    Table(std::string file);
  };

}

extern Gc::Terminal Term;