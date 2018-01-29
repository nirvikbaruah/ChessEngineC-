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
        bool reachedEnd = false;
        int curRank;
        
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
                    if (curPos < 0 || curPos > 63 || ((*board).GetPieceAtPosition(curFile, curRank))->GetValue() != 0 || abs(previousFile-curFile) > 2){
                        reachedEnd = true;
                    }
                    else{
                        boardNums.insert(curPos);
                    }
                    previousFile = curFile;
                }
            }
        }
        //std::cout << ((*board).GetPieceAtPosition(3, 7))->GetValue() << std::endl;
        return boardNums;

    }
}
