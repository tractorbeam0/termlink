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

    const winsize tableSize = {12, 15};
    const size_t tableArea = tableSize.ws_row * tableSize.ws_col;
    #ifndef NDEBUG
    const std::string garble = ".";
    #else
    const std::string garble = "\".!@#$%^&*()_+-=[]{};':,/<>?`~\\|";
    #endif
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