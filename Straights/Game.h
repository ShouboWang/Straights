//
//  Game.h
//  Straights
//
//  Created by Jack on 2014-06-14.
//  Copyright (c) 2014 Jack. All rights reserved.
//

#ifndef Straights_Game_h
#define Straights_Game_h

#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Deck.h"

class Game{
public:
    Game();
    ~Game();
    void startGame();
private:
    void invitePlayers();
    Player* players_[4];
    Deck* deck_;
    
};


#endif
