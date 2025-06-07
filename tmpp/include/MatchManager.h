#ifndef MATCHMANAGER_H
#define MATCHMANAGER_H

#include <vector>
#include <string>
#include "Player.h"
#include "Match.h"

class MatchManager {
private:
    std::vector<Player> players;
    std::vector<Match> matches;

    int getPlayerIndex(const std::string& name);

public:
    void loadData();
    void saveData();
    void addMatchFormatted(const std::string& matchInput);
    void showLeaderboard();
    void showHistory(const std::string& name);
};

#endif
