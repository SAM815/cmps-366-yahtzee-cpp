/*
************************************************************
* Name:  Samman Bhetwal                                    *
* Project:  1 yahtzee                                      *
* Class:  CMPS-366                                         *
* Date:  10/26/2024                                        *
*****************************************************************
*/
#pragma once

#include "Player.h"

// The Human class inherits from the Player class
class Human : public Player
{
public:
    // Constructor: Initializes the Human player with the name "Human"
    Human() : Player("Human")
    {
    }
};
