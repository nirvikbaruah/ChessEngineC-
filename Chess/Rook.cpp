//
//  Rook.cpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#include "Rook.hpp"
#include "Constants.h"

Rook::Rook(int color) {
    colour = color;
    if (colour == -1){
        value = -rook;
    } else{
        value = rook;
    }
}

char Rook::GetLetter(void) {
    if (colour == 1){
        return 'R';
    }
    return 'r';
}

int* Rook::GetDelta(void){
    return delta;
}

