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
#include "ScoreCard.h"
#include "helper_functions.h"
#include <memory>

using namespace std;
using namespace helpers;
/* *********************************************************************
Function Name: play_turn
Purpose: To manage a player's turn in the Yahtzee game, allowing them to roll dice, keep selected dice,
            and make decisions about their strategy based on current and kept dice.
Parameters:
            player, a shared pointer to a Player object. It represents the player whose turn is being played.
            score_card, a constant reference to a ScoreCard object. It holds the scoring information and possible categories.
Return Value: A vector of integers representing the dice the player kept at the end of their turn.
Algorithm:
            1) Initialize an empty vector to hold kept dice and set the current roll count to 1.
            2) Loop until the player has rolled 3 times or has kept all 5 dice:
                a) Display the current roll number and available scoring categories.
                b) Display the player's current kept dice.
                c) Get new dice rolls based on the number of dice not kept.
                d) Update potential scoring categories based on the new dice rolls.
                e) Check if the player wants to end their turn or seek help, and handle those cases.
                f) Allow the player to select which dice to keep and update the kept dice vector.
                g) If all dice are kept, end the turn early.
                h) Optionally display the player's category pursuit and target.
            3) Output the final set of kept dice for the player.
Reference: none
c
********************************************************************* */

class Turn
{
public:
    static vector<int> play_turn(const shared_ptr<Player> &player,
                                 const ScoreCard &score_card)
    {

        vector<int> kept_dice = {};
        int current_roll = 1;

        while (current_roll <= 3)
        {
            cout << '\n';
            cout << "Roll " << current_roll << " of 3" << endl;

            cout << "\n Available Categories:" << endl;
            // Show potential categories based on kept dice
            auto potential_categories = score_card.get_possible_categories(kept_dice);
            show_categories(potential_categories);

            cout << player->get_name() << "'s current dice: " << to_string_vector(kept_dice) << '\n'
                 << endl;

            // Get new dice rolls from the player (roll only the dice not kept)
            vector<int> dice_rolls = player->get_dice_roll(5 - kept_dice.size());
            cout << player->get_name() << " rolled: " << to_string_vector(dice_rolls) << '\n'
                 << endl;

            // Recalculate potential categories with the newly rolled dice and Show potential categories based on kept dice
            potential_categories = score_card.get_possible_categories(kept_dice);
            cout << "Potential categories: " << endl;
            // Show updated scoring options
            show_categories(potential_categories);

            // If this is the third roll, the turn automatically ends
            if (current_roll == 3)
            {
                cout << '\n';
                cout << "End of turn." << endl;
                kept_dice.insert(kept_dice.end(), dice_rolls.begin(), dice_rolls.end());
                break;
            }

            // Check if the player wants help (only applies to the computer, where the help system is triggered)
            if (player->wants_help())
            {
                auto help = Computer().get_help(score_card, kept_dice, dice_rolls);
                cout << "Help: \n"
                     << help << '\n'
                     << endl;
            }

            // Check if the player decides to "stand" and keep their dice (ending the turn early)
            if (player->wants_to_stand(score_card, kept_dice, dice_rolls))
            {
                cout << player->get_name() << " chose to stand." << endl;
                kept_dice.insert(kept_dice.end(), dice_rolls.begin(), dice_rolls.end());
                break;
            }

            // Determine which dice the player wants to keep based on the dice rolled and kept
            auto dice_to_keep = player->get_dice_to_keep(score_card, dice_rolls, kept_dice);
            cout << player->get_name() << " kept: " << to_string_vector(dice_to_keep) << '\n'
                 << endl;

            // Add the kept dice to the kept_dice vector
            kept_dice.insert(kept_dice.end(), dice_to_keep.begin(), dice_to_keep.end());

            // If all 5 dice are kept, the turn ends
            if (kept_dice.size() == 5)
            {
                cout << "All dice kept. End of turn.\n"
                     << endl;
                break;
            }

            // Show user pursuit
            optional<map<Category, Reason>> user_pursuit = player->get_category_pursuits(score_card, kept_dice);
            if (user_pursuit.has_value())
            {
                cout << player->get_name() << "'s pursuit: " << endl;
                show_category_pursuits(user_pursuit.value());
            }

            // show the specific dice the player is aiming to roll for their target category
            optional<pair<Category, vector<int>>> user_target = player->get_target(score_card, kept_dice);
            if (user_target.has_value())
            {
                cout << player->get_name() << "'s target: " << CATEGORY_NAMES[user_target.value().first] << " by rolling " << to_string_vector(user_target.value().second) << '\n'
                     << endl;
            }

            current_roll++;
        }

        cout << player->get_name() << "'s final dice for round " << player->get_name() << ": " << to_string_vector(kept_dice) << '\n'
             << endl;

        return kept_dice;
    }
};
