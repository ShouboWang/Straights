//
//  Deck.h
//  Straights
//
//  Created by Jack,Errin on 2014-06-14.
//  Copyright (c) 2014 Jack,Errin. All rights reserved.
//

/*
 To do
 - copy human->AI 
 - score (player)
 - round
 - AI
 - display order - smallest to largest
 */



#include "Game.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory>


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
    
    bool gameEnd = false;
    
    while(!gameEnd){
    
        // Shuffle the deck
        deck_->shuffle();
    
        // Deal the cards
        for(int playerIndex = 0; playerIndex < 4; playerIndex ++){
            for(int cardI = 0; cardI < 13; cardI++){
                players_[playerIndex]->getDeltCards(deck_->getNextCard());
            }
        }
    
        // Get the player that should go first
        for(int playerIndex = 0; playerIndex < 4; playerIndex++){
            if(players_[playerIndex]->hasSevenSpade()){
                startingPlayer_ = playerIndex;
                break;
            }
        }
    
        // Start of the game
        int turn = 0;
        std::cout << "A new round begins. It’s player " << (startingPlayer_+1) << "’s turn to play."<<std::endl;
        for(int turnIndex = startingPlayer_; turn < 52; turnIndex++){
            players_[turnIndex%4]->displayHand(cardsOnTable_);
            Command *command = players_[turnIndex%4]->turn(cardsOnTable_);
        
            if(command->type == DECK){
                do{
                    deck_->displayDeck();
                    command = players_[turnIndex%4]->turn(cardsOnTable_);
                }while(command->type == DECK);
            }
        
            if(command->type == PLAY) {
                do{
                    try{
                        cardsOnTable_.push_back(players_[turnIndex%4]->playCard(command->card.getSuit(), command->card.getRank()));
                    break;
                    }catch(std::runtime_error& e){
                        std::cout << e.what() << std::endl;
                        command = players_[turnIndex%4]->turn(cardsOnTable_);
                    }
                }while(true);
            } else if(command->type == DISCARD){
                players_[turnIndex%4]->discardCard(command->card.getSuit(), command->card.getRank());
            }else if(command->type == QUIT){
                delete command;
                return;
            } else if(command->type == RAGEQUIT) {
                std::cout << "Player " << (turnIndex%4) << "ragequits. A computer will now take over." << std::endl;
                Player *player = new ComputerPlayer(*players_[turnIndex%4]);
                delete players_[turnIndex%4];
                players_[turnIndex%4] = player;
            }
        
            delete command;
            ++turn;
        }
        
        // Turn is 13, All players have played their cards
        for(int index = 0; index < 4; index++){
            players_[index]->printDiscardedCards();
            int roundScore = players_[index]->calculateScore();
        }
        gameEnd = true;
    }
}





void Game::invitePlayers(){
    std::string playerType;
    
    for(int index = 0; index < 4; index++){
        std::cout << "Is player "<<(index+1)<<" a human(h) or a computer(c)?" << std::endl << ">";
        std::cin >> playerType;
        
        std::ostringstream oss;
        oss << (index+1);
        
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

