/*
************************************************************
* Name:  Samman Bhetwal                                    *
* Project:  1 yahtzee                                      *
* Class:  CMPS-366                                         *
* Date:  10/26/2024                                        *
*****************************************************************
*/
#pragma once

#include "ScoreCard.h"
#include <queue>
#include <memory>

#include "Dice.h"
#include "Turn.h"

class Round
{
public:
/*
*****************************************************************
Function Name: play_round
Purpose: To execute a single round of Yahtzee, managing the turn
        order of players, rolling dice, and updating scores.
Parameters:
        const int round_number: The current round number being played.
        const ScoreCard &score_card: A reference to the current scorecard
            containing the scores of all players.
        const vector<shared_ptr<Player> > &players: A vector of shared pointers
            to Player objects participating in the round.
Return Value: The updated ScoreCard after the round has concluded.
Algorithm:
        1. Retrieve player scores from the scorecard.
        2. Create a player queue based on scores to determine turn order.
        3. Copy the current scorecard to track changes during the round.
        4. Loop until the round is over (when all players have played or
            the scorecard is full):
            a. Get the next player from the queue.
            b. Output the current state of the scorecard.
            c. Announce the player's turn.
            d. Simulate the player's turn by rolling the dice.
            e. Determine the highest scoring category based on the rolled dice.
            f. If a valid category is found, display the score achieved.
            g. Update the scorecard with the new scores.
            h. Re-check if the round is over.
        5. Announce the end of the round.
*****************************************************************
*/
    static ScoreCard play_round(const int round_number, const ScoreCard &score_card,
                                const vector<shared_ptr<Player>> &players)
    {
        // Get the player scores and create a queue of players which determines the order of players
        auto player_scores = score_card.get_player_scores(players);
        auto player_queue = get_player_queue(player_scores);

        // Copy the current scorecard
        ScoreCard current_score_card = score_card;

        // Check if the round is over (when all players have played or the scorecard is full)
        bool round_over = player_queue.empty() || score_card.is_full();
        while (!round_over)
        {
            // Get the next player from the queue and remove them from the front
            auto player = player_queue.front();
            player_queue.pop();

            // Output the current state of the scorecard to the console
            cout << current_score_card.get_string() << endl;

            // Announce the player's turn
            cout << "It's " << player->get_name() << "'s turn." << endl;

            // Simulate the player's turn by rolling the dice
            vector<int> dice = Turn::play_turn(player, score_card);

            // Determine the highest scoring category based on the rolled dice
            auto scored_category = score_card.get_max_scoring_category(dice);

            // If a valid scoring category is found, display the score
            if (scored_category.has_value())
            {
                cout << player->get_name() << " scored " << get_score(dice, scored_category.value()) << " points in the "
                     << CATEGORY_NAMES[scored_category.value()] << " category.\n\n"
                     << endl;
            }
            // Update the scorecard with the new scores for this player and round
            current_score_card = current_score_card.add_entry(round_number, player, dice);

            // Check again if the round is over (queue is empty or scorecard is full)
            round_over = player_queue.empty() || current_score_card.is_full();
        }

        // Announce the end of the round
        cout << "Round ends" << endl;

        // Return the updated scorecard after the round
        return current_score_card;
    }


private:
/*
*****************************************************************
Function Name: get_player_queue
Purpose: To create a queue of players ordered by their scores,
        determining who plays first based on the lowest score.
Parameters:
    const map<shared_ptr<Player>, int> &player_scores: A map of
            players and their corresponding scores.
Return Value: A queue of shared pointers to Player objects
                in the order they will take their turns.
Algorithm:
        1. Extract the top two players from the player_scores map.
        2. Compare their scores.
        3. If scores are tied, conduct a tie-breaker to determine the
            turn order.
        4. If scores differ, enqueue players based on their scores
            (lowest score goes first).
*****************************************************************
  */
    static queue<shared_ptr<Player>> get_player_queue(const map<shared_ptr<Player>, int> &player_scores)
    {
        queue<Player> player_queue;

        // Extract the players and their scores (for comparison)
        const auto player_1 = player_scores.begin()->first;
        const auto player_2 = player_scores.rbegin()->first;

        const int player_1_score = player_scores.begin()->second;
        const int player_2_score = player_scores.rbegin()->second;

        // If both players have the same score, conduct a tie-breaker to determine the turn order
        if (player_1_score == player_2_score)
        {
            if (player_1_score == 0)
            {
                cout << "Determining who goes first by rolling a die." << endl;
            }
            else
            {
                cout << "Both players have a score of " << player_1_score << ". Conducting a tie breaker." << endl;
            }
            // Return a player queue based on the tie-breaker result
            return queue_from_tie_breaker(player_1, player_2);
        }

        // If the scores differ, enqueue players based on their scores (lowest score goes first)
        return enqueue_players_by_score(player_scores);
    }


/*
*****************************************************************
Function Name: queue_from_tie_breaker
Purpose: To resolve a tie-breaker between two players to determine
        who will play first.
Parameters:
        const shared_ptr<Player> &player_1: A shared pointer to the
            first player in the tie.
        const shared_ptr<Player> &player_2: A shared pointer to the
            second player in the tie.
Return Value: A queue of shared pointers to Player objects,
            ordered by the result of the tie-breaker.
Algorithm:
        1. Identify the human and computer players based on their names.
        2. Simulate a tie-breaker, e.g., rolling a die.
        3. Depending on the result, enqueue players in the correct order.
*****************************************************************
*/
    static queue<shared_ptr<Player>>
    queue_from_tie_breaker(const shared_ptr<Player> &player_1, const shared_ptr<Player> &player_2)
    {
        auto player_queue = queue<shared_ptr<Player>>();

        // Identify human and computer players from the list
        const auto human_player = player_1->get_name() == "Human" ? player_1 : player_2;
        const auto computer_player = player_1->get_name() == "Computer" ? player_1 : player_2;

        // Simulate a tie-breaker to decide who plays first (e.g., rolling a die)
        if (human_won_tie_breaker())
        {
            // If the human wins, they are added first in the queue
            player_queue.push(human_player);
            player_queue.push(computer_player);
        }
        else
        {
            // If the computer wins, they are added first
            player_queue.push(computer_player);
            player_queue.push(human_player);
        }

        // Return the player queue after the tie-breaker
        return player_queue;
    }


/*
*****************************************************************
Function Name: enqueue_players_by_score
Purpose: To create a queue of players sorted by their scores in
        ascending order.
Parameters:
            const map<shared_ptr<Player>, int> &player_scores: A map of
            players and their corresponding scores.
Return Value: A queue of shared pointers to Player objects,ordered by their scores.
Algorithm:
        1. Convert the player_scores map to a vector of player-score pairs.
        2. Sort the vector by scores in ascending order.
        3. Create a queue and enqueue players in order of their scores.
*****************************************************************
   */
    static queue<shared_ptr<Player>>
    enqueue_players_by_score(const map<shared_ptr<Player>, int> &player_scores)
    {
        // Convert the player scores map to a vector of player-score pairs
        vector<pair<shared_ptr<Player>, int>> player_score_vector(player_scores.begin(), player_scores.end());

        // Sort the players by their scores in ascending order
        sort(player_score_vector.begin(), player_score_vector.end(),
             [](const pair<shared_ptr<Player>, int> &a, const pair<shared_ptr<Player>, int> &b)
             {
                 return a.second < b.second;
             });

        // Create a queue and enqueue players in order of their scores (lowest to highest)
        queue<shared_ptr<Player>> player_queue;
        for (const auto &[player, score] : player_score_vector)
        {
            player_queue.push(player);
        }

        // Return the ordered queue of players
        return player_queue;
    }
};
