#ifndef PLAYER_C
#define PLAYER_C


#ifndef PLAYER_H
#include "Player.hpp"
#endif
#include <string>

#ifndef GAME_H
 #include "Game.hpp"
#endif


class PlayerImpl : public virtual Player{
    private:
        uint64_t board;
        std::string *playerName;
        Game& game;
    public: 
        uint64_t getBoard(){return this->board;}
        std::string& getPlayerName(){return *this->playerName;}
        Game& getGame(){return this->game;}
        void setBoard(uint64_t newBoard);
        PlayerImpl(std::string* playerName, Game& game);
        ~PlayerImpl();
        bool nextMove();
        bool hasPlayerWon();
        };

#endif