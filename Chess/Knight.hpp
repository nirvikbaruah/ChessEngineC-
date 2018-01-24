//
//  Knight.hpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#ifndef Knight_hpp
#define Knight_hpp

#include <stdio.h>
#include "Piece.hpp"

class Knight : public Piece {
    public:
        Knight(int color);
        char GetLetter(void) override;
        int* GetDelta(void) override;
    private:
        //Top-left to middle-left (clockwise fashion)
        int delta[8] = {15, 17, 10, -6, -15, -17, -10, 6};
};

#endif /* Knight_hpp */
