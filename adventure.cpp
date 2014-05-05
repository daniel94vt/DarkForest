#include "actionclass.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

// Global variables
Action actions[250];
int numactions = 0;
int cur = 0, health = 100, sanity = 5;
string username = "Stranger";

// Function prototypes
void filein(char* gamefile);
int playerChoice(void);
void printcurrent(int eventenable);
void notification(int helpint);

// Reads in record-jar format file and initializes array of Action objects
void filein(char* gamefile)
{
	string start, end, newpath;
	int endint;

	ifstream gametext (gamefile);

	if(gametext != NULL)
	{
		while (gametext.peek() != EOF) 
		{
			if (gametext.peek() == '%') {
				getline(gametext, start, '\n');
				continue; }

			while (gametext.peek() != '%' && gametext.peek() != EOF) {

				// Get key prior to colon
				getline(gametext, start, ':');

				// Ignore leading whitespace for data after colon
				while (gametext.peek() == ' ')
					gametext.ignore(1, ' ');

				// Multiple paths can be specified on single line, so a loop is initiated under this circumstance
				if (start == "path") {
					while (gametext.peek() != '\n') 
					{
						while (gametext.peek() == ' ')
					           gametext.ignore(1, ' ');

						if (gametext.peek() != '\n')
						{
							getline(gametext, newpath, ',');
							actions[numactions].addpath(newpath); 
						}
					}
					ifstream& get();
				}

				// If key != "path", the value after the colon is a single item string
				getline(gametext, end, '\n');

				// Create integer based on the text following the colon
				stringstream endconvert(end);
				endconvert >> endint;
			
				// The data string or int is passed directly into the function indicated by the key string
				if (start == "name") 
					actions[numactions].setname(end); 
				else if (start == "prompt") 
					actions[numactions].setprompt(end); 
				else if (start == "description") 
					actions[numactions].setdescr(end); 
				else if (start == "chance") 
					actions[numactions].setchance(endint); 
				else if (start == "event") 
					actions[numactions].setevent(end); 
				else if (start == "change") 
					actions[numactions].setalt(endint); 
				else if (start == "win") 
					actions[numactions].gameover(endint); 
				else if (start == "max")
					actions[numactions].eventlimit(endint);
			}
			// Track number of areas taken from the input file
			numactions++;
		}
		gametext.close();
	}
}

// Prints possible paths to player and accepts input based on the letter of the given strings. Returns integer corresponding to path choice.
int playerChoice()
{
	string path;
	int choice = 42;
	int numpath = actions[cur].getnumpaths();

	while (choice == 42) 
	{
		// Prints the options according to the number of paths in the current Action object along with their associated prompts
		for (int i = 0; i < numpath; i++)
		{
			if (i == 0)
				cout << "a. ";
			else if (i == 1)
				cout << "b. ";
			else if (i == 2)
				cout << "c. ";
			else if (i == 3)
				cout << "d. ";
			else if (i == 4)
				cout << "e. ";

			// Iterates through the Actions to find the specified prompt
			for (int j = 0; j < numactions; j++)
			{
				if (actions[cur].getpath(i) == actions[j].getname())
				{
				    cout << actions[j].getprompt() << endl;
					break;
				}
			}
		}

		// Allow user input to choose path. Lower/upper-case a-e are associated with choices, 'h' calls notification() to display help text.
		// 'Z' calls notification() to exit the game. An invalid entry calls notification() to alert the player and print instructions.
	    cin >> path;

		if (path == "a" || path == "A")
			choice = 0;
		else if ((path == "b" || path == "B") && numpath > 1)
			choice = 1;
		else if ((path == "c" || path == "C") && numpath > 2)
			choice = 2;
		else if ((path == "d" || path == "D") && numpath > 3)
			choice = 3;
		else if ((path == "e" || path == "E") && numpath > 4)
			choice = 4;
		else if (path == "h" || path == "H")
			notification(1);
		else if (path == "z" || path == "Z")
			notification(2);
		else 
		    notification(0);

	}
	return choice;
}

// Prints top reminder help header, current action description, and current stats.
// If parameter given is 1, the event for the current action is processed. 
void printcurrent(int eventenable)
{
	int effect;

	system("CLS");
	cout << "z: Exit       h: Help \n-------------------------------------------------\n";

	// Print description of current location
	cout << (actions[cur].getdescr());

	// Processes event. If a non-zero integer is returned, either health or sanity is affected. 
	// If either reaches zero, the game ends. 
	if (eventenable == 1)
	{
		effect = actions[cur].itshappening();

		if (effect % 5 == 0)
			health += effect;
		else
			sanity += effect;
	}

	// Maximum health cannot exceed 100.
	if (health > 100)
		health = 100;
	else if (health <= 0)
	{
		cout << "\n\n** Your health has been depleted. Your adventure has prematurely come to its end.\n\n";
		exit(0);
	}
	if (sanity <= 0)
	{
		cout << "\n\n** The wilderness has driven you crazy. You have lost your mind and cannot continue.\n\n";
	    exit(0);
	}

	cout << "\n\nHealth: " << health << "     Sanity: " << sanity << "\n";
	cout << "-------------------------------------------------- \n" << username << ", choose your path: \n";
}

// Called if the player input 'h' for help, 'z' to quit, or an invalid string upon path selection. 
void notification(int help)
{
	string user;

	system("CLS");

	if (help == 0)
		cout << "\nInvalid input. Please enter an indicated character at the front of one of the choices, \n'h' for help, or 'z' to quit. Press enter to return.\n";
	else if (help == 1)
		cout << "\nTo play: Enter an input character corresponding to the letter before the period of the path you wish to take. \nInput 'z' to quit the game. Press enter to continue.\n";
	else {
		cout << "\nCome back soon, " << username << "! \n\n";
		exit(0);
	}

	cin >> user;

	// After user input, clears screen and prints current location description and path options without activating possible events
	printcurrent(0);

	return;
}

// Contains while loop encompassing the adventure game. 
int main()
{
	// Read in record-jar formatted text string
	filein("story.rjar");

	string startgame;
	string next;

	// Welcome screen: Addresses player by name and allows for a confidence booster. 
	system("CLS");
	cout << "Welcome to your adventure, " << username << ".\n\n";
	cout << "Enter 'Hug' for a hug. Enter something else to start your journey.\n";
	cin >> startgame;

	// Hugs
	while (startgame == "Hug" || startgame == "hug")
	{
		cout << "I <3 " << username << "! <(^-^)>\n";
		cin >> startgame;
	}

	// Encompasses the entire story portion of the game. While loop never ends.
	while (1)
	{
		// Print current description, player statistics, and event outcome.
        printcurrent(1);

		// Prints array of path choices and prompts for input for path decision. Returns name of chosen path.
		next = actions[cur].getpath(playerChoice());
		
		// Searches for the action associated with the chosen path name and returns the action array location whose name corresponds to that string. 
		for (int i = 0; i < numactions; i++)
		{
			if (next == actions[i].getname())
			{
				cur = i;
				break;
			}
		}
	}
}
