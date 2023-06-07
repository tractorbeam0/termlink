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
// Side note: Thank the heavens for intellisense, this function would never get finished this way if it weren't for that telling me what would go wrong
class Singleton {
  public:
  vector<bool> inUse;
  vector<string> content;
  size_t population = content.size();

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
  const string garble = "$?_/%(){}[]*:!@#`\",.<>:'"; //24 characters total.
  
  struct Singleton {
    size_t length = 15;
    size_t height = 12;
    size_t area = length * height;

    vector<int> coordStore;
    unsigned charsBeforeNextPassword;
    unsigned charsReservedToPasswords;
    string result;
  } table;

  //  Generating this in advance so we can tell how many characters in the table will be used by passwords.
  unsigned coordStoreTmp;
  //For some reason trying to get a random integer between 50% and 100% of whatever int is in password.population only works if I seperate
  //that into an int *before* modulating it with rand. Oh well, at least it makes the for loop more efficient.
  unsigned n = round(password.population/2);
  for (int i = 0; i < password.population - (rand()% n); i++) {

    coordStoreTmp = password.getRandom();

    table.charsReservedToPasswords += password.content[coordStoreTmp].length();
    table.coordStore.push_back(coordStoreTmp);
  }

  //  Find out where to put the passwords in the table (for now it will just distribute them evenly)
  int i = 0;
  for (int coord : table.coordStore) {
    i++;
    //God forgive me for what I'm about to do (it's the math that evenly distributes the passwords)
    //It evaluates the number of characters before the center of that password, subtracted by half the length of the password that's going in.
    table.charsBeforeNextPassword = i*(round(table.area / table.coordStore.size())) - round(password.content[coord].length() / 2);
    
    //Add the proper amount of garble characters
    for (int i = 0; i < table.charsBeforeNextPassword; i++) {
      table.result += garble[rand()%garble.length()];
    }

    //And FINALLY insert the password
    table.result += password.content[coord];
  }

  return table.result;
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
  
  throw tableGenerate();
}