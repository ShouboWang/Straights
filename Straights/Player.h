//
//  Deck.h
//  Straights
//
//  Created by Jack,Errin on 2014-06-14.
//  Copyright (c) 2014 Jack,Errin. All rights reserved.
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
    ~Player();
    int getScore() const;                       // Responds to score request
    void setScore(const int &);                 // Set score
    int calculateScore() const;                      // Calculate score after each round
    void getDeltCards(Card*);                   // Add a card to the hand
    bool hasSevenSpade() const;                 // Checks if the player has the seven of spade
    void printDiscardedCards() const;           // Print the list of discarded cards
    
    virtual Command* turn(std::vector<Card*>) const = 0;
    virtual void displayHand(std::vector<Card*>) const = 0;
    
    // Command - play
    Card* playCard(const Suit, const Rank);
    
    // Command - Discard
    void discardCard(const Suit, const Rank);
    
    
    //Card* playCard(const Suit, const Rank);
    bool checkCardPlayable(const Card*, const std::vector<Card*>) const;
    
private:
    Player& operator=(Player&);                             // Prohibited assignment operator
    void displayGameTable(const std::vector<Card*>, const std::vector<Card*>);
    
protected:
    Player(const Player&);                      // Cope constructor that is used for AI/Human copying
    
    struct PlayerData{
        const std::string playerName_;
        int playerScore_;
        std::vector<Card*> cardsInHand_;
        std::vector<Card*> discardedCards_;
        
        PlayerData(const std::string);
        PlayerData(const PlayerData& playerData);
    };                                          // Data hiding
    PlayerData* playerData;                     // Data hiding
    
    PlayerData* getData();
    
    static const std::string suits[SUIT_COUNT]; // Array of string that corresponds to the suit
    static const std::string ranks[RANK_COUNT]; // Array of string that corresponds to the rank
    std::vector<Card*> getLegalCards(const std::vector<Card*>) const;
    Card* removeCardFromHand(const Suit, const Rank);       // Returns a card from hand
};

#endif
