//
//  MoveGenerator.cpp
//  Chess
//
//  Created by Nirvik Baruah on 25/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

//STATIC CLASS TO GENERATE MOVES

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
        bool reachedEnd;
        int curPlayer = (*board).GetCurrentPlayer();
        int curRank;
        if (!isSpecialCase){
            for (int curDelta = 0; curDelta < 8; curDelta++){
                curPos = numberedBoard[file][rank];
                curFile = (curPos % 8);
                previousFile = curFile;
                curRank = ((curPos - curFile) / 8);
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
                            boardNums.insert(curPos);
                            reachedEnd = true;
                        }
                        //Stops if reached own piece
                        else if (curPlayer * ((*board).GetPieceAtPosition(curFile, curRank))->GetValue() > 0){
                            reachedEnd = true;
                        }
                        else{
                            boardNums.insert(curPos);
                        }
                        previousFile = curFile;
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
                    curPos += delta[curDelta];
                    curFile = (curPos % 8);
                    curRank = ((curPos - curFile) / 8);
                    if (curPos > 0 && curPos < 63 && abs(previousFile-curFile) <= 2 && curPlayer * ((*board).GetPieceAtPosition(curFile, curRank))->GetValue() <= 0){
                        boardNums.insert(curPos);
                    }
                }
            }
            else{
                int attackFile = curFile - 1;
                int attackRank = curRank + curPlayer;
                if (curFile > 0 && curPlayer * ((*board).GetPieceAtPosition(attackFile, attackRank))->GetValue() < 0){
                    boardNums.insert(numberedBoard[attackRank][attackFile]);
                }
                attackFile = curFile + 1;
                attackRank = curRank + curPlayer;
                if (curFile < 7 && curPlayer * ((*board).GetPieceAtPosition(attackFile, attackRank))->GetValue() < 0){
                    boardNums.insert(numberedBoard[attackRank][attackFile]);
                }
                curPos += delta[2];
                curPos += delta[3];
                if (curRank > 0 && curRank < 7){
                    //One will always be 0 so more efficient to just add both rather than
                    //use an IF statement
                    boardNums.insert(curPos);
                    curFile = (curPos % 8);
                    curRank = ((curPos - curFile) / 8);
                    if (curRank == 2 || curRank == 5){
                        curPos += delta[2];
                        curPos += delta[3];
                        boardNums.insert(curPos);
                    }
                }
            }
        }
        return boardNums;
    }
    std::set<int> GenerateAllMoves(Board* board, int player){
        std::set<int> allMoves;
        std::set<int> pieceMoves;
        bool isSpecialCase;
        for (int i = 0; i < 8; i++){
            cout << endl;
            for (int j = 0; j < 8; j++){
                //Checks if piece belongs to player
                Piece* curPiece = (*board).GetPieceAtPosition(j, i);
                isSpecialCase = false;
                if (curPiece->GetValue() * player > 0){
                    if (abs(((*board).GetPieceAtPosition(j, i))->GetValue()) == 10 || abs(((*board).GetPieceAtPosition(j, i))->GetValue()) == 30){
                        isSpecialCase = true;
                    }
                    pieceMoves = GenerateMoves(curPiece->GetDelta(), isSpecialCase, i, j, board);
                    allMoves.insert(pieceMoves.begin(), pieceMoves.end());
                }
            }
        }
        return allMoves;
    }
}
