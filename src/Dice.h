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
#include <random>

using namespace std;

class Dice
{
public:
/* *********************************************************************
Function Name: roll_die
Purpose: To simulate the rolling of a single six-sided die.
Parameters: None
Return Value: An integer representing the result of the die roll (1 to 6).
Algorithm:
        1) Generate a random number between 1 and 6 using a random number generator.
        2) Return the generated number as the result of the die roll.
Reference: none
********************************************************************* */
    static int roll_die()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 6);

        return dis(gen);
    }


/* *********************************************************************
    Function Name: roll_dice
    Purpose: To roll a specified number of dice and return their values.
    Parameters:
                num_dice, an integer passed by value. It specifies how many dice to roll.
    Return Value: A vector of integers representing the results of each die roll.
    Algorithm:
            1) Create a vector to store the results of each dice roll.
            2) Reserve space in the vector to optimize memory allocation for the specified number of dice.
            3) Loop through the number of dice to roll.
            4) In each iteration, roll a die and store the result in the vector.
            5) Return the vector containing all the dice roll results.
    Reference: none
    ********************************************************************* */
    static vector<int> roll_dice(const int num_dice)
    {
        // Vector to store the results of each dice roll
        vector<int> dice_rolls;

        // Reserve space for the specified number of dice to optimize memory allocation
        dice_rolls.reserve(num_dice);

        for (int i = 0; i < num_dice; i++)
        {

            // Roll a die and add the result to the vector
            dice_rolls.push_back(roll_die());
        }

        // Return the vector containing all the dice roll results
        return dice_rolls;
    }

    
};
