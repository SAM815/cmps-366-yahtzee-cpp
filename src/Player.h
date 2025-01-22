/*
************************************************************
* Name:  Samman Bhetwal                                    *
* Project:  1 yahtzee                                      *
* Class:  CMPS-366                                         *
* Date:  10/26/2024                                        *
*****************************************************************
*/
#pragma once

#include <string>
#include <optional>

#include "Dice.h"
#include "Reason.h"
#include "io_functions.h"

using namespace std;
using namespace helpers;

class ScoreCard;

class Player
{
public:
    // Constructors
    Player() = default;
/* *********************************************************************
Function Name: Player
Purpose: To initialize a Player object with a given name.
Parameters:
            name, a string passed by value. It refers to the name of the player.
Return Value: None
Algorithm:
            1) Set the player's name to the provided name.
Reference: None
********************************************************************* */
    Player(const std::string &name) : name(name)
    {
    }


// Copy constructor for creating a new Player from an existing one
/* *********************************************************************
Function Name: Player (Copy Constructor)
Purpose: To create a copy of an existing Player object.
Parameters:
            other, a Player object passed by reference. It is the source player to copy from.
Return Value: None
Algorithm:
            1) Copy the name from the other Player object.
Reference: None
********************************************************************* */
    Player(const Player &other) : name(other.name)
    {
    }


/* *********************************************************************
Function Name: operator=
Purpose: To assign the values of one Player object to another.
Parameters:
            other, a Player object passed by reference. It refers to the source player for assignment.
Return Value: A reference to the current Player object after assignment.
Algorithm:
            1) Check if the current object is not the same as the other.
            2) Destroy the current object.
            3) Create a new Player with the name from the other object using placement new.
Reference: None
********************************************************************* */
    Player &operator=(const Player &other)
    {
        if (this != &other)
        {
            // Since `name` is const, we cannot assign it a new value.
            // Instead, we need to create a new Player object.
            this->~Player();               // Destroy the current object
            new (this) Player(other.name); // Placement new to reinitialize the object
        }
        return *this;
    }


/* *********************************************************************
Function Name: operator==
Purpose: To compare two Player objects for equality based on their names.
Parameters:
            other, a Player object passed by reference. It is the Player to compare with.
Return Value: A boolean indicating if the two players are equal.
Algorithm:
            1) Check if both Player names are equal.
Reference: None
********************************************************************* */
    bool operator==(const Player &other) const
    {
        return name == other.name;
    }


/* *********************************************************************
Function Name: operator!=
Purpose: To compare two Player objects for inequality.
Parameters:
            other, a Player object passed by reference. It is the Player to compare with.
Return Value: A boolean indicating if the two players are not equal.
Algorithm:
            1) Use the equality operator to check if players are not equal.
Reference: None
********************************************************************* */
    bool operator!=(const Player &other) const
    {
        return !(*this == other);
    }


/* *********************************************************************
Function Name: operator<
Purpose: To compare two Player objects based on their names.
Parameters:
            other, a Player object passed by reference. It is the Player to compare with.
Return Value: A boolean indicating if the current player is less than the other.
Algorithm:
            1) Check if the current Player's name is less than the other Player's name.
Reference: None
********************************************************************* */
    bool operator<(const Player &other) const
    {
        return name < other.name;
    }


/* *********************************************************************
Function Name: get_name
Purpose: To retrieve the name of the Player.
Parameters: None
Return Value: The name of the player as a string.
Algorithm: Return the player's name.
Reference: None
********************************************************************* */
    string get_name() const
    {
        return name;
    }


/* *********************************************************************
Function Name: toss_die
Purpose: To simulate rolling a die and returning the result
Parameters:
            prompt, a string passed by value. It is the message shown to the user before rolling the die
Return Value: An integer representing the result of the die roll
Algorithm:
            1) Display the provided prompt message to the user
            2) Call the get_die_roll function to simulate the die roll
            3) Return the result of the die roll
Reference: None
********************************************************************* */
    static int toss_die(const string &prompt)
    {
        show_message(prompt);
        return get_die_roll();
    }


/* *********************************************************************
Function Name: get_dice_roll
Purpose: To get a specified number of dice rolls from the user
Parameters:
            num_dice, an integer passed by value. It specifies how many dice should be rolled
Return Value: A vector of integers representing the results of the dice rolls
Algorithm:
            1) Call the helpers::get_dice_roll function with the specified number of dice
            2) Return the vector of dice rolls
Reference: None
********************************************************************* */
    virtual vector<int> get_dice_roll(const int num_dice)
    {
        return helpers::get_dice_roll(num_dice);
    }


/* *********************************************************************
Function Name: get_dice_to_keep
Purpose: To determine which dice the player wants to keep after rolling
Parameters:
            score_card, a constant reference to a ScoreCard object. It provides the current state of the game
            dice_rolls, a vector of integers passed by value. It contains the current dice roll results
            kept_dice, a vector of integers passed by value. It holds the dice that the player has chosen to keep
Return Value: A vector of integers representing the dice the player wants to keep
Algorithm:
            1) Display the kept dice to the player
            2) Display the current dice rolls to the player
            3) Call helpers::get_dice_to_keep to get the player's decision on which dice to keep
            4) Return the vector of dice to keep
Reference: None
********************************************************************* */
    virtual vector<int> get_dice_to_keep(const ScoreCard &score_card, const vector<int> &dice_rolls,
                                         const vector<int> &kept_dice)
    {
        show_message("Kept dice: " + to_string_vector(kept_dice));
        show_message("Current dice rolls: " + to_string_vector(dice_rolls));
        return helpers::get_dice_to_keep(dice_rolls);
    }


/* *********************************************************************
Function Name: get_category_pursuits
Purpose: To determine the categories that the player wants to pursue based on kept dice
Parameters:
            score_card, a constant reference to a ScoreCard object. It provides the current state of the game
            kept_dice, a vector of integers passed by value. It holds the dice that the player has chosen to keep
Return Value: An optional map of categories and reasons for pursuing them
Algorithm:
            1) Return nullopt as the default behavior for the Player class
Reference: None
********************************************************************* */
    virtual optional<map<Category, Reason>> get_category_pursuits(const ScoreCard &score_card,
                                                                  const vector<int> &kept_dice)
    {
        return nullopt;
    }


/* *********************************************************************
Function Name: get_target
Purpose: To determine the target category for scoring based on kept dice
Parameters:
            score_card, a constant reference to a ScoreCard object. It provides the current state of the game
            kept_dice, a vector of integers passed by value. It holds the dice that the player has chosen to keep
Return Value: An optional pair containing the target category and the corresponding dice
Algorithm:
            1) Return nullopt as the default behavior for the Player class
Reference: None
********************************************************************* */
    virtual optional<pair<Category, vector<int>>> get_target(const ScoreCard &score_card,
                                                             const vector<int> &kept_dice)
    {
        return nullopt;
    }


/* *********************************************************************
Function Name: wants_to_stand
Purpose: To determine if the player wants to stand (keep their current choice)
Parameters:
            score_card, a constant reference to a ScoreCard object. It provides the current state of the game
            kept_dice, a vector of integers passed by value. It holds the dice that the player has chosen to keep
            dice_rolls, a vector of integers passed by value. It contains the current dice roll results
Return Value: A boolean indicating whether the player wants to stand
Algorithm:
            1) Display the kept dice to the player
            2) Display the current dice rolls to the player
            3) Call helpers::wants_to_stand to get the player's decision
Reference: None
********************************************************************* */
    virtual bool wants_to_stand(const ScoreCard &score_card, const vector<int> &kept_dice,
                                const vector<int> &dice_rolls)
    {
        show_message("Kept dice: " + to_string_vector(kept_dice));
        show_message("Current dice rolls: " + to_string_vector(dice_rolls));
        return helpers::wants_to_stand();
    }


/* *********************************************************************
Function Name: wants_help
Purpose: To determine if the player wants help during the game
Parameters: None
Return Value: A boolean indicating whether the player wants help
Algorithm:
            1) Call helpers::wants_help to get the player's decision
Reference: None
********************************************************************* */
    virtual bool wants_help()
    {
        return helpers::wants_help();
    }

