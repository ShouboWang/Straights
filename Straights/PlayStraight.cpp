//
//  PlayStraight.cpp
//  Straights
//
//  Created by Jack on 2014-06-15.
//  Copyright (c) 2014 Jack. All rights reserved.
//

#include "Game.h"

int main(int argc,char *argv[]){
    
    srand48(argc);
    Game* game = new Game();
    game->startGame();
    delete game;
    return 0;
}
