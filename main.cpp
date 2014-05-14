#include <iostream>
#include <vector>
#include <string>
#include "action.h"
#include "adventure.cpp"
#include "authentication.h"

using namespace std;

// Global game object
Authentication game;

// Main prompts player to indicate new or existing user, then calls the appropriate function for either. Afterward,
// the function containing the adventure game is called.
int main(int argc, char *argv[]) {
    msgDisplay(0);
    void gameBegin(string);
    bool rightInp = false;

    while (rightInp == false){	
        string input;
	cout << "> ";
	cin >> input;
	if (input == "l"){          // Existing user
		rightInp = true;
		game.login(); 
		gameBegin(game.getUserName());
	}
	else if ( input == "n"){    // New user
		rightInp = true;
		game.newUser();
		gameBegin(game.getUserName());
	}
	else {
		msgDisplay(1);     // Instructions reiterated if invalid entry given
	}
    }
   return 0;
}

// This function encompasses the adventure game, including reading in the record-jar file, calling the welcome
// screen, calling the function to print path selections, and updating the current action position.
void gameBegin(string name){
    username = name;

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
}
