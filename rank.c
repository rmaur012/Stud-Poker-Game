#include <stdio.h>
#include "deck.h"

//For rankNames, '!' serves as an indicator of the end of that string
const char * rankNames[10] = {"None", "High Card!", "Pair!", "Two Pairs!", "3 Of A Kind!", "Straight!", "Flush!", "Full House!", "4 Of A Kind!", "Straight Flush!"};
const char * cardFaces[14] = {"Blank", "A", "2", "3","4","5","6","7","8","9","10","J","Q","K"};

struct card * determineRanks(struct card * players,  int totalPlayers){
	
	//playerRanks holds that info of all the player's hands that we need in order to determine 
	//each player's ranks and then declare the winner.
	struct status playerRanks [totalPlayers];
	
	//Pointer used in checking for flush and straight
	struct card * determinerOne = players; 
	
	//Assists previous pointer in determining if there is a straight
	//And help determining high card, pairs, 3-of-kind, and 4-of-kind for each hand
	struct card * determinerTwo = players;  
	
	int sequencecount=1;  //Counts how many cards are in sequence, 5 = straight
	int suitcount=1;  //Counts how many cards have the same suit as first card, 5 = flush
	int facecount=0;
	
	//These 4 variables are used to then (in another function) determine the rank of the hand per player
	
	//----------------IMPORTANT--------------------------------------------------------------------------
	//High and Low are used to determine the highest and second highest faces
	//that corresponds to the highest two ranks
	//ex. Hand = 77553, the highcount = 2, highface = 7, lowcount=2, lowface=5, therefore two pairs of 7 and 5
	//ex. Hand = 76553, the highcount = 2, highface = 5, lowcount=1, lowface=7, therefore one pairs of 5 and high card of 7
	//ex. Hand = 77543, the highcount = 2, highface = 7, lowcount=1, lowface=5, therefore one pairs of 7 and high card of 5
	//etc.
	int highcount=0;
	int highface=0;
	int lowcount=0;
	int lowface=0;
	
	int currentface = (*determinerOne).value;
	char currentsuit = (*determinerOne).suit;
	determinerOne++;
	
	int i, j;
	for(i=0; i<totalPlayers; i++){ //Every iteration is checking the "status" of one player
		
		
		//The for loop below will count how many cards have the same suit as the first card. 
		//If they are all the same suit, "suitcount" should equal to 5, thus a flush
		
		for(j=0; j<4; j++){ //4 since there are 4 cards hat we have to look at to determine if hand is a flush
			
			if(currentsuit == (*determinerOne).suit){
				suitcount++;
			}
			determinerOne++;
		}
		
		determinerOne = players + 1;
		
		//This for loop will count the cards that are in sequence of the next card. 
		//ex. A-K-Q-J-10 are in sequence, 10-6-5-3-A only has 6 & 5 in sequence,& 9-7-5-3-1 aren't in sequence
		//If they are all in sequence, "seqcount" should equal to 5, thus a straight
		
		for(j=0; j<4; j++){ //4 since there are 4 cards hat we have to look at to determine if hand is a straight
			
			if((*determinerTwo).value == ((*determinerOne).value)+1){
				sequencecount++;
			} else if((*players).value == 13 && sequencecount == 4 && (*determinerOne).value){ //In case there is a straight w/ high card A
				sequencecount++;
			}
			determinerOne++;
			determinerTwo++; 
		}
		
		
		
		for(j=0; j<5; j++){ //5 since there are 5 cards that we have to look at to determine pairs, 3-Of-Kind, etc.
			determinerTwo = (players+j);
			currentface = (*determinerTwo).value;
			while((*determinerTwo).belongsToPlayer == (i+1)){ 
				if((*determinerTwo).value == currentface){
					facecount++;
				}
				determinerTwo++;
			}
			
			if(highcount == 0){
				highcount = facecount;
				highface = currentface;
			} else if(highcount != 0 && highface!=currentface){
				if(highcount>facecount){
					if(lowcount==facecount && currentface==1){
							lowcount = facecount;
							lowface = currentface;
					} else if(lowcount<facecount){
						lowcount = facecount;
						lowface = currentface;
					}
				} else if(highcount<facecount){
					lowcount = highcount;
					lowface = highface;
					highcount = facecount;
					highface = currentface;
				} else if(highcount==facecount){
					if(highface>currentface && currentface == 1){ //If currentface is an Ace
						lowcount = highcount;
						lowface = highface;
						highcount = facecount;
						highface = currentface;
					} else if(highface>currentface){
						if(lowface<currentface || lowcount<facecount ){
							lowcount = facecount;
							lowface = currentface;
						} else if(lowcount==facecount && lowface<currentface){
							lowcount = facecount;
							lowface = currentface;
						}
					} else if(highface<currentface){
						lowcount = highcount;
						lowface = highface;
						highcount = facecount;
						highface = currentface;
					}
				}
			}
			facecount = 0;
			
		}
		
		playerRanks[i].seqcount = sequencecount;
		playerRanks[i].suitcount = suitcount;
		playerRanks[i].highfacecount = highcount;
		playerRanks[i].highfaceofcount = highface;
		playerRanks[i].lowfacecount = lowcount;
		playerRanks[i].lowfaceofcount = lowface;
		
		//Uncommenting the printf below can show the inner workings of the program when it runs, not needed for regular users
		//printf("Player %d: High: %d - %d | Low: %d - %d | Sequence: %d | Suit: %d\n", (i+1), playerRanks[i].highfacecount, playerRanks[i].highfaceofcount, playerRanks[i].lowfacecount, playerRanks[i].lowfaceofcount, playerRanks[i].seqcount, playerRanks[i].suitcount);
		
		//------Resets all variables to the needed declarations to process the next player
		
		highcount=0;
		highface=0;
		lowcount=0;
		lowface=0;
		
		suitcount=1;
		sequencecount=1;
		currentface = (*determinerOne).value;
		currentsuit = (*determinerOne).suit;
		determinerOne++;
		players+=5;
		determinerTwo = players;
	}
	
