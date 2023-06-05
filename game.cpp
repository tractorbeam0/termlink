/* COPYRIGHT NOTICE
  game      - The vast majority of the termlink program
  termlink  - A recreation of the terminal hacking minigame from the
              Fallout series, with a sizable portion of personal
              touches

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

#include "termfunk.hpp"
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

//Clears everything on the screen *except* the "Welcome to ROBCO..." in an animated manor.
void termClear() {
  setCursorPos(0,1);
  for (int i = 2;  i < w.ws_row; i++) {
    clearLine();
    cout << '\n' << flush;
    usleep(16666);
  }
  setCursorPos(0,1);
}

size_t passCount;
class password {
  public:
  string content;
  size_t size;
  bool inUse;

  password(string input) {
    size = input.length();
    content = input;
    inUse = false;
    passCount++;
  }
  ~password() {
    totalPasswords--;
  }
};

//The size of the password list will change in the future.
#define PASSWORD_COUNT 4
class tableGenerate {
  public:
  tableGenerate();
  string tableGet() {
    if (output.str()[0] == NULCHAR)
      throw 1000;
    return output.str();
  }

  private:
  //The generated table itself
  //Declared as a stringstream so it can be contributed to as you would contribute to std::cout (eg with output << string[i];)
  stringstream output;

  //The size of the table
  const size_t outputSize = 384;

  //Keeps track of which passwords have already been placed in a table
  bool passwordInUse[PASSWORD_COUNT] = {};

  //The passwords to choose from (Make sure to change PASSWORD_COUNT if you add/delete any)
  const string password[PASSWORD_COUNT] = {
    "ONE","TWO","THREE","FOUR"
  };

  //The unimportant garble to choose from
  const char garble[24] = {
    '$','?','_','/','%',
    '(',')','{','}','[',
    ']','*',':','!','@',
    '#','`','"',',','.',
    '<','>',':','\''
  };
};

//tableGenerate class constructor, generates the table.
//Currently going through it's development pass, it will look terrible.
tableGenerate::tableGenerate() {
  unsigned random;
  string passwordGoingToUse[PASSWORD_COUNT] = {};
  size_t passwordGoingToUseSizeTotal;
  //Generate the order of passwords to use
  for (int i; i < PASSWORD_COUNT; i++) {
    random = rand()%PASSWORD_COUNT;             //I'm having flashbacks of times when this variable wouldn't change across loops... God help me.
    passwordGoingToUse[i] = password[random];
    if (passwordInUse[random]) {
      i--;
      continue;
    }
    passwordInUse[random] = true;
  }
  //Determine the size of each password in the array
  int passwordSize[PASSWORD_COUNT] = {};
  for (int i; i < PASSWORD_COUNT; i++) {
    passwordSize[i] = passwordGoingToUse[i].length();
    passwordGoingToUseSizeTotal += passwordGoingToUse[i].length();
  }

  //FINALLY building the table
  for (int i = 0; i < outputSize; i++) {  //For every character that can be placed in the table...
    unsigned randomGarble = rand()%24;
    unsigned randomPassword = rand()%PASSWORD_COUNT;
    if (i < 7) {                          //...make sure the first 7 characters are garble
      output << garble[randomGarble];
      continue;
    }

  }
};

void Game() {
  clearScreen();

  usleep(3000000);
  slowPrint(0, 0, "Welcome to ROBCO Industries (TM) Termlink");
  slowPrint(0, 1, "**LOGIN SCRIPT ACTIVE**\n\n");
  usleep(150000);
  slowPrint(0, 3, "TERMINAL SET TO MAINTANANCE MODE - If you don't know what this means, contact your administrator.\n");
  usleep(50000);
  slowPrint(0, 4, "00> LOD 00,7D\n");
  slowPrint(0, 5, "70> LOD E1,FF\n");
  slowPrint(0, 6, "78> INS 69, 00 5F 4B D8 A7 01\n");
  slowPrint(0, 7, "79> INS 6A, FF 4D 0A AA 6B 4F\n");
  slowPrint(0, 8, "7A> INS 6B, 07 55 7C 3E D1 1F\n");
  slowPrint(0, 9, "7B> //CODE INJECTION COMPLETE\n");
  slowPrint(0,10, "7B> RUN E1\n");
  usleep(520000);  
  termClear();
  slowPrint(0, 2, "Password Required\n\n");
  usleep(200000);
  slowPrint(0, 4, "Starting Debugger...");
  usleep(400000);
  clearLine();
  slowPrint(0, 4, "Please wait...\n");

  tableGenerate lol;
  slowPrint(0, 6, lol.tableGet());
}