Darren Lee 

CruzID: danalee 

Spring 2021
# Assignment 1: Left, Right and Center 
In the game Left, Right, and Center, there are 2 to 14 players that each have $3 and three dice with 6 faces each. 
3 of the faces are a •, 1 is an L (left), 1 is an R (right), and 1 is a C (center). Player 1 rolls 3 dice if he or she has 
$3 or more. A player rolls 2 dice if he or has $2 and 1 die if he or she has $1. Players pass if they have no money. 

For each die:  

If the player rolls L, he gives $1 to the player on his left. 

If the player rolls R, he gives $1 to the player on his right. 

If the player rolls C, he puts the $1 in the pot in the center. 

If the player rolls •, he ignores it. 

Then move to the next player to the right. Repeat until only one player has any money. That remaining player wins the pot in the center. 
## Build
	$ make
## Running
	$ ./lrc
## Cleaning
	$ make clean
## Files
	philos.h
		Header file that contains the array of the names of the philosopher players in the game
	
	lrc.c
		File containing C program for the game
	
	Makefile
		Contains the directives for building lrc and and cleaning
	
	DESIGN.pdf
		Contains a description of the game, inputs and expected outputs, pseudocode, and drawings/scratch work on paper