	struct status * stats = &playerRanks[0];
	
	ranker(stats, totalPlayers); //Assigns each player their hand's rank number
	
	determineWinner(stats, totalPlayers); //Prints out who is/are the winner(s)
		
	return players;
}


void ranker(struct status * playerStats, int totalPlayer){
	
	//Rank & Rank number
	//9 - Straight Flush
	//8 - 4 of a kind
	//7 - Full House
	//6 - Flush
	//5 - Straight
	//4 - 3 of a kind
	//3 - Two Pairs
	//2 - One Pair
	//1 - High Card
	
	const char * ranks;
	int i;
	for(i=0;i<totalPlayer;i++){
		
		if((*playerStats).highfacecount == 1 & (*playerStats).lowfacecount == 1){ //High Card - Count: High=1, Low=1
			(*playerStats).rank = 1;
		} else if((*playerStats).highfacecount == 2 & (*playerStats).lowfacecount == 1){ //One Pair - Count: High=2, Low=1
			(*playerStats).rank = 2;
		} else if((*playerStats).highfacecount == 2 & (*playerStats).lowfacecount == 2){ //Two Pair - Count: High=2, Low=2
			(*playerStats).rank = 3;
		} else if((*playerStats).highfacecount == 3 & (*playerStats).lowfacecount == 1){ //3 Of A Kind - Count: High=3, Low=1
			(*playerStats).rank = 4;
		} else if((*playerStats).seqcount == 5){ //Straight - Seqcount = 5
			(*playerStats).rank = 5;
		} else if((*playerStats).suitcount == 5){ //Flush - Suitcount = 5
			(*playerStats).rank = 6;
		} else if((*playerStats).highfacecount == 3 & (*playerStats).lowfacecount == 2){ //Full House - Count: High=3, Low=2
			(*playerStats).rank = 7;
		} else if((*playerStats).highfacecount == 4 & (*playerStats).lowfacecount == 1){ //4 Of A Kind - Count: High=4, Low=1
			(*playerStats).rank = 8;
		} else if((*playerStats).seqcount == 5 & (*playerStats).suitcount == 5){ //Straight Flush - seqcount & Suitcount = 5
			(*playerStats).rank = 9;
		}
		printf("Rank for Player %d is (a) ", (i+1)); 
		ranks = rankNames[(*playerStats).rank];
			
		while(*ranks != '!'){  //While loop prints out the rank of the highest hand
			printf("%c", *ranks);
			ranks++;
		}
		if((*playerStats).highfaceofcount == 10){ //'10' has 2 chars to print so this if statement is needed in case of a 10
			printf(" with a highest face of %c%c\n", *cardFaces[(*playerStats).highfaceofcount], *(cardFaces[(*playerStats).highfaceofcount]+1));
		} else {
			printf(" with a highest face of %c\n", *cardFaces[(*playerStats).highfaceofcount]);
		}
		playerStats++;	
	}
}

