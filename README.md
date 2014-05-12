Dark Forest
===========

This project involves a C++ authentication interface which saves username and password information, and uses this to connect the user to a text-based story-driven adventure game with branching paths. Players will choose their fate as they avoid losing both their health and sanity while navigating a lethal, supernatural forest setting. The branching nature of the game means at least two playthroughs are required to experience all major portions of the game.

<!-- more -->

Contributors: daniel94 (aka stryder25), arenascf, alirmajd

URL: https://github.com/stryder25/DarkForest


How to Play:
--------------

To run the program, enter the commands:   
__$ make   
$ ./Forest [option]__

*Where [option] is __-l__ for existing user or __-n__ for new user*

If a new user, the game will ask you to enter a new username and create a new password, which must be entered twice for accuracy. If an existing user, you must enter an existing username, then enter the appropriate password when prompted. You will then be able to enter 'y' if you want to change the current password, or 'n' otherwise. At the end of either state, you will be transferred to the text game. 

To play the game, type the single alphabetical character (a-e) marking the start of your desired next path and press 'Enter'. Input 'z' to exit the game, enter 'h' for help. If an invalid entry is given, you will be notified and then return to the previous screen without any negative effect. 

Stay aware of your health and sanity levels throughout the game. If either reaches zero, you lose the game. There are also instant-death paths to look out for; be aware of your surroundings and pay attention to environmental clues. 

*(Protip: Accept some hugs into your life at the welcome screen for additional starting stats)*

Description:
-----------

The adventure portion of the project is composed of three major components. The action class defines the scenarios/actions of the player, encompassing its title, the prompt displayed on the path select screen, the description of the scnario, the names of the actions that it connects to, and an optional event composed of a probability, description, status effect, and maximum occurrences. The gameplay source file has a while loop that calls functions displaying the current scenario description, help text, player status, and prompts for path choices. It accepts player input to determine the next scenario based on the array of actions. This array is formed by calling a function that reads in a record-jar formatted file outlining the story by defining each actions necessary attributes; defaults are given because not every attribute needs to be specified.
 
We have tried to make the adventure exemplify the Unix design philosophy by making these compoments independent and modular so as to be less reliant on one another, transparent and simple for easier debugging, clear enough in both design and output that the player and potential future programmers can understand it, and designed with the Rule of Composition in mind so that it could be cleanly connected to the username/password interface.  

Alterations after user reviews:
- A player mentioned it was unclear at first how to play the game. Though directions were on the github page as well as the help menu, abbreviated instructions were placed in the top line of each page to help avoid confusion.
- One player mentioned that it was unclear how to return to the path selection screen after the invalid entry screen. Additional text is output to more explicitly guide the player.
- It was noted that the number of hugs (and thus stat increases) was seemingly unlimited; a cap was placed directly in that process so that the game will start after no more than 5 hugs.
- It was suggested that more functions be made to increase modularity, so changes were made including delegating the welcome screen previously in main() to its own function and simply calling it at the start.
- Naming schemes for functions was made more consistent
