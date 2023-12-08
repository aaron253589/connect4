#include <vector>
#define GAME_H

#ifndef PLAYER_H
#include "Player.hpp"
#endif

constexpr auto BOARD_X_DIMENTION = 7;
constexpr auto BOARD_Y_DIMENTION = 6;
constexpr auto WINNING_LENGTH = 4;

class Game{
    public: 
       virtual Player& getPlayer1() = 0;
       virtual Player& getPlayer2() = 0;
       virtual std::vector<uint64_t>& getWinningPostitions() = 0;
       virtual uint64_t extractCoordinates(const int column) = 0;
       virtual void display() = 0;
       virtual bool hasPlayerWon(uint64_t board) = 0;
};