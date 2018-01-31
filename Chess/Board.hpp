//
//  Board.hpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include "Constants.h"
#include "Pawn.hpp"
#include "Piece.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Queen.hpp"

using namespace std;

class Board{
    public:
        int GetTurn(void);
        void Output(void);
        bool MovePiece(string userMove);
        static int** GetNumberedBoard(void);
        void MakeQueenAtPoint(int startFile, int startRank);
        Piece* GetPieceAtPosition(int startFile, int startRank);
        int GetCurrentPlayer();
        Board();
    protected:
        static bool ValidMove(string userMove);
        Piece* board[8][8];
        //1 = white to move; -1 = black to move
        int turn = -1;
        int currentPlayer;
};

#endif /* Board_hpp */
