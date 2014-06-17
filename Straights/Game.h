//
//  Deck.h
//  Straights
//
//  Created by Jack,Errin on 2014-06-14.
//  Copyright (c) 2014 Jack,Errin. All rights reserved.
//

#ifndef Straights_Game_h
#define Straights_Game_h

#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Deck.h"
#include <vector>

class Game{
public:
    Game();
    ~Game();
    void startGame();
private:
    void invitePlayers();
    Player* players_[4];
    Deck* deck_;
    std::vector<Card*> cardsOnTable_;
    int startingPlayer_;
};


#endif
