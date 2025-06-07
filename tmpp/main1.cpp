#include <iostream>
#include "MatchManager.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]) {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode)) {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
#endif

    MatchManager manager;
    manager.loadData();

    if (argc == 5 && std::string(argv[1]) == "add_match") {
        std::string combined = std::string(argv[2]) + " " + argv[3] + " " + argv[4];
        manager.addMatchFormatted(combined);
    } else {
        std::cout << "\x1B[33mUsage:\x1B[0m\n"
                  << "\x1B[32madd_match Player1 Score1/Score2 Player2\x1B[0m\n";
        return 1;
    }

    return 0;
}
