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
#include <tuple>
#include "MoveGenerator.hpp"
#include <stdlib.h>

using namespace std;

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

Board::Board(void) {
    int i;
    int j;
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            board[i][j] = startupBoard[i][j];
        }
    }
    currentPlayer = 1;
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
        //std::get<1>(MoveGenerator::GenerateAllMoves(this, currentPlayer)).size()
        int startRank = userMove[0] - 'a';
        int startFile = userMove[1] - '1';
        int endRank = userMove[2] - 'a';
        int endFile = userMove[3] - '1';
        bool isSpecialCase = false;
        //Other way around as made mistake in rank and file assignment...
        if (abs(GetPieceAtPosition(startRank, startFile)->GetValue()) == 10 || abs(GetPieceAtPosition(startRank, startFile)->GetValue()) == 30 || abs(GetPieceAtPosition(startRank, startFile)->GetValue()) == 1000){
            isSpecialCase = true;
        }
        
        if (currentPlayer == GetPieceAtPosition(startRank, startFile)->GetColour() && (MoveGenerator::GenerateMoves(board[startFile][startRank]->GetDelta(), isSpecialCase, startFile, startRank, this)).count(numberedBoard[endFile][endRank])) {
            board[endFile][endRank] = board[startFile][startRank];
            board[startFile][startRank] = new Piece();
            currentPlayer *= -1;
            if (MoveGenerator::IsCheck(this, currentPlayer)){
                if (MoveGenerator::IsCheckmate(this, currentPlayer)){
                    cout << "Checkmate!" << endl;
                    if (currentPlayer == 1){
                        cout << "Black wins!" << endl;
                    }
                    else{
                        cout << "White wins!" << endl;
                    }
                }
            }
            return true;
        }
    }
    cout << "Illegal move" << endl;
    return false;
}

bool Board::ValidMove(string userMove){
    if (userMove.substr(0, 1) >= "a" && userMove.substr(0, 1) <= "h" && userMove.substr(1, 1) >= "1" && userMove.substr(1, 1) <= "8" && userMove.substr(2, 1) >= "a" && userMove.substr(2, 1) <= "h" && userMove.substr(3, 1) >= "1" && userMove.substr(3, 1) <= "8")   {
        return true;
    }
    return false;
}

int Board::GetCurrentPlayer(){
    return currentPlayer;
}

void Board::MakeQueenAtPoint(int startFile, int startRank){
    board[startFile][startRank] = new Queen(GetCurrentPlayer());
}

Piece* Board::GetPieceAtPosition(int file, int rank){
    return board[rank][file];
}

void Board::SetPieceAtPosition(int file, int rank, Piece* piece){
    board[rank][file] = piece;
}


