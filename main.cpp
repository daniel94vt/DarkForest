#include <iostream>
#include <vector>
#include <string>
#include "action.h"
#include "adventure.cpp"
#include "authentication.h"

using namespace std;

int main(int argc, char *argv[]) {
    Authentication game;

    if(argc == 1)
        displayError(0);

    string parseCommandList = argv[1];


    if(parseCommandList == "-l") {
        game.login();
    }
    else if(parseCommandList == "-n") {
        game.newUser();
    }

    username = game.getUserName();

    int numAct, gameover;

    // Read in record-jar formatted text string
    numAct = fileRead("story.rjar");

    string startgame;
    string next;

    while (1)
    {
        // Initialize player stats
        health = 50;
        sanity = 5;
        curPath = 0;

	// Display opening text to player and prompt for hugs
        welcomeScreen();

        // Encompasses the story portion of the game. While loop is broken when player dies/goes insane or when player exits program.
        while (1)
        {
            // Print current description, player statistics, and event outcome.
            gameover = printCurrent(1);

            if (gameover == 1)
            {
                restartGame();
                break;
            }
            // Prints array of path choices and prompts for input for path decision. Returns name of chosen path.
            next = actions[curPath].getpath(playerChoice(numAct));

            // Searches for the action associated with the chosen path name and returns the action array location whose name corresponds to that string.
            for (int i = 0; i < numAct; i++)
            {
                if (next == actions[i].getname())
                {
                    curPath = i;
                    break;
                }
            }
        }
    }

    return 0;
}
