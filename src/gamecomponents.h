#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>

#include "termfunk.h"

namespace GameComponents {
  class Terminal;
  class TableManager {
    private:

    struct Password {
      std::string ID;
      bool isCorrect;
    };

    const winsize tableSize = {12, 15};
    const size_t tableArea = tableSize.ws_row * tableSize.ws_col;
    const std::string garble = "\".!@#$%^&*()_+-=[]{};':,/<>?`~\\|";

    std::vector<std::string> keyTable;
    std::vector<std::string> outputTable;
    std::vector<bool> passInUse;

    void openFile(std::string input);
    std::vector<std::string> shuffledKeys();
    std::string generateSegment(std::string key, size_t size);
    void sortSegments(std::vector<std::string> keyTable);
    
    public:

    TableManager(std::string file);
    void generateTable();
    char getRandomChar();
    void printTable(unsigned x, unsigned y);
  };
}