//
//  ComputerMove.hpp
//  Chess
//
//  Created by Nirvik Baruah on 7/5/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#ifndef ComputerMove_hpp
#define ComputerMove_hpp

#include <stdio.h>
#include <tuple>
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
namespace ComputerMove
{
    std::tuple<int, int>ChooseMove(Board* board, int currentPlayer);
    int evaluateBoard(Board* board, int currentPlayer);
}
#endif /* ComputerMove_hpp */
