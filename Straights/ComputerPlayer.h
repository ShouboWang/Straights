
#ifndef __Straights__ComputerPlayer__
#define __Straights__ComputerPlayer__

#include <iostream>
#include "Player.h"
#include "HumanPlayer.h"

class ComputerPlayer: public Player{
public:
    ComputerPlayer(const std::string&);            //constructor
    ComputerPlayer(const HumanPlayer&);     //copy constructor
    
};

#endif /* defined(__Straights__ComputerPlayer__) */
