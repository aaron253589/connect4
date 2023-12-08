
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#ifndef GAME_C
#include "Game.hpp"
#endif
#ifndef PLAYER_C
#include "PlayerImpl.hpp"
#endif
// constexpr auto BOARD_X_DIMENTION = 7;
// constexpr auto BOARD_Y_DIMENTION = 6;
// constexpr auto WINNING_LENGTH = 4;
constexpr auto MAX_DEPTH = 5;
#define DEBUG true




// uint64_t extractCoordinates(const int column, const uint64_t bitMap) {
//     for (int i = 0; i < BOARD_Y_DIMENTION; i++) {
//         uint64_t value = (uint64_t)1 << (BOARD_X_DIMENTION*i+column);
//         if (!(value & bitMap)) {
//             return value;
//         }
//     }
//     throw __cpp_exceptions;
// }

// void display(const uint64_t redBoard, const uint64_t blueBoard) {

//     for (int i = 0; i < BOARD_Y_DIMENTION; i++) {
//         uint64_t fixedOffset = ((BOARD_Y_DIMENTION - 1) * BOARD_X_DIMENTION) - (i * BOARD_X_DIMENTION);
//         uint64_t offset = (uint64_t)1 << fixedOffset;

//         std::cout << '|';
//         for (int j = 0; j < BOARD_X_DIMENTION; j++) {

//             if (offset & redBoard) {
//                 std::cout << 'R';
//             }
//             else if (offset & blueBoard) {
//                 std::cout << 'B';
//             }
//             else {
//                 std::cout << ' ';
//             }
//             offset <<= 1;
//             std::cout << '|';
//         }
//         std::cout << std::endl;
//     }
// }

// #if DEBUG
// void displayInLog(const uint64_t redBoard, const uint64_t blueBoard) {

//     for (int i = 0; i < BOARD_Y_DIMENTION; i++) {
//         uint64_t fixedOffset = ((BOARD_Y_DIMENTION - 1) * BOARD_X_DIMENTION) - (i * BOARD_X_DIMENTION);
//         uint64_t offset = (uint64_t)1 << fixedOffset;

//         myfile << '|';
//         for (int j = 0; j < BOARD_X_DIMENTION; j++) {

//             if (offset & redBoard) {
//                 myfile << 'R';
//             }
//             else if (offset & blueBoard) {
//                 myfile << 'B';
//             }
//             else {
//                 myfile << ' ';
//             }
//             offset <<= 1;
//             myfile << '|';
//         }
//         myfile << std::endl;
//     }
// }
// #endif

// bool hasPlayerWon(const uint64_t board,const std::vector<uint64_t>& winningPositions){

//     for(uint64_t positionIndex = 0; positionIndex < winningPositions.size(); positionIndex++) {
//         if ((board & winningPositions[positionIndex] ) == winningPositions[positionIndex]) {
//             return true;
//         }
//     }

//     return false;
// }

// std::vector<uint64_t>* getPostitions(const int steakLength) {

//     std::vector<uint64_t>* winningPositions = new std::vector<uint64_t>;

//     uint64_t horizontalWinningSteak = 0;
//     uint64_t verticalWinningStreak = 0;
//     uint64_t bottomLeftToTopRight = 0;
//     uint64_t bottomRightToTopLeft = 0;

//     for (int i = 0; i < steakLength; i++) {
//         horizontalWinningSteak += (uint64_t)1 << i;
//         verticalWinningStreak += (uint64_t)1 << (i * BOARD_X_DIMENTION);
//         bottomLeftToTopRight += (uint64_t)1 << ((i * BOARD_X_DIMENTION) + i);
//         bottomRightToTopLeft += (uint64_t)1 << (((steakLength -1-i) * BOARD_X_DIMENTION) + i);
//     }

//     winningPositions->push_back(verticalWinningStreak);

//     //horizontal
//     for (int i = 0; i < BOARD_Y_DIMENTION; i++) {
//         winningPositions->push_back(horizontalWinningSteak);
//         for (int j = 0; j < BOARD_X_DIMENTION - steakLength; j++) {
//             horizontalWinningSteak <<= 1;
//             winningPositions -> push_back(horizontalWinningSteak);
//         }
//         horizontalWinningSteak <<= steakLength;
//     }

//     //vertical
//     for (int i = 0; i < (BOARD_Y_DIMENTION-steakLength+1) * (BOARD_X_DIMENTION) - 1; i++) {
//             verticalWinningStreak <<= 1;
//             winningPositions->push_back(verticalWinningStreak);
//         }

