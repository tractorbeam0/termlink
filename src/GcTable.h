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

#ifdef linux
  #include <sys/ioctl.h>
#elif _WIN32
  #include <windows.h>
  #include "GcTerminal.h"
#endif

#include <vector>
#include <string>

namespace GameComponents {
  class Table
  {
    private:

    struct Key {
      std::string ID;
      bool isUsed;

      Key(std::string id = "", bool used = false) : ID(id), isUsed(used) {}
    };

    static const std::string garble;
    static constexpr winsize Size = {12, 15, 0, 0};
    static constexpr size_t Area = Size.ws_row * Size.ws_col;
    
    Key password;
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