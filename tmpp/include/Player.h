#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    std::string name;
    int wins;
    int losses;

    Player(const std::string& n, int w = 0, int l = 0);
};

#endif
