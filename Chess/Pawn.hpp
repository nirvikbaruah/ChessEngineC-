//
//  Pawn.hpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#ifndef Pawn_hpp
#define Pawn_hpp

#include <stdio.h>
#include "Piece.hpp"

class Pawn : public Piece {
    public:
        char GetLetter(void) override;
        Pawn(int color);
        int* GetDelta(void) override;
    private:
        int delta[8] = {0, 0, 8, 0, 0, 0, 0, 0};
};


#endif /* Pawn_hpp */
