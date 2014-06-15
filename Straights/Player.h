//
//  Player.h
//  Straights
//
//  Created by Jack on 2014-06-14.
//  Copyright (c) 2014 Jack. All rights reserved.
//

#ifndef __Straights__Player__
#define __Straights__Player__

#include <iostream>
#include "Card.h"
#include <vector>

class Player{
public:
    Player(std::string);
    int getScore() const;
    void receiveDeltCards(std::vector<Card*>);

private:
    Player(Player&);
    Player& operator=(Player&);
    const std::string playerName_;

protected:
    std::vector<Card*> cardsOnHand_;
    std::vector<Card*> discardedCards_;
};

#endif /* defined(__Straights__Player__) */
