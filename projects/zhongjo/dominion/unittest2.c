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
    int i;
    int seed = 1809;
    int numPlayers = 2; 
    int thisPlayer = 0; // players designated by number
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    //discard all cards from thisPlayer's hand
    for (i = 0; i < G.handCount[thisPlayer]; i++)
    {
        G.hand[thisPlayer][i] = -1;
    }

	printf("----------------- Testing updateCoins ----------------\n");
	printf("TEST 1: Player has 1 copper\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
    // 1 copper
    testG.hand[thisPlayer][0] = copper;
    updateCoins(thisPlayer, &testG, 0);
    // assert(testG.coins == 1);
	printf("coin count = %d, expected = %d\n", testG.coins, 1);

    // 1 silver
	printf("TEST 2: Player has 1 silver\n");
	memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][0] = silver;
    updateCoins(thisPlayer, &testG, 0);
    assert(testG.coins == 2);
	printf("coin count = %d, expected = %d\n", testG.coins, 2);

    // 1 gold
	printf("TEST 3: Player has 1 gold\n");
	memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][0] = gold;
    updateCoins(thisPlayer, &testG, 0);
    assert(testG.coins == 3);
	printf("coin count = %d, expected = %d\n", testG.coins, 3);

    // 1 each
	printf("TEST 4: Player has 1 copper, 1 silver, 1 gold\n");
	memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][0] = copper;
    testG.hand[thisPlayer][1] = silver;
    testG.hand[thisPlayer][2] = gold;
    updateCoins(thisPlayer, &testG, 0);
    assert(testG.coins == 6);
	printf("coin count = %d, expected = %d\n", testG.coins, 6);

    // 1 each and positive bonus
	printf("TEST 5: Player has 1 copper, 1 silver, 1 gold, 4 bonus coins\n");
	memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][0] = copper;
    testG.hand[thisPlayer][1] = silver;
    testG.hand[thisPlayer][2] = gold;
    updateCoins(thisPlayer, &testG, 4);
    assert(testG.coins == 10);
	printf("coin count = %d, expected = %d\n", testG.coins, 10);

    // 1 each and negative bonus
	printf("TEST 6: Player has 1 copper, 1 silver, 1 gold, -6 bonus coins\n");
	memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][0] = copper;
    testG.hand[thisPlayer][1] = silver;
    testG.hand[thisPlayer][2] = gold;
    updateCoins(thisPlayer, &testG, -6);
    assert(testG.coins == 0);
	printf("coin count = %d, expected = %d\n", testG.coins, 0);

    // 1 each and negative bonus exceeding positive coin value
	printf("TEST 7: Player has 1 copper, 1 silver, 1 gold, -7 bonus coins\n");
	memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][0] = copper;
    testG.hand[thisPlayer][1] = silver;
    testG.hand[thisPlayer][2] = gold;
    updateCoins(thisPlayer, &testG, -7);
    // assert(testG.coins == 0);
    if (testG.coins == 0) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("coin count = %d, expected = %d\n", testG.coins, 0);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", "updateCoins");

	return 0;
}


