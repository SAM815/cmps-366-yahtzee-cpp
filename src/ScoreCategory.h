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
#include "helper_functions.h"

using namespace std;

// Enum class for all possible categories
enum class Category
{
    Ones = 1,
    Twos = 2,
    Threes = 3,
    Fours = 4,
    Fives = 5,
    Sixes = 6,
    ThreeOfAKind,
    FourOfAKind,
    FullHouse,
    FourStraight,
    FiveStraight,
    Yahtzee
};

// Function prototypes for scoring and checking applicable categories
vector<Category> get_applicable_categories(const vector<int> &dice);

int get_score(const vector<int> &dice, Category category);

bool is_applicable_category(const vector<int> &dice, Category category);

// Mapping of category enums to their corresponding string names
inline map<Category, string> CATEGORY_NAMES = {
    {Category::Ones, "Ones"},
    {Category::Twos, "Twos"},
    {Category::Threes, "Threes"},
    {Category::Fours, "Fours"},
    {Category::Fives, "Fives"},
    {Category::Sixes, "Sixes"},
    {Category::ThreeOfAKind, "Three of a Kind"},
    {Category::FourOfAKind, "Four of a Kind"},
    {Category::FullHouse, "Full House"},
    {Category::FourStraight, "Four Straight"},
    {Category::FiveStraight, "Five Straight"},
    {Category::Yahtzee, "Yahtzee"}};

// List of all categories for easy iteration
const vector<Category> CATEGORIES = {
    Category::Ones,
    Category::Twos,
    Category::Threes,
    Category::Fours,
    Category::Fives,
    Category::Sixes,
    Category::ThreeOfAKind,
    Category::FourOfAKind,
    Category::FullHouse,
    Category::FourStraight,
    Category::FiveStraight,
    Category::Yahtzee};


/* *********************************************************************
Function Name: get_applicable_categories
Purpose: To determine which scoring categories are applicable based on the rolled dice.
Parameters:
            dice, a vector of integers passed by reference. It holds the values of the rolled dice.
Return Value: A vector of Category enums representing the applicable scoring categories.
Algorithm:
            1) Initialize an empty vector for applicable categories.
            2) Iterate over all defined categories.
            3) For each category, check if it is applicable using the is_applicable_category function.
            4) If applicable, add the category to the vector.
            5) Return the vector of applicable categories.
Reference: None
********************************************************************* */
inline vector<Category> get_applicable_categories(const vector<int> &dice)
{
    vector<Category> applicable_categories;
    for (Category category : CATEGORIES)
    {
        if (is_applicable_category(dice, category))
        {
            applicable_categories.push_back(category);
        }
    }
    return applicable_categories;
}


/* *********************************************************************
Function Name: get_score
Purpose: To calculate the score based on the rolled dice and the chosen category.
Parameters:
            dice, a vector of integers passed by reference. It holds the values of the rolled dice.
            category, an enum of type Category. It specifies the scoring category to evaluate.
Return Value: An integer representing the score for the specified category. Returns 0 if the category is not applicable.
Algorithm:
            1) Check if the category is applicable using is_applicable_category.
            2) If not applicable, return 0.
            3) Use a switch statement to calculate the score based on the selected category.
            4) Return the calculated score.
Reference: None
********************************************************************* */
inline int get_score(const vector<int> &dice, Category category)
{
    if (!is_applicable_category(dice, category))
    {
        return 0;
    }

    // Calculate score based on the category using a switch statement
    switch (category)
    {
    case Category::Ones:
        return count_n(dice, 1);
    case Category::Twos:
        return count_n(dice, 2) * 2;
    case Category::Threes:
        return count_n(dice, 3) * 3;
    case Category::Fours:
        return count_n(dice, 4) * 4;
    case Category::Fives:
        return count_n(dice, 5) * 5;
    case Category::Sixes:
        return count_n(dice, 6) * 6;
    case Category::ThreeOfAKind:
        return is_applicable_category(dice, Category::ThreeOfAKind) ? sum(dice) : 0;
    case Category::FourOfAKind:
        return is_applicable_category(dice, Category::FourOfAKind) ? sum(dice) : 0;
    case Category::FullHouse:
        return is_applicable_category(dice, Category::FullHouse) ? 25 : 0;
    case Category::FourStraight:
        return is_applicable_category(dice, Category::FourStraight) ? 30 : 0;
    case Category::FiveStraight:
        return is_applicable_category(dice, Category::FiveStraight) ? 40 : 0;
    case Category::Yahtzee:
        return is_applicable_category(dice, Category::Yahtzee) ? 50 : 0;
    default:
        return 0;
    };
};


