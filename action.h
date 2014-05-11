#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

/*
 Defines an action class wherein each object has attributes:
    Name: Title of object for easier bookkeeping
    Prompt: String output to player to detail nature of the path
    Description: String output if the object is the current action, describes action or surroundings
    Chance: Possibility of event to occur
    Eventstr: String output if the event happens
    Alteration: Change made to health or sanity due to event
    Numpaths: Number of other actions this object points to
    Numevents: Maximum number of events that can occur in a single game at this particular action
    Winlose: Indicates winstate and program exit
    Paths[5]: Array of actions pointed to by current object
*/
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
    int itshappening(void);             // Determines if event will happen and processes if true
};

#endif  // ACTION_H
