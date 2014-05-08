Dark Forest
===========

This project will involve a Qt interface that saves username and password information, and it will connect the user to a text-based story-driven adventure game with branching paths. Players will choose their fate as they avoid losing both their health and sanity while navigating a lethal, supernatural forest setting. The branching nature of the game means at least two playthroughs are required to experience all major portions of the game.

<!-- more -->

Contributors: daniel94, arenascf, alirmajd

URL: https://github.com/stryder25/DarkForest

*(Note: The Qt interface will be up at a later time. But for now, enjoy the game!)*

How to Play:
------------

To run the C++ program, enter the commands:   
__$ make   
$ ./Forest *desired_username*__

*If you don't enter a username, it will acknowledge you as Stranger. The username should not have any spaces.*

To play the game, type the single alphabetical character (a-e) marking the start of your desired next path and press 'Enter'. Input 'z' to exit the game, enter 'h' for help. If an invalid entry is given, you will be notified and then return to the previous screen without any negative effect. 

Stay aware of your health and sanity levels throughout the game. If eithe reaches zero, you lose the game. There are also instant-death paths to look out for; be aware of your surroundings and pay attention to environmental clues. 

*(Protip: Accept some hugs into your life at the welcome screen for additional starting stats)*

Description:
-----------

The adventure portion of the project is composed of three major components. The action class defines the scenarios/actions of the player, encompassing its title, the prompt displayed on the path select screen, the description of the scnario, the names of the actions that it connects to, and an optional event composed of a probability, description, status effect, and maximum occurrences. The gameplay source file has a while loop that calls functions displaying the current scenario description, help text, player status, and prompts for path choices. It accepts player input to determine the next scenario based on the array of actions. This array is formed by calling a function that reads in a record-jar formatted file outlining the story by defining each action's necessary attributes; defaults are given because not every attribute needs to be specified.
 
We have tried to make the adventure exemplify the Unix design philosophy by making these compoments independent and modular so as to be less reliant on one another, transparent and simple for easier debugging, clear enough in both design and output that the player and potential future programmers can understand it, and designed with the Rule of Composition in mind so that it can be cleanly connected to the outer Qt program in the future.  
