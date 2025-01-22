
#include <iostream>
#include <memory>

#include "Computer.h"
#include "Game.h"
#include "Human.h"
#include "Player.h"
#include "ScoreCard.h"
#include "io_functions.h"

/* *********************************************************************
Function Name: main
Purpose: To execute the game loop for a Yahtzee game involving a human player and a computer player.
         The function manages the game's flow, including initialization of players, rounds, and saving/loading game state.
Parameters: None
Return Value: None
Algorithm:
            1) Create shared pointers for the human and computer players.
            2) Initialize a `Game` object, passing in the new scorecard, starting round, and list of players.
            3) Check if the user wants to load a saved game. If so, get the serialized game data and reinitialize the game state using the deserialization process.
            4) Enter a loop that continues until the game is over:
                  - Play a round of the game.
                  - After each round, save the game's current state.
            5) Once the game is over, display the final scores.
            6) Check if the game ends in a draw. If not, retrieve the winner from the scorecard and display their name.
Reference: None
Shared pointer: OOP class and ChatGPT
********************************************************************* */

int main()
{
    // Create shared pointers to Human and Computer objects using the `make_shared` function.
    auto human = make_shared<Human>();
    auto computer = make_shared<Computer>();

    // Create a vector (list) of shared pointers to Player objects, containing the human and computer players.
    const auto players = vector<shared_ptr<Player>>{human, computer};

    // Create a `Game` object, passing in a new `ScoreCard`, a starting round of 1, and the list of players.
    Game game = Game(ScoreCard(), 1, players);

    cout << "Welcome to the yahtzee Game:\n";
    cout << endl;

    // Check if the user wants to load a previously saved game.
    if (user_wants_to_load_game())
    {

        // Get the serialized string game data from the user.
        // the file contents we got from get_serial is stored in serial
        string serial = get_serial();

        // Deserialize the game data and reinitialize the `game` object to restore the previous state.
        game = Game::deserialize(serial);
    }
    // Game loop: continue playing rounds until the game is over.
    while (!game.is_over())
    {

        // Play a single round and update the `game` object.
        game = game.play_round();

        // Save the current state of the game after each round by serializing the game data.
        save_game_procedure(game.serialize());
    }

    // Once the game is over, display the final scores.
    game.show_scores();

    // Check if the game is a draw (if no winner).
    if (game.is_draw())
    {
        cout << "It's a draw!" << endl;
    }
    else
    {

        // If there is a winner, retrieve the winner from the scorecard.
        auto winner = game.score_card.get_winner();

        cout << "The winner is " << winner.value()->get_name() << "!" << endl;
    }
}
