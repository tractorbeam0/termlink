# termlink
*THIS IS THE DEVELOPMENT BRANCH. It's specifically reserved for source code that either doesn't compile or doesn't run correctly (eg segfault). I will merge with main whenever that doesn't happen.*

A recreation of the terminal hacking minigame from the Fallout series, with a sizable portion of personal touches.

This serves a few purposes:

* Learning how to actually use git beyond cloning repos (ignore my first few commits being just bad)
* Actually learning C++ (ignore the whole thing just being generally bad)
* Because I have an actual vintage terminal from the late 70's, an SWTPC CT-82 Terminal, and I wanted to see this sorta thing on it.

## Building
You know how Cmake was created for the purpose of generating makefiles so things are cross-compatible? I thought that was too complicated, so here we are with a makefile to manage cmake, making a makefile, in which the first makefile runs the second makefile to build the project. How fun.

At the very least, that means building is simple. Just run make, and the compiled binary will be located in `.../build/release/termlink`. All you have to do is ensure `passwords.txt` is in the same directory.