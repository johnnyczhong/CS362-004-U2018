// cardtest4.c
// card to test: council room 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council room"

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
    int testCard = council_room;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    // place the test card into the player's hand, position 0
    G.hand[thisPlayer][0] = council_room;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("----------------- Testing %s ----------------\n", TESTCARD);

    // check initial conditions
    assert(testG.handCount[thisPlayer] == 5);
    assert(testG.numActions == 1);
    assert(testG.deckCount[thisPlayer] == 5);
    assert(testG.discardCount[thisPlayer] == 0);

    // check final conditions 
    // test 1: played successfully
	printf("TEST 1: Player has played the card successfully\n");
    result = playCard(0, 0, 0, 0, &testG);
    if (result == 0) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("playCard result = %d, expected = %d\n", result, 0);

    // test 2: deck decrease by 4
	printf("TEST 2: Player deck has decreased by 4\n");
    if (testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 4) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("playCard result = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);

    // test 3: hand has 8 cards
	printf("TEST 3: Player has 8 cards in hand\n");
    if (testG.handCount[thisPlayer] == 8) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("handCount result = %d, expected = %d\n", testG.handCount[thisPlayer], 5);
    
    // test 4: check that the card is in the played pile
	printf("TEST 4: Player has council_room card in playedCard pile\n");
    for (i = 0; i < testG.playedCardCount; i++)
    {
        if (testG.playedCards[i] == testCard) { playedTestCardCount++; };
    }
    if (playedTestCardCount == 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("played count = %d, expected = %d\n", playedTestCardCount, 1);

    // test 5: current player has more buys
	printf("TEST 5: Player has 1 more buy\n");
    if (testG.numBuys == G.numBuys + 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("numActions count = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);

	printf("TEST 6: Test that other players draw 1 card, discard unaffected\n");
    // ensure hand, deck, discard counts remain the same for all other players
    for (i = 1; i < numPlayers; i++)
    {
        if (testG.deckCount[i] == G.deckCount[i] - 1) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i] - 1);
        
        if (testG.handCount[i] == G.handCount[i] + 1) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i] + 1);
        
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


