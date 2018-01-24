//
//  Queen.hpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#ifndef Queen_hpp
#define Queen_hpp

#include <stdio.h>
#include "Piece.hpp"

class Queen : public Piece {
    public:
        Queen(int color);
        char GetLetter(void) override;
        int* GetDelta(void) override;
    private:
        int delta[8] = {-1, 1, -8, 8, 7, 9, -9, -7};
};

#endif /* Queen_hpp */
