// unittest1.c
// function to test: whoseTurn

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