//     //diagonals
//     for (int i = 0; i < BOARD_Y_DIMENTION- steakLength +1; i++) {
//         winningPositions->push_back(bottomLeftToTopRight);
//         winningPositions->push_back(bottomRightToTopLeft);
//         for (int j = 0; j < BOARD_X_DIMENTION - steakLength; j++) {
//             bottomLeftToTopRight <<= 1;
//             winningPositions->push_back(bottomLeftToTopRight);
//             bottomRightToTopLeft <<= 1;
//             winningPositions->push_back(bottomRightToTopLeft);
//         }
//         bottomLeftToTopRight <<= steakLength;
//         bottomRightToTopLeft <<= steakLength;
//     }
  
// #if DEBUG
//     std::for_each(winningPositions->cbegin(), winningPositions->cend(),
//         [](const uint64_t& position) {
//             displayInLog(position, position);
//             myfile << std::endl; 
//         });
// #endif
//     return winningPositions;
// }

// char getNextPlayer(const char current){
//     if (current == 'R') {
//         return 'B';
//     }
//     else {
//         return 'R'; }
// }

// uint8_t getProximity(const uint64_t a, const uint64_t b){
//     uint64_t temp = (a & b);
//     int count = 0;
//     while (temp > 0) {
//         if ((uint64_t)1 & temp) {
//             count++;
//         }       
//         temp >>= 1;

//     }

//     if (count == WINNING_LENGTH) {
//         return LONG_MAX;
//     }
//     else if (count == WINNING_LENGTH - 1) {
//         return 200;
//     }
//     else {
//         return count;
//     }
// }

// long getPlayerScore(const uint64_t currentPlayerBoard, const uint64_t oppositionPlayerBoard, const std::vector<uint64_t>& winningPositions) {
//     long positiveScore = 0;
//     for (int i = 0; i < winningPositions.size(); i++) {
//         if (winningPositions[i] & oppositionPlayerBoard) {
//             continue;
//         }
//         positiveScore += getProximity(winningPositions[i], currentPlayerBoard);
//     }
//     return positiveScore;
// }

// long getOverallScore(const uint64_t currentPlayerBoard, const uint64_t oppositionPlayerBoard, const std::vector<uint64_t>& winningPositions) {
//   auto score = getPlayerScore(currentPlayerBoard, oppositionPlayerBoard, winningPositions) - getPlayerScore(oppositionPlayerBoard, currentPlayerBoard, winningPositions);
// #if DEBUG
//   myfile << "Overall Score:" << std::endl;
//   myfile << "score: " << score << std::endl;
// #endif
//   return score;
// }

// long playNextMove(uint64_t playerA, uint64_t playerB, int depth, bool playerIndicator, const std::vector<uint64_t>& winningPositions) {


//     /*
//     a b

//     for each column
//     new a move
//     if game over return score for a
//     if depth return score for a
//     get next move

//     get best worst


//     */
    
//     long *scores = new long[BOARD_X_DIMENTION];
    
//     for (int i = 0; i < BOARD_X_DIMENTION; i++) {
//         if ((uint64_t)1 << ((BOARD_Y_DIMENTION - 1) * BOARD_X_DIMENTION + i) & (playerB|playerA)) {
//             continue;
//         }

//         uint64_t newState = playerB | extractCoordinates(i, playerA | playerB);
      
// #if DEBUG
//         displayInLog(playerIndicator ? newState : playerA, playerIndicator ? playerA : newState);
// #endif
//         if (hasPlayerWon(newState, winningPositions)) {
//             return LONG_MAX;
//         }
//         if (depth > MAX_DEPTH) {
// #if DEBUG
//             myfile << "depthReached" << std::endl;
//             displayInLog(newState, playerA);

// #endif
//             scores[i] = getOverallScore(newState, playerA, winningPositions);
//         }
//    //     std::cout << "depth: " << depth << " i: " << i << std::endl;
//         else { scores[i] = -playNextMove(newState, playerA, depth + 1, !playerIndicator, winningPositions); }
//   //      std::cout << scores[i] << std::endl;
//     }
// //    std::cout << std::endl;
// #if DEBUG
//     myfile << "Depth: " << depth << std::endl;
//     myfile << "scores" << std::endl;
//     for (int i = 0; i < BOARD_X_DIMENTION; i++) {
//         myfile << scores[i] << " ";
//     }
//     myfile << std::endl;
// #endif
   