    void inform(const string &message) const
    {
        cout << name << ": " << message << endl;
    }


private:
    const string name;
};

/* *********************************************************************
Function Name: operator==
Purpose: To compare two shared pointers of Player objects for equality.
Parameters:
        lhs, a shared pointer to a Player object. It represents the left-hand side operand in the comparison.
        rhs, a shared pointer to a Player object. It represents the right-hand side operand in the comparison.
Return Value: A boolean value indicating whether the two Player objects are equal.
            Returns true if both pointers are non-null and the underlying Player objects are equal; otherwise, false.
Algorithm:
        1) Check if both shared pointers are non-null.
        2) Dereference the shared pointers and compare the underlying Player objects.
Reference: None
********************************************************************* */
inline bool operator==(const shared_ptr<Player> &lhs, const shared_ptr<Player> &rhs)
{
    return lhs && rhs && *lhs == *rhs;
}


/* *********************************************************************
Function Name: operator!=
Purpose: To compare two shared pointers of Player objects for inequality.
Parameters:
            lhs, a shared pointer to a Player object. It represents the left-hand side operand in the comparison.
            rhs, a shared pointer to a Player object. It represents the right-hand side operand in the comparison.
Return Value: A boolean value indicating whether the two Player objects are not equal.
              Returns true if the two Player objects are not equal; otherwise, false.
Algorithm:
            1) Use the equality operator to check if the Player objects are equal.
            2) Return the negation of the equality result.
Reference: None
********************************************************************* */
inline bool operator!=(const shared_ptr<Player> &lhs, const shared_ptr<Player> &rhs)
{
    return !(lhs == rhs);
}
