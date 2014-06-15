#include "Game.h"
#include <iostream>
#include <sstream>


Game::Game(){
    deck_ = new Deck();
}

Game::~Game(){
    
    // Delete players
    for(int index = 0; index < 4; index++){
        delete players_[index];
    }
    
    // Delete deck
    delete deck_;
};

void Game::startGame(){
    
    // Invite players
    invitePlayers();
    
    // Shuffle the deck
    deck_->shuffle();
    
    // Deal the cards
    for(int playerIndex = 0; playerIndex < 4; playerIndex ++){
        for(int cardI = 0; cardI < 13; cardI++){
            players_[playerIndex]->receiveDeltCards(deck_->getNextCard());
        }
    }
    
    // Get the player that should go first
    for(int playerIndex = 0; playerIndex < 4; playerIndex++){
        if(players_[playerIndex]->hasSevenSpade()){
            startingPlayer_ = playerIndex;
            break;
        }
    }
    
    // First player must play
    cardsOnTable_.push_back(players_[startingPlayer_]->playCard(SPADE, SEVEN));
    
    for(int turnIndex = startingPlayer_;;turnIndex++){
        
    }
}




void Game::invitePlayers(){
    std::string playerType;
    
    for(int index = 0; index < 4; index++){
        std::cout << "Is player "<<(index+1)<<" a human(h) or a computer(c)?" << std::endl;
        std::cin >> playerType;
        
        std::ostringstream oss;
        oss << "Player"<<(index+1);
        
        if(std::cin.eof()){
            std::exit(0);
        }
        if(playerType == "h"){
            players_[index] = new HumanPlayer(oss.str());
        } else if(playerType == "c"){
            players_[index] = new ComputerPlayer(oss.str());
        }
    }
}

