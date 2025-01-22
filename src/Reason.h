/*
************************************************************
* Name:  Samman Bhetwal                                    *
* Project:  1 yahtzee                                      *
* Class:  CMPS-366                                         *
* Date:  10/26/2024                                        *
*****************************************************************
*/
#pragma once

#include <vector>
#include "ScoreCategory.h"

using namespace std;

// Struct to represent the reasoning behind pursuing a specific category in the game
struct Reason
{

    // The current dice values the player has at the moment
    vector<int> current_dice;

    // The category that the player is currently pursuing based on their dice
    Category pursued_category;

    // The maximum possible score that can be achieved by pursuing this category
    int max_score;

    // The dice values the player would need to roll in order to achieve the maximum score in this category
    vector<int> roll_to_get_max;

    // The minimum possible score that can be achieved by pursuing this category
    int min_score;

    // The dice values the player would need to roll in order to achieve the minimum score in this category
    vector<int> roll_to_get_min;
};
