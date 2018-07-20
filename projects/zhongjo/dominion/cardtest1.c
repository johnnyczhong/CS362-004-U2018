// cardtest1.c
// function to test: playSmithy 

// what to test?
//    1. adds cards in hand by 3
//    2. decreases the number of actions remaining by 1
//    3. 1 more smithy card is now in discard

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

#define TESTCARD "smithy"

int main() {

    // set up gamestate such that a player can buy
    int i, result;
    int seed = 1809;
    int numPlayers = 2; 
    int numSmithy = 0, thisPlayer = 0; // players designated by number
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int testCard = village;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

    // place the smithy card into the player's hand, position 0
    testG.hand[thisPlayer][0] = smithy;

	printf("----------------- Testing buyCard: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: player can buy --------------
    // check initial conditions (handCount == 5, actions == 1, smithy in discard = 0)
    assert(testG.handCount[thisPlayer] == 5);
    assert(testG.numActions == 1);

    for (i = 0; i < testG.discardCount[thisPlayer]; i++)
    {
        if (testG.discard[thisPlayer][i] == smithy) { numSmithy++; };
    }
    assert(numSmithy == 0);

    // check final conditions (handCount == 7, actions == 0, smithy in discard == 1)
	// ----------- TEST 1: player can buy --------------
	printf("TEST 1: Player has played the card successfully\n");
    result = playCard(0, 0, 0, 0, &testG);
    if (result == 0) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("playCard result = %d, expected = %d\n", result, 0);

	printf("TEST 2: Player has 2 more cards after playing\n");
    if (testG.handCount[thisPlayer] == 7) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("handCount result = %d, expected = %d\n", testG.handCount[thisPlayer], 7);

    // check that the card is in the discard pile
    // number of this card before + 1
    int smithyDiscardCount = 0;
    for (i = 0; i < testG.discardCount[thisPlayer]; i++)
    {
        if (testG.discard[thisPlayer][i] == testCard) { smithyDiscardCount++; };
    }
    assert(smithyDiscardCount == numSmithy + 1);
	printf("discard count = %d, expected = %d\n", smithyDiscardCount, numSmithy + 1);

    // check that the number of actions is 0
    assert(testG.numActions == 0);
	printf("numActions count = %d, expected = %d\n", testG.numActions, 0);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", "smithy");

	return 0;
}


