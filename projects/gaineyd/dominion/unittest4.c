// unittest1.c
// function to test: endTurn

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


