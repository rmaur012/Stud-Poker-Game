#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

#define MAXLIMIT 13

int main(int argc, char *argv[]){
	
	int numofcards;
	int numofplayers;
	if(argv[1] == NULL){
		numofcards = -1;
	} else if(argv[2] == NULL){
		numofplayers = -1;
	} else {
		numofcards = atoi(argv[1]);
	
		numofplayers = atoi(argv[2]);
	}
	int cardsrequired;
	
	if((cardsrequired = numofcards * numofplayers) <= ALLCARDS && numofcards<= MAXLIMIT && numofplayers<=MAXLIMIT && numofcards >0 && numofplayers >0){
		
		struct card wholePass[cardsrequired];
		struct card * topCard;
		struct card * ptrToPassedCards = &wholePass[0];
		
		topCard = generateShuffleAndDisplayDeck();
		
		ptrToPassedCards = passOutCards(topCard, wholePass, cardsrequired, numofplayers);		
			
		printPlayersHands(ptrToPassedCards, cardsrequired, numofcards);
		
		sortAndPrint(ptrToPassedCards, cardsrequired, numofcards);
		
		determineRanks(ptrToPassedCards,  numofplayers);	

	} else { //This section acts as error handling
		
		/*Errors in order:
		*-If input is null.
		*-If input is zero.
		*-If input is more than maximum limit (13).
		*-If the resulting amount of cards is more than 52.
		*/

		if(numofcards == -1){
			printf("Error: Enter the number of cards to give per player.\n");
		} else if(numofplayers == -1){
			printf("Error: Enter the number of players to give cards to.\n");
		}else if(numofcards == 0){
			printf("Error: Number of cards need to be more than zero.\n");
		}else if(numofplayers == 0){
			printf("Error: Number of players need to be more than zero.\n");
		} else if(numofcards>MAXLIMIT){
			printf("Error: Amount of cards per player cannot exceed %d.\n", MAXLIMIT);
		} else if(numofplayers>MAXLIMIT){
			printf("Error: Amount of players cannot exceed %d.\n", MAXLIMIT);
		} else {
			printf("Error: Invalid combination of cards and players. Requires more than %d cards.\n", ALLCARDS);
		}
	}
		
	return 0;
}
