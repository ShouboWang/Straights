//
//  Deck.h
//  Straights
//
//  Created by Jack on 2014-06-14.
//  Copyright (c) 2014 Jack. All rights reserved.
//

#ifndef __Straights__Deck__
#define __Straights__Deck__

#include <iostream>
#include "Card.h"

class Deck{
public:
    Deck();             //constuctor
    ~Deck();            //destructor
    void shuffle();     //shuffle algorithm
    
private:
    const int CARD_COUNT = 52;
    Card* cards_[];
    
};

#endif /* defined(__Straights__Deck__) */
