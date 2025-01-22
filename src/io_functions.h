/*
************************************************************
* Name:  Samman Bhetwal                                    *
* Project:  1 yahtzee                                      *
* Class:  CMPS-366                                         *
* Date:  10/26/2024                                        *
*****************************************************************
*/
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

#include "ScoreCategory.h"

struct Reason;
using namespace std;

namespace helpers
{

/* *********************************************************************
Function Name: get_yes_no
Purpose: Prompts the user with a yes/no question and returns true for 'y' and false for 'n'.
Parameters:
            prompt, a string. The question to display to the user.
Return Value: A boolean indicating the user's response (true for 'y', false for 'n').
Algorithm:
            1. Display the prompt to the user.
            2. Get the user's response.
            3. Check if the response is 'y' or 'n' and return the corresponding boolean value.
            4. If the response is invalid, repeat from step 1.
Reference: None
********************************************************************* */
    inline bool get_yes_no(const string &prompt)
    {
        string response;
        while (true)
        {
            cout << prompt << " (y/n): ";
            getline(cin, response);
            cout << endl;
            if (response == "y")
            {
                return true;
            }
            else if (response == "n")
            {
                return false;
            }
            else
            {
                cout << "Invalid response. Please enter 'y' or 'n'." << endl;
            }
        }
    }


/* *********************************************************************
Function Name: get_manual_die_roll
Purpose: Prompts the user to input a manual die roll value between 1 and 6 and validates the input.
Parameters: None
Return Value: An integer representing the valid die roll value.
Algorithm:
            1. Display prompt to enter the die roll value.
            2. Get the user's response and convert it to an integer.
            3. Validate the response to ensure it's between 1 and 6.
            4. If valid, return the integer; if not, repeat from step 1.
Reference: None
********************************************************************* */
    inline int get_manual_die_roll()
    {
        string response;
        while (true)
        {
            cout << "Enter the value of the die roll: ";
            getline(cin, response);
            istringstream iss(response);
            int i;
            if (iss >> i && i >= 1 && i <= 6)
            {
                return i;
            }
            else
            {
                cout << "Invalid response. Please enter an integer between 1 and 6." << endl;
            }
        }
    }


/* *********************************************************************
Function Name: get_auto_die_roll
Purpose: Automatically generates a random die roll value using the Dice class.
Parameters: None
Return Value: An integer representing the randomly generated die roll value.
Algorithm:
            1. Call the roll_die function from the Dice class to generate a random value.
            2. Return the generated value.
Reference: None
********************************************************************* */
    inline int get_auto_die_roll()
    {
        return Dice::roll_die();
    }


/* *********************************************************************
Function Name: get_die_roll
Purpose: Determines whether to manually roll a set of dice or automatically roll them based on user input.
Parameters: None
Return Value: An integer representing the result of the die roll.
Algorithm:
            1. Ask the user if they want to manually roll the die.
            2. If yes, call get_manual_die_roll to get the value.
            3. If no, call get_auto_die_roll to get a random value.
            4. Return the resulting value.
Reference: None
********************************************************************* */
    inline int get_die_roll()
    {
        bool manual_roll = get_yes_no("Would you like to manually roll the die?");
        if (manual_roll)
        {
            return get_manual_die_roll();
        }
        else
        {
            return get_auto_die_roll();
        }
    }


/* *********************************************************************
Function Name: get_manual_dice_roll
Purpose: Prompts the user to manually input a set of dice rolls and validates the input.
Parameters:
            num_dice, an integer. It specifies the number of dice to roll.
Return Value: A vector of integers containing the valid dice rolls.
Algorithm:
            1. Prompt the user to enter dice rolls separated by spaces.
            2. Read the input and convert it to integers.
            3. Validate that each roll is between 1 and 6.
            4. Ensure the number of inputs matches the expected count.
            5. Return the vector of valid rolls.
Reference: None
********************************************************************* */
    inline vector<int> get_manual_dice_roll(const int num_dice)
    {
        vector<int> dice_rolls;
        string response;

        cout << "Enter " << num_dice << " dice rolls separated by spaces: ";
        getline(cin, response);
        istringstream iss(response);
        int i;
        while (iss >> i)
        {
            if (i >= 1 && i <= 6)
            {
                dice_rolls.push_back(i);
            }
            else
            {
                cout << "Invalid response. Please enter an integer between 1 and 6. Please try again." << endl;
                return get_manual_dice_roll(num_dice);
            }
        }

        if (dice_rolls.size() != num_dice)
        {
            cout << "Invalid response. Please enter " << num_dice << " integers between 1 and 6. Please try again." << endl;
            return get_manual_dice_roll(num_dice);
        }

        return dice_rolls;
    }


/* *********************************************************************
Function Name: get_auto_dice_roll
Purpose: Automatically generates a set of random dice rolls.
Parameters:
            num_dice, an integer. It specifies the number of dice to roll.
Return Value: A vector of integers containing the randomly generated dice rolls.
Algorithm:
            1. Create an empty vector to hold the rolls.
            2. Loop through the number of dice.
            3. Call get_auto_die_roll to generate a random die value.
            4. Add the generated value to the vector.
            5. Return the vector of rolls.
Reference: None
********************************************************************* */
    inline vector<int> get_auto_dice_roll(const int num_dice)
    {
        vector<int> rolls;
        for (int i = 0; i < num_dice; i++)
        {
            rolls.push_back(get_auto_die_roll());
        }
        return rolls;
    }


/* *********************************************************************
Function Name: get_dice_roll
Purpose: Determines whether to manually roll a set of dice or automatically roll them based on user input.
Parameters:
            num_dice, an integer. It specifies the number of dice to roll.
Return Value: A vector of integers representing the result of the dice rolls.
Algorithm:
            1. Ask the user if they want to manually roll the dice.
            2. If yes, call get_manual_dice_roll to get the values.
            3. If no, call get_auto_dice_roll to generate random values.
            4. Return the resulting vector of dice rolls.
Reference: None
********************************************************************* */
    inline vector<int> get_dice_roll(const int num_dice)
    {
        bool manual_roll = get_yes_no("Would you like to manually roll the dice?");
        if (manual_roll)
        {
            return get_manual_dice_roll(num_dice);
        }
        else
        {
            return get_auto_dice_roll(num_dice);
        }
    }


/* *********************************************************************
Function Name: show_message
Purpose: Displays a simple message to the user.
Parameters:
            message, a string. The message to display.
Return Value: None
Algorithm:
            1. Output the message to the console.
Reference: None
********************************************************************* */
    inline void show_message(const string &message)
    {
        cout << message << endl;
    }


/* *********************************************************************
Function Name: human_won_tie_breaker
Purpose: Conducts a tie-breaker where both human and computer roll a die. Returns true if the human wins.
Parameters: None
Return Value: A boolean indicating whether the human won the tie-breaker (true) or the computer won (false).
Algorithm:
            1. Generate a random die roll for the computer.
            2. Prompt the human to roll the die.
            3. Compare the two rolls.
            4. If the human's roll is higher, return true.
            5. If the computer's roll is higher, return false.
            6. If there's a tie, repeat the process.
Reference: None
********************************************************************* */
    inline bool human_won_tie_breaker()
    {
        const int computer_roll = Dice::roll_die();
        const int human_roll = get_die_roll();

        cout << "You rolled a " << human_roll << endl;
        cout << "The computer rolled a " << computer_roll << endl;

        if (human_roll > computer_roll)
        {
            cout << "You go first!\n"
                 << endl;
            return true;
        }
        else if (computer_roll > human_roll)
        {
            cout << "The computer goes first!\n"
                 << endl;
            return false;
        }

        cout << "It's a tie! Rolling again.\n"
             << endl;
        return human_won_tie_breaker();
    }


/* *********************************************************************
Function Name: get_dice_to_keep
Purpose: Prompts the user to select specific dice to keep from their rolled dice and validates the input to ensure the selected dice were originally rolled.
Parameters:
            dice_rolls, a vector of integers passed by reference. It holds the values of the dice that were rolled in the current turn.
Return Value: A vector of integers containing the valid dice selected by the user to keep.
Algorithm:
            1) Prompt the user for input on which dice to keep.
            2) Parse the user's input to extract the selected dice values.
            3) Validate that each selected die is between 1 and 6.
            4) Check that each selected die is among the originally rolled dice.
            5) Return the validated list of dice to keep.
Reference: None
********************************************************************* */
    inline vector<int> get_dice_to_keep(const vector<int> &dice_rolls)
    {
        vector<int> dice_to_keep;
        string response;

        cout << "Enter the dice you would like to keep separated by spaces: ";
        getline(cin, response);
        istringstream iss(response);
        int i;
        while (iss >> i)
        {
            if (i >= 1 && i <= 6)
            {
                dice_to_keep.push_back(i);
            }
            else
            {
                cout << "Invalid response. Please enter an integer between 1 and 6. Please try again." << endl;
                return get_dice_to_keep(dice_rolls);
            }
        }

        for (int die : dice_to_keep)
        {
            if (find(dice_rolls.begin(), dice_rolls.end(), die) == dice_rolls.end())
            {
                cout << "Invalid response. Please enter a die that was rolled. Please try again." << endl;
                return get_dice_to_keep(dice_rolls);
            }
        }

        return dice_to_keep;
    }


/* *********************************************************************
Function Name: to_string_vector
Purpose: Converts a vector of integers into a string representation for display purposes.
Parameters:
            vec, a vector of integers passed by reference. It holds the integers to be converted to a string.
Return Value: A string representation of the vector, formatted as a list.
Algorithm:
            1) Initialize an empty string to hold the formatted representation.
            2) Iterate through each element of the vector.
            3) Append each integer to the string with proper formatting.
            4) Return the formatted string.
Reference: None
********************************************************************* */
    inline string to_string_vector(const vector<int> &vec)
    {
        string str = "[";
        for (int i = 0; i < vec.size(); i++)
        {
            str += to_string(vec[i]);
            if (i != vec.size() - 1)
            {
                str += ", ";
            }
        }
        str += "]";
        return str;
    }


/* *********************************************************************
Function Name: show_categories
Purpose: Displays the available scoring categories to the user for their selection.
Parameters:
            categories, a vector of Category enums passed by reference. It contains the available scoring categories.
Return Value: None (void function).
Algorithm:
            1) Iterate through the provided categories.
            2) Output each category name to the console.
            3) Format the display for clarity.
Reference: None
********************************************************************* */
    inline void show_categories(const vector<Category> &categories)
    {
        for (int i = 0; i < categories.size(); i++)
        {
            cout << CATEGORY_NAMES[categories[i]];
            if (i != categories.size() - 1)
            {
                cout << "\n";
            }
        }
        cout << '\n'
             << endl;
    }


/* *********************************************************************
Function Name: user_wants_to_load_game
Purpose: Prompts the user to decide whether they want to load a saved game.
Parameters: None.
Return Value: A boolean indicating the user's choice (true if they want to load a game, false otherwise).
Algorithm:
            1) Call a helper function to get a yes/no response from the user.
            2) Return the result of the helper function.
Reference: None
********************************************************************* */
    inline bool user_wants_to_load_game()
    {
        return get_yes_no("Would you like to load a saved game?");
    }


/* *********************************************************************
Function Name: get_serial
Purpose: Prompts the user for the name of the file to load a saved game and validates the existence and content of the file.
Parameters: None.
Return Value: A string containing the content of the loaded file.
Algorithm:
            1) Prompt the user for the file name.
            2) Attempt to open the specified file.
            3) Check if the file was successfully opened.
            4) Read the entire content of the file into a string.
            5) Validate that the file is not empty.
            6) Return the file content as a string.
Reference: None
********************************************************************* */
    inline string get_serial()
    {
        // Ask user for the serial file name
        string serial;
        cout << "Enter the name of the file you would like to load: ";
        getline(cin, serial);

        ifstream file(serial);
        if (!file)
        {
            cerr << "Error: File does not exist or cannot be opened." << endl;
            cout << "Please try again." << endl;
            return get_serial();
        }

        // reads entire content after the file is succesfully opened in string serial_string
        string serial_string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        if (serial_string.empty())
        {
            cerr << "Error: File is empty." << endl;
            cout << "Please try again." << endl;
            return get_serial();
        }

        // returns the file content as a string
        return serial_string;
    }


/* *********************************************************************
Function Name: save_game_procedure
Purpose: Saves the current game state to a specified file and allows the user to exit the program.
Parameters:
            serial, a string passed by value. It contains the serialized state of the current game.
Return Value: None (void function).
Algorithm:
            1) Ask the user if they wish to save the game and exit.
            2) If yes, prompt for the desired file name.
            3) Write the current game state to the specified file.
            4) Confirm that the game has been saved successfully.
            5) Exit the program.
Reference: None
********************************************************************* */
    inline void save_game_procedure(const string &serial)
    {
        if (get_yes_no("Would you like to save the game and exit?"))
        {
            string file_name;
            cout << "Enter the name of the file you would like to save: ";
            getline(cin, file_name);

            ofstream file(file_name);
            file << serial;
            file.close();
            cout << "Game saved successfully." << endl;
            exit(0);
        }
    }


/* *********************************************************************
Function Name: wants_to_stand
Purpose: Asks the user if they would like to stand and not reroll any dice.
Parameters: None.
Return Value: A boolean indicating the user's choice (true if they want to stand, false otherwise).
Algorithm:
            1) Call a helper function to get a yes/no response from the user.
            2) Return the result of the helper function.
Reference: None
********************************************************************* */
    inline bool wants_to_stand()
    {
        return get_yes_no("Would you like to stand?");
    }


/* *********************************************************************
Function Name: show_category_pursuits
Purpose: Displays the potential scoring opportunities based on the current dice roll.
Parameters:
            category_pursuits, a map of Category to Reason passed by reference. It holds potential scoring opportunities and their associated reasons.
Return Value: None (void function).
Algorithm:
            1) Extract reasons from the category pursuits.
            2) Sort reasons based on maximum score.
            3) Display the current dice and potential scoring opportunities.
Reference: None
********************************************************************* */
    inline void show_category_pursuits(const map<Category, Reason> &category_pursuits)
    {
        vector<Reason> reasons;
        for (const auto &[category, reason] : category_pursuits)
        {
            reasons.push_back(reason);
        }
        sort(reasons.begin(), reasons.end(), [](const Reason &a, const Reason &b)
             { return a.max_score < b.max_score; });

        cout << "Current dice: " << to_string_vector(reasons[0].current_dice) << endl;

        for (const auto &[category, reason] : category_pursuits)
        {
            if (reason.min_score == 0)
            {
                cout << "Can get " << CATEGORY_NAMES[reason.pursued_category] << " with a score of " << reason.max_score << " by rolling " << to_string_vector(reason.roll_to_get_max) << endl;
                continue;
            }

            cout << "Can get " << CATEGORY_NAMES[reason.pursued_category] << " with a minimum score of " << reason.min_score << " by getting " << to_string_vector(reason.roll_to_get_min) << " and a maximum score of " << reason.max_score << " by rolling " << to_string_vector(reason.roll_to_get_max) << endl;
        }
    }


/* *********************************************************************
Function Name: wants_help
Purpose: Asks the user if they would like help during the game.
Parameters: None.
Return Value: A boolean indicating the user's choice (true if they want help, false otherwise).
Algorithm:
            1) Call a helper function to get a yes/no response from the user.
            2) Return the result of the helper function.
Reference: None
********************************************************************* */
    inline bool wants_help()
    {
        return get_yes_no("Would you like help?");
    }


/* *********************************************************************
Function Name: human_wants_to_roll_for_computer
Purpose: Asks the user if they would like to roll the dice for the computer player.
Parameters: None.
Return Value: A boolean indicating the user's choice (true if they want to roll for the computer, false otherwise).
Algorithm:
            1) Call a helper function to get a yes/no response from the user.
            2) Return the result of the helper function.
Reference: None
********************************************************************* */
    inline bool human_wants_to_roll_for_computer()
    {
        return get_yes_no("Would you like to roll for the computer?");
    }
}
