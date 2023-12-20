#ifndef LOGGING
#define LOGGING
#include <iostream>
#include <fstream>
#include <thread>
#ifndef GAME_H
#include "Game.hpp"
#endif

std::ofstream myfile;

void setupLogger(){
    myfile.open ("log.txt");
}

void closeLogger(){
    myfile.close();
}

void log(std::string string){
    myfile<<std::this_thread::get_id()<<std::endl;
myfile<<string<<std::endl;
}

void displayInLog(const uint64_t redBoard, const uint64_t blueBoard) {
    myfile<<std::this_thread::get_id()<<std::endl;
myfile << "R: "<<redBoard<<std::endl;
myfile<<"B: "<<blueBoard<<std::endl;
    for (int i = 0; i < BOARD_Y_DIMENTION; i++) {
        uint64_t fixedOffset = ((BOARD_Y_DIMENTION - 1) * BOARD_X_DIMENTION) - (i * BOARD_X_DIMENTION);
        uint64_t offset = (uint64_t)1 << fixedOffset;

        myfile << '|';
        for (int j = 0; j < BOARD_X_DIMENTION; j++) {

            if (offset & redBoard) {
                myfile << 'R';
            }
            else if (offset & blueBoard) {
                myfile << 'B';
            }
            else {
                myfile << ' ';
            }
            offset <<= 1;
            myfile << '|';
        }
        myfile << std::endl;
    }
}
#endif