#include <string>
#include <sys/ioctl.h>

struct termfunk {
    winsize TermSize;
    winsize TermPos;

    termfunk();
    ~termfunk();
    void clearScreen();
    void clearLine();
    static void cursorHide();
    static void cursorShow();
    static void setCursorPos(int x, int y);
    void slowPrint(std::string input);
    std::string center(std::string input);
    
private:
    void termf_cout(std::string input);
    void updatePos(unsigned short int &ws_col, unsigned short int &ws_row);
    static size_t strlen_utf8(const std::string& str);
} t;