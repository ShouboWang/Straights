
#ifndef __Straights__HumanPlayer__
#define __Straights__HumanPlayer__

#include <iostream>
#include "Player.h"

class HumanPlayer: public Player{
public:
    HumanPlayer(std::string);
    Command& turn(std::vector<Card*>) const;
private:
    void displayGameTable(const std::vector<Card*>, const std::vector<Card*>) const;
};

#endif