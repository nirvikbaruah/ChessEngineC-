//
//  Bishop.hpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#ifndef Bishop_hpp
#define Bishop_hpp

#include <stdio.h>
#include "Piece.hpp"

class Bishop : public Piece {
    public:
        Bishop(int color);
        char GetLetter(void) override;
        int* GetDelta(void) override;
    private:
        int delta[8] = {0, 0, 0, 0, 7, 9, -9, -7};
};


#endif /* Bishop_hpp */
