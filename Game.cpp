#ifndef GAME_C
#define GAME_C

#include "PlayerImpl.cpp"
#include "AutoPlayer.cpp"
#include <iostream>
#include "Game.hpp"
#include "LoggingUtil.cpp"

class GameImpl : public virtual Game{
    private:
        Player* player1 = nullptr;
        Player* player2 = nullptr; 
        std::vector<uint64_t>* winningPositions;
        std::vector<uint64_t>* calculateWinningPostitions();
    public: 
       Player& getPlayer1(){return *this->player1;}
       Player& getPlayer2(){return *this->player2;}
       std::vector<uint64_t>& getWinningPostitions(){return *this->winningPositions;}
       uint64_t extractCoordinates(const int column);
       void display();
       bool hasPlayerWon(uint64_t board);
       GameImpl(std::string name1, std::string name2);
       GameImpl(std::string name1);
       ~GameImpl();
};
 
        GameImpl::GameImpl(std::string name1, std::string name2){
          this->winningPositions=this->calculateWinningPostitions();
          this->player1 = new PlayerImpl(&name1, *this);
          this->player2 = new PlayerImpl(&name2, *this);
        }   

        GameImpl::GameImpl(std::string name1){
             this->winningPositions=this->calculateWinningPostitions();
          this->player1 = new PlayerImpl(&name1, *this);
          std::string* autoPlayerName = new std::string("Auto_Player");
          this->player2 = new AutoPlayer(autoPlayerName, *this);
          #if DEBUG
          std::string s = "player1: ";
          s.append(this->player1->getPlayerName()).append(" player2: ").append(this->player2->getPlayerName());
          log(s);
          #endif
        }

        GameImpl::~GameImpl(){
            delete winningPositions;
            delete player1;
            delete player2;
        }

    
    void GameImpl::display() {

        int len1 =  this->player1->getPlayerName().size();
        int len2 = this->player2->getPlayerName().size();

        int maxPlayerWidth = len1 >= len2 ? len1 : len2;

        for (int i = 0; i < BOARD_Y_DIMENTION; i++) {
        uint64_t fixedOffset = ((BOARD_Y_DIMENTION - 1) * BOARD_X_DIMENTION) - (i * BOARD_X_DIMENTION);
        uint64_t offset = (uint64_t)1 << fixedOffset;
           
           std::cout<<' ';
        for (int i = 0; i < BOARD_X_DIMENTION; i++) {
        for(int i=0;i<maxPlayerWidth;i++){
            std::cout<<'-';
        }
        std::cout<<' ';
        }
std::cout<<std::endl;
        std::cout << '|';
        for (int j = 0; j < BOARD_X_DIMENTION; j++) {

            if (offset & this->player1->getBoard()) {
                std::cout << this->player1->getPlayerName();
                for(int i=0;i<maxPlayerWidth-len1;i++){
                                    std::cout << ' ';
                }
            }
            else if (offset & this->player2->getBoard()) {
                std::cout << this->player2->getPlayerName();
                for(int i=0;i<maxPlayerWidth-len2;i++){
                                    std::cout << ' ';
                }
            }
            else {
                for(int i=0;i<maxPlayerWidth;i++){
                std::cout << ' ';
                }
            }
            offset <<= 1;
            std::cout << '|';
        }
        std::cout << std::endl;
    }
     std::cout<<' ';
        for (int i = 0; i < BOARD_X_DIMENTION; i++) {
        for(int i=0;i<maxPlayerWidth;i++){
            std::cout<<'-';
        }
        std::cout<<' ';
        }
        std::cout<<std::endl;
    }

    std::vector<uint64_t>* GameImpl::calculateWinningPostitions() {

    std::vector<uint64_t>* winningPositions = new std::vector<uint64_t>;

    uint64_t horizontalWinningSteak = 0;
    uint64_t verticalWinningStreak = 0;
    uint64_t bottomLeftToTopRight = 0;
    uint64_t bottomRightToTopLeft = 0;

    for (int i = 0; i < WINNING_LENGTH; i++) {
        horizontalWinningSteak += (uint64_t)1 << i;
        verticalWinningStreak += (uint64_t)1 << (i * BOARD_X_DIMENTION);
        bottomLeftToTopRight += (uint64_t)1 << ((i * BOARD_X_DIMENTION) + i);
        bottomRightToTopLeft += (uint64_t)1 << (((WINNING_LENGTH -1-i) * BOARD_X_DIMENTION) + i);
    }

    winningPositions->push_back(verticalWinningStreak);

    //horizontal
    for (int i = 0; i < BOARD_Y_DIMENTION; i++) {
        winningPositions->push_back(horizontalWinningSteak);
        for (int j = 0; j < BOARD_X_DIMENTION - WINNING_LENGTH; j++) {
            horizontalWinningSteak <<= 1;
            winningPositions -> push_back(horizontalWinningSteak);
        }
        horizontalWinningSteak <<= WINNING_LENGTH;
    }

    //vertical
    for (int i = 0; i < (BOARD_Y_DIMENTION-WINNING_LENGTH+1) * (BOARD_X_DIMENTION) - 1; i++) {
            verticalWinningStreak <<= 1;
            winningPositions->push_back(verticalWinningStreak);
        }

    //diagonals
    for (int i = 0; i < BOARD_Y_DIMENTION- WINNING_LENGTH +1; i++) {
        winningPositions->push_back(bottomLeftToTopRight);
        winningPositions->push_back(bottomRightToTopLeft);
        for (int j = 0; j < BOARD_X_DIMENTION - WINNING_LENGTH; j++) {
            bottomLeftToTopRight <<= 1;
            winningPositions->push_back(bottomLeftToTopRight);
            bottomRightToTopLeft <<= 1;
            winningPositions->push_back(bottomRightToTopLeft);
        }
        bottomLeftToTopRight <<= WINNING_LENGTH;
        bottomRightToTopLeft <<= WINNING_LENGTH;
    }
    return winningPositions;
    }

uint64_t GameImpl::extractCoordinates(const int column) {
    for (int i = 0; i < BOARD_Y_DIMENTION; i++) {
        uint64_t value = (uint64_t)1 << (BOARD_X_DIMENTION*i+column);
        if (!(value & (this->getPlayer1().getBoard() | this->getPlayer2().getBoard()))) {
            return value;
        }
    };
    return 0;
}

bool GameImpl::hasPlayerWon(uint64_t board){
        std::vector<uint64_t>& winningPosistions = *this->winningPositions;
    for(uint64_t positionIndex = 0; positionIndex < winningPosistions.size(); positionIndex++) {
        if ((board & winningPosistions[positionIndex] ) == winningPosistions[positionIndex]) {
            return true;
        }
    }

    return false;}

    #endif