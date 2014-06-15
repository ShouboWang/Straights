#include "Game.h"
#include <iostream>


Game::Game(){
    
}

Game::~Game(){
    for(int index = 0; index < 4; index++){
        delete players_[index];
    }
};

void Game::startGame(){
    //invitePlayers();
    deck_ = new Deck();
    deck_->shuffle();
}

void Game::invitePlayers(){
    std::string playerType;
    for(int index = 0; index < 4; index++){
        std::cout << "Is player "<<(index+1)<<" a human(h) or a computer(c)?" << std::endl;
        std::cin >> playerType;
        if(std::cin.eof()){
            std::exit(0);
        }
        if(playerType == "h"){
            players_[index] = new HumanPlayer("Player"+std::to_string(index+1));
        } else if(playerType == "c"){
            players_[index] = new ComputerPlayer("Player"+std::to_string(index+1));
        }
    }
}

