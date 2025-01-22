/*
************************************************************
* Name:  Samman Bhetwal                                    *
* Project:  1 yahtzee                                      *
* Class:  CMPS-366                                         *
* Date:  10/26/2024                                        *
*****************************************************************
*/

#pragma once

#include <iomanip>
#include <optional>
#include <map>
#include <memory>

#include "ScoreCategory.h"
#include "Player.h"

using namespace std;

// Forward declarations
struct ScoreCardEntry;
enum class Category;

// Struct to hold the points, winner, and round of a scorecard entry
struct ScoreCardEntry
{
    int points;
    shared_ptr<Player> winner;
    int round;

    // Equality operator to compare two ScoreCardEntry objects
    bool operator==(const ScoreCardEntry &other) const
    {
        return points == other.points && winner == other.winner && round == other.round;
    }
};

class ScoreCard
{
public:
    // Default constructor that initializes the scorecard with nullopt values for all categories
    ScoreCard() : score_card(initialize_score_card())
    {
    }

    
/* *********************************************************************
Function Name: deserialize
Purpose: To construct a ScoreCard from a serialized string representation.
Parameters:
        serial, a string that contains serialized scorecard data.
        human, a shared_ptr to the human player. It tracks the human's score.
        computer, a shared_ptr to the computer player. It tracks the computer's score.
Return Value: A ScoreCard object populated with the deserialized data.
Algorithm:
        1) Split the serialized string into lines.
        2) For each line, trim leading/trailing spaces and check if it's empty.
        3) If line is "0", mark the category as unfilled.
        4) Split the line into points, winner, and round.
        5) Parse these values and store them in the scorecard.
        6) Return the populated ScoreCard.
Reference: none
Optional: cppreference.com
********************************************************************* */
    static ScoreCard deserialize(const string &serial, const shared_ptr<Player> &human,
                                 const shared_ptr<Player> &computer)
    {
        const vector<string> lines = split(serial, '\n');

        // Track which category we are processing
        int category_index = 0;
        map<Category, optional<ScoreCardEntry>> score_card;

        // loop through each line,remove leading/trailing whitespaces, skip empty lines
        for (auto line : lines)
        {
            line = trim(line);
            if (line.empty())
            {
                continue;
            }

            // If line is "0", it indicates the category is unfilled
            if (line == "0")
            {
                score_card[CATEGORIES[category_index]] = nullopt;
                category_index++;
                continue;
            }

            // Split the line into three parts (points, winner, and round)
            vector<string> parts = split(line, ' ');

            // If the line is incorrectly formatted, skip it

            if (parts.size() != 3)
            {
                continue;
            }

            const Category category = CATEGORIES[category_index];

            // Parse the points, winner, and round
            const int points = stoi(parts[0]);
            const auto winner = parts[1] == "Human" ? human : computer;
            const int round = stoi(parts[2]);

            // Create a ScoreCardEntry and store it in the scorecard
            score_card[category].emplace(ScoreCardEntry{points, winner, round});
            category_index++;
        }

        // returns the scorecard with categories mapped to their details(winner, points, round)
        return ScoreCard(score_card);
    }


/* *********************************************************************
Function Name: serialize
Purpose: To convert the scorecard to a string representation.
Parameters: None
Return Value: A string representing the serialized scorecard.
Algorithm:
        1) Create a stringstream to build the serialized string.
        2) Iterate through the scorecard entries.
        3) If an entry has a value, serialize points, winner's name, and round.
        4) If the entry is empty, represent it with "0".
        5) Return the string representation of the scorecard.
Reference: none
********************************************************************* */
    string serialize() const
    {
        stringstream serial;
        for (auto const &entry : score_card)
        {
            if (entry.second.has_value())
            {
                // If the entry has a value, serialize points, winner's name, and round
                ScoreCardEntry score_card_entry = entry.second.value();
                serial << to_string(score_card_entry.points) << " " << score_card_entry.winner->get_name() << " "
                       << to_string(score_card_entry.round) << "\n";
            }
            else
            {
                // If the entry is empty, represent it with "0"
                serial << "0\n";
            }
        }
        return serial.str();
    }

