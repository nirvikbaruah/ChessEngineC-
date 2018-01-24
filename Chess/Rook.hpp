//
//  Rook.hpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#ifndef Rook_hpp
#define Rook_hpp

#include <stdio.h>
#include "Piece.hpp"

class Rook : public Piece {
    public:
        Rook(int color);
        char GetLetter(void) override;
        int* GetDelta(void) override;
    private:
        int delta[8] = {-1, 1, -8, 8, 0, 0, 0, 0};
};


#endif /* Rook_hpp */
