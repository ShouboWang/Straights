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
    Player(std::string playerName);
    int getScore() const;
    void setScore(const int &);              //set score
    void calculateScore();                  //calculate score after each round
    void receiveDeltCards(Card*);
    virtual Command* turn(std::vector<Card*>) const = 0;
    bool hasSevenSpade() const;
    Card* playCard(const Suit, const Rank);
    std::string getPlayerName() const;                //accessor
    bool checkCardPlayable(const Card*, const std::vector<Card*>) const;

private:
    Player(Player&);                                    //prohibited copy
    Player& operator=(Player&);                         //prohibited assignment
    void displayGameTable(const std::vector<Card*>, const std::vector<Card*>) const;
    const std::string playerName_;
    int score_;
    static const std::string suits[SUIT_COUNT];
    static const std::string ranks[RANK_COUNT];

protected:
    std::vector<Card*> cardsOnHand_;
    std::vector<Card*> discardedCards_;
};

#endif /* defined(__Straights__Player__) */
