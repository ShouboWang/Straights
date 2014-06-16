/*
 To do
 - Rage quit (game)
 - copy human->AI 
 - score (player)
 - round
 - AI
 - move player display to human only
 - quit
 - display deck
 - display order - smallest to largest
 */



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
    //cardsOnTable_.push_back(players_[startingPlayer_]->playCard(SPADE, SEVEN));
    std::cout << "A new round begins. ";
    for(int turnIndex = startingPlayer_;;turnIndex++){
        std::cout << "It’s player " << (turnIndex%4) << "’s turn to play."<<std::endl;
        Command *command = players_[turnIndex%4]->turn(cardsOnTable_);
        if(command->type == PLAY) {
            cardsOnTable_.push_back(players_[turnIndex%4]->playCard(command->card.getSuit(), command->card.getRank()));
        }
        if(command->type == DECK){
            deck_->displayDeck();
        }
    }
}





void Game::invitePlayers(){
    std::string playerType;
    
    for(int index = 0; index < 4; index++){
        std::cout << "Is player "<<(index+1)<<" a human(h) or a computer(c)?" << std::endl << ">";
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

