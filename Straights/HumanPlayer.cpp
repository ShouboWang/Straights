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

Command& HumanPlayer::turn(std::vector<Card*> cardsOnTable) const{
    // Get the legal plays for the player
    std::vector<Card*> legalPlays;
    for(Card* card : cardsOnHand_){
        if(checkCardPlayable(card,cardsOnTable)){
            legalPlays.push_back(card);
        }
    }
    
    // Display the current cards on the table and the avlaible options for player
    displayGameTable(cardsOnTable, legalPlays);
    
    Command* command;
    
    do{
        std::cout << ">";
        std::cin>>*command;
        
    } while(command->type == BAD_COMMAND);
    
    return *command;
}

void HumanPlayer::displayGameTable(const std::vector<Card*> cardsOnTable, const std::vector<Card*> legalPlays) const {
    
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
