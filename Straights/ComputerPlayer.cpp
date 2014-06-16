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
    
    std::vector<Card*> legalCards = getLegalCards(cardsOnTable);
    if(legalCards.size() >0){
        command->type = PLAY;
        command->card = Card(legalCards[0]->getSuit(),legalCards[0]->getRank());
    } else {
        command->type = DISCARD;
        command->card = Card(playerData->cardsInHand_[0]->getSuit(),playerData->cardsInHand_[0]->getRank());
    }
    return command;
}