/* *********************************************************************
Function Name: is_applicable_category
Purpose: To check if a given scoring category can be achieved with the current rolled dice.
Parameters:
            dice, a vector of integers passed by reference. It holds the values of the rolled dice.
            category, an enum of type Category. It specifies the scoring category to evaluate.
Return Value: A boolean indicating whether the category is applicable for scoring.
Algorithm:
            1) Use a switch statement to evaluate the category.
            2) For each category, use the appropriate helper function to check applicability.
            3) Return true if applicable; otherwise, return false.
Reference: None
********************************************************************* */
inline bool is_applicable_category(const vector<int> &dice, Category category)
{
    switch (category)
    {
    case Category::Yahtzee:
        return atleast_n_same(dice, 5);
    case Category::FiveStraight:
        return five_sequence(dice);
    case Category::FourStraight:
        return four_sequence(dice);
    case Category::FullHouse:
        return full_house(dice);
    case Category::FourOfAKind:
        return atleast_four_same(dice);
    case Category::ThreeOfAKind:
        return atleast_three_same(dice);
    case Category::Sixes:
        return contains_n(dice, 6);
    case Category::Fives:
        return contains_n(dice, 5);
    case Category::Fours:
        return contains_n(dice, 4);
    case Category::Threes:
        return contains_n(dice, 3);
    case Category::Twos:
        return contains_n(dice, 2);
    case Category::Ones:
        return contains_n(dice, 1);
    default:
        return false;
    };
};


/* *********************************************************************
Function Name: is_possible_category
Purpose: To determine whether a specific Yahtzee scoring category is achievable
   based on the current rolled dice.
Parameters:
            const vector<int> &dice: A reference to a vector of integers representing
   the current rolled dice. This vector is passed by reference and is not modified.
            Category category: The scoring category to be evaluated for possibility.
Return Value: A boolean value indicating whether the specified category can
   be achieved with the given dice rolls.
Algorithm:
            1) Check if the dice vector is empty. If it is, return true as any
               category is possible.
            2) Calculate the number of available slots for additional dice rolls
               by subtracting the size of the dice vector from 5.
            3) Use a switch statement to evaluate the given category:
               a) For Yahtzee, check if all dice are the same.
               b) For FiveStraight, ensure there are no repeated numbers and
                  that the dice do not contain both 1 and 6.
               c) For FourStraight, ensure there are less than 2 repeated numbers.
               d) For FullHouse, verify that there are at most 2 unique dice values
                  and that the maximum count of any number does not exceed 3.
               e) For FourOfAKind, confirm that the maximum count of any number
                  plus the slots left is at least 4.
               f) For ThreeOfAKind, check similarly for a count of at least 3.
               g) For Ones, Twos, Threes, Fours, and Sixes, check if the respective
                  number exists in the dice or if the size of the dice is less
                  than 5.
Reference: None
********************************************************************* */
inline bool is_possible_category(const vector<int> &dice, Category category)
{
    if (dice.empty())
        return true;
    int slots_left = 5 - dice.size();
    switch (category)
    {
    case Category::Yahtzee:
        return all_same(dice);
    case Category::FiveStraight:
        return num_repeats(dice) < 1 &&
               !(contains_n(dice, 1) && contains_n(dice, 6));
    case Category::FourStraight:
        return num_repeats(dice) < 2;
    case Category::FullHouse:
        return count_unique(dice) <= 2 && max_count(dice) <= 3;
    case Category::FourOfAKind:
        return slots_left + max_count(dice) >= 4;
    case Category::ThreeOfAKind:
        return slots_left + max_count(dice) >= 3;
    case Category::Sixes:
        return contains_n(dice, 6) || dice.size() < 5;
    case Category::Fives:
        return contains_n(dice, 5) || dice.size() < 5;
    case Category::Fours:
        return contains_n(dice, 4) || dice.size() < 5;
    case Category::Threes:
        return contains_n(dice, 3) || dice.size() < 5;
    case Category::Twos:
        return contains_n(dice, 2) || dice.size() < 5;
    case Category::Ones:
        return contains_n(dice, 1) || dice.size() < 5;
    default:
        return true;
    };
};
