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
    int thisPlayer = 0;
    int numPlayers = 2; 
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("----------------- Testing endTurn ----------------\n");
	printf("TEST 1: check turn is next player\n");
    endTurn(&testG);
    player = whoseTurn(&testG);
    if (player == thisPlayer + 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("player = %d, expected = %d\n", player, thisPlayer + 1);

	printf("TEST 2: check new player starts with 1 buy\n");
    if (testG.numBuys == 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("numBuys = %d, expected = %d\n", testG.numBuys, 1);
    

	printf("TEST 3: check new player starts with 1 action\n");
    if (testG.numActions == 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("numActions = %d, expected = %d\n", testG.numActions, 1);

	printf("TEST 4: check new player starts at initial phase\n");
    if (testG.phase == 0) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("phase = %d, expected = %d\n", testG.phase, 0);

	printf("TEST 5: check new player starts with 0 cards played\n");
    if (testG.playedCardCount == 0) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("playedCardCount = %d, expected = %d\n", testG.playedCardCount, 0);

	printf("TEST 6: check new player starts with 5 cards in hand\n");
    if (testG.handCount[player] == 5) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("handCount = %d, expected = %d\n", testG.handCount[player], 5);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", "endTurn");

	return 0;
}


