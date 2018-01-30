//
//  Pawn.cpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#include "Pawn.hpp"
#include "Constants.h"

Pawn::Pawn(int color) {
    colour = color;
    if (colour == -1){
        value = -pawn;
        //Flips move direction for black pawn
        delta[3] = -8;
        delta[2] = 0;
    } else{
        value = pawn;
    }
    //TODO: SPECIAL CASE FOR PAWN
}

char Pawn::GetLetter(void) {
    if (colour == 1){
        return 'P';
    }
    return 'p';
}

int* Pawn::GetDelta(void){
    return delta;
}
