//
//  King.hpp
//  Chess
//
//  Created by Nirvik Baruah on 24/1/18.
//  Copyright © 2018 Nirvik Baruah. All rights reserved.
//

#ifndef King_hpp
#define King_hpp

#include <stdio.h>
#include "Piece.hpp"

class King : public Piece {
    public:
        King(int color);
        char GetLetter(void) override;
        int* GetDelta(void) override;
    private:
        int delta[8] = {-1, 1, -8, 8, 7, 9, -9, -7};
};

#endif /* King_hpp */
