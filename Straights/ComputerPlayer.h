
#ifndef __Straights__ComputerPlayer__
#define __Straights__ComputerPlayer__

#include <iostream>
#include "Player.h"
#include "HumanPlayer.h"

class ComputerPlayer: public Player{
public:
    ComputerPlayer(std::string);
    Command& turn(std::vector<Card*>) const;
    
};

#endif /* defined(__Straights__ComputerPlayer__) */
