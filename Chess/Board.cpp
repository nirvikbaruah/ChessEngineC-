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
#include "ComputerMove.hpp"
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
    cout << "     A     B     C     D     E     F     G     H   " << endl;
    for (i = 7; i >= 0; i--){
        cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
        cout << "  |     |     |     |     |     |     |     |     |" << endl;
        cout << i + 1 << " ";
        for (j = 0; j < 8; j++){
            cout << "|  " << (*board[i][j]).GetLetter() << "  ";
        }
        cout << "|" << endl;
        cout << "  |     |     |     |     |     |     |     |     |" << endl;
    }
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    cout << endl;
}

bool Board::MovePiece(string userMove){
    if (ValidMove(userMove)){
        int startRank = userMove[0] - 'A';
        int startFile = userMove[1] - '1';
        int endRank = userMove[2] - 'A';
        int endFile = userMove[3] - '1';
        bool isSpecialCase = false;
        //Other way around as made mistake in rank and file assignment...
        if (abs(GetPieceAtPosition(startRank, startFile)->GetValue()) == 10 || abs(GetPieceAtPosition(startRank, startFile)->GetValue()) == 30 || abs(GetPieceAtPosition(startRank, startFile)->GetValue()) == 1000){
            isSpecialCase = true;
        }
        if (currentPlayer == GetPieceAtPosition(startRank, startFile)->GetColour() && (MoveGenerator::GenerateMoves(board[startFile][startRank]->GetDelta(), isSpecialCase, startFile, startRank, this, currentPlayer)).count(numberedBoard[endFile][endRank])) {
            board[endFile][endRank] = board[startFile][startRank];
            board[startFile][startRank] = new Piece();
            currentPlayer *= -1;
            return true;
        }
    }
    cout << "Illegal move" << endl;
    return false;
}

bool Board::MoveCommentary(int currentPlayer){
    if (MoveGenerator::IsCheck(this, currentPlayer)){
        cout << "Check!" << endl;
        if (MoveGenerator::IsCheckmate(this, currentPlayer)){
            cout << "Checkmate!" << endl;
            //Checmate for White so Black wins
            if (currentPlayer == 1){
                cout << "Black wins!" << endl;
            }
            else{
                cout << "White wins!" << endl;
            }
            return true;
        }
    }
    return false;
}

void Board::MoveComputer(){
    tuple<int, int> move = ComputerMove::ChooseMove(this, currentPlayer);
    int startFile = get<0>(move) % 8;
    int startRank = (get<0>(move) - startFile) / 8;
    int endFile = get<1>(move) % 8;
    int endRank = (get<1>(move) - endFile) / 8;
    //cout << startFile << " " << startRank << endl;
    //cout << endFile << " " << endRank << endl;
    board[endRank][endFile] = board[startRank][startFile];
    board[startRank][startFile] = new Piece();
    cout << "Computer has moved " << static_cast<char>('A' + startFile) << startRank+1 << static_cast<char>('A' + endFile) << endRank+1 << endl;
    currentPlayer *= -1;
}

bool Board::ValidMove(string userMove){
    if (userMove.substr(0, 1) >= "A" && userMove.substr(0, 1) <= "H" && userMove.substr(1, 1) >= "1" && userMove.substr(1, 1) <= "8" && userMove.substr(2, 1) >= "A" && userMove.substr(2, 1) <= "H" && userMove.substr(3, 1) >= "1" && userMove.substr(3, 1) <= "8")   {
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


