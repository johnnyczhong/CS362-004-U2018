// cardtest3.c
// card to test: village

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
    int i, result;
    int seed = 1809;
    int numPlayers = 2; 
    int thisPlayer = 0; 
    int playedTestCardCount = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int testCard = village;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    // place the test card into the player's hand, position 0
    G.hand[thisPlayer][0] = village;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("----------------- Testing %s ----------------\n", TESTCARD);

    // check initial conditions
    assert(testG.handCount[thisPlayer] == 5);
    assert(testG.numActions == 1);
    assert(testG.deckCount[thisPlayer] == 5);
    assert(testG.discardCount[thisPlayer] == 0);

    // check final conditions 
	printf("TEST 1: Player has played the card successfully\n");
    result = playCard(0, 0, 0, 0, &testG);
    if (result == 0) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("playCard result = %d, expected = %d\n", result, 0);

    // test 2: deck decrease by 1
	printf("TEST 2: Player deck has decreased by 1\n");
    if (testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("playCard result = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);

    // test 3: hand has 5 cards
	printf("TEST 3: Player has 5 cards in hand\n");
    if (testG.handCount[thisPlayer] == 5) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("handCount result = %d, expected = %d\n", testG.handCount[thisPlayer], 5);
    
    // test 4: check that the card is in the played pile
	printf("TEST 4: Player has village card in playedCard pile\n");
    for (i = 0; i < testG.playedCardCount; i++)
    {
        if (testG.playedCards[i] == testCard) { playedTestCardCount++; };
    }
    if (playedTestCardCount == 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("played count = %d, expected = %d\n", playedTestCardCount, 1);

    // test 5: increase actions test (-1 for playing card, +2 for card effect)
	printf("TEST 5: Player has sum of +2 actions\n");
    if (testG.numActions == 2) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("numActions count = %d, expected = %d\n", testG.numActions, 2);

	printf("TEST 6: No state changes for other players\n");
    // ensure hand, deck, discard counts remain the same for all other players
    for (i = 1; i < numPlayers; i++)
    {
        if (testG.deckCount[i] == G.deckCount[i]) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
        
        if (testG.handCount[i] == G.handCount[i]) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
        
        if (testG.discardCount[i] == G.discardCount[i]) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("discard count = %d, expected = %d\n", testG.discardCount[i], G.discardCount[i]);
    }

    printf("TEST 7: No changes to Kingdom Supply Card Piles\n");
    int numKingdomCards = sizeof(k)/sizeof(k[0]);
    for (i = 0; i < numKingdomCards; i++)
    {
        if (supplyCount(k[i], &testG) == supplyCount(k[i], &G)) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("kingdom count = %d, expected = %d\n", supplyCount(k[i], &testG), supplyCount(k[i], &G));
    }

    printf("TEST 8: No Changes to Victory Supply Card Piles\n");
    int v[3] = {estate, duchy, province};
    for (i = 0; i < 3; i++)
    {
        if (supplyCount(v[i], &testG) == supplyCount(v[i], &G)) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("victory count = %d, expected = %d\n", supplyCount(v[i], &testG), supplyCount(v[i], &G));
    }

    printf("TEST 9: No Changes to Treasure Supply Card Piles\n");
    int t[3] = {copper, silver, gold};
    for (i = 0; i < 3; i++)
    {
        if (supplyCount(t[i], &testG) == supplyCount(t[i], &G)) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("treasure count = %d, expected = %d\n", supplyCount(t[i], &testG), supplyCount(t[i], &G));
    }

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


