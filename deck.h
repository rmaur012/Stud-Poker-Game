#include <stdio.h>

#define ALLCARDS 52
#define MODULARFORSHUFFLING 53

extern const char * rankNames[];
extern const char * cardFaces[];

struct card{
	int belongsToPlayer; //This shows which player the card belongs to.
	char suit;
	int value;
};

struct status{
	int seqcount;     //5 if the 5 cards are in sequence (straight)
	int suitcount;     //5 if all 5 cards have the same suit (flush)
	int highfacecount;  //Tells the amount of cards that are the same
	int highfaceofcount; //Tells the face that corresponds to facecount
	int lowfacecount;     //Tells the amount of cards that are the same
	int lowfaceofcount;    //Tells the face that corresponds to facecount
	int rank;
};

struct card *generateShuffleAndDisplayDeck();
struct card * passOutCards(struct card *deck, struct card * allPlay, int neededCards, int players);
void printPlayersHands(struct card * allPlayrs, int neededCards, int cardsPerPlayer);
void sortAndPrint(struct card * plyrCards, int NC, int CPP);
struct card * determineRanks(struct card * players, int totalPlayers);
void ranker(struct status * playerStats, int totalPlayers);
void determineWinner(struct status * playerStats, int allPlayers);
