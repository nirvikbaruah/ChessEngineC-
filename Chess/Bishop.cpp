//
//  Bishop.cpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#include "Bishop.hpp"
#include "Constants.h"

Bishop::Bishop(int color) {
    colour = color;
    if (colour == -1){
        value = -bishop;
    } else{
        value = bishop;
    }
}

char Bishop::GetLetter(void) {
    if (colour == 1){
        return 'B';
    }
    return 'b';
}

int* Bishop::GetDelta(void){
    return delta;
}
