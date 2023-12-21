#ifndef PLAYER_H
#define PLAYER_H

class Player{
    public: 
        virtual uint64_t getBoard() = 0;
        virtual std::string& getPlayerName() = 0;
        virtual bool nextMove() = 0;
        virtual bool hasPlayerWon() = 0;
        };
#endif