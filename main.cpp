#ifndef MAIN
#define MAIN

#include <iostream>
#include <stdio.h>

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include "Router.h"
#ifndef LOGGING
    #include "LoggingUtil.cpp"
#endif
#ifndef GAME_C
    #include "Game.cpp"
#endif
#ifndef PLAYER_C
    #include "PlayerImpl.hpp"
#endif
#ifndef SOCKET_C
    #include "Serverlet.cpp"
#endif
#ifndef RESPONSE_H
    #include "Response.h"
#endif

Response func(std::string s){
    return Response();
}

int main()
{
    Router* r = new Router();
    r->add(Router::HttpMethod::GET, "board", func);
    Serverlet socket = Serverlet();
    socket.socketFlow();
//     setupLogger();

//     while (1) {
//         std::cout << "New Game: " << std::endl;

//         std::cout << "Enter name for Player 1:"<<std::endl;
// std::string player1Name;
//         std::getline(std::cin, player1Name);player1Name;

//         std::cout << "Enter name for Player 2:"<<std::endl;
// std::string player2Name;
//         std::getline(std::cin,player2Name);
// Game* game;
// if(player2Name.empty()){
//               game = new GameImpl(player1Name);}
//               else{
//                 game = new GameImpl(player1Name, player2Name);
//               }
        

//         game->display();
// while(1){
//         game->getPlayer1().nextMove();
//         if(game->getPlayer1().hasPlayerWon()){
//             std::cout<<game->getPlayer1().getPlayerName()<<" has won"<<std::endl;
//             break;
//         }
//         std::cout<<game->getPlayer1().getPlayerName()<<std::endl;
//                 std::cout<<game->getPlayer2().getPlayerName()<<std::endl;
//                 game->display();
//         game->getPlayer2().nextMove();

//         if(game->getPlayer2().hasPlayerWon()){
//             std::cout<<game->getPlayer2().getPlayerName()<<" has won"<<std::endl;
//             break;
//         }
//                 game->display();

//         }
//         game->display();
//         delete game;
//     }
//     closeLogger();
}
#endif