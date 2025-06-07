#include "../include/MatchManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

#define COLOR_RESET   "\x1B[0m"
#define COLOR_RED     "\x1B[31m"
#define COLOR_GREEN   "\x1B[32m"
#define COLOR_YELLOW  "\x1B[33m"
#define COLOR_PINK    "\x1B[95m"
#define COLOR_BLUE    "\x1B[34m"

#define PLAYER_FILE "players.csv"
#define MATCH_FILE "matches.csv"

int MatchManager::getPlayerIndex(const std::string& name) {
    for (size_t i = 0; i < players.size(); ++i)
        if (players[i].name == name) return i;
    players.emplace_back(name);
    return players.size() - 1;
}

void MatchManager::loadData() {
    std::ifstream file(PLAYER_FILE);
    if (file) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string name;
            int wins, losses;
            getline(ss, name, ',');
            ss >> wins;
            ss.ignore();
            ss >> losses;
            players.emplace_back(name, wins, losses);
        }
    }
    file.close();

    file.open(MATCH_FILE);
    if (file) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string p1, p2;
            int s1, s2;
            getline(ss, p1, ',');
            getline(ss, p2, ',');
            ss >> s1;
            ss.ignore();
            ss >> s2;
            matches.emplace_back(p1, p2, s1, s2);
        }
    }
    file.close();
}

void MatchManager::saveData() {
    std::ofstream file(PLAYER_FILE);
    for (const auto& p : players)
        file << p.name << "," << p.wins << "," << p.losses << "\n";
    file.close();

    file.open(MATCH_FILE);
    for (const auto& m : matches)
        file << m.p1name << "," << m.p2name << "," << m.p1score << "," << m.p2score << "\n";
    file.close();
}

void MatchManager::addMatchFormatted(const std::string& matchInput) {
    std::stringstream ss(matchInput);
    std::string p1, p2, scorePart;
    int s1, s2;

    ss >> p1 >> scorePart >> p2;
    size_t slashPos = scorePart.find('/');
    if (slashPos == std::string::npos) {
        std::cout << COLOR_RED << "Invalid score format. Use Score1/Score2." << COLOR_RESET << "\n";
        return;
    }

    try {
        s1 = std::stoi(scorePart.substr(0, slashPos));
        s2 = std::stoi(scorePart.substr(slashPos + 1));
    } catch (...) {
        std::cout << COLOR_RED << "Invalid score values." << COLOR_RESET << "\n";
        return;
    }

    if (s1 < 0 || s1 > 21 || s2 < 0 || s2 > 21) {
        std::cout << COLOR_RED << "Invalid scores. Must be between 0 and 21." << COLOR_RESET << "\n";
        return;
    }

    matches.emplace_back(p1, p2, s1, s2);
    int idx1 = getPlayerIndex(p1);
    int idx2 = getPlayerIndex(p2);

    if (s1 > s2) {
        players[idx1].wins++;
        players[idx2].losses++;
    } else {
        players[idx2].wins++;
        players[idx1].losses++;
    }

    saveData();
    std::cout << COLOR_GREEN << "Match recorded successfully." << COLOR_RESET << "\n";
}

void MatchManager::showLeaderboard() {
    std::vector<Player> sorted = players;
    std::sort(sorted.begin(), sorted.end(), [](const Player& a, const Player& b) {
        if (a.wins != b.wins) return a.wins > b.wins;
        return a.losses < b.losses;
    });

    std::cout << COLOR_YELLOW << "Leaderboard:" << COLOR_RESET << "\n";
    std::cout << std::left << std::setw(15) << "Player" << COLOR_GREEN << "Wins" << COLOR_RED << "  Losses" << COLOR_RESET << "\n";
    for (const auto& p : sorted) {
        std::cout << std::left << std::setw(15) << p.name
                  << COLOR_GREEN << p.wins << COLOR_RESET << "     "
                  << COLOR_RED << p.losses << COLOR_RESET << "\n";
    }
}

void MatchManager::showHistory(const std::string& name) {
    auto it = std::find_if(players.begin(), players.end(), [&name](const Player& p) {
        return p.name == name;
    });

    if (it == players.end()) {
        std::cout << COLOR_RED << "Player not found." << COLOR_RESET << "\n";
        return;
    }

    std::cout << "Match history for " << name << ":\n";
    for (const auto& m : matches) {
        if (m.p1name == name || m.p2name == name) {
            std::cout << COLOR_RED << m.p1name << " " << m.p1score << COLOR_RESET
                      << " / "
                      << COLOR_BLUE << m.p2score << " " << m.p2name << COLOR_RESET << "\n";
        }
    }
    std::cout << COLOR_YELLOW << "Wins: " << it->wins << ", Losses: " << it->losses << COLOR_RESET << "\n";
}
