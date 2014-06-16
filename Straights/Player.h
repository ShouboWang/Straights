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
#include "Command.h"
#include <vector>

class Player{
public:
    Player(std::string playerName);             // Constructor
    int getScore() const;                       // Responds to score request
    void setScore(const int &);                 // Set score
    void calculateScore();                      // Calculate score after each round
    void receiveDeltCards(Card*);               // Adds a card to the hand
    virtual Command* turn(std::vector<Card*>) const = 0;    
    virtual void displayHand(std::vector<Card*>) const = 0;
    
    
    //Play
    Card* playCard(const Suit, const Rank);
    
    bool hasSevenSpade() const;
    
    
    //Card* playCard(const Suit, const Rank);
    bool checkCardPlayable(const Card*, const std::vector<Card*>) const;
    
private:
    Player& operator=(Player&);                             // Prohibited assignment operator
    Card* removeCardFromHand(const Suit, const Rank);       // Returns a card from hand
    void displayGameTable(const std::vector<Card*>, const std::vector<Card*>) const;
    
protected:
    Player(const Player&);                      // Cope constructor that is used for AI/Human copying
    
    struct PlayerData{
        const std::string playerName_;
        int playerScore_;
        std::vector<Card*> cardsInHand_;
        std::vector<Card*> discardedCards_;
        
        PlayerData(const std::string);
        PlayerData(const PlayerData& playerData);
        ~PlayerData();
        
    };                                          // Data hiding
    PlayerData* playerData;                     // Data hiding
    
    static const std::string suits[SUIT_COUNT]; // Array of string that corresponds to the suit
    static const std::string ranks[RANK_COUNT]; // Array of string that corresponds to the rank
};

#endif
