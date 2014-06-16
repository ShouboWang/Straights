//
//  Deck.h
//  Straights
//
//  Created by Jack,Errin on 2014-06-14.
//  Copyright (c) 2014 Jack,Errin. All rights reserved.
//

#include "Game.h"

int main(int argc,char *argv[]){
    
    srand48(argc);
    Game* game = new Game();
    game->startGame();
    delete game;
    return 0;
}
