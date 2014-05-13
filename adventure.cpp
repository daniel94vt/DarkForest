#include "action.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

// Global variables
Action actions[250];
int curPath = 0, health, sanity;
string username;

// Function prototypes
int fileRead(string gamefile);
int playerChoice(int totalactions);
int printCurrent(int eventenable);
void notifyPlayer(int helpint);
void clearScreen(void);
void restartGame(void);
void displayError(int err);
void welcomeScreen(void);

// Function that clears the terminal, should work in both unix and windows environments
void clearScreen(void)
{
    int status;
    if (system("CLS"))
        status = system("clear");

    status++;
}

// Reads in record-jar format file and initializes array of Action objects
// Returns the number of action objects created
int fileRead(string gamefile)
{
    string start, end, newpath;
    int endint, numactions = 0;

    ifstream gametext(gamefile.c_str());

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
                    actions[numactions].setwin(endint);
                else if (start == "max")
                    actions[numactions].seteventlimit(endint);
            }
            // Track number of areas taken from the input file
            numactions++;
        }
        gametext.close();
    }
    return numactions;
}

// Prints possible paths to player and accepts input based on the letter of the given strings. Returns integer corresponding to path choice.
// Parameter given is the total number of action objects to iterate through.
int playerChoice(int totalactions)
{
    string path;
    int choice = 42;
    int numpath = actions[curPath].getnumpaths();

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
            for (int j = 0; j < totalactions; j++)
            {
                if (actions[curPath].getpath(i) == actions[j].getname())
                {
                    cout << actions[j].getprompt() << endl;
                    break;
                }
            }
        }

        // Allow user input to choose path. Lower/upper-case a-e are associated with choices, 'h' calls notifyPlayer() to display help text.
        // 'Z' calls the same function to exit the game. An invalid entry calls notifyPlayer() to alert the player and print instructions.
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
            notifyPlayer(1);
        else if (path == "z" || path == "Z")
            notifyPlayer(2);
        else
            notifyPlayer(0);

    }
    return choice;
}

// Displays welcome text to player, and prompts for hugs for status boost pre-game.
void welcomeScreen()
{
	string startgame;

        clearScreen();

        // Addresses player by name
        cout << "Welcome to your adventure, " << username << ".\n\n";
        cout << "Enter 'Hug' for a hug. Enter something else to start your journey.\n";
        cin >> startgame;

        while (startgame == "Hug" || startgame == "hug")
        {
            cout << "I <3 " << username << "! <(^-^)>\n";
                    sanity++;
            health += 10;

            // Hug limit is capped at 5, when the player hits 100 health
            if (health >= 100)
                break;

            cin >> startgame;
        }
}

// Prints top reminder help header, current action description, and current stats.
// If parameter given is 1, the event for the current action is processed.
int printCurrent(int eventenable)
{
    int effect;
    int prevhp = health;
    int prevsan = sanity;

    clearScreen();
    cout << "a-e: Choose path     z: Exit       h: Help \n-------------------------------------------------\n";

    // Print description of current location
    cout << (actions[curPath].getdescr());

    // Processes event. If a non-zero integer is returned, either health or sanity is affected.
    // If either reaches zero, the game ends.
    if (eventenable == 1)
    {
        effect = actions[curPath].processevent();

        // Winstate achieved
        if (effect == 99)
            return 1;

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
        return 1;
    }

    if (sanity > 10)
        sanity = 10;
    else if (sanity <= 0)
    {
        cout << "\n\n** The wilderness has driven " << username << " crazy. "
             << username << " has lost " << username << "'s mind and cannot continue.\n\n";
        return 1;
    }

    if (prevhp != health)
        cout << "\n\nHealth: " << health << " <" << health-prevhp << ">     Sanity: " << sanity << "\n";
    else if (prevsan != sanity)
        cout << "\n\nHealth: " << health << "     Sanity: " << sanity << " <" << sanity-prevsan << ">\n";
    else
        cout << "\n\nHealth: " << health << "     Sanity: " << sanity << "\n";

    cout << "-------------------------------------------------- \n" << username << ", choose your path: \n";

    return 0;
}

// Called if the player input 'h' for help, 'z' to quit, or an invalid string upon path selection.
void notifyPlayer(int help)
{
    string user;

    clearScreen();

    if (help == 0)
        cout << "\nUh-oh, invalid input, " << username << "! \n";
    else if (help == 1)
        cout << "\nWelcome to the Help Screen, " << username << "!\n";
    else {
        cout << "\nCome back soon, " << username << "! \n\n";
        exit(0);
    }

    cout << "-------------------------------------\n";
    cout << "To play: Enter an indicated character ('a'-'e') corresponding to the letter before the period marking the path you wish to take. Input 'z' to quit the game, or 'h' for help, as indicated in the top menu. \n\nInput any value to return to the previous screen.\n";

    cin >> user;

    // After user input, clears screen and prints current location description and path options without activating possible events
    printCurrent(0);
}

// Function that determines, from player input, if the game is to be restarted or exited
void restartGame(void)
{
    string repeat;

    cout << "\n----------------------------------\n\n";
    cout << "\nInput 'z' to exit the program. Input anything else to play again, " << username << "! \n";
    cin >> repeat;

    clearScreen();

    if (repeat == "z" || repeat == "Z")
    {
        cout << "\nCome back soon, " << username << "!\n\n";
        exit(0);
    }
}

void displayError(int err) {
    if(err == 0) {
        fputs("Usage:     ./Forest command1\n"
                    "command1 : -l\t Current User   : Login with your username and password\n"
                    "           -n\t New User       : Create a new username and password\n", stderr);
        exit(EXIT_FAILURE);
    }
    else if(err == 1) {
        fputs("Error:  Invalid command", stderr);
        exit (EXIT_FAILURE);
    }
}