    // Copy constructor
    ScoreCard(const ScoreCard &other) : score_card(other.score_card)
    {
    }


/* *********************************************************************
Function Name: operator=
Purpose: To assign one ScoreCard object to another.
Parameters:
            other, a reference to another ScoreCard object to be copied.
Return Value: A reference to the updated ScoreCard object.
Algorithm:
            1) Check for self-assignment.
            2) Destroy the current object to free resources.
            3) Use placement new to create a new ScoreCard object from 'other'.
            4) Return a reference to this object.
Reference: none
********************************************************************* */
    ScoreCard &operator=(const ScoreCard &other)
    {
        if (this != &other)
        {
            this->~ScoreCard();          // Destroy the current object
            new (this) ScoreCard(other); // Placement new to reinitialize the object
        }
        return *this;
    }


/* *********************************************************************
Function Name: operator==
Purpose: To compare two ScoreCard objects for equality.
Parameters:
            other, a reference to another ScoreCard object to compare against.
Return Value: True if both scorecards are equal; otherwise, false.
Algorithm:
            1) Use std::equal to compare the score_card entries of both scorecards.
            2) Check if the keys and their corresponding values match.
Reference: none
Optional: cppreference.com
********************************************************************* */
    bool operator==(const ScoreCard &other) const
    {
        return std::equal(score_card.begin(), score_card.end(), other.score_card.begin(), other.score_card.end(),
                          [](const auto &a, const auto &b)
                          {
                              return a.first == b.first && a.second == b.second;
                          });
    }

