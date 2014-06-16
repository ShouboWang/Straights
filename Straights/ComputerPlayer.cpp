//
//  ComputerPlayer.cpp
//  Straights
//
//  Created by Jack on 2014-06-14.
//  Copyright (c) 2014 Jack. All rights reserved.
//

#include "ComputerPlayer.h"
    
Command* ComputerPlayer::turn(std::vector<Card*> cardsOnTable) const{
    
    Command* command = new Command();
    
    //check for legal playable cards
    for(int index = 0; index < cardsOnTable.size(); index++){
        if(checkCardPlayable(playerData->cardsInHand_[index],cardsOnTable)){
            //if there is a legal card, play the card
            std::string card="";
            card.append(ranks[playerData->cardsInHand_[index]->getRank()] + suits[playerData->cardsInHand_[index]->getSuit()]);
            std::cout << "Player "<< playerData->playerName_ << " plays " << card <<std::endl;
            
            //create a command for the legal play
            command->type = PLAY;
            command->card = removeCardFromHand(playerData->cardsInHand_[index]->getSuit(), playerData->cardsInHand_[index]->getSuit());

            return command;
        }
    }
    
    //dont have legal cards, so discard the first card on hand
    //create command
    command->type = DISCARD;
    command->card = *cardsOnHand_[0];
    
    //add first card on hand to discardedCards list
    
    //delete the first card on hand
    
    
    
    return command;
}