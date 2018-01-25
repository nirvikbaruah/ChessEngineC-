//
//  Board.cpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#include "Board.hpp"
#include "Constants.h"
#include <iostream>
#include <string>

using namespace std;

Board::Board(void) {
    int i;
    int j;
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            board[i][j] = startupBoard[i][j];
        }
    }
}

int Board::GetTurn(void) {
    return turn;
}

//Print board
void Board::Output(void){
    int i;
    int j;
    string piece;
    //Iterate downwards so it prints from white's perspective
    for (i = 7; i >= 0; i--){
        cout << endl;
        for (j = 0; j < 8; j++){
            cout << " " << (*board[i][j]).GetLetter() << " ";
        }
    }
    cout << endl << endl;
}

bool Board::MovePiece(string userMove){
    if (ValidMove(userMove)){
        int startRank = userMove[0] - 'a';
        int startFile = userMove[1] - '1';
        int endRank = userMove[2] - 'a';
        int endFile = userMove[3] - '1';
        board[endFile][endRank] = board[startFile][startRank];
        board[startFile][startRank] = new Piece();
        return true;
    }
    return false;
}

bool Board::ValidMove(string userMove){
    if (userMove.substr(0, 1) >= "a" && userMove.substr(0, 1) <= "h" && userMove.substr(1, 1) >= "1" && userMove.substr(1, 1) <= "8" && userMove.substr(2, 1) >= "a" && userMove.substr(2, 1) <= "h" && userMove.substr(3, 1) >= "1" && userMove.substr(3, 1) <= "8")   {
        return true;
    }
    return false;
}
