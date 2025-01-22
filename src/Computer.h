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

class Computer : public Player
{
public:
    // Constructor: Initialize the player with the name "Computer"
    Computer() : Player("Computer")
    {
    }
/* *********************************************************************
Function Name: get_dice_roll
Purpose: To handle the dice roll for the computer's turn
Parameters:
            num_dice, an integer. It refers to the number of dice to roll
Return Value: A vector of integers representing the rolled dice values
Algorithm:
            1) Check if human wants to manually input the dice roll
            2) If yes, call the Player's get_dice_roll function
            3) If no, roll the dice using Dice::roll_dice and return the result
Reference: none
********************************************************************* */
    vector<int> get_dice_roll(const int num_dice) override
    {

        // Optionally allow the human to manually input dice rolls for testing
        auto human_wants_to_roll = human_wants_to_roll_for_computer();
        if (human_wants_to_roll)
        {
            return Player::get_dice_roll(num_dice);
        }
        auto roll = Dice::roll_dice(num_dice);
        return roll;
    }

/* *********************************************************************
Function Name: generate_possible_final_rolls
Purpose: To generate all possible final rolls based on the kept dice
Parameters:
           kept_dice, a vector of integers representing the dice kept
Return Value: A vector of vectors of integers representing all possible final rolls
Algorithm:
           1) Generate all possible rolls based on the current dice size
           2) Merge kept dice with each generated roll
           3) Sort each final roll and store the results
Reference: none
********************************************************************* */
    static vector<vector<int>> generate_possible_final_rolls(const vector<int> &kept_dice)
    {
        // Generate all possible rolls based on the current dice size
        auto possible_rolls = dice_combinations(5 - kept_dice.size());

        // Prepare the possible final rolls by merging kept dice and possible rolls
        vector<vector<int>> possible_final_rolls;
        possible_final_rolls.reserve(possible_rolls.size()); // Reserve memory to avoid resizing

        // Merge kept dice with each generated roll, then sort and store the results
        for (const auto &roll : possible_rolls)
        {
            auto final_roll = concatenate(kept_dice, roll);
            sort(final_roll.begin(), final_roll.end());
            possible_final_rolls.push_back(final_roll);
        }

        return possible_final_rolls;
    }

/* *********************************************************************
Function Name: calculate_scores
Purpose: To calculate scores for all possible final rolls based on open categories
Parameters:
            final_rolls, a vector of vectors of integers representing final rolls
            score_card, a ScoreCard object containing the current game state
Return Value: A vector of pairs containing final rolls and their corresponding scores
Algorithm:
            1) Get open categories from the score card
            2) For each possible roll, calculate its score for each open category
            3) Store each roll and its score in the scores vector
            4) Sort scores in descending order of score
     Reference: none
********************************************************************* */
    static vector<pair<vector<int>, int>> calculate_scores(const vector<vector<int>> &final_rolls,
                                                           const ScoreCard &score_card)
    {

        // Store roll and its corresponding score
        vector<pair<vector<int>, int>> scores;

        // Get unfilled categories
        auto open_categories = score_card.get_open_categories();

        // For each possible roll, calculate its score for each open category
        for (const auto &final_roll : final_rolls)
        {
            for (const auto &category : open_categories)
            {
                int score = get_score(final_roll, category);
                // appends a pair (containing final_roll and score) to the scores vector.
                scores.emplace_back(final_roll, score);
            }
        }

        // Sort scores in descending order of score
        sort(scores.begin(), scores.end(), [](const pair<vector<int>, int> &a, const pair<vector<int>, int> &b)
             { return a.second > b.second; });

        return scores;
    }

/***********************************************************************
Function Name: find_best_roll
Purpose: To find the best roll by maximizing score and minimizing the difference from the current roll
Parameters:
            scores, a vector of pairs containing rolls and their corresponding scores
            dice_rolls, a vector of integers representing the current dice rolls
Return Value: A vector of integers representing the best roll
Algorithm:
            1) Initialize max_score with the score of the first roll
            2) Iterate over all scores to find the best roll with minimal dice difference
            3) Return the roll that has the highest score and the least difference from current rolls
Reference: none
********************************************************************* */
    static vector<int> find_best_roll(const vector<pair<vector<int>, int>> &scores, const vector<int> &dice_rolls)
    {
        int max_score = scores[0].second;
        vector<int> best_roll = scores[0].first;
        int best_roll_diff_size = difference(best_roll, dice_rolls).size();

        // Iterate over all scores to find the best roll with minimal dice difference
        for (const auto &[roll, score] : scores)
        {
            // Exit early if the score is lower than the max score
            if (score < max_score)
                break;

            auto roll_diff = difference(roll, dice_rolls);
            if (roll_diff.size() < best_roll_diff_size)
            {
                best_roll = roll;
                best_roll_diff_size = roll_diff.size();
            }
        }

        return best_roll;
    }

/***********************************************************************
Function Name: determine_dice_to_keep
Purpose: To determine which dice to keep based on the best roll
Parameters:
            best_roll, a vector of integers representing the best roll
            dice_rolls, a vector of integers representing the current dice rolls
            kept_dice, a vector of integers representing the dice kept from previous rolls
Return Value: A vector of integers representing the dice to keep for the next roll
Algorithm:
            1) Identify dice needed to complete the best roll
            2) Return only the dice that match the current roll
Reference: none
********************************************************************* */
    static vector<int> determine_dice_to_keep(const vector<int> &best_roll, const vector<int> &dice_rolls,
                                              const vector<int> &kept_dice)
    {
        // Identify dice needed to complete the best roll
        vector<int> dice_needed = difference(best_roll, kept_dice);

        // Return only the dice that match the current roll
        return intersection(dice_needed, dice_rolls);
    }

/*********************************************************************
Function Name: get_best_roll
Purpose: To find the best roll the computer should aim for based on the scorecard and kept dice
Parameters:
            score_card, a ScoreCard object containing the current game state
            kept_dice, a vector of integers representing the dice kept
Return Value: A vector of integers representing the best roll
Algorithm:
            1) Generate possible final rolls
            2) Calculate scores for all possible final rolls
            3) Find the best roll with the highest score and minimal difference
Reference: none
********************************************************************* */
    static vector<int> get_best_roll(const ScoreCard &score_card, const vector<int> &kept_dice)
    {

        // Step 1: Generate possible final rolls
        auto possible_final_rolls = generate_possible_final_rolls(kept_dice);

        // Step 2: Calculate scores for all possible final rolls
        auto scores = calculate_scores(possible_final_rolls, score_card);

        // Step 3: Find the best roll with the highest score and minimal difference
        auto best_roll = find_best_roll(scores, kept_dice);

        return best_roll;
    }

/**********************************************************************
Function Name: get_dice_to_keep
Purpose: To determine which dice to keep for the next roll
Parameters:
        score_card, a ScoreCard object containing the current game state
        dice_rolls, a vector of integers representing the current dice rolls
        kept_dice, a vector of integers representing the dice kept
Return Value: A vector of integers representing the dice to keep for the next roll
Algorithm:
           1) Concatenate kept_dice and dice_rolls to get final_roll
           2) Check for specific categories and handle them accordingly
           3) Generate possible final rolls
           4) Calculate scores for all possible final rolls
           5) Find the best roll and determine which dice to keep
Reference: ChatGPT for brainstorming and correcting the function.
   ********************************************************************* */
    vector<int> get_dice_to_keep(const ScoreCard &score_card, const vector<int> &dice_rolls,
                                 const vector<int> &kept_dice) override
    {

        // Step 0:
        vector<int> final_roll = concatenate(kept_dice, dice_rolls);
        auto open_categories = score_card.get_open_categories();
        if (contains(open_categories, Category::Yahtzee) && is_applicable_category(final_roll, Category::Yahtzee))
        {
            return dice_rolls;
        }
        if (contains(open_categories, Category::FiveStraight))
        {
            auto unique_dice = get_unique(dice_rolls);
            final_roll = concatenate(kept_dice, unique_dice);
            if (is_applicable_category(final_roll, Category::FiveStraight))
            {
                return unique_dice;
            }
        }
        if (contains(open_categories, Category::FourStraight))
        {
            auto unique_dice = get_unique(dice_rolls);
            final_roll = concatenate(kept_dice, unique_dice);
            if (is_applicable_category(final_roll, Category::FourStraight))
            {
                return unique_dice;
            }
        }
        // Step 1: Generate possible final rolls
        auto possible_final_rolls = generate_possible_final_rolls(kept_dice);

        // Step 2: Calculate scores for all possible final rolls
        auto scores = calculate_scores(possible_final_rolls, score_card);

        // Step 3: Find the best roll with the highest score and minimal difference
        auto best_roll = find_best_roll(scores, dice_rolls);

        // Step 4: Determine which dice to keep
        auto dice_to_keep = determine_dice_to_keep(best_roll, dice_rolls, kept_dice);

        return dice_to_keep;
    }

/**********************************************************************
Function Name: get_category_pursuits
Purpose: To identify potential categories that the computer could pursue
            based on the current dice and scorecard.
Parameters:
            score_card, a constant reference to a ScoreCard object. It holds
            the current state of the scorecard.
            kept_dice, a vector of integers. It contains the dice values that
            the computer has decided to keep for the current turn.
Return Value: An optional map of Category to Reason. It represents the
                categories the computer can pursue along with reasons for
                pursuing each category.
Algorithm:
            1) Generate all possible final rolls based on the kept dice.
            2) Retrieve possible categories from the scorecard that can
                be pursued with the kept dice.
            3) For each category, calculate the minimum and maximum scores
                possible using the generated rolls.
            4) Store the results in a map, associating each category with
                the corresponding reasons.
Reference: none
Optional: cppreference.com
********************************************************************* */
    optional<map<Category, Reason>> get_category_pursuits(const ScoreCard &score_card,
                                                          const vector<int> &kept_dice) override
    {
        auto possible_final_rolls = generate_possible_final_rolls(kept_dice);
        auto possible_categories = score_card.get_possible_categories(kept_dice);

        // Find the minimum and maximum scores for each category
        // Store reasons for pursuing categories

        map<Category, Reason> category_pursuits;

        // For each category, find the best and worst possible outcomes based on rolls
        for (const auto category : possible_categories)
        {
            int min_score = numeric_limits<int>::max();
            int max_score = numeric_limits<int>::min();

            int min_dice_diff = numeric_limits<int>::max();
            int max_dice_diff = numeric_limits<int>::max();

            vector<int> roll_to_get_max;
            vector<int> roll_to_get_min;

            for (const auto &roll : possible_final_rolls)
            {
                int dice_diff = difference(roll, kept_dice).size();
                if (get_score(roll, category) >= max_score && dice_diff <= max_dice_diff)
                {
                    max_score = get_score(roll, category);
                    roll_to_get_max = difference(roll, kept_dice);
                    max_dice_diff = dice_diff;
                }

                if (get_score(roll, category) < min_score && dice_diff <= min_dice_diff)
                {
                    if (min_score == 0)
                        continue;
                    min_score = get_score(roll, category);
                    roll_to_get_min = difference(roll, kept_dice);
                    min_dice_diff = dice_diff;
                }
            }

            category_pursuits[category] = Reason{
                kept_dice, category, max_score, roll_to_get_max, min_score, roll_to_get_min};
        }
        return category_pursuits;
    }

/**********************************************************************
Function Name: get_target
Purpose: To identify the best category and strategy for the computer
            based on the current kept dice and scorecard.
Parameters:
            score_card, a constant reference to a ScoreCard object. It holds
            the current state of the scorecard.
            kept_dice, a vector of integers. It contains the dice values that
            the computer has decided to keep for the current turn.
Return Value: An optional pair containing the best category and the dice
                combination needed to achieve it.
Algorithm:
            1) Determine the best possible roll that can be achieved
                with the kept dice.
            2) Identify the category that offers the maximum score for
                the best roll.
            3) If a category exists, return it along with the difference
                between the best roll and the kept dice.
Reference: none
Optional: cppreference.com
********************************************************************* */
    optional<pair<Category, vector<int>>> get_target(const ScoreCard &score_card,
                                                     const vector<int> &kept_dice) override
    {
        auto best_roll = get_best_roll(score_card, kept_dice);
        auto category = score_card.get_max_scoring_category(best_roll);
        if (!category.has_value())
        {
            return nullopt;
        }
        return make_pair(category.value(), difference(best_roll, kept_dice));
    }

/**********************************************************************
Function Name: wants_to_stand
Purpose: To decide whether the computer should stop rolling based on
            its current scorecard and kept dice.
Parameters:
            score_card, a constant reference to a ScoreCard object. It holds
            the current state of the scorecard.
            kept_dice, a vector of integers. It contains the dice values
            that the computer has decided to keep.
            dice_rolls, a vector of integers. It represents the current
            dice rolls in the turn.
Return Value: A boolean value indicating whether the computer wants to
                stop rolling (true) or continue rolling (false).
Algorithm:
            1) Determine which dice should be kept based on the scorecard
                and current dice rolls.
            2) Compare the dice to keep with the rolled dice; if they match,
                the computer should stop rolling.
Reference: none
    ********************************************************************* */
    bool wants_to_stand(const ScoreCard &score_card, const vector<int> &kept_dice,
                        const vector<int> &dice_rolls) override
    {
        auto dice_to_keep = get_dice_to_keep(score_card, dice_rolls, kept_dice);

        // If all dice should be kept, stop rolling
        return unordered_equal(dice_to_keep, dice_rolls);
    }

/**********************************************************************
Function Name: wants_help
Purpose: To determine if the computer requires assistance (always
            returns false).
Parameters: none
Return Value: A boolean value indicating if assistance is required
                (always false).
Algorithm:
            1) Return false as the computer operates autonomously.
Reference: none
********************************************************************* */
    bool wants_help() override
    {
        return false;
    }
/* *********************************************************************
Function Name: get_help
Purpose: To generate advice for a human player based on the current
            game state, providing suggestions on which dice to keep and
            potential scoring categories to pursue.
Parameters:
            score_card, a constant reference to a ScoreCard object. It holds
            the current state of the scorecard.
            kept_dice, a vector of integers. It contains the dice values
            that the player has decided to keep.
            dice_rolls, a vector of integers. It represents the current
            dice rolls in the turn.
Return Value: A string containing advice for the player regarding which
                dice to keep and potential scoring categories to target.
Algorithm:
            1) Retrieve recommended dice to keep based on the current
                scorecard and rolled dice.
            2) Combine the kept dice and recommended dice for the final
                suggestion.
            3) Get potential category pursuits and their associated reasons.
            4) Identify the best target category for the player and suggest
                dice combinations to achieve it.
            5) Advise whether the player should stand or keep rolling based
                on the game state.
Reference: none
********************************************************************* */
    string get_help(const ScoreCard &score_card, const vector<int> &kept_dice, const vector<int> &dice_rolls)
    {

        // Get the recommended dice to keep based on the current scorecard and dice rolls
        auto dice_to_keep = get_dice_to_keep(score_card, dice_rolls, kept_dice);

        // Combine kept dice and the newly suggested dice to keep
        // This is the final dice that we hope to put in the scorecard
        auto help_dice = concatenate(kept_dice, dice_to_keep);

        // Determine which categories the player could pursue based on the dice
        // Gets a map of category and the Reason
        // Reason is a struct that includes details such as max and min scores and the dice combination to achieve them
        auto category_pursuits = get_category_pursuits(score_card, help_dice);

        // Get the player's target category and the best dice combination to achieve it
        auto target = get_target(score_card, help_dice);

        string help_message = "You should keep: " + to_string_vector(dice_to_keep) + " becauseL\n";

        // Loop through the possible category pursuits and give reasons for each
        for (const auto &[category, reason] : category_pursuits.value())
        {

            // If the minimum score for the category is 0, provide advice based on max score potential
            if (reason.min_score == 0)
            {
                help_message += " - You can get " + CATEGORY_NAMES[reason.pursued_category] +
                                " with a score of " + to_string(reason.max_score) + ". For example, "
                                                                                    "by rolling " +
                                to_string_vector(reason.roll_to_get_max) + "\n";
                continue;
            }
            // Otherwise, provide both the minimum and maximum score potential and the dice needed
            help_message += " - You can get " + CATEGORY_NAMES[reason.pursued_category] +
                            " with a minimum score of " + to_string(reason.min_score) +
                            " by getting " + to_string_vector(reason.roll_to_get_min) +
                            " and a maximum score of " + to_string(reason.max_score) +
                            " by rolling " + to_string_vector(reason.roll_to_get_max) + "\n";
        }

        // Advise the player on which category they should target based on current rolls
        help_message += "\nConsidering this, your target should be to get ";
        if (target.has_value())
        {
            help_message += CATEGORY_NAMES[target.value().first] + ". A way to do this would be to roll " +
                            to_string_vector(target.value().second) + " in your subsequent rolls."
                                                                      "\n";
        }
        else
        {
            help_message += "None\n";
        }

        // Suggest if the player should stop rolling (stand) or keep rolling based on the game state
        if (wants_to_stand(score_card, kept_dice, dice_rolls))
        {
            help_message += "You should stand.\n";
        }
        else
        {
            help_message += "Do not stand. You should keep rolling.\n";
        }

        // Advise the player on whether to keep dice or roll all of them again
        if (dice_to_keep.empty())
        {
            help_message += "Do not keep any dice. You should roll all the dice.\n";
        }
        else
        {
            help_message += "You should keep the following dice before you roll: " + to_string_vector(dice_to_keep);
        }
        return help_message;
    }
};
 
