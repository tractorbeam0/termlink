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

#include "termfunk.hpp"
#include "scripts.hpp"

int main() {

  funkInit();
  srand(time(NULL));

  Intro();
  Game();
  
  funkClose();
  return 0;
}