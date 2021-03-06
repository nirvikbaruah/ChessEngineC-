//
//  MoveGenerator.hpp
//  Chess
//
//  Created by Nirvik Baruah on 25/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

//STATIC CLASS TO GENERATE MOVES

#ifndef MoveGenerator_hpp
#define MoveGenerator_hpp

#include <stdio.h>
#include <set>
#include <tuple>
#include <vector>
#include "Board.hpp"
#include "Constants.h"
#include "Pawn.hpp"
#include "Piece.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Queen.hpp"

//Use namespace to add behaviour of a static class
namespace MoveGenerator
{
    std::set<int> GenerateMoves(int* delta, bool isSpecialCase, int startFile, int startRank, Board* board, int curPlayer);
    bool IsCheck(Board* board, int currentPlayer);
    bool IsCheckmate(Board* board, int currentPlayer);
    std::tuple<std::vector<int>, std::vector<std::set<int>>> GenerateAllMoves(Board* board, int currentPlayer);
}

#endif /* MoveGenerator_hpp */
