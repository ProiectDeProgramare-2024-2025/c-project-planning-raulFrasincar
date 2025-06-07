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

    if (argc == 2 && std::string(argv[1]) == "leaderboard") {
        manager.showLeaderboard();
    } else if (argc == 3 && std::string(argv[1]) == "history") {
        manager.showHistory(argv[2]);
    } else {
        std::cout << "\x1B[33mUsage:\x1B[0m\n"
                  << "\x1B[32mleaderboard\x1B[0m\n"
                  << "\x1B[32mhistory PlayerName\x1B[0m\n";
        return 1;
    }

    return 0;
}