void determineWinner(struct status * playerStats, int allPlayers){
	
	struct status * topPlayer = playerStats; //topPlayer will be needed for printing out the winner
	int allWinners[allPlayers]; //Have 1 for the winner or winners in case of tie
	allWinners[0] = 1;
	int highestHand = (*playerStats).rank;
	int highestHandSuit = (*playerStats).highfaceofcount;
	int lowparthighestHand = (*playerStats).lowfaceofcount;
	playerStats++;
	
	int j;
	int i;
	
	//This for loop uses the information derived in the "determineWinner" function
	//and the algorithm in the function to determine the winner(s) 
	for(i=1; i<allPlayers; i++){
		
		if((*playerStats).rank > highestHand){ //If the current hand is a higher rank than highest hand
		
			for(j=0; j<allPlayers; j++){ //Unmark all previous winners since they are not higher ranks
				allWinners[j] = 0;
			}
			allWinners[i] = 1;  //Mark current hand as winner
			highestHand = (*playerStats).rank;
			highestHandSuit = (*playerStats).highfaceofcount;
			lowparthighestHand = (*playerStats).lowfaceofcount;
		} else if((*playerStats).rank == highestHand){ //if the highest hand and current hand are the same rank
		
			if((*playerStats).highfaceofcount == highestHandSuit){ //if the highest hand and current hand are the same suit
				
				//if the low of the current hand is better than low of highest hand OR if current hand has high Ace and the highest hand isn't an Ace
				if(((*playerStats).lowfaceofcount > lowparthighestHand) || ((*playerStats).lowfaceofcount == 1 && (*playerStats).lowfaceofcount != lowparthighestHand)){
					for(j=0; j<allPlayers; j++){
						allWinners[j] = 0;
					}
					allWinners[i] = 1;
					highestHand = (*playerStats).rank;
					highestHandSuit = (*playerStats).highfaceofcount;
					lowparthighestHand = (*playerStats).lowfaceofcount;
					
				//if the low of the current hand & low of highest hand are the same, both are winners (along with any other winner)
				} else if((*playerStats).lowfaceofcount == lowparthighestHand){
					allWinners[i] = 1; //More than 1 winner
				} 
				
			} else if((*playerStats).highfaceofcount > highestHandSuit){ //if current hand has higher face, current hand is now highest hand
			
				for(j=0; j<allPlayers; j++){ //Unmark all previous winners since they are not the real winners
					allWinners[j] = 0;
				}
				allWinners[i] = 1;  //Mark current hand as winner
				highestHand = (*playerStats).rank;
				highestHandSuit = (*playerStats).highfaceofcount;
				lowparthighestHand = (*playerStats).lowfaceofcount;
			}
		}
		playerStats++;
	}
	
	printf("\nThe Winner(s) is/are:\n");
	
	const char * ranks;
	for(i=0; i<allPlayers; i++){  //For loop will print out the winner(s) by checking which players are winners, have a 1
		//printf("%c\n", rankNames[2]);
		if(allWinners[i] == 1){
			printf("Player %d with (a) ", (i+1));
			ranks = rankNames[(*topPlayer).rank];
			
			while(*ranks != '!'){  //While loop prints out the rank of the highest hand
				printf("%c", *ranks);
				ranks++;
			}
			if((*topPlayer).highfaceofcount == 10){ //'10' has 2 chars to print so this if statement is needed in case of a 10
				printf(" with a highest face of %c%c\n", *cardFaces[(*topPlayer).highfaceofcount], *(cardFaces[(*topPlayer).highfaceofcount]+1));
			} else {
				printf(" with a highest face of %c\n", *cardFaces[(*topPlayer).highfaceofcount]);
			}
			
		}
		topPlayer++;
	}
	
}
