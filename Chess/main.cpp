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
#include "ComputerMove.hpp"

using namespace std;

int main() {
    Board board;
    string userMove;
    //srand(time(NULL));
    bool legalMove;
    while(1){
        legalMove = false;
        board.Output();
        do{
            cout << "Enter move e.g D2D4: ";
            cin >> userMove;
            legalMove = board.MovePiece(userMove);
        } while (legalMove == false);
        board.MoveComputer();
    }
    return 0;
}
