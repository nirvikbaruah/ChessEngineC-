//
//  MoveGenerator.cpp
//  Chess
//
//  Created by Nirvik Baruah on 25/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

//STATIC CLASS TO GENERATE MOVES

#include "MoveGenerator.hpp"

class MoveGenerator
{
public:
    static int* GenerateMoves(int* delta, bool isSpecialCase);
    
private:
    // Disallow creating an instance of this object
    MoveGenerator() {}
};
