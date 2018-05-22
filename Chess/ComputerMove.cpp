//
//  ComputerMove.cpp
//  Chess
//
//  Created by Nirvik Baruah on 7/5/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#include "ComputerMove.hpp"
#include "MoveGenerator.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <tuple>
#include "Board.hpp"
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include "Constants.h"

using namespace std;

namespace ComputerMove
{
    std::tuple<int, int> ChooseMove(Board* board, int currentPlayer){
        /*set<int> x = std::get<1>(MoveGenerator::GenerateAllMoves(this, currentPlayer)).at(1);
         cout << std::get<0>(MoveGenerator::GenerateAllMoves(this, currentPlayer)).at(1) << endl;
         for (set<int>::iterator i = x.begin(); i != x.end(); i++) {
         cout << *i << endl;
         }*/
        //cout << std::get<1>(MoveGenerator::GenerateAllMoves(this, currentPlayer)).at(4).size() << endl;
        //cout << std::get<0>(MoveGenerator::GenerateAllMoves(this, currentPlayer)).at(4) << endl;
        
        std::tuple<std::vector<int>, std::vector<std::set<int>>> allMoves = MoveGenerator::GenerateAllMoves(board, currentPlayer);
        long int numPieces = std::get<0>(allMoves).size();
        
        int previousFile;
        int previousRank;
        int curFile;
        int curRank;
        int curPos;
        Piece* tempStart;
        Piece* tempEnd;
        int bestMoveEvaluation = 10000;
        int currentEvaluation;
        std::tuple<int, int> bestMove;
        for (int a = 0; a < numPieces; a++){
            std::set<int> moves = std::get<1>(allMoves).at(a);
            long int numMoves = moves.size();
            for (set<int>::iterator i = moves.begin(); i != moves.end(); i++) {
                //Makes an inital first move to get minimax ball rolling...
                curPos = std::get<0>(allMoves).at(a);
                previousFile = curPos % 8;
                previousRank = (curPos - previousFile) / 8;
                curFile = *i % 8;
                curRank = (*i - curFile) / 8;
                tempStart = (*board).GetPieceAtPosition(previousFile, previousRank);
                tempEnd = (*board).GetPieceAtPosition(curFile, curRank);
                (*board).SetPieceAtPosition(curFile, curRank, tempStart);
                (*board).SetPieceAtPosition(previousFile, previousRank, new Piece());
                //Set search depth here - determines how many plys to think ahead
                currentEvaluation = minimax(board, currentPlayer * -1, 2, -10000, 10000);
                (*board).SetPieceAtPosition(curFile, curRank, tempEnd);
                (*board).SetPieceAtPosition(previousFile, previousRank, tempStart);
                if (currentEvaluation < bestMoveEvaluation){
                    bestMoveEvaluation = currentEvaluation;
                    bestMove = {std::get<0>(allMoves).at(a), *i};
                }
            }
        }
        return bestMove;
        
    }
    
    //Alpha-beta pruning implemented
    int minimax(Board* board, int currentPlayer, int currentDepth, int alpha, int beta){
        std::tuple<std::vector<int>, std::vector<std::set<int>>> allMoves = MoveGenerator::GenerateAllMoves(board, currentPlayer);
        long int numPieces = std::get<0>(allMoves).size();
        int previousFile;
        int previousRank;
        int curFile;
        int curRank;
        int curPos;
        int bestMove;
        Piece* tempStart;
        Piece* tempEnd;
        
        //Break if no more moves or end of Minimax tree
        if (currentDepth == 0 || numPieces <= 0){
            //Negative as black is minimizing player
            return evaluateBoard(board, currentPlayer);
        }
        
        //White wants to maximise
        if (currentPlayer == 1){
            bestMove = -10000;
            for (int a = 0; a < numPieces; a++){
                std::set<int> moves = std::get<1>(allMoves).at(a);
                long int numMoves = moves.size();
                for (set<int>::iterator i = moves.begin(); i != moves.end(); i++) {
                    //Makes temporary move
                    curPos = std::get<0>(allMoves).at(a);
                    previousFile = curPos % 8;
                    previousRank = (curPos - previousFile) / 8;
                    curFile = *i % 8;
                    curRank = (*i - curFile) / 8;
                    tempStart = (*board).GetPieceAtPosition(previousFile, previousRank);
                    tempEnd = (*board).GetPieceAtPosition(curFile, curRank);
                    (*board).SetPieceAtPosition(curFile, curRank, tempStart);
                    (*board).SetPieceAtPosition(previousFile, previousRank, new Piece());
                    bestMove = max(bestMove, minimax(board, currentPlayer * -1, currentDepth - 1, alpha, beta));
                    
                    (*board).SetPieceAtPosition(curFile, curRank, tempEnd);
                    (*board).SetPieceAtPosition(previousFile, previousRank, tempStart);
                    
                    //AB Pruning section
                    alpha = max(alpha, bestMove);
                    if (beta <= alpha) {
                        return bestMove;
                    }
                }
            }
        }
        else{
            //Black wants to minimize
            bestMove = 10000;
            for (int a = 0; a < numPieces; a++){
                std::set<int> moves = std::get<1>(allMoves).at(a);
                long int numMoves = moves.size();
                for (set<int>::iterator i = moves.begin(); i != moves.end(); i++) {
                    //Makes temporary move
                    curPos = std::get<0>(allMoves).at(a);
                    previousFile = curPos % 8;
                    previousRank = (curPos - previousFile) / 8;
                    curFile = *i % 8;
                    curRank = (*i - curFile) / 8;
                    tempStart = (*board).GetPieceAtPosition(previousFile, previousRank);
                    tempEnd = (*board).GetPieceAtPosition(curFile, curRank);
                    (*board).SetPieceAtPosition(curFile, curRank, tempStart);
                    (*board).SetPieceAtPosition(previousFile, previousRank, new Piece());
                    bestMove = min(bestMove, minimax(board, currentPlayer * -1, currentDepth - 1, alpha, beta));
                    (*board).SetPieceAtPosition(curFile, curRank, tempEnd);
                    (*board).SetPieceAtPosition(previousFile, previousRank, tempStart);
                    
                    //AB Pruning
                    beta = min(beta, bestMove);
                    if (beta <= alpha) {
                        return bestMove;
                    }
                }
            }
        }
        return bestMove;
    }
    
    int evaluateBoard(Board* board, int currentPlayer){
        int whiteTotal = 0;
        int blackTotal = 0;
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                //Checks if piece belongs to other player
                Piece* curPiece = (*board).GetPieceAtPosition(j, i);
                int pieceVal = curPiece->GetValue();
                if (pieceVal > 0){
                    whiteTotal += pieceVal;
                }
                else if (pieceVal < 0) {
                    blackTotal += pieceVal;
                }
            }
        }
        if (MoveGenerator::IsCheck(board, currentPlayer)){
            if (currentPlayer == 1){
                if (MoveGenerator::IsCheckmate(board, currentPlayer)){
                    blackTotal += -10000;
                }
                //Estimating check is worth 0.5 pawn advantage
                blackTotal += -5;
            }
            else{
                if (MoveGenerator::IsCheckmate(board, currentPlayer)){
                    whiteTotal += 10000;
                }
                whiteTotal += 5;
            }
        }
        //Black total is negative so add rather than subtract
        return whiteTotal + blackTotal;
    }
}
