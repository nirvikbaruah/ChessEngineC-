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
        
        int test = rand() % numPieces;
        
        for (int a = 0; a < numPieces; a++){
            std::set<int> moves = std::get<1>(allMoves).at(a);
            if (a == test){
                long int numMoves = moves.size();
                int randomMove = rand() % numMoves;
                int count = 0;
                for (set<int>::iterator i = moves.begin(); i != moves.end(); i++) {
                    if (count == randomMove){
                        return std::tuple<int, int> {std::get<0>(allMoves).at(a), *i};
                    }
                    count += 1;
                }
            }
        }
        return std::tuple<int, int> {1, 1};
    }
}
