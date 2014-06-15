//
//  ComputerPlayer.cpp
//  Straights
//
//  Created by Jack on 2014-06-14.
//  Copyright (c) 2014 Jack. All rights reserved.
//

#include "ComputerPlayer.h"
ComputerPlayer::ComputerPlayer(const std::string& playerName):Player(playerName){
    
}

//copy human data to computer data when user rage quites
ComputerPlayer::ComputerPlayer(const HumanPlayer& rageUser): Player(rageUser.getPlayerName()){
    //copy the score of the human player
    setScore(rageUser.getScore());
    
    //copy the cards on hand
    for (int i = 0; i < rageUser.cardsOnHand_.size(); i++){
        
    
    }
    
    
    
}

Command& ComputerPlayer::turn(std::vector<Card*>) const{
    Command c;
    return c;
}