//
//  main.cpp
//  Chess
//
//  Created by Nirvik Baruah on 23/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#include <iostream>
#include <string>
#include "Board.hpp"

using namespace std;

void moveGen(int file, int rank){
    //cout << numberedBoard[file][rank]<< endl;
}


int main() {
    Board board;
    board.Output();
    /*
    string userMove;
    while(1){
        output();
        cout << "Enter move e.g d2d4: ";
        cin >> userMove;
        if (validateInput(userMove)){
            int startFile;
            int startRank;
            int endFile;
            int endRank;
            startRank = userMove[0] - 'a';
            startFile = userMove[1] - '1';
            endRank = userMove[2] - 'a';
            endFile = userMove[3] - '1';
            board[endFile][endRank] = board[startFile][startRank];
            board[startFile][startRank] = 0;
            moveGen(startFile, startRank);
        }
    }*/
    return 0;
}
