//
//  MoveGenerator.cpp
//  Chess
//
//  Created by Nirvik Baruah on 25/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

//STATIC CLASS TO GENERATE MOVES
//TODO: CHECK IF PAWN CAN CHECK KING

#include "MoveGenerator.hpp"
#include <iostream>
#include <set>
#include "Board.hpp"
#include <stdlib.h>
#include "Constants.h"

namespace MoveGenerator
{
    std::set<int> GenerateMoves(int* delta, bool isSpecialCase, int file, int rank, Board* board){
        //TAKE OCCUPIED SQUARES AS ARRAY
        std::set<int> boardNums;
        int curPos = numberedBoard[file][rank];
        int curFile;
        int previousFile;
        int previousRank;
        bool reachedEnd;
        int curPlayer = (*board).GetCurrentPlayer();
        int curRank;
        Piece* tempStart;
        Piece* tempEnd;
        if (!isSpecialCase){
            for (int curDelta = 0; curDelta < 8; curDelta++){
                curPos = numberedBoard[file][rank];
                curFile = (curPos % 8);
                previousFile = curFile;
                curRank = ((curPos - curFile) / 8);
                previousRank = curRank;
                reachedEnd = false;
                if (delta[curDelta] != 0){
                    while (reachedEnd != true){
                        curPos += delta[curDelta];
                        curFile = (curPos % 8);
                        curRank = ((curPos - curFile) / 8);
                        //Maximum of 2 file move so check doesn't wrap around board
                        if (curPos < 0 || curPos > 63 || abs(previousFile-curFile) > 2){
                            reachedEnd = true;
                        }
                        //Check if taking different player piece
                        else if (curPlayer * ((*board).GetPieceAtPosition(curFile, curRank))->GetValue() < 0){
                            tempStart = (*board).GetPieceAtPosition(previousFile, previousRank);
                            tempEnd = (*board).GetPieceAtPosition(curFile, curRank);
                            (*board).SetPieceAtPosition(curFile, curRank, tempStart);
                            (*board).SetPieceAtPosition(previousFile, previousRank, new Piece());
                            if (IsCheck(board, curPlayer)){
                                reachedEnd = true;
                            }
                            else{
                                boardNums.insert(curPos);
                            }
                            (*board).SetPieceAtPosition(curFile, curRank, tempEnd);
                            (*board).SetPieceAtPosition(previousFile, previousRank, tempStart);
                        }
                        //Stops if reached own piece
                        else if (curPlayer * ((*board).GetPieceAtPosition(curFile, curRank))->GetValue() > 0){
                            reachedEnd = true;
                        }
                        else{
                            tempStart = (*board).GetPieceAtPosition(previousFile, previousRank);
                            tempEnd = (*board).GetPieceAtPosition(curFile, curRank);
                            (*board).SetPieceAtPosition(curFile, curRank, tempStart);
                            (*board).SetPieceAtPosition(previousFile, previousRank, new Piece());
                            if (IsCheck(board, curPlayer)){
                                reachedEnd = true;
                            }
                            else{
                                boardNums.insert(curPos);
                            }
                            (*board).SetPieceAtPosition(curFile, curRank, tempEnd);
                            (*board).SetPieceAtPosition(previousFile, previousRank, tempStart);
                        }
                        previousFile = curFile;
                        previousRank = curRank;
                    }
                }
            }
        } else{
            curPos = numberedBoard[file][rank];
            curFile = (curPos % 8);
            curRank = ((curPos - curFile) / 8);
            if (abs((*board).GetPieceAtPosition(curFile, curRank)->GetValue()) == 30){
                for (int curDelta = 0; curDelta < 8; curDelta++){
                    //Only iterate once for knights
                    curPos = numberedBoard[file][rank];
                    previousFile = (curPos % 8);
                    previousRank = ((curPos - curFile) / 8);
                    curPos += delta[curDelta];
                    curFile = (curPos % 8);
                    curRank = ((curPos - curFile) / 8);
                    if (curPos > 0 && curPos < 63 && abs(previousFile-curFile) <= 2 && curPlayer * ((*board).GetPieceAtPosition(curFile, curRank))->GetValue() <= 0){
                        tempStart = (*board).GetPieceAtPosition(previousFile, previousRank);
                        tempEnd = (*board).GetPieceAtPosition(curFile, curRank);
                        (*board).SetPieceAtPosition(curFile, curRank, tempStart);
                        (*board).SetPieceAtPosition(previousFile, previousRank, new Piece());
                        if (IsCheck(board, curPlayer)){
                            (*board).SetPieceAtPosition(curFile, curRank, tempEnd);
                            (*board).SetPieceAtPosition(previousFile, previousRank, tempStart);
                            break;
                            //Pinned piece so break out of loop
                        }
                        else{
                            (*board).SetPieceAtPosition(curFile, curRank, tempEnd);
                            (*board).SetPieceAtPosition(previousFile, previousRank, tempStart);
                            boardNums.insert(curPos);
                        }
                    }
                }
            }
            else{
                int attackFile = curFile - 1;
                int attackRank = curRank + curPlayer;
                if (attackFile >= 0 && curPlayer * ((*board).GetPieceAtPosition(attackFile, attackRank))->GetValue() < 0){
                    tempStart = (*board).GetPieceAtPosition(curFile, curRank);
                    tempEnd = (*board).GetPieceAtPosition(attackFile, attackRank);
                    (*board).SetPieceAtPosition(attackFile, attackRank, tempStart);
                    (*board).SetPieceAtPosition(curFile, curRank, new Piece());
                    if (!IsCheck(board, curPlayer)){
                        boardNums.insert(numberedBoard[attackRank][attackFile]);
                    }
                    (*board).SetPieceAtPosition(attackFile, attackRank, tempEnd);
                    (*board).SetPieceAtPosition(curFile, curRank, tempStart);
                }
                attackFile = curFile + 1;
                attackRank = curRank + curPlayer;
                if (attackFile <= 7 && curPlayer * ((*board).GetPieceAtPosition(attackFile, attackRank))->GetValue() < 0){
                    tempStart = (*board).GetPieceAtPosition(curFile, curRank);
                    tempEnd = (*board).GetPieceAtPosition(attackFile, attackRank);
                    (*board).SetPieceAtPosition(attackFile, attackRank, tempStart);
                    (*board).SetPieceAtPosition(curFile, curRank, new Piece());
                    if (!IsCheck(board, curPlayer)){
                        boardNums.insert(numberedBoard[attackRank][attackFile]);
                    }
                    (*board).SetPieceAtPosition(attackFile, attackRank, tempEnd);
                    (*board).SetPieceAtPosition(curFile, curRank, tempStart);
                }
                previousFile = curFile;
                previousRank = curRank;
                curPos += delta[2];
                curPos += delta[3];
                if (curRank > 0 && curRank < 7){
                    //One will always be 0 so more efficient to just add both rather than
                    //use an IF statement
                    curFile = (curPos % 8);
                    curRank = ((curPos - curFile) / 8);
                    tempStart = (*board).GetPieceAtPosition(previousFile, previousRank);
                    tempEnd = (*board).GetPieceAtPosition(curFile, curRank);
                    (*board).SetPieceAtPosition(curFile, curRank, tempStart);
                    (*board).SetPieceAtPosition(previousFile, previousRank, new Piece());
                    if (!IsCheck(board, curPlayer)){
                        boardNums.insert(curPos);
                    }
                    (*board).SetPieceAtPosition(curFile, curRank, tempEnd);
                    (*board).SetPieceAtPosition(previousFile, previousRank, tempStart);
                    
                    previousFile = curFile;
                    previousRank = curRank;
                    
                    if (curRank == 2 && ((*board).GetPieceAtPosition(curFile, 3))->GetValue() == 0){
                        curPos += delta[2];
                        curFile = (curPos % 8);
                        curRank = ((curPos - curFile) / 8);
                        tempStart = (*board).GetPieceAtPosition(previousFile, previousRank);
                        tempEnd = (*board).GetPieceAtPosition(curFile, curRank);
                        (*board).SetPieceAtPosition(curFile, curRank, tempStart);
                        (*board).SetPieceAtPosition(previousFile, previousRank, new Piece());
                        if (!IsCheck(board, curPlayer)){
                            boardNums.insert(curPos);
                        }
                        (*board).SetPieceAtPosition(curFile, curRank, tempEnd);
                        (*board).SetPieceAtPosition(previousFile, previousRank, tempStart);
                    } else if (curRank == 5 && ((*board).GetPieceAtPosition(curFile, 4))->GetValue() == 0){
                        curPos += delta[3];
                        curFile = (curPos % 8);
                        curRank = ((curPos - curFile) / 8);
                        tempStart = (*board).GetPieceAtPosition(previousFile, previousRank);
                        tempEnd = (*board).GetPieceAtPosition(curFile, curRank);
                        (*board).SetPieceAtPosition(curFile, curRank, tempStart);
                        (*board).SetPieceAtPosition(previousFile, previousRank, new Piece());
                        if (!IsCheck(board, curPlayer)){
                            boardNums.insert(curPos);
                        }
                        (*board).SetPieceAtPosition(curFile, curRank, tempEnd);
                        (*board).SetPieceAtPosition(previousFile, previousRank, tempStart);
                    }
                }
            }
        }
        return boardNums;
    }
    