//     int temp = NULL;
//     for (int i = 0; i < BOARD_X_DIMENTION; i++) {
//         if (scores[i] == NULL) { continue; }
//         if (temp == NULL) {
//             temp = i;
//             continue;
//         }
//         if (scores[i] > scores[temp]) {
//             temp = i;
//         }
//     }
//  //   std::cout<<"depth "<<depth<<" chosen column:" <<temp<<std::endl;

//     long score = temp != NULL ? scores[temp] : BOARD_X_DIMENTION;
//     delete[] scores;
//     return score;

// }

// int getNextMove(uint64_t currentPlayerState, uint64_t oppositionPlayerState, const std::vector<uint64_t>& winningPositions){
//     long scores[BOARD_X_DIMENTION];
//     for (int i = 0; i < BOARD_X_DIMENTION; i++) {
//         uint64_t newState = currentPlayerState | extractCoordinates(i, currentPlayerState | oppositionPlayerState);
//         if (hasPlayerWon(newState, winningPositions)) {
//             return i;
//         }
//         else {
//             scores[i] = -playNextMove(newState, oppositionPlayerState, 0, true, winningPositions);
//         }
//     }
//     int temp = 0;
//     myfile << "scoresa: "<<scores[temp]<<" ";
//     for (int i = 1; i < BOARD_X_DIMENTION; i++) {
//         if (scores[i] > scores[temp]) {
//             temp = i;
//         }
//         myfile << scores[i] << " ";
//     }
//     myfile << std::endl;
//     myfile << "chosen: " <<temp<< std::endl;
//     return temp;
// }

int main()
{

  

    // std::vector<uint64_t>* winningPositions = getPostitions(WINNING_LENGTH); 


    while (1) {
        std::cout << "New Game: " << std::endl;


        std::cout << "Enter name for Player 1:"<<std::endl;
std::string player1Name;
        std::cin>>player1Name;

        std::cout << "Enter name for Player 2:"<<std::endl;
std::string player2Name;
        std::cin>>player2Name;
Game* game;
              game = new GameImpl(player1Name);
        

        game->display();
while(1){
        game->getPlayer1().nextMove();
        if(game->getPlayer1().hasPlayerWon()){
            std::cout<<game->getPlayer1().getPlayerName()<<" has won"<<std::endl;
            delete game;
            break;
        }
        // std::cout<<"player1: "<<game->getPlayer1().getBoard()<<std::endl;
                game->display();
        
        game->getPlayer2().nextMove();
        if(game->getPlayer2().hasPlayerWon()){
            std::cout<<game->getPlayer2().getPlayerName()<<" has won"<<std::endl;
            delete game;
            break;
        }
                // std::cout<<"player2: "<<game->getPlayer2().getBoard()<<std::endl;
                game->display();

        }
        
//         uint64_t red_board = 0;
//         uint64_t blue_board = 0;
//         char player = 'R';

//         while (1) {
//             //wait for move
//             std::cout << player <<"'s move:" << std::endl;
//             display(red_board, blue_board);
//             std::cout << " 0 1 2 3 4 5 6" << std::endl;

//             int column;
//             std::cin >> column;

//             uint64_t coordinates = extractCoordinates(column, red_board | blue_board);
// #if(DEBUG)
//             myfile <<"coordinates: " << coordinates << std::endl;
// #endif

//             player == 'R' ? red_board |= coordinates : blue_board |= coordinates;

            

//             bool hasWon = hasPlayerWon(player == 'R' ? red_board : blue_board, *winningPositions);


//             display(red_board, blue_board);
// #if DEBUG
//             myfile<<"Red score: "<<getOverallScore(red_board, blue_board, *winningPositions)<<std::endl;
//             myfile << "Blue score: " << getOverallScore(blue_board, red_board, *winningPositions)<<std::endl;
// #endif
//             if (hasWon) {
//                 std::cout << "Game over, winner: " << player << std::endl;
//                 break;
//             }
//             player = getNextPlayer(player);
//             column = getNextMove(blue_board, red_board, *winningPositions);
//             uint64_t x = extractCoordinates(column, red_board | blue_board);
//             blue_board |= x;
    
//             if (hasPlayerWon(player == 'R' ? red_board : blue_board, *winningPositions)) {
//                 display(red_board, blue_board);
//                 std::cout << "Game over, winner: " << player << std::endl;
//                 break;
//             }
//             player = getNextPlayer(player);
//         }
    }
    myfile.close();

}
