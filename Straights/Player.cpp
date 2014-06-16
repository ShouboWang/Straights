//
//  Player.cpp
//  Straights
//
//  Created by Jack on 2014-06-14.
//  Copyright (c) 2014 Jack. All rights reserved.
//

#include "Player.h"
#include <vector>
#include <stdexcept>
#include <memory>


const std::string Player::suits[SUIT_COUNT] = {"C", "D", "H", "S"};
const std::string Player::ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
    "7", "8", "9", "10", "J", "Q", "K"};



/*
 Struct Functions
 */

// Constructor
Player::PlayerData::PlayerData(std::string playerName):playerName_(playerName){
    playerScore_ = 0;
}
    
// Copy constructor
Player::PlayerData::PlayerData(const PlayerData& playerData):playerName_(playerData.playerName_){
    playerScore_ = playerData.playerScore_;
    for(int index = 0; index < playerData.cardsInHand_.size(); index++) {
        cardsInHand_.push_back(playerData.cardsInHand_[index]);
    }
    for(int index = 0; index < playerData.discardedCards_.size(); index++) {
        discardedCards_.push_back(playerData.discardedCards_[index]);
    }
}
    
// Destructor
Player::PlayerData::~PlayerData(){
    //something?
}

/*
 Player Functions
 */

// Constructor for Player
Player::Player(std::string playerName){
    playerData = new PlayerData(playerName);
}

// Copye constructor for Player
Player::Player(const Player& player) {
    playerData = new PlayerData(*player.playerData);
}

// Get the card delt and adds the card to hand
void Player::getDeltCards(Card* card) {
    playerData->cardsInHand_.push_back(card);
}

// Responds to score request
int Player::getScore() const {
    return playerData->playerScore_;
}

// Sets the score for player
void Player::setScore(const int& newScore){
    playerData->playerScore_ = newScore;
}

// Checks if the player has the seven of spade
bool Player::hasSevenSpade() const {
    for(int index = 0; index < playerData->cardsInHand_.size(); index++) {
        if(playerData->cardsInHand_[index]->getSuit() == SPADE && playerData->cardsInHand_[index]->getRank() == SEVEN)
            return true;
    }
    return false;
}

// Responds to the "play" command
// If the card is invalid play, throw runtime_error
// If the card is valid play, remove the card from hand and return the card
Card* Player::playCard(const Suit suit, const Rank rank){
    return removeCardFromHand(suit, rank);
}

// Remove a card from player's hand and returns the card back
// Assume that the card already exist in the player's hand
Card* Player::removeCardFromHand(const Suit suit, const Rank rank){
    
    for(int index = 0; index < playerData->cardsInHand_.size(); index++){
        if(playerData->cardsInHand_[index]->getRank() == rank && playerData->cardsInHand_[index]->getSuit() == suit){
            Card* cardToReturn = playerData->cardsInHand_[index];
            playerData->cardsInHand_.erase(playerData->cardsInHand_.begin()+index);
            return cardToReturn;
        }
    }
    
    throw std::runtime_error("This is not a legal play.");
}

void Player::calculateScore(){
    //print out the list of discarded cards of the player
    std::cout<< playerData->playerName_ << "'s discards: ";
    std::string discards="";
    int newScore = 0;
    
    //find all discarded cards and calculate new score based on its rank
    for (int i = 0; i < playerData->discardedCards_.size(); i++){
        discards.append(ranks[playerData->discardedCards_[i]->getRank()] +
                                    suits[playerData->discardedCards_[i]->getSuit()] + " ");
        newScore += playerData->discardedCards_[i]->getRank()+1;
    }
    std::cout << discards<< std::endl;
    
    std::cout << playerData->playerName_ << "'s score: " << playerData->playerScore_
                        << " + " << newScore << " = " << playerData->playerScore_+newScore;
    
    //calculate total score
    playerData->playerScore_+=newScore;

}

// Checks if the card is a legal card to be played
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

// Returns a vector of Arrays that contains all the legal cards for a player's turn
std::vector<Card*> Player::getLegalCards(const std::vector<Card*> cardsOnTable) const {
    std::vector<Card*> legalCards;
    for(int index = 0; index < playerData->cardsInHand_.size(); index++){
        if(checkCardPlayable(playerData->cardsInHand_[index], cardsOnTable)){
            legalCards.push_back(playerData->cardsInHand_[index]);
        }
    }
    return legalCards;
}