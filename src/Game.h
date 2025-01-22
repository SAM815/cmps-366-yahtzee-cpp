/*
************************************************************
* Name:  Samman Bhetwal                                    *
* Project:  1 yahtzee                                      *
* Class:  CMPS-366                                         *
* Date:  10/26/2024                                        *
*****************************************************************
*/
#pragma once

#include <memory>

#include "Human.h"
#include "ScoreCard.h"
#include "Round.h"

struct Game
{
    const ScoreCard score_card;
    const int current_round;
    const vector<shared_ptr<Player>> players;

/* *********************************************************************
Function Name: Game (Constructor)
Purpose: Initializes a Game object with a scorecard, round number, and list of players.
Parameters:
            score_card, a ScoreCard passed by reference. It represents the current scorecard.
            current_round, an integer passed by value. It indicates the current round number.
            players, a vector of shared_ptr<Player> passed by reference. It contains the players in the game.
Return Value: None
Algorithm:
        1) Initialize the score_card with the provided scorecard.
        2) Set the current_round to the given round number.
        3) Initialize the players vector with the provided list of players.
Reference: none
********************************************************************* */
    Game(const ScoreCard &score_card, const int current_round,
         const vector<shared_ptr<Player>> &players) : score_card(score_card),
                                                      current_round(current_round), players(players)
    {
    }


/* *********************************************************************
Function Name: Game (Copy Constructor)
Purpose: Creates a copy of another Game object.
Parameters:
            other, a Game object passed by reference. It represents the Game to copy from.
Return Value: None
Algorithm:
        1) Initialize the score_card with the scorecard of the other Game object.
        2) Set the current_round to the round number of the other Game object.
        3) Copy the players vector from the other Game object.
Reference: none
********************************************************************* */
    Game(const Game &other) : score_card(other.score_card), current_round(other.current_round), players(other.players)
    {
    }


/* *********************************************************************
    Function Name: deserialize
    Purpose: Reconstruct a Game object from a serialized string (saved game state).
    Parameters:
                serial, a string passed by reference. It contains the serialized representation of the game state.
    Return Value: A Game object reconstructed from the serialized data.
    Algorithm:
            1) Create shared pointers for the human and computer players.
            2) Split the serialized string into individual lines representing game state.
            3) Extract the round number from the appropriate line.
            4) Find the start index for the scorecard data.
            5) Extract and reconstruct the scorecard from the serialized lines.
            6) Return a new Game object with the reconstructed scorecard, round number, and players.
    Reference: none
    ********************************************************************* */

