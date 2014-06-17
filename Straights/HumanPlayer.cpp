//
//  Deck.h
//  Straights
//
//  Created by Jack,Errin on 2014-06-14.
//  Copyright (c) 2014 Jack,Errin. All rights reserved.
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
            for(unsigned int index = 0; index < legalCards.size(); index++){
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
        } else if(command->type == QUIT){
            legalPlay = true;
        } else if(command->type == RAGEQUIT){
            legalPlay = true;
        } else if(command->type == DECK){
            legalPlay = true;
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

void HumanPlayer::displayGameTable(const std::vector<Card*> cardsOnTable, const std::vector<Card*> legalPlays) const{
    
    std::string displayMessage = "Cards on the table:";
   /* std::string clubs = "Clubs: ";
    std::string diamonds = "Diamonds: ";
    std::string hearts = "Hearts: ";
    std::string spades = "Spades: "; */
    
    std::vector<Card*> clubs;
    std::vector<Card*> diamonds;
    std::vector<Card*> hearts;
    std::vector<Card*> spades;
    
    for(unsigned int index = 0; index < cardsOnTable.size(); index++){
        switch (cardsOnTable[index]->getSuit()){
            case(CLUB):
                clubs.push_back(cardsOnTable[index]);
                //clubs.append(ranks[cardsOnTable[index]->getRank()] + " ");
                break;
            case(DIAMOND):
                diamonds.push_back(cardsOnTable[index]);
                //diamonds.append(ranks[cardsOnTable[index]->getRank()] + " ");
                break;
            case(HEART):
                hearts.push_back(cardsOnTable[index]);
                //hearts.append(ranks[cardsOnTable[index]->getRank()] + " ");
                break;
            case(SPADE):
                spades.push_back(cardsOnTable[index]);
                //spades.append(ranks[cardsOnTable[index]->getRank()] + " ");
                break;
            default:
                break;
        }
    }
    
    //sort each array of Suit
    std::string clubsSorted = sort(clubs);
    std::string diamondsSorted = sort(diamonds);
    std::string heartsSorted = sort(hearts);
    std::string spadesSorted = sort(spades);
    
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
    std::cout << "Clubs: " << clubsSorted << std::endl;
    std::cout << "Diamonds: " << diamondsSorted<<std::endl;
    std::cout << "Hearts: " << heartsSorted<<std::endl;
    std::cout << "Spades: " <<spadesSorted <<std::endl;
    std::cout << playerHand << std::endl;
    std::cout << playerLegalCards << std::endl;
    
    
}

std::string HumanPlayer::sort(const std::vector<Card*>& cards) const{
    std::string combine = "";
    for (int i = 0; i < 13; i ++){
        for (int j = 0; j < cards.size(); j++){
            if (i == cards[j]->getRank())   combine.append(ranks[cards[j]->getRank()]+ " ");
        }
    }
    return combine;
}
