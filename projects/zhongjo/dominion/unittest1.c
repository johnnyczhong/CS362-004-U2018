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

#define TESTCARD "village"

int main() {

    // set up gamestate such that a player can buy
    int i, buyCardResult;
    int seed = 1809;
    int numPlayers = 2; 
    int thisPlayer = 0; // players designated by number
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int testCard = village;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing buyCard: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: player can buy --------------
	printf("TEST 1: Player can buy cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

    // ensure the player has enough coins to buy the card
    updateCoins(thisPlayer, &testG, getCost(testCard));
    int initialCoins = testG.coins;

    // check that the conditions allow the player to buy cards
    int initialNumBuys = testG.numBuys;
    assert(initialNumBuys > 0);

    // supply has at least 1 remaining card
    int initialSupply = supplyCount(testCard, &testG);
    assert(initialSupply > 1);
    
    // player has enough coins to purchase card
    assert(testG.coins >= getCost(testCard));

    // record the number of this card in the player's current discard pile
    int initialTestCardCount = 0;
    for (i = 0; i < testG.discardCount[thisPlayer]; i++)
    {
        if (testG.discard[thisPlayer][i] == testCard) { initialTestCardCount++; };
    }

    // buyCard
    buyCardResult = buyCard(testCard, &testG);
    assert(buyCardResult == 0);
	printf("buy attempt result = %d, expected = %d\n", buyCardResult, 0);

    // check that the card is in the discard pile
    // number of this card before + 1
    int finalTestCardCount = 0;
    for (i = 0; i < testG.discardCount[thisPlayer]; i++)
    {
        if (testG.discard[thisPlayer][i] == testCard) { finalTestCardCount++; };
    }
    assert(finalTestCardCount == initialTestCardCount + 1);
	printf("discard count = %d, expected = %d\n", finalTestCardCount, initialTestCardCount + 1);

    // check that the number of buys is decreased by 1
    assert(testG.numBuys == initialNumBuys - 1);
	printf("numBuys count = %d, expected = %d\n", testG.numBuys, initialNumBuys - 1);

    // check that the player's available coins is decreased by the cost
    // of the purchased card
    assert(testG.coins == initialCoins - getCost(testCard));
	printf("coins count = %d, expected = %d\n", testG.coins, initialCoins - getCost(testCard));

    // check that the number of available supply has decreased by 1
    assert(supplyCount(testCard, &testG) == initialSupply - 1);
	printf("supply count = %d, expected = %d\n", supplyCount(testCard, &testG), initialSupply - 1);
    
    // failure tests
    // too few coins
	printf("TEST 2: Player can not buy cards, too few coins\n");

    // copy gamestate
	memcpy(&testG, &G, sizeof(struct gameState));

    // decrease coins
    // updateCoins(thisPlayer, &testG, -10);
    testG.coins = 0;
    // buyCard
    buyCardResult = buyCard(testCard, &testG);
    assert(buyCardResult == -1);
	printf("buy attempt result = %d, expected = %d\n", buyCardResult, -1);


	printf("TEST 3: Player can not buy cards, no buys remaining\n");
    //copy gamestate
	memcpy(&testG, &G, sizeof(struct gameState));
    // set buys to 0, not allowing player to buy
    testG.numBuys = 0;

    buyCardResult = buyCard(testCard, &testG);
    assert(buyCardResult == -1);
	printf("buy attempt result = %d, expected = %d\n", buyCardResult, -1);

	printf("TEST 4: Player can not buy cards, no supply remaining\n");
    // testCard has no supply
    testG.supplyCount[testCard] = 0;
    
    buyCardResult = buyCard(testCard, &testG);
    assert(buyCardResult == -1);
	printf("buy attempt result = %d, expected = %d\n", buyCardResult, -1);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", "buyCard");

	return 0;
}


