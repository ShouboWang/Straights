//
//  Deck.h
//  Straights
//
//  Created by Jack,Errin on 2014-06-14.
//  Copyright (c) 2014 Jack,Errin. All rights reserved.
//

#include "ComputerPlayer.h"
    
Command* ComputerPlayer::turn(std::vector<Card*> cardsOnTable) const{
    
    Command* command = new Command();
    
    std::vector<Card*> legalCards = getLegalCards(cardsOnTable);
    //for(int i = 0; i < legalCards.size(); i++){
    //    std::cout << *legalCards[i]<<" ";
    //}
    //std::cout << std::endl;
    if(legalCards.size() >0){
        command->type = PLAY;
        command->card = *legalCards[0];
    } else {
        command->type = DISCARD;
        command->card = *playerData->cardsInHand_[0];
    }
    return command;
}