//
//  HumanPlayer.cpp
//  Straights
//
//  Created by Jack on 2014-06-14.
//  Copyright (c) 2014 Jack. All rights reserved.
//

#include "HumanPlayer.h"
HumanPlayer::HumanPlayer(std::string playerName):Player(playerName){
    
}

Command* HumanPlayer::turn(std::vector<Card*> cardsOnTable) const{
    
    Command* command = new Command();
    bool legalPlay = false;
    do{
        legalPlay = false;
        std::cout << ">";
        std::cin>>*command;
        if(command->type == PLAY) {
            std::vector<Card*> legalCards = getLegalCards(cardsOnTable);
            for(int index = 0; index < legalCards.size(); index++){
                if(command->card.getSuit() == legalCards[index]->getSuit() &&
                   command->card.getRank() == legalCards[index]->getRank()){
                    legalPlay = true;
                }
            }
        } else if(command->type == DISCARD) {
            std::vector<Card*> legalCards = getLegalCards(cardsOnTable);
            if(legalCards.size() == 0) {
                legalPlay = true;
            }
        }
        if(!legalPlay){
            std::cout << "This is not a legal play." << std::endl;
        }
        
    } while(command->type == BAD_COMMAND || !legalPlay);
    
    return command;
}

void HumanPlayer::displayHand(std::vector<Card*> cardsOnTable) const{
    // Get the legal plays for the player
    std::vector<Card*> legalPlays = getLegalCards(cardsOnTable);
    
    // Display the current cards on the table and the avlaible options for player
    displayGameTable(cardsOnTable, legalPlays);
}

void HumanPlayer::displayGameTable(const std::vector<Card*> cardsOnTable, const std::vector<Card*> legalPlays) const {
    
    std::string displayMessage = "Cards on the table:";
    std::string clubs = "Clubs: ";
    std::string diamonds = "Diamonds: ";
    std::string hearts = "Hearts: ";
    std::string spades = "Spades: ";
    
    for(unsigned int index = 0; index < cardsOnTable.size(); index++){
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
    
    for(unsigned int index = 0; index < playerData-> cardsInHand_.size(); index++){
        playerHand.append(ranks[playerData->cardsInHand_[index]->getRank()]+suits[playerData->cardsInHand_[index]->getSuit()]+" ");
    }
    
    std::string playerLegalCards = "Legal plays: ";
    for(unsigned int index = 0; index < playerData->cardsInHand_.size(); index++){
        for(unsigned int legalIndex = 0; legalIndex < legalPlays.size(); legalIndex++){
            if(playerData->cardsInHand_[index] == legalPlays[legalIndex]){
                playerLegalCards.append(ranks[playerData->cardsInHand_[index]->getRank()]+suits[playerData->cardsInHand_[index]->getSuit()]+" ");
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
