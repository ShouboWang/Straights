//
//  Player.cpp
//  Straights
//
//  Created by Jack on 2014-06-14.
//  Copyright (c) 2014 Jack. All rights reserved.
//

#include "Player.h"
#include <vector>

Player::Player(std::string playerName):playerName_(playerName){
    score = 0;
}


void Player::receiveDeltCards(Card* card) {
    cardsOnHand_.push_back(card);//front or back
}


bool Player::hasSevenSpade() const {
    for(int index = 0; index < cardsOnHand_.size(); index++) {
        if(cardsOnHand_[index]->getSuit() == SPADE && cardsOnHand_[index]->getRank() == SEVEN) return true;
    }
    return false;
}

Card* Player::playCard(const Suit suit, const Rank rank){
    Card* cardToReturn = nullptr;
    
    for(int index = 0; index < cardsOnHand_.size(); index++){
        if(cardsOnHand_[index]->getRank() == rank && cardsOnHand_[index]->getSuit() == suit){
            cardToReturn = cardsOnHand_[index];
            cardsOnHand_.erase(cardsOnHand_.begin()+index);
        }
    }
    
    return cardToReturn;
}

bool Player::checkCardPlayable(const Card* card, const std::vector<Card*> cardsOnTable) const {
    for(int index = 0; index < cardsOnTable.size(); index++){
        Card* inGameCard = cardsOnTable[index];
        // current played card is 7S
        
        //if the card is rank 7
        if(card->getRank() == inGameCard->getRank()) return true;
        // If the card is the same suit but one rank below
        if(card->getSuit() == inGameCard->getSuit() && card->getRank() == (inGameCard->getRank()-1)) return true;
        // If the card is the same suit but one rank above
        if(card->getSuit() == inGameCard->getSuit() && card->getRank() == (inGameCard->getRank()+1)) return true;
    }
    return false;
}