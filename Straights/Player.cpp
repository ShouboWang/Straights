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
    cardsOnHand_.push_back(card);
}

Command& Player::turn(std::vector<Card*> cardsOntable, std::vector<Card*> legalPlays) const{
    
    // Display the current cards on the table and the avlaible options for player
    displayGameTable(cardsOntable, legalPlays);
    
    Command* command;
    
    do{
        std::cin>>*command;
        
    } while(command->type == BAD_COMMAND);
    
    return *command;
}

void Player::displayGameTable(const std::vector<Card*> cardsOnTable, const std::vector<Card*> legalPlays) const{
    
    std::string displayMessage = "Cards on the table:/n";
    std::string clubs = "Clubs: ";
    std::string diamonds = "Diamonds: ";
    std::string hearts = "Hearts: ";
    std::string spades = "Spades: ";
    
    std::string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
    std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
    
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
    for(int index = 0; index < cardsOnHand_.size(); index++){
        playerHand.append(ranks[cardsOnHand_[index]->getRank()]+suits[cardsOnHand_[index]->getSuit()]+" ");
    }
    
    std::string playerLegalCards = "Your hand: ";
    for(int index = 0; index < cardsOnHand_.size(); index++){
        for(int legalIndex = 0; legalIndex < legalPlays.size(); legalIndex++){
            if(cardsOnHand_[index] == legalPlays[legalIndex]){
                playerLegalCards.append(ranks[cardsOnHand_[index]->getRank()]+suits[cardsOnHand_[index]->getSuit()]+" ");
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