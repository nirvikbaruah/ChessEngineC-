//
//  Piece.cpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#include "Piece.hpp"
#include "Constants.h"
#include <iostream>

using namespace std;

Piece::Piece() {
    colour = 0;
    value = 0;
}

int Piece::GetValue(void){
    return value;
}

int* Piece::GetDelta(void){
    return delta;
}

char Piece::GetLetter(void) {
    return '-';
}
