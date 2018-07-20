// unittest1.c
// function to test: buyCard

// what to test?
// 1. success:
//    a. places the card in the player's discard pile
//    b. reduces the number of coins available to the player equal to the number of the cost of the card
//    c. decreases the number of buys remaining by 1
//    d. decreases the number of available cards of that type by 1
// 2. failure:
//    a. does not add a card to the player's hand or discard pile
//    b. does not reduce the number of coins.
//    c. 

// agenda:
// 1. set up game state
// 2.

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {

    // set up gamestate such that a player can buy
    int player;
    int seed = 1809;
    int numPlayers = 2; 
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("----------------- Testing whoseTurn ----------------\n");
	printf("TEST 1: 0th player's turn\n");
    player = whoseTurn(&testG);
    if (player == 0) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("player = %d, expected = %d\n", player, 0);

	printf("TEST 2: 1st player's turn\n");
    endTurn(&testG);
    player = whoseTurn(&testG);
    if (player == 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("player = %d, expected = %d\n", player, 1);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", "whoseTurn");

	return 0;
}


