/* COPYRIGHT NOTICE
  intro     - A large and not-so-vital piece of the termlink program
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

#include "termfunk.h"
#include <iostream>
#include <cmath>
#include <unistd.h>
#include <sys/ioctl.h>
using namespace std;

void intro() {

  usleep(2401000); //Dramatic pause...
  cursorHide();
  
  //Startup
  int j = 0;
  while (j < 4) {
    for (int i = 0; i < 7; i++) {
      int linecoord = rand()%w.ws_col;
      for (int i = 0; i < w.ws_col; i++) {
        setCursorPos(i, linecoord);
        cout << "█";
      }
    }
    j++;
    usleep(30000);
  }
  usleep(30000);
  
  //White screen
  setCursorPos(0,0);
  for (int i = 0; i < w.ws_row * w.ws_col; i++) {
    cout << "█";
  }
  cout << flush;
  usleep(100000);
  
  clearScreen();
  for (int i = 0; i < w.ws_row * (w.ws_col/2); i++) {
    cout << " │";
  }
  cout << flush;
  
  setCursorPos(0,0);
  for (int i = 0; i < w.ws_row * (w.ws_col/2); i++) {
    cout << "─┼";
  }
  cout << flush;

  setCursorPos(0,0);
  for (int i = 0; i < w.ws_row * w.ws_col; i++) {
    cout << "─";
  }
  cout << flush;

  setCursorPos(0,0);
  for (int i = 0; i < w.ws_row * w.ws_col; i++) {
    cout << " ";
  }
  cout << flush;
  
  //Wait Screen
  clearScreen();
  usleep(1000000);
  cout << "PLEASE WAIT..." << flush;
  usleep(2300000);
  
  //Wait Screen, post ascii init
  clearScreen();
  cout << "Please Wait..." << flush;
  usleep(2300000);
 
  //Term OK screen
  clearScreen();
 
  usleep(200000);  
  setCursorPos(0, round(w.ws_row/2) - 1);
  cout << BEEP;
  cout << center("┏━━━━━━━━━━━━━━━━━━┓") << '\n';
  cout << center("┃    RT-1200 OK    ┃") << '\n';
  cout << center("┗━━━━━━━━━━━━━━━━━━┛") << '\n';

  //1/4 up from the bottom of the screen.
  setCursorPos(0, floor(round(w.ws_row/2) + round(w.ws_row/2)/2));
  cout << center("Firmware and Termlink Copyright (C) 2065,75") << "\n\n" << flush;
  
  //Loading Lines
  cout << center("ROBCO Industries (TM)") << "\n\n" << flush;
  usleep(600000);
  cout << center("Loading Termlink interface...") << flush;
  usleep(1400000);
  clearLine();
  cout << center("Looking for Host...") << flush;
  usleep(700000);
  clearLine();
  cout << center("Host Found!") << flush;
  usleep(300000);
  clearLine();
  cout << center("Handshake Complete") << flush;
  usleep(500000);
  cout << "\n" << center("Connected at 600 bits/s") << "\x1b[A" << flush; //last ascii code is essentially an reverse newline
  usleep(400000);
  clearLine();
  cout << center("Host is finishing up...") << flush;
  usleep(1100000);
  
  for (int i = 0; i <= w.ws_row; i++) {
    cout << "\n" << flush;
    usleep(16666);
  }
  setCursorPos(0,0);
  cursorShow();

  //Loading debugger's physical RAM viewer, loading the Login program, editing the debugger to display section of RAM with potential password over login program. 
  //  ^^^Obviously this is fake, it's just that it'll seem even faker if it doesn't sound at least plausible in concept.
  usleep(3000000);
  slowPrint(0, 0, "Welcome to ROBCO Industries (TM) Termlink");
  
  slowPrint(0, 1, "**LOGIN SCRIPT ACTIVE**\n\n");
  usleep(150000);
  slowPrint(0, 3, "TERMINAL SET TO MAINTANANCE MODE - Please contact your administrator.\n");
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
  slowPrint(0, 4, "Mapping physical RAM...\n");
}