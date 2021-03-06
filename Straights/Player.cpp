//
//  Deck.h
//  Straights
//
//  Created by Jack,Errin on 2014-06-14.
//  Copyright (c) 2014 Jack,Errin. All rights reserved.
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
    for(unsigned int index = 0; index < playerData.cardsInHand_.size(); index++) {
        cardsInHand_.push_back(playerData.cardsInHand_[index]);
    }
    for(unsigned int index = 0; index < playerData.discardedCards_.size(); index++) {
        discardedCards_.push_back(playerData.discardedCards_[index]);
    }
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

// Dectructor
Player::~Player(){
    delete playerData;
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
    for(unsigned int index = 0; index < playerData->cardsInHand_.size(); index++) {
        if(playerData->cardsInHand_[index]->getSuit() == SPADE && playerData->cardsInHand_[index]->getRank() == SEVEN)
            return true;
    }
    return false;
}

// Responds to the "play" command
// If the card is invalid play, throw runtime_error
// If the card is valid play, remove the card from hand and return the card
Card* Player::playCard(const Suit suit, const Rank rank){
    Card* card = removeCardFromHand(suit, rank);
    std::cout << "Player " << playerData->playerName_ << " plays " << *card << "." <<std::endl;
    return card;
}

// Remove a card from player's hand and returns the card back
// Assume that the card already exist in the player's hand
Card* Player::removeCardFromHand(const Suit suit, const Rank rank){
    
    for(unsigned int index = 0; index < playerData->cardsInHand_.size(); index++){
        
        //find the selected card on hand
        if(playerData->cardsInHand_[index]->getRank() == rank && playerData->cardsInHand_[index]->getSuit() == suit){
            Card* cardToReturn = playerData->cardsInHand_[index];
            playerData->cardsInHand_.erase(playerData->cardsInHand_.begin()+index);
            return cardToReturn;
        }
    }
    
    //if not find, error
    throw std::runtime_error("This is not a legal play.");
}

// Calculate the score based on the player's discarded cards
int Player::calculateScore() const{
    int score = 0;
    
    for(unsigned int index = 0; index < playerData->discardedCards_.size(); index++){
        for(int rankIndex = 0; rankIndex < RANK_COUNT; rankIndex++) {
            
            //check for the existance of enum rank
            if(ranks[rankIndex] == ranks[playerData->discardedCards_[index]->getRank()]) {
                score += (rankIndex + 1);
            }
        }
    }
    
    return score;
}

// Checks if the card is a legal card to be played
bool Player::checkCardPlayable(const Card* card, const std::vector<Card*> cardsOnTable) const {
    
    // Seven of Spade
    if(card->getRank() == SEVEN && card->getSuit() == SPADE) return true;

    for(unsigned int index = 0; index < cardsOnTable.size(); index++){
        Card* inGameCard = cardsOnTable[index];
        //if the card is the same rank
        if(card->getRank() == SEVEN) return true;
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
    for(unsigned int index = 0; index < playerData->cardsInHand_.size(); index++){
        
        // if the card is a legal card, add it into the list of legal playable cards
        if(checkCardPlayable(playerData->cardsInHand_[index], cardsOnTable)){
            legalCards.push_back(playerData->cardsInHand_[index]);
        }
    }
    return legalCards;
}

// Print the list of discarded cards
void Player::printDiscardedCards() const {
    std::cout << "Player " << playerData->playerName_ << "'s discards: ";
    
    //the list of cards are in the order where they're discarded
    for(unsigned int index = 0; index < playerData->discardedCards_.size(); index++) {
        std::cout << *playerData->discardedCards_[index] << " ";
    }
    std::cout << std::endl;
}

// Discard Card
void Player::discardCard(const Suit suit, const Rank rank){
    
    //remove the card from hand and add it into the list of discarded cards
    Card* card = removeCardFromHand(suit, rank);
    playerData->discardedCards_.push_back(card);
    std::cout << "Player " << playerData->playerName_ <<" discards " << *card <<"."<<std::endl;
}

//clear the cards on hand and also the discarded cards arrays
void Player::clearHand(){
    playerData->cardsInHand_.clear();
    playerData->discardedCards_.clear();
}