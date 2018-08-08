// cardtest1.c
// function to test: playAdventurer

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {

    // set up gamestate such that a player can buy
    int i, result, finalTreasureCount;
    int seed = 1809;
    int numPlayers = 2; 
    int initialDiscardTreasureCount = 0, finalDiscardTreasureCount = 0, playedAdventurerCount = 0;
    int initialTreasureCount = 0, thisPlayer = 0; 
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int testCard = adventurer;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    // place the test card into the player's hand, position 0
    G.hand[thisPlayer][0] = adventurer;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("----------------- Testing %s ----------------\n", TESTCARD);

    // check initial conditions
    assert(testG.handCount[thisPlayer] == 5);
    assert(testG.numActions == 1);
    
    for (i = 0; i < testG.handCount[thisPlayer]; i++)
    {
        if (handCard(i, &testG) == copper || handCard(i, &testG) == silver || handCard(i, &testG) == gold)
            initialTreasureCount++;
    }

    for (i = 0; i < testG.discardCount[thisPlayer]; i++)
    {
        if (testG.discard[thisPlayer][i] == copper || testG.discard[thisPlayer][i] == silver || testG.discard[thisPlayer][i] == gold)
            initialDiscardTreasureCount++;
    }

    // check final conditions 
	printf("TEST 1: Player has played the card successfully\n");
    result = playCard(0, 0, 0, 0, &testG);
    if (result == 0) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("playCard result = %d, expected = %d\n", result, 0);

    // initial tests with coppers (standard start)
	printf("TEST 2a: Player has 2 additional copper cards in hand after playing\n");
    finalTreasureCount = 0;
    for (i = 0; i < testG.handCount[thisPlayer]; i++)
    {
        if (handCard(i, &testG) == copper || handCard(i, &testG) == silver || handCard(i, &testG) == gold)
            finalTreasureCount++;
    }

    if (finalTreasureCount == initialTreasureCount + 2) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("treasure count result = %d, expected = %d\n", finalTreasureCount, initialTreasureCount + 2);

	printf("TEST 2b: Player has 2 additional silver cards in hand after playing\n");
	memcpy(&testG, &G, sizeof(struct gameState));
    // replace all treasures with silvers
    for (i = 0; i < testG.deckCount[thisPlayer]; i++)
    {
        if (testG.deck[thisPlayer][i] == copper)
            testG.deck[thisPlayer][i] = silver;
    }
    result = playCard(0, 0, 0, 0, &testG);

    finalTreasureCount = 0;
    for (i = 0; i < testG.handCount[thisPlayer]; i++)
    {
        if (handCard(i, &testG) == copper || handCard(i, &testG) == silver || handCard(i, &testG) == gold)
            finalTreasureCount++;
    }

    if (finalTreasureCount == initialTreasureCount + 2) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("treasure count result = %d, expected = %d\n", finalTreasureCount, initialTreasureCount + 2);

    // replace all treasures with gold
	printf("TEST 2c: Player has 2 additional gold cards in hand after playing\n");
	memcpy(&testG, &G, sizeof(struct gameState));
    // replace all treasures with silvers
    for (i = 0; i < testG.deckCount[thisPlayer]; i++)
    {
        if (testG.deck[thisPlayer][i] == copper)
            testG.deck[thisPlayer][i] = gold;
    }

    result = playCard(0, 0, 0, 0, &testG);

    finalTreasureCount = 0;
    for (i = 0; i < testG.handCount[thisPlayer]; i++)
    {
        if (handCard(i, &testG) == copper || handCard(i, &testG) == silver || handCard(i, &testG) == gold)
            finalTreasureCount++;
    }

    if (finalTreasureCount == initialTreasureCount + 2) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("treasure count result = %d, expected = %d\n", finalTreasureCount, initialTreasureCount + 2);

    // test 3
	printf("TEST 3: Player has same or 0 treasure cards in discard\n");
    for (i = 0; i < testG.discardCount[thisPlayer]; i++)
    {
        if (testG.discard[thisPlayer][i] == copper || testG.discard[thisPlayer][i] == silver || testG.discard[thisPlayer][i] == gold)
            finalDiscardTreasureCount++;
    }

    if (initialDiscardTreasureCount == finalDiscardTreasureCount || finalDiscardTreasureCount == 0) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("discard result = %d, expected = %d or 0\n", finalDiscardTreasureCount, initialDiscardTreasureCount);

    // check that the card is in the played pile
    // number of this card before + 1
	printf("TEST 4: Player has adventurer card in playedCard pile\n");
    for (i = 0; i < testG.playedCardCount; i++)
    {
        if (testG.playedCards[i] == testCard) { playedAdventurerCount++; };
    }
    if (playedAdventurerCount == 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("played count = %d, expected = %d\n", playedAdventurerCount, 1);

    // check that the number of actions is 0
	printf("TEST 5: Player has no remaining actions\n");
	printf("numActions count = %d, expected = %d\n", testG.numActions, 0);
    assert(testG.numActions == 0);

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


