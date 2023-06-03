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
#ifndef TERMFUNK_H
#define TERMFUNK_H
/*
  ,^.   "I am the header guard..."
  |||
  |||       _T_     "If you have been here before,
  |||   .-.[:|:].-.  YOU SHALL NOT PASS!"
  ===_ /\|  "'"  |/
   E]_|\/ \--|-|''''|
   O  `'  '=[:]| A  |
          /""""|  P |
         /"""""`.__.'
        []"/"""\"[]
        | \     / |
        | |     | |
      <\\\)     (///>
(Art courtesy of ascii.co.uk)
*/

#define BEEP    '\7'
#define NULCHAR '\0'

#include <string>

extern struct winsize w;
void funkInit();
void cursorHide();
void cursorShow();
void setCursorPos(int, int);
void clearScreen();
void slowPrint(int, int, std::string);
std::string center(std::string);
void clearLine();
void termClear();
void termReset();

#endif