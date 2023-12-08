#include "AutoPlayer.hpp"
#ifndef LOGGING
#include "LoggingUtil.cpp"
#endif
#include <climits>
#define DEBUG false
#include <iostream>
#include <chrono>
#include <functional>
#include <ctime>
#include <future>
#include <thread>
#include <string>
#define DEPTH 5

AutoPlayer::AutoPlayer(std::string* playerName, Game& game):PlayerImpl(playerName, game){}

uint8_t AutoPlayer::getProximity(const uint64_t a, const uint64_t b){
    uint64_t temp = (a & b);
    int count = 0;
    while (temp > 0) {
        if ((uint64_t)1 & temp) {
            count++;
        }       
        temp >>= 1;

    }

    return count;
}

long AutoPlayer::getPlayerScore(const uint64_t currentPlayerBoard, const uint64_t oppositionPlayerBoard) {
    long positiveScore = 0;
    auto winningPositions = this->getGame().getWinningPostitions();
    for (int i = 0; i < winningPositions.size(); i++) {
        if (winningPositions[i] & oppositionPlayerBoard) {
            continue;
        }
        int count = getProximity(winningPositions[i], currentPlayerBoard);

        if (count == WINNING_LENGTH) {
        return LONG_MAX;
    }
    else if (count == WINNING_LENGTH - 1) {
        positiveScore+= 200;
    }
    else {
        positiveScore+= count;
    }
    
    }
    return positiveScore;
}

long AutoPlayer::getOverallScore(const uint64_t currentPlayerBoard, const uint64_t oppositionPlayerBoard) {
  auto score = this->getPlayerScore(currentPlayerBoard, oppositionPlayerBoard) - this->getPlayerScore(oppositionPlayerBoard, currentPlayerBoard);
#if DEBUG
  myfile << "Overall Score:" << std::endl;
  myfile << "score: " << score << std::endl;
#endif
  return score;
}

uint64_t extractCoordinates(const int column, uint64_t board) {
    for (int i = 0; i < BOARD_Y_DIMENTION; i++) {
        uint64_t value = (uint64_t)1 << (BOARD_X_DIMENTION*i+column);
        if (!(value & board)) {
            return value;
        }
    };
    return 0;
}



long AutoPlayer::playNextMove(uint64_t playerA, uint64_t playerB, int depth, bool playerIndicator) {
    
    long *scores = new long[BOARD_X_DIMENTION];
    
    for (int i = 0; i < BOARD_X_DIMENTION; i++) {
        if ((uint64_t)1 << ((BOARD_Y_DIMENTION - 1) * BOARD_X_DIMENTION + i) & (playerB|playerA)) {
            continue;
        }

        uint64_t newState = playerB | extractCoordinates(i, playerA | playerB);
      
#if DEBUG
        displayInLog(playerIndicator ? newState : playerA, playerIndicator ? playerA : newState);
#endif
        if (this->getGame().hasPlayerWon(newState)) {
            return LONG_MAX;
        }
        if (depth > DEPTH) {
#if DEBUG
            myfile << "depthReached" << std::endl;
        displayInLog(playerIndicator ? newState : playerA, playerIndicator ? playerA : newState);

#endif
            scores[i] = getOverallScore(newState, playerA);
        }
        else { scores[i] = -playNextMove(newState, playerA, depth + 1, !playerIndicator); }
    }
#if DEBUG
    myfile << "Depth: " << depth << std::endl;
    myfile << "scores" << std::endl;
    for (int i = 0; i < BOARD_X_DIMENTION; i++) {
        myfile << scores[i] << " ";
    }
    myfile << std::endl;
#endif
   
    int temp = NULL;
    for (int i = 0; i < BOARD_X_DIMENTION; i++) {
        if (scores[i] == NULL) { continue; }
        if (temp == NULL) {
            temp = i;
            continue;
        }
        if (scores[i] > scores[temp]) {
            temp = i;
        }
    }
 //   std::cout<<"depth "<<depth<<" chosen column:" <<temp<<std::endl;

    long score = temp != NULL ? scores[temp] : BOARD_X_DIMENTION;
    delete[] scores;
    if(depth == 0){
    std::string s = "returning with depth: ";
    log(s.append(std::to_string(depth)));}
    return score;

}

int AutoPlayer::getNextMove(uint64_t currentPlayerState, uint64_t oppositionPlayerState, const std::vector<uint64_t>& winningPositions){
    std::vector<std::future<long>> scores;
    for (int i = 0; i < BOARD_X_DIMENTION; i++) {
        uint64_t newState = currentPlayerState | this->getGame().extractCoordinates(i);
        if (this->getGame().hasPlayerWon(newState)) {
            return i;
        }
        else {  
            scores.emplace_back(std::async(std::launch::async,std::bind(&AutoPlayer::playNextMove, this, newState, oppositionPlayerState, 0, true)));
        } 
    }
    
    int y = 0;
    long x = -scores[0].get();
        std::cout<<"in: "<<0<<std::endl;
        std::cout<<x<<std::endl;

    for (int i = 1; i < BOARD_X_DIMENTION; i++) {
        std::cout<<"in: "<<i<<std::endl;
        long temp = -scores[i].get();
        std::cout<<temp<<std::endl;
        if (temp > x) {
            x = temp;
            y = i;
        }
    }
    return y;
}

bool AutoPlayer::nextMove(){
     int column;
         uint64_t coordinates = 0;
         while(coordinates == 0){
            std::cout<<"player "<<this->getPlayerName()<<" move: "<<std::endl;
            #if DEBUG
              displayInLog(this->getGame().getPlayer1().getBoard(), this->getGame().getPlayer2().getBoard());
            #endif
                auto start = std::chrono::system_clock::now();

            column = this->getNextMove(this->getBoard(), this->getGame().getPlayer1().getBoard(), this->getGame().getWinningPostitions());

                auto end = std::chrono::system_clock::now();
                    std::chrono::duration<double> elapsed_seconds = end-start;
std::cout<<"time for move: "<<elapsed_seconds.count()<<std::endl;

            coordinates = this->getGame().extractCoordinates(column);   
                this->setBoard( this->getBoard() | coordinates);
            }
            return true;
}