    ScoreCard(const map<Category, optional<ScoreCardEntry>> &score_card) : score_card(score_card)
    {
    }


/* *********************************************************************
Function Name: add_entry
Purpose: To add a score entry to the specified category with points, winner, and round.
Parameters:
            category, a Category enum value indicating the category to add to.
            points, an integer representing the score points for this entry.
            winner, a shared_ptr to the Player who won this entry.
            round, an integer representing the round number.
Return Value: A new ScoreCard object with the updated entry.
Algorithm:
            1) Check if the specified category already has an entry.
            2) If it does, throw an exception.
            3) Create a new scorecard map and add the entry.
            4) Return the new ScoreCard object.
Reference: none
Optional: cppreference.com
********************************************************************* */
    ScoreCard add_entry(const Category category, const int points, const shared_ptr<Player> &winner,
                        const int round) const
    {
        if (score_card.at(category).has_value())
        {
            throw invalid_argument("Category already has a score card entry");
        }

        map<Category, optional<ScoreCardEntry>> new_score_card = score_card;
        new_score_card[category].emplace(ScoreCardEntry{points, winner, round});
        return ScoreCard(new_score_card);
    }


/* *********************************************************************
Function Name: add_entry
Purpose: To automatically add a score entry for the max scoring category based on dice roll.
Parameters:
            round, an integer representing the round number.
            winner, a shared_ptr to the Player who won this entry.
            dice, a vector of integers representing the rolled dice values.
Return Value: A new ScoreCard object with the updated entry.
Algorithm:
            1) Get the maximum scoring category based on the current dice.
            2) Check if the category is already filled.
            3) If not, create a new scorecard map, add the entry, and return it.
Reference: none
********************************************************************* */
    ScoreCard add_entry(const int round, const shared_ptr<Player> &winner, const vector<int> &dice) const
    {
        auto max_category = get_max_scoring_category(dice);
        if (!max_category.has_value())
        {
            return *this;
        }
        return add_entry(max_category.value(), get_score(dice, max_category.value()), winner, round);
    }


/* *********************************************************************
Function Name: get_max_scoring_category
Purpose: To find the best scoring category based on the current dice roll.
Parameters:
    - const vector<int> &dice: The current roll of the dice.
Return Value:
    - optional<Category>: The category that yields the highest score based on the dice roll, or nullopt if no category can be scored.
Algorithm:
        1) Retrieve the list of open categories (categories that are unfilled).
        2) Retrieve the list of applicable categories based on the current dice roll.
        3) Find the intersection of open categories and applicable categories to determine which categories can be assigned a score.
        4) If no assignable categories exist, return nullopt.
        5) Calculate scores for each assignable category.
        6) Determine the category with the highest score and return it.
Reference: none
Optional: cppreference.com
********************************************************************* */
    optional<Category> get_max_scoring_category(const vector<int> &dice) const
    {
        vector<Category> open_categories = get_open_categories();
        vector<Category> applicable_categories = get_applicable_categories(dice);
        vector<Category> assignable_categories = intersection(open_categories, applicable_categories);

        if (assignable_categories.empty())
        {
            return nullopt;
        }

        map<Category, int> category_scores;
        for (Category category : assignable_categories)
        {
            int score = get_score(dice, category);
            category_scores[category] = score;
        }

        Category max_category = Category::Ones;
        int max_score = 0;
        for (auto const &entry : category_scores)
        {
            if (entry.second >= max_score)
            {
                max_score = entry.second;
                max_category = entry.first;
            }
        }

        return max_category;
    }


/* *********************************************************************
Function Name: is_full
Purpose: To check if the scorecard is completely filled with entries.
Parameters: None
Return Value:
    - bool: True if all categories in the scorecard are filled; otherwise, false.
Algorithm:
        1) Iterate through all entries in the scorecard.
        2) If any category is not filled (i.e., has no score entry), return false.
        3) If all categories are filled, return true.
Reference: none
********************************************************************* */
    bool is_full() const
    {
        for (auto const &entry : score_card)
        {
            if (!entry.second.has_value())
            {
                return false;
            }
        }
        return true;
    }


/* *********************************************************************
Function Name: get_open_categories
Purpose: To retrieve a vector of categories that have not been filled in the scorecard.
Parameters: None
Return Value:
    - vector<Category>: A vector containing all unfilled categories.
Algorithm:
        1) Initialize an empty vector to store open categories.
        2) Iterate through the scorecard entries.
        3) For each entry, check if it is unfilled; if so, add the category to the vector.
        4) Return the vector of open categories, reversed to prioritize higher categories.
Reference: none
********************************************************************* */
    vector<Category> get_open_categories() const
    {
        vector<Category> open_categories;
        for (auto const &entry : score_card)
        {
            if (!entry.second.has_value())
            {
                open_categories.push_back(entry.first);
            }
        }

        // Returning reversed category because higher categories are more likely to be chosen
        return reversed(open_categories);
    }


/* *********************************************************************
Function Name: get_possible_categories
Purpose: To determine which categories are possible to score based on the current dice roll.
Parameters:
    - const vector<int> &dice: The current roll of the dice.
Return Value:
    - vector<Category>: A vector of categories that can be scored with the given dice roll.
Algorithm:
        1) Retrieve the list of open categories.
        2) Initialize an empty vector for possible categories.
        3) For each open category, check if it is a possible category based on the current dice roll.
        4) If a category is possible, add it to the vector of possible categories.
        5) Return the vector of possible categories.
Reference: none
********************************************************************* */
    vector<Category> get_possible_categories(const vector<int> &dice) const
    {
        vector<Category> open_categories = get_open_categories();

        vector<Category> possible_categories;
        for (Category category : open_categories)
        {
            if (is_possible_category(dice, category))
            {
                possible_categories.push_back(category);
            }
        }

        return possible_categories;
    }


/* *********************************************************************
Function Name: get_player_score
Purpose: To calculate the total score for a given player based on their filled categories in the scorecard.
Parameters:
    - const shared_ptr<Player> &player: The player whose score is being calculated.
Return Value:
    - int: The total score of the player.
Algorithm:
        1) Initialize a variable to store the total score, starting at zero.
        2) Iterate through the scorecard entries.
        3) For each filled category, check if the winner matches the specified player.
        4) If it does, add the points for that entry to the total score.
        5) Return the total score.
Reference: none
********************************************************************* */
    int get_player_score(const shared_ptr<Player> &player) const
    {
        int total_score = 0;
        for (auto const &entry : score_card)
        {
            // if that category is filled and the winner of that category is player
            if (entry.second.has_value() && entry.second.value().winner == player)
            {
                total_score += entry.second.value().points;
            }
        }
        return total_score;
    }


/* *********************************************************************
Function Name: get_player_scores
Purpose: To generate a map of player scores for all players.
Parameters:
    - const vector<shared_ptr<Player>> &players: A vector containing all players in the game.
Return Value:
    - map<shared_ptr<Player>, int>: A map associating each player with their corresponding score.
Algorithm:
        1) Initialize an empty map to store player scores.
        2) For each player in the provided vector, retrieve their score using get_player_score.
        3) Add the player and their score to the map.
        4) Return the map of player scores.
Reference: none
********************************************************************* */
    map<shared_ptr<Player>, int> get_player_scores(const vector<shared_ptr<Player>> &players) const
    {
        map<shared_ptr<Player>, int> player_scores;
        for (const auto &player : players)
        {
            int player_score = get_player_score(player);
            player_scores[player] = player_score;
        }
        return player_scores;
    }


/* *********************************************************************
Function Name: get_winner
Purpose: To determine the winner of the game by comparing player scores.
Parameters: None
Return Value:
    - optional<shared_ptr<Player>>: The player with the highest score, or nullopt if the scorecard is not full.
Algorithm:
        1) Initialize a variable to hold the winner, starting as nullopt.
        2) Check if the scorecard is full; if not, return nullopt.
        3) Retrieve the list of players and their scores.
        4) Find the player with the highest score by iterating through the scores.
        5) Return the player with the highest score.
Reference: none
Optional: cppreference.com
********************************************************************* */
    optional<shared_ptr<Player>> get_winner() const
    {
        optional<shared_ptr<Player>> winner = nullopt;

        if (!is_full())
        {
            return nullopt;
        }

        auto players = get_players();
        auto player_scores = get_player_scores(players);

        // find the player with the highest score
        int max_score = 0;
        for (auto const &entry : player_scores)
        {
            if (entry.second > max_score)
            {
                max_score = entry.second;
                winner = entry.first;
            }
        }

        return winner;
    }


/* *********************************************************************
Function Name: is_draw
Purpose: To check if the game resulted in a draw between players.
Parameters: None
Return Value:
    - bool: True if there is a draw, false otherwise.
Algorithm:
        1) If the scorecard is not full, return false (no draw possible).
        2) Retrieve the player scores.
        3) Determine the maximum score among the players.
        4) Count how many players have this maximum score.
        5) Return true if more than one player has the maximum score; otherwise, return false.
Reference: none
********************************************************************* */
    bool is_draw() const
    {
        // If the scorecard is not full, there cannot be a draw
        if (!is_full())
        {
            return false;
        }

        auto players = get_players();
        auto player_scores = get_player_scores(players);

        // find the player with the highest score
        int max_score = 0;
        for (auto const &entry : player_scores)
        {
            if (entry.second > max_score)
            {
                max_score = entry.second;
            }
        }

        // check if there is a draw
        int count = 0;
        for (auto const &entry : player_scores)
        {
            if (entry.second == max_score)
            {
                count++;
            }
        }

        return count > 1;
    }


/* *********************************************************************
Function Name: get_players
Purpose: To retrieve a list of all players who have entries in the scorecard.
Parameters: None
Return Value:
    - vector<shared_ptr<Player>>: A vector containing all players who have scored in the scorecard.
Algorithm:
        1) Initialize an empty vector to store unique players.
        2) Iterate through the scorecard entries.
        3) For each entry, check if it has a value and if the player is not already in the list.
        4) If both conditions are met, add the player to the vector.
        5) Return the vector of players.
Reference: none
********************************************************************* */
    vector<shared_ptr<Player>> get_players() const
    {
        vector<shared_ptr<Player>> players;

        // Loop through the scorecard and collect all unique players
        for (auto const &entry : score_card)
        {
            // If a scorecard entry has a value and the player isn't already in the list, add the player
            if (entry.second.has_value() && !contains(players, entry.second.value().winner))
            {
                players.push_back(entry.second.value().winner);
            }
        }
        return players;
    }


/* *********************************************************************
Function Name: get_string
Purpose: To generate a formatted string representation of the scorecard for display.
Parameters: None
Return Value:
    - string: A formatted string displaying categories, rounds, winners, and points in the scorecard.
Algorithm:
        1) Initialize a stringstream to build the scorecard string.
        2) Add headers for category, round, winner, and points.
        3) Iterate through the scorecard entries.
        4) For each entry, append the category and its corresponding details (round, winner, points) to the string.
        5) Return the constructed string representation of the scorecard.
Reference: none
********************************************************************* */
    string get_string() const
    {
        stringstream score_card_string;
        score_card_string << left << setw(20) << "Category" << setw(10) << "Round" << setw(15) << "Winner" << setw(10)
                          << "Points" << "\n";
        score_card_string << string(50, '-') << "\n";
        for (auto const &entry : score_card)
        {
            score_card_string << left << setw(20) << CATEGORY_NAMES.at(entry.first);
            if (entry.second.has_value())
            {
                ScoreCardEntry score_card_entry = entry.second.value();
                score_card_string << setw(10) << to_string(score_card_entry.round)
                                  << setw(15) << score_card_entry.winner->get_name()
                                  << setw(10) << to_string(score_card_entry.points);
            }
            else
            {
                score_card_string << setw(10) << "-" << setw(15) << "-" << setw(10) << "-";
            }
            score_card_string << "\n";
        }
        return score_card_string.str();
    }


private:
    // Hashmap of categories to score card entries
    const map<Category, optional<ScoreCardEntry>> score_card;

/* *********************************************************************
Function Name: initialize_score_card
Purpose: To create and initialize the scorecard for the game, setting all
        categories to nullopt to indicate that no entries have been made yet.
Parameters: None
Return Value: A map where each key is a Category and the value is an
            optional ScoreCardEntry, all initialized to nullopt.
Algorithm:
        1) Create an empty map to hold the scorecard entries.
        2) Loop through all predefined categories.
        3) For each category, set its corresponding entry in the map
            to nullopt, indicating it is currently unfilled.
        4) Return the initialized scorecard map.
Reference: None
Optional: cppreference.com
********************************************************************* */
    static map<Category, optional<ScoreCardEntry>> initialize_score_card()
    {
        map<Category, optional<ScoreCardEntry>> temp_score_card;
        for (Category category : CATEGORIES)
        {
            temp_score_card[category] = nullopt;
        }
        return temp_score_card;
    }
};
