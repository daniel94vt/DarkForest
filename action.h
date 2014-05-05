#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

class Action
{
private:
	string name;
	string prompt;
	string description;
	int chance;
	string eventstr;
	int alteration;
	int numpaths;
	int numevents;
	int winlose;
	string paths[5];

public:
	Action();
	~Action();
	void setname(string name);
	void setprompt(string prompt);
	void setdescr(string descr);
	void setchance(int chance);
	void setevent(string eventout);
	void setalt(int change);
	void eventlimit(int setlimit);
	void addpath(string newpath);
	void gameover(int winlose);
	string getname(void);
	string getprompt(void);
	string getdescr(void);
	string getpath(int chosenpath);
	int getnumpaths(void);
	int itshappening(void);
};

#endif
