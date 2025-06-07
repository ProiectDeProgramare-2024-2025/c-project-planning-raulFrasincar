#ifndef MATCH_H
#define MATCH_H

#include <string>

class Match {
public:
    std::string p1name, p2name;
    int p1score, p2score;

    Match(const std::string& p1, const std::string& p2, int s1, int s2);
};

#endif
