//
//  Queen.cpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#include "Queen.hpp"
#include "Constants.h"

Queen::Queen(int color) {
    colour = color;
    if (colour == -1){
        value = -queen;
    } else{
        value = queen;
    }
}

char Queen::GetLetter(void) {
    if (colour == 1){
        return 'Q';
    }
    return 'q';
}

int* Queen::GetDelta(void){
    return delta;
}
