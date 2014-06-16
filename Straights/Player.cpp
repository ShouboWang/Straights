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
Player::Player(std::string playerName){
    playerData = new PlayerData(playerName);
    
}

Player::Player(const Player& player) {
    playerData = new PlayerData(*player.playerData);
}


void Player::receiveDeltCards(Card* card) {
    playerData->cardsInHand_.push_back(card);
}

int Player::getScore() const {
    return playerData->playerScore_;
}


void Player::displayGameTable(const std::vector<Card*> cardsOnTable, const std::vector<Card*> legalPlays) const{
    
    std::string displayMessage = "Cards on the table:/n";
    std::string clubs = "Clubs: ";
    std::string diamonds = "Diamonds: ";
    std::string hearts = "Hearts: ";
    std::string spades = "Spades: ";

    for(int index = 0; index < cardsOnTable.size(); index++){
        switch (cardsOnTable[index]->getSuit()){
            case(CLUB):
                clubs.append(ranks[cardsOnTable[index]->getRank()] + " ");
                break;
            case(DIAMOND):
                diamonds.append(ranks[cardsOnTable[index]->getRank()] + " ");
                break;
            case(HEART):
                hearts.append(ranks[cardsOnTable[index]->getRank()] + " ");
                break;
            case(SPADE):
                spades.append(ranks[cardsOnTable[index]->getRank()] + " ");
                break;
            default:
                break;
        }
    }
    
    std::string playerHand = "Your hand: ";
    for(int index = 0; index < playerData->cardsInHand_.size(); index++){
        playerHand.append(ranks[playerData->cardsInHand_[index]->getRank()]+
                          suits[playerData->cardsInHand_[index]->getSuit()]+" ");
    }
    
    std::string playerLegalCards = "Legal plays: ";
    for(int index = 0; index < playerData->cardsInHand_.size(); index++){
        for(int legalIndex = 0; legalIndex < legalPlays.size(); legalIndex++){
            if(playerData->cardsInHand_[index] == legalPlays[legalIndex]){
                playerLegalCards.append(ranks[playerData->cardsInHand_[index]->getRank()]
                                        +suits[playerData->cardsInHand_[index]->getSuit()]+" ");
            }
        }
    }
    
    std::cout << displayMessage << std::endl;
    std::cout << clubs << std::endl;
    std::cout << diamonds << std::endl;
    std::cout << hearts << std::endl;
    std::cout << spades << std::endl;
    std::cout << playerHand << std::endl;
    std::cout << playerLegalCards << std::endl;
    
}

void Player::setScore(const int& newScore){
    playerData->playerScore_ = newScore;
}

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
Card* playCard(const Suit, const Rank){
    throw "error";
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