#include "action.h"

#ifndef ACTIONCLASS_H
#define ACTIONCLASS_H

Action :: Action()
{
	name = "";
	prompt = "";
	description = "";
	chance = 0;
	eventstr = "";
	alteration = 0;
	numpaths = 0;
	numevents = -1;
	winlose = 0;
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

void Action :: addpath(string newpath)
{
    paths[numpaths] = newpath;

	numpaths++;
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

int Action :: itshappening(void)
{
	int rollthedice;

	rollthedice = rand() % 100;

	if (chance > rollthedice)
	{
		if (numevents != 0)
		{
			if (winlose == 1)
			{
				cout << "\n\n\nCongratulations, you win!\n\n";
				exit(0);
			}
			else if (winlose == -1)
			{
				cout << "\n\n\nYour adventure has come to its end.\n\n";
				exit(0);
			}

			cout << "\n\n* " << eventstr;

			if (numevents != -1)
				numevents--;

			return alteration;
		}
	}

	return 0;
}

#endif
