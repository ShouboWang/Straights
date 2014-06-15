//
//  Deck.cpp
//  Straights
//
//  Created by Jack on 2014-06-14.
//  Copyright (c) 2014 Jack. All rights reserved.
//

#include "Deck.h"

Deck::Deck():CARD_COUNT(52){
    
    //index of the cards_ array;
    int index = 0;
    //iterate through Suit enum
    for (int i = CLUB; i < SUIT_COUNT; i++){
        //iterate through Rank enum
        for (int j = ACE; j < RANK_COUNT; j++){
            cards_[index++] = new Card((Suit)i, (Rank)j);
        }
    }
}

//destructor
Deck::~Deck(){
    
    for (int i = 0; i < CARD_COUNT; i++){
        //delete every pointer of card in cards_
        delete cards_[i];
        cards_[i] = NULL;
    }
}

void Deck::shuffle(){
    
    
    for(int i = 0; i < 52; i++){
        std::cout << *cards_[i] << " ";
    }
    std::cout << std::endl;
     
    /* To ensure that the your cards are ordered the same way as
     the given program, use this shuffling algorithm.
     
     CARD_COUNT is the constant 52
     cards_ is an array of pointers to cards
     */

    int n = CARD_COUNT;

    while ( n > 1 ) {
        int k = (int) (lrand48() % n);
        --n;
        Card *c = cards_[n];
        cards_[n] = cards_[k];
        cards_[k] = c;
    }
    
    for(int i = 0; i < 52; i++){
        std::cout << *cards_[i] << " ";
    }
    std::cout << std::endl;
}