    bool IsCheckmate(Board* board, int currentPlayer){
        int kingPos = 0;
        int kingCol = 0;
        int kingRow = 0;
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                //Checks if piece belongs to player
                Piece* curPiece = (*board).GetPieceAtPosition(j, i);
                if (curPiece->GetValue() * currentPlayer == 1000){
                    kingPos = i*8+j;
                    kingRow = i;
                    kingCol = j;
                    break;
                }
            }
        }
        if ((GenerateMoves(((*board).GetPieceAtPosition(kingCol, kingRow))->GetDelta(), false, kingRow, kingCol, board)).size() == 0){
            return true;
        }
        return false;
    }
    
    bool IsCheck(Board* board, int currentPlayer){
        int kingPos = 0;
        int kingCol = 0;
        int kingRow = 0;
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                //Checks if piece belongs to player
                Piece* curPiece = (*board).GetPieceAtPosition(j, i);
                if (curPiece->GetValue() * currentPlayer == 1000){
                    kingPos = i*8+j;
                    kingRow = i;
                    kingCol = j;
                    break;
                }
            }
        }
        //Check upwards
        int newRow = kingRow + 1;
        while (newRow < 8 && ((*board).GetPieceAtPosition(kingCol, newRow))->GetValue() == 0){
            newRow++;
        }
        if (newRow < 8 && (((currentPlayer * ((*board).GetPieceAtPosition(kingCol, newRow))->GetValue()) == -50) || ((currentPlayer * ((*board).GetPieceAtPosition(kingCol, newRow))->GetValue()) == -90))){
            cout << "Straight up check" << endl;
            return true;
        }
        
        //Check downwards
        newRow = kingRow - 1;
        while (newRow >= 0 && ((*board).GetPieceAtPosition(kingCol, newRow))->GetValue() == 0){
            newRow--;
        }
        if (newRow >= 0 && (((currentPlayer * ((*board).GetPieceAtPosition(kingCol, newRow))->GetValue()) == -50) || ((currentPlayer * ((*board).GetPieceAtPosition(kingCol, newRow))->GetValue()) == -90))){
            cout << "Straight down check" << endl;
            return true;
        }
        
        //Check right row
        int newCol = kingCol + 1;
        while (newCol < 8 && ((*board).GetPieceAtPosition(newCol, kingRow))->GetValue() == 0){
            newCol++;
        }
        if (newCol < 8 && (((currentPlayer * ((*board).GetPieceAtPosition(newCol, kingRow))->GetValue()) == -50) || ((currentPlayer * ((*board).GetPieceAtPosition(newCol, kingRow))->GetValue()) == -90))){
            cout << "Straight right check" << endl;
            return true;
        }
        
        //Check left row
        newCol = kingCol - 1;
        while (newCol >= 0 && ((*board).GetPieceAtPosition(newCol, kingRow))->GetValue() == 0){
            newCol--;
        }
        if (newCol >= 0 && (((currentPlayer * ((*board).GetPieceAtPosition(newCol, kingRow))->GetValue()) == -50) || ((currentPlayer * ((*board).GetPieceAtPosition(newCol, kingRow))->GetValue()) == -90))){
            cout << "Straight left check" << endl;
            return true;
        }
        
        //Check right-up diagonal
        newCol = kingCol + 1;
        newRow = kingRow + 1;
        while (newCol < 8 && newRow < 8 && ((*board).GetPieceAtPosition(newCol, newRow))->GetValue() == 0){
            newCol++;
            newRow++;
        }
        if (newCol < 8 && newRow < 8 && (((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -90) || ((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -35))){
            cout << "Straight right-up check" << endl;
            return true;
        }
        
        //Check right-down diagonal
        newCol = kingCol + 1;
        newRow = kingRow - 1;
        while (newCol < 8 && newRow >= 0 && ((*board).GetPieceAtPosition(newCol, newRow))->GetValue() == 0){
            newCol++;
            newRow--;
        }
        if (newCol < 8 && newRow >= 0 && (((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -90) || ((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -35))){
            cout << "Straight right-down check" << endl;
            return true;
        }
        
        //Check left-up diagonal
        newCol = kingCol - 1;
        newRow = kingRow + 1;
        while (newCol >= 0 && newRow < 8 && ((*board).GetPieceAtPosition(newCol, newRow))->GetValue() == 0){
            newCol--;
            newRow++;
        }
        if (newCol >= 0 && newRow < 8 && (((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -90) || ((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -35))){
            cout << "Straight left-up check" << endl;
            return true;
        }
        
        //Check left-down diagonal
        newCol = kingCol - 1;
        newRow = kingRow - 1;
        while (newCol >= 0 && newRow >= 0 && ((*board).GetPieceAtPosition(newCol, newRow))->GetValue() == 0){
            newCol--;
            newRow--;
        }
        if (newCol >= 0 && newRow >= 0 && (((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -90) || ((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -35))){
            cout << "Straight left-down check" << endl;
            return true;
        }
        
        //Check top-right knight
        newCol = kingCol + 1;
        newRow = kingRow + 2;
        if (newCol < 8 && newRow < 8 && ((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -30)){
            cout << "Top-right knight check" << endl;
            return true;
        }
        
        //Check top-left knight
        newCol = kingCol - 1;
        newRow = kingRow + 2;
        if (newCol >= 0 && newRow < 8 && ((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -30)){
            cout << "Top-left knight check" << endl;
            return true;
        }
        
        //Check right-top knight
        newCol = kingCol + 2;
        newRow = kingRow + 1;
        if (newCol < 8 && newRow < 8 && ((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -30)){
            cout << "right-top knight check" << endl;
            return true;
        }
        
        //Check right-bottom knight
        newCol = kingCol + 2;
        newRow = kingRow - 1;
        if (newCol < 8 && newRow >= 0 && ((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -30)){
            cout << "right-bottom knight check" << endl;
            return true;
        }
        
        //Check left-top knight
        newCol = kingCol - 2;
        newRow = kingRow + 1;
        if (newCol >= 0 && newRow < 8 && ((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -30)){
            cout << "left-top knight check" << endl;
            return true;
        }
        
        //Check left-bottom knight
        newCol = kingCol - 2;
        newRow = kingRow - 1;
        if (newCol >= 0 && newRow >= 0 && ((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -30)){
            cout << "left-bottom knight check" << endl;
            return true;
        }
        
        //Check bottom-left knight
        newCol = kingCol - 1;
        newRow = kingRow - 2;
        if (newCol >= 0 && newRow >= 0 && ((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -30)){
            cout << "bottom-left knight check" << endl;
            return true;
        }
        
        //Check bottom-right knight
        newCol = kingCol + 1;
        newRow = kingRow - 2;
        if (newCol < 8 && newRow >= 0 && ((currentPlayer * ((*board).GetPieceAtPosition(newCol, newRow))->GetValue()) == -30)){
            cout << "bottom-right knight check" << endl;
            return true;
        }
        return false;
    }
}

