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
    string userMove;
    while(1){
        board.Output();
        cout << "Enter move e.g d2d4: ";
        cin >> userMove;
        board.MovePiece(userMove);
    }
    return 0;
}