    static Game deserialize(const string &serial)
    {

        // Create a shared_ptr to the human player
        auto human = make_shared<Human>();

        // Create a shared_ptr to the human player
        auto computer = make_shared<Computer>();

        const vector<shared_ptr<Player>> players = {human, computer};

        // split into individual lines, each line is string representation of game's saved state
        vector<string> lines = split(serial, '\n');

        int round_number = 1;
        for (const string &line : lines)
        {
            if (line.find("Round: ") != string::npos)
            {
                // Set scorecard start index to the line after "Scorecard:"
                round_number = stoi(line.substr(7));
                break;
            }
        }

        // extracts all lines after Scorecard which represents scorecard's serialized form
        int scorecard_start = 0;
        for (int i = 0; i < lines.size(); i++)
        {
            if (lines[i].find("Scorecard:") != string::npos)
            {
                scorecard_start = i + 1;
                break;
            }
        }
        // Extract the scorecard lines and reconstruct the scorecard from serialized data
        vector<string> scorecard_lines(lines.begin() + scorecard_start, lines.end());
        string scorecard_serial = join(scorecard_lines, '\n');
        ScoreCard score_card = ScoreCard::deserialize(scorecard_serial, human, computer);

        // Return a new Game object with the deserialized scorecard, round number, and players
        return Game(score_card, round_number, players);
    }


/* *********************************************************************
    Function Name: serialize
    Purpose: Converts the current game state into a string for saving.
    Parameters: None
    Return Value: A string representing the serialized game state.
    Algorithm:
            1) Create a stringstream to build the serialized string.
            2) Add the current round number to the stringstream.
            3) Add the serialized scorecard to the stringstream.
            4) Return the constructed string from the stringstream.
    Reference: none
    ********************************************************************* */
    string serialize() const
    {
        stringstream serial;
        serial << "Round: " << current_round << endl;
        serial << "Scorecard:" << endl;
        serial << score_card.serialize() << endl;
        return serial.str();
    }


/* *********************************************************************
    Function Name: operator=
    Purpose: Copy assignment operator for the Game struct.
    Parameters:
                other, a Game object passed by reference. It represents the Game to copy from.
    Return Value: A reference to the current Game object after assignment.
    Algorithm:
            1) Check for self-assignment by comparing addresses.
            2) Destroy the current object using the destructor.
            3) Reinitialize the object using placement new with the other Game object.
    Reference: none
    ********************************************************************* */
    Game &operator=(const Game &other)
    {
        if (this != &other)
        {
            this->~Game();          // Destroy the current object
            new (this) Game(other); // Placement new to reinitialize the object
        }
        return *this;
    }


/* *********************************************************************
Function Name: is_over
Purpose: Checks if the game is over by checking if the scorecard is full.
Parameters: None
Return Value: A boolean indicating whether the game is over (true) or not (false).
Algorithm:
        1) Call the is_full method on the scorecard to determine if the game is over.
Reference: none
********************************************************************* */
    bool is_over() const
    {
        return score_card.is_full();
    }


/* *********************************************************************
    Function Name: is_draw
    Purpose: Checks if the game resulted in a draw (tie score).
    Parameters: None
    Return Value: A boolean indicating whether the game ended in a draw (true) or not (false).
    Algorithm:
            1) Call the is_draw method on the scorecard to determine if the game ended in a draw.
    Reference: none
    ********************************************************************* */
    bool is_draw() const
    {
        return score_card.is_draw();
    }


/* *********************************************************************
Function Name: play_round
Purpose: Plays a round of the game and returns the updated Game object.
Parameters: None
Return Value: A new Game object representing the updated state after playing a round.
Algorithm:
        1) Check if the game is over; if yes, print a message and return the current game object.
        2) Print the current round number.
        3) Show the scores of all players.
        4) Play a round and get the updated scorecard.
        5) Display the updated scorecard.
        6) Create and return a new Game object with the updated scorecard and incremented round number.
Reference: none
********************************************************************* */
    Game play_round() const
    {
        if (is_over())
        {
            cout << "The game is over!" << endl;
            return *this;
        }

        cout << "Round " << current_round << endl;
        show_scores();

        // Play a round and get the updated scorecard
        const ScoreCard new_score_card = Round::play_round(current_round, score_card, players);

        // Display the updated scorecard
        cout << new_score_card.get_string() << endl;

        // Create and return a new Game object with the updated scorecard and incremented round number
        auto result = Game(new_score_card, current_round + 1, players);

        // Show the updated scores after the round
        result.show_scores();

        return result;
    }


/* *********************************************************************
Function Name: get_player_scores
Purpose: To retrieve the scores of all players from the scorecard
Parameters: None
Return Value: A map that associates each player with their corresponding score
Algorithm:
            1) Call the score_card's get_player_scores function
            2) Pass the list of players to retrieve their scores
            3) Return the map containing player scores
Reference: None
********************************************************************* */
    map<shared_ptr<Player>, int> get_player_scores() const
    {

        // return the player scores as a map
        return score_card.get_player_scores(players);
    }


/* *********************************************************************
Function Name: show_scores
Purpose: To display the current scores of all players
Parameters: None
Return Value: None
Algorithm:
            1) Print "Scores:" to indicate the beginning of the score list
            2) Call get_player_scores to retrieve current player scores
            3) Iterate over the player scores map
                a) For each player-score pair, print the player's name and their score
            4) Print an empty line for better readability
Reference: None
********************************************************************* */
    void show_scores() const
    {
        cout << "Scores:" << endl;

        // get the scores of each player
        auto player_scores = get_player_scores();

        // Iterate over each player's score
        for (const auto &player_score : player_scores)
        {
            cout << player_score.first->get_name() << ": " << player_score.second << endl;
        }
        cout << endl;
    }
};
