#include <stdio.h>
#include <time.h>
#include "deck.h"

struct card *generateShuffleAndDisplayDeck(){

//----------------Deck will be created in order--------------------------------------
	
	struct card deck[51];
	
	int determineValue = 1;
	int i;	
	
	for(i=0; i < ALLCARDS; i++){ //This will create the deck in order
		
		if(i < 13 && determineValue < 14){
			deck[i].suit = 'S';
			deck[i].value = determineValue;
			determineValue++;
		} else if(i>12 && i<26 && determineValue < 14){
			deck[i].suit = 'H';
			deck[i].value = determineValue;
			determineValue++;
		} else if(i>25 && i<39 && determineValue < 14){
			deck[i].suit = 'D';
			deck[i].value = determineValue;
			determineValue++;
		} else if(i>38 && i<ALLCARDS && determineValue < 14){
			deck[i].suit = 'C';
			deck[i].value = determineValue;
			determineValue++;
		} else {
			determineValue = 1;
			i--;
		}
	}

//----------------Deck has been created in order. Deck will now be shuffled-----------
	
	time_t times;
	srand(time(&times));
	
	int goThrough; //Will point to a card that will be moved to shuflocation
	int shuflocation; //This will be the new location of the current card
	struct card tempcard; //Hold the card when it moves
	
	for(goThrough=0; goThrough< ALLCARDS; goThrough++){ //This will "shuffle" the deck
		shuflocation = (rand()%ALLCARDS);
		tempcard = deck[goThrough];
		deck[goThrough] = deck[shuflocation];
		deck[shuflocation] = tempcard;
	}
	
//---------------Deck has been shuffled. It will now be printed-----------------------	
	
	int val;
	char suits;
	
	printf("Deck: ");
		
	for(goThrough = 0; goThrough < ALLCARDS; goThrough++){
		
		val = deck[goThrough].value;
		suits = deck[goThrough].suit;
		
		if(val == 1){ //Card is an Ace
			printf("  A-%c,", suits);
		} else if(val == 11){ //Card is a Jack
			printf("  J-%c,", suits);
		} else if(val == 12){ //Card is a Queen
			printf("  Q-%c,", suits);
		} else if(val == 13){ //Card is a King
			printf("  K-%c,", suits);
		} else { //Card is a number
			printf(" %2d-%c,", val, suits);
		}
	}
		
	printf("\n");
				
//---------------The deck has been printed--------------------------------------------	
		
	struct card *top =  &deck[0];
	return top;
}






/* deck points to the deck, initially to the top "card"
* allPlay points to the cards that belong to a certain player, initially to card 1 of player 1
* neededCards tells the number of total cards needed to pass out
* cardsPerPlayer tells how many cards to give each player
*
* cardPlaceholder is to know how many cards we have passed to a player and when to move on to the next player by modulus
*/

struct card * passOutCards(struct card *deck, struct card * allPlay, int neededCards, int cardsPerPlayer){
	
	int countCardsPassed=0;
	int cardPlaceholder;
	struct card *returnPointer = allPlay; //This is to have a pointer that points to the beginning.
	int playerCounter = 1; //Keeps tabs on which player we are giving cards to.
	
	
	while(countCardsPassed < neededCards){
		
		(*allPlay).value = (*deck).value;
		(*allPlay).suit = (*deck).suit;
		(*allPlay).belongsToPlayer = playerCounter; 
		countCardsPassed++;
		
		cardPlaceholder = countCardsPassed % cardsPerPlayer;
		
		if(cardPlaceholder == 0){ //Moves to the next player after passing required cards to the previous
			playerCounter++;
		}
		allPlay += 1;
		deck++;		
	}
	return returnPointer;
}




void printPlayersHands(struct card * allPlayrs, int neededCards, int cardsPerPlayer){

	int countCardsPrinted = 0;
	int cardPlaceholder;
	int cardValue;
	int playerNumber = 1;
	int totalPlayers = (neededCards / cardsPerPlayer);
	
	printf("\n Player %d:\n", (*allPlayrs).belongsToPlayer);
	
	while(countCardsPrinted < neededCards){
		
		cardValue = (*allPlayrs).value;
		
		if(cardValue == 1){
			printf("- A %c\n", (*allPlayrs).suit);
		} else if(cardValue == 11){
			printf("- J %c\n", (*allPlayrs).suit);
		} else if(cardValue == 12){
			printf("- Q %c\n", (*allPlayrs).suit);
		} else if(cardValue == 13){
			printf("- K %c\n", (*allPlayrs).suit);
		} else {
			printf("- %d %c\n",(*allPlayrs).value, (*allPlayrs).suit);
		}	
		
		countCardsPrinted++;
		
		cardPlaceholder = countCardsPrinted % cardsPerPlayer;
		
		if(cardPlaceholder == 0 && playerNumber < totalPlayers){
			playerNumber++;
			printf("\n Player %d:\n", playerNumber);
		} 
		allPlayrs += 1;		
	}	
}



//NC = Needed Cards
//CPP = Cars Per Player

void sortAndPrint(struct card * plyrCards, int NC, int CPP){
	
	int lookAtPlayer = 1;
	int higherValueFound = 0;
	int nextPlayerBoolean = 0;
	int cardCounter = 0;
	struct card temp = (*plyrCards);
	struct card * tempIndex;
	struct card * currentCard = plyrCards+1;
 	struct card * head = plyrCards; //To be used to pass to parameters of the print function
	
	int i;
	
	for(i=0; i<NC; i++){
		
		while((*currentCard).belongsToPlayer == lookAtPlayer){
			
			if((*currentCard).value > (*plyrCards).value && temp.value < (*currentCard).value){
				higherValueFound = 1;
				temp = (*currentCard);
				tempIndex = currentCard;
			}	
				
			currentCard += 1;	
			nextPlayerBoolean++;
		}
		
		if(higherValueFound == 1){
			(*tempIndex) = (*plyrCards);
			(*plyrCards) = temp;
			higherValueFound = 0;
		}
		if(nextPlayerBoolean == 0){
			lookAtPlayer++;
		}
		plyrCards +=1;
		temp = (*plyrCards);
		currentCard = plyrCards+1;
		cardCounter++;
		nextPlayerBoolean = 0;
		
	}
	
	printf("\nBy sorting the hands, they now look like...\n");

//---------------Cards have been sorted. It will be printed in the function below.--------------
	
	printPlayersHands(head, NC, CPP);
	
}
