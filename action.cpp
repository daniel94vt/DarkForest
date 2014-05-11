#include "action.h"

// Constructor: Initializes default values for all action variables
// chance set to zero so events will not occur unless explicitly set.
// numevents initialized to -1 to indicate infinite events possible for this action
Action :: Action()
{
<<<<<<< HEAD
	name = "";
	prompt = "";
	description = "";
	chance = 0;
	eventstr = "";
	alteration = 0;
	numpaths = 0;
	numevents = -1;
	winlose = 0;
=======
    name = "";
    prompt = "";
    description = "";
    chance = 0;
    eventstr = "";
    alteration = 0;
    numpaths = 0;
    numevents = -1;
    winlose = 0;
>>>>>>> 16856cd61e51943d93fd9127140280c93844964f
}

Action :: ~Action()
{}

void Action :: setname(string newname)
{ name = newname; }

void Action :: setprompt(string newprompt)
{ prompt = newprompt; }

void Action :: setdescr(string newdescr)
{ description = newdescr; }

void Action :: setchance(int possibility)
{ chance = possibility; }

void Action :: setevent(string newevent)
{ eventstr = newevent; }

void Action :: setalt(int change)
{ alteration = change; }

void Action :: eventlimit(int setlimit)
{ numevents = setlimit; }

// Add new action name within the array of paths in the current object
void Action :: addpath(string newpath)
{
    paths[numpaths] = newpath;

<<<<<<< HEAD
	numpaths++;
=======
    numpaths++;
>>>>>>> 16856cd61e51943d93fd9127140280c93844964f
}

void Action :: gameover(int gameover)
{ winlose = gameover; }

string Action :: getname()
{ return name; }

string Action :: getprompt()
{ return prompt; }

string Action :: getdescr()
{ return description; }

string Action :: getpath(int chosenpath)
{ return paths[chosenpath]; }

int Action :: getnumpaths()
{ return numpaths; }

// Creates random number to compare to event chance to determine if the event occurs
// Returns the health/sanity alteration if it is processed, and decrements the remaining events if they are set as finite
int Action :: itshappening(void)
{
<<<<<<< HEAD
	int rollthedice;

	rollthedice = rand() % 100;

	if (chance > rollthedice)
	{
		if (numevents != 0)
		{
			if (winlose == 1)
			{
				cout << "\n\n\nCongratulations, you win!\n\n";
				return 99;
			}

			cout << "\n\n* " << eventstr;

			if (numevents != -1)
				numevents--;

			return alteration;
		}
	}

	return 0;
}

=======
    int rollthedice;

    rollthedice = rand() % 100;

    if (chance > rollthedice)
    {
        if (numevents != 0)
        {
            if (winlose == 1)
            {
                cout << "\n\n\nCongratulations, you win!\n\n";
                return 99;
            }

            cout << "\n\n* " << eventstr;

            if (numevents != -1)
                numevents--;

            return alteration;
        }
    }

    return 0;
}
>>>>>>> 16856cd61e51943d93fd9127140280c93844964f
