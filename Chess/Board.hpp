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
        Board();
    private:
        static bool ValidMove(string userMove);
        Piece* board[8][8];
        //1 = white to move; -1 = black to move
        int turn = -1;
        Piece* startupBoard[8][8] = {
            {new Rook(1), new Knight(1), new Bishop(1), new Queen(1), new King(1), new Bishop(1), new Knight(1), new Rook(1)},
            {new Pawn(1), new Pawn(1), new Pawn(1), new Pawn(1), new Pawn(1), new Pawn(1), new Pawn(1), new Pawn(1)},
            {new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece()},
            {new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece()},
            {new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece()},
            {new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece()},
            {new Pawn(-1), new Pawn(-1), new Pawn(-1), new Pawn(-1), new Pawn(-1), new Pawn(-1), new Pawn(-1), new Pawn(-1)},
            {new Rook(-1), new Knight(-1), new Bishop(-1), new Queen(-1), new King(-1), new Bishop(-1), new Knight(-1), new Rook(-1)}
        };
        int numberedBoard[8][8] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};
};

#endif /* Board_hpp */
