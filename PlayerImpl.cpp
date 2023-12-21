#ifndef PLAYER_IMPL_C
#define PLAYER_IMPL_C

#include "PlayerImpl.hpp"
        
         PlayerImpl::PlayerImpl(std::string* name, Game& game):playerName(name), game(game), board(0){}
        PlayerImpl::~PlayerImpl(){
            delete this->playerName;
        }

        bool PlayerImpl::nextMove(){
         int column;
         uint64_t coordinates = 0;
         while(coordinates == 0){
            std::cout<<"player "<<*this->playerName<<" move: "<<std::endl;
            std::cin >> column;
            coordinates = this->game.extractCoordinates(column);   
                this->board |= coordinates;
            }
            return true;
        }

 bool PlayerImpl::hasPlayerWon(){

   return this->getGame().hasPlayerWon(this->board);
}

void PlayerImpl::setBoard(uint64_t newBoard){
    this->board = newBoard;
}

#endif