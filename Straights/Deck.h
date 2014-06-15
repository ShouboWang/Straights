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
#include <cstdlib>
#include "Card.h"

class Deck{
public:
    Deck();             //constuctor
    ~Deck();            //destructor
    void shuffle();     //shuffle algorithm
    Card* getNextCard();    // Recieve the next card in deck
    
private:
    int currentCardIndex_;
    const int CARD_COUNT;
    Card* cards_[52];
};

#endif /* defined(__Straights__Deck__) */
