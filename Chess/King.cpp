//
//  King.cpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#include "King.hpp"
#include "Constants.h"

King::King(int color) {
    colour = color;
    if (colour == -1){
        value = -king;
    } else{
        value = king;
    }
}

char King::GetLetter(void) {
    if (colour == 1){
        return 'K';
    }
    return 'k';
}

int* King::GetDelta(void){
    return delta;
}
