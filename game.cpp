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
#include <math.h>
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

//NONE OF THIS UNTIL THE GAME FUNCTION HAS BEEN TESTED. It's still being developed in bulk.
class Singleton {
  public:
  vector<bool> inUse;
  size_t population;
  vector<string> content;

  Singleton(vector<string> input) {
    population = input.size();
    content = input;
  }
    
  int getRandom() {
    unsigned r = rand()%population;
    if (!inUse[r]) {
      inUse[r] = true;
      return r;
    } else getRandom();
  }
} password({"ONE","TWO","THREE","FOUR","FIVE"});

//tableGenerate generates the wall of text that includes some potential passwords.
string tableGenerate() {
  const string garble = "$?_/%(){}[]*:!@#`\",.<>:'"; //Yes, I know it won't include the \, it's there to protect the ".
  
  string tableBuffer;
  
  struct Singleton {
    size_t length = 15;
    size_t height = 12;
    size_t area = length * height;
  } tableSize;

  //Generating this in advance so we can tell how many characters in the table will be used by passwords.
  vector<int> toBeUsed;
  unsigned numOfUsedChars;
  unsigned coord;
  int n = round(password.population/2); //For some reason trying to get a random integer between 0.5 and 1.0 of password.population only works if I seperate that into an int *before* modulating it with rand(). Oh well.
  for (int i = 0; i < password.population - (rand()% n); i++) {
    coord = password.getRandom();
    numOfUsedChars += password.content[coord].length();
    toBeUsed.push_back(coord);
  }

  //Find out where to put the passwords in the table (for now it will just distribute them evenly)
  for (int i : toBeUsed) {
    
  }

  //Finally go about building the table.
  for (int i = 0; i < tableSize.area; i++) {
    
  }

  return tableBuffer;
}

void Game() {
  clearScreen();

  usleep(3000000);
  slowPrint(0, 0, "Welcome to ROBCO Industries (TM) Termlink");
  slowPrint(0, 1, "**LOGIN SCRIPT ACTIVE**\n\n");
  usleep(150000);
  slowPrint(0, 3, "TERMINAL SET TO MAINTANANCE MODE - Contact your administrator.\n");
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
  

}