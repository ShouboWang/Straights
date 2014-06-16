//
//  Player.cpp
//  Straights
//
//  Created by Jack on 2014-06-14.
//  Copyright (c) 2014 Jack. All rights reserved.
//

#include "Player.h"
#include <vector>


const std::string Player::suits[SUIT_COUNT] = {"C", "D", "H", "S"};
const std::string Player::ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
    "7", "8", "9", "10", "J", "Q", "K"};


Player::Player(std::string playerName):playerName_(playerName){
    score_ = 0;
}


void Player::receiveDeltCards(Card* card) {
    cardsOnHand_.push_back(card);//front or back
}

std::string Player::getPlayerName() const{
    return playerName_;
}

int Player::getScore() const {
    return score_;
}


void Player::setScore(const int& newScore){
    score_ = newScore;
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
    // Seven of Spade
    if(card->getRank() == SEVEN && card->getSuit() == SPADE) return true;
    for(int index = 0; index < cardsOnTable.size(); index++){
        Card* inGameCard = cardsOnTable[index];
        //if the card is the same rank
        if(card->getRank() == inGameCard->getRank()) return true;
        // If the card is the same suit but one rank below
        if(card->getSuit() == inGameCard->getSuit() && card->getRank() == (inGameCard->getRank()-1)) return true;
        // If the card is the same suit but one rank above
        if(card->getSuit() == inGameCard->getSuit() && card->getRank() == (inGameCard->getRank()+1)) return true;
    }
    return false;
}
