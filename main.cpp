/* COPYRIGHT NOTICE
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

//"YOU ARE OUT OF UNIFORM SOLDIER, WHERE IS YOUR POOWHHERR AAHHRRMOR!?"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "termfunk.hpp"
#include "scripts.hpp"

void sigintHandler(int sig_num) {
  signal(SIGINT, sigintHandler);
  printf("\n\nCtrl-C Recieved! You're lucky I catch those. Cleaning up properly...\n");
  funkClose();
  exit(0);
}

int main() {
  funkInit();
  srand(time(NULL));
  signal(SIGINT, sigintHandler);

  //The actual code (Intro skipped for debugging)
  try {
    //Intro();
    Game();
  }

  //This is the error handler. I may or may not end up seperating this into its own source file.
  catch (int error) {
    clearScreen();
    printf("Exception!\n\n");
    switch (error) {
      case 1000: printf("(%d) Unable to retrieve a table that hasn't been generated yet!", error); break;
      default  : printf("(%d) An integer has been thrown, but it is out of index! Unable to determine error.", error); break;
    }
    printf("\n\nUnable to continue. Cleaning up and exiting...\n");
    funkClose();
    return error;
  }

  //Used primarily just to see the output of something for debugging. Should never happen in prod.
  catch (std::string debugError) {
    clearScreen();
    printf("Exception!\n\n");
    printf("A string was thrown. This shouldn't normally happen at all. The string in question:\n\n%s", debugError);
    printf("\nUnable to continue. Cleaning up and exiting...\n");
    funkClose();
    return 1;
  }

  funkClose();
  return 0;
}