//
//  Knight.cpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#include "Knight.hpp"
#include "Constants.h"

Knight::Knight(int color) {
    colour = color;
    if (colour == -1){
        value = -knight;
    } else{
        value = knight;
    }
}

char Knight::GetLetter(void) {
    if (colour == 1){
        return 'N';
    }
    return 'n';
}

int* Knight::GetDelta(void){
    return delta;
}

