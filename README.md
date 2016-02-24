This is a ReadMe file for the Stud Poker Program.

___About___

A simple stud poker program where a deck is created and the specified cards are given to the specified players.
This program does not allow bets or throwing away cards for new cards. The hand given is the hand each player is
stuck with. Each hand has a rank and a winner is determined.

Amount of players allowed: 1-13
Amount of cards per player allowed: 1-13
Any combination of the two that requires more than 52 cards will not be accepted. 
  (Ex. 10 cards for 10 players = 100 cards required. 100 > 52, therefore an error will be shown) 


Upon executing the program, a deck of cards will be generated in order, shuffled, and displayed.

The "cards" will be passed out, the amount specified (#1) to the amount of players specified (#2), and displayed.
 
The hands will then be sorted per player and then display the hands again, sorted.

Each hand will be ranked and the player with the highest hand wins.



What you should see:

-The cards in the deck (All 52 cards in a random order)
-The player's cards, Unsorted.
-The player's cards, Sorted.
-Player's ranks.
-Winner Chosen.



__For_Execution___

You will require three files that should be bundled with this ReadMe file: Main.c deck.c and deck.h

You are to compile them using the GCC compiler.
Make sure to have deck.h in the same directory.
 

Like this:	gcc main.c deck.c


That should generate an a.out file.

To use the file it must be in the following format:


./a.out (#1) (#2)


(#1) = number of cards to give per player. Minimum of 1. Maximum of 13.

(#2) = number of players to give cards. Minimum of 1. Maximum of 13.
