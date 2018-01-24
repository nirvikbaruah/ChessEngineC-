//
//  Piece.hpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class Piece{
    public:
        Piece();
        int GetValue(void);
        virtual char GetLetter(void);
        virtual int* GetDelta(void);
    protected:
        int value;
        int colour;
    private:
        int delta[8] = {0, 0, 0, 0, 0, 0, 0, 0};
};

#endif /* Piece_hpp */
