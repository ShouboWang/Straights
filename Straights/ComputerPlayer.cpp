//
//  ComputerPlayer.cpp
//  Straights
//
//  Created by Jack on 2014-06-14.
//  Copyright (c) 2014 Jack. All rights reserved.
//

#include "ComputerPlayer.h"
ComputerPlayer::ComputerPlayer(std::string playerName):Player(playerName){
    
}

Command& ComputerPlayer::turn(std::vector<Card*>) const{
    Command c;
    return c;
}