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

    
        //int test = rand() % numPieces;
        int previousFile;
        int previousRank;
        int curFile;
        int curRank;
        int curPos;
        Piece* tempStart;
        Piece* tempEnd;
        int min = 50000;
        int evaluation;
        std::tuple<int, int> bestMove;
        for (int a = 0; a < numPieces; a++){
            std::set<int> moves = std::get<1>(allMoves).at(a);
            long int numMoves = moves.size();
            for (set<int>::iterator i = moves.begin(); i != moves.end(); i++) {
                curPos = std::get<0>(allMoves).at(a);
                previousFile = curPos % 8;
                previousRank = (curPos - previousFile) / 8;
                curFile = *i % 8;
                curRank = (*i - curFile) / 8;
                tempStart = (*board).GetPieceAtPosition(previousFile, previousRank);
                tempEnd = (*board).GetPieceAtPosition(curFile, curRank);
                (*board).SetPieceAtPosition(curFile, curRank, tempStart);
                (*board).SetPieceAtPosition(previousFile, previousRank, new Piece());
                evaluation = evaluateBoard(board, currentPlayer * -1);
                if (evaluation < min){
                    min = evaluation;
                    bestMove = {std::get<0>(allMoves).at(a), *i};
                }
                (*board).SetPieceAtPosition(curFile, curRank, tempEnd);
                (*board).SetPieceAtPosition(previousFile, previousRank, tempStart);
            }
        }
        return bestMove;
    }
    
    int evaluateBoard(Board* board, int currentPlayer){
        int total = 0;
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                //Checks if piece belongs to player
                Piece* curPiece = (*board).GetPieceAtPosition(j, i);
                int pieceVal = curPiece->GetValue() * currentPlayer;
                if (pieceVal > 0){
                    total += pieceVal;
                }
            }
        }
        return total;
    }
}
