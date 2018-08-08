#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

// because we're providing random tests for cards
//   we just need to randomize the inputs for the cards
//   if there are any to be had
// this means that we need to stabilize the gamestate
//   such that randomization is restricted to the action
//   of playing the card
// so the question becomes "what actually affects the card being played?"
// in adventurer's case, it's the number of treasure cards in the player's deck
// and the type of treasure cards in the player's deck

int checkSmithy(int* k, struct gameState *gs, struct gameState *postGs)
{

    int i;
    int initialCounter, finalCounter;
    int thisPlayer = whoseTurn(gs);

	printf("TEST 1: Player has 2 more cards after playing\n");
    if (postGs->handCount[thisPlayer] == gs->handCount[thisPlayer] + 2) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("handCount result = %d, expected = %d\n", postGs->handCount[thisPlayer], gs->handCount[thisPlayer] + 2);

	printf("TEST 2: Player drew 3 cards from deck\n");
    if (postGs->deckCount[thisPlayer] == gs->deckCount[thisPlayer] - 3) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("deckCount result = %d, expected = %d\n", postGs->deckCount[thisPlayer], gs->deckCount[thisPlayer] - 3);

    // check that the card is in the discard pile
    // number of this card before + 1
	printf("TEST 3: Player has adventurer card in playedCard pile\n");
    initialCounter = 0, finalCounter = 0;
    for (i = 0; i < gs->playedCardCount; i++)
    {
        if (gs->playedCards[i] == smithy) { initialCounter++; };
    }
    for (i = 0; i < postGs->playedCardCount; i++)
    {
        if (postGs->playedCards[i] == smithy) { finalCounter++; };
    }
    if (finalCounter == initialCounter + 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("played count = %d, expected = %d\n", finalCounter, initialCounter + 1);

    // check that the number of actions is 0
	printf("TEST 4: Player has no remaining actions\n");
	printf("numActions count = %d, expected = %d\n", postGs->numActions, gs->numActions-1);
    assert(postGs->numActions == gs->numActions-1);

	printf("TEST 5: No state changes for other players\n");
    // ensure hand, deck, discard counts remain the same for all other players
    for (i = 0; i < gs->numPlayers; i++)
    {
        if (i != whoseTurn(gs))
        {
            if (postGs->deckCount[i] == gs->deckCount[i]) { printf("Test Passed: "); }
            else { printf("Test Failed: "); }
            printf("deck count = %d, expected = %d\n", postGs->deckCount[i], gs->deckCount[i]);
            
            if (postGs->handCount[i] == gs->handCount[i]) { printf("Test Passed: "); }
            else { printf("Test Failed: "); }
            printf("hand count = %d, expected = %d\n", postGs->handCount[i], gs->handCount[i]);
            
            if (postGs->discardCount[i] == gs->discardCount[i]) { printf("Test Passed: "); }
            else { printf("Test Failed: "); }
            printf("discard count = %d, expected = %d\n", postGs->discardCount[i], gs->discardCount[i]);
        }
    }

    printf("TEST 6: No changes to Kingdom Supply Card Piles\n");
    int numKingdomCards = sizeof(k)/sizeof(k[0]);
    for (i = 0; i < numKingdomCards; i++)
    {
        if (supplyCount(k[i], postGs) == supplyCount(k[i], gs)) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("kingdom count = %d, expected = %d\n", supplyCount(k[i], postGs), supplyCount(k[i], gs));
    }

    printf("TEST 7: No Changes to Victory Supply Card Piles\n");
    int v[3] = {estate, duchy, province};
    for (i = 0; i < 3; i++)
    {
        if (supplyCount(v[i], postGs) == supplyCount(v[i], gs)) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("victory count = %d, expected = %d\n", supplyCount(v[i], postGs), supplyCount(v[i], gs));
    }

    printf("TEST 8: No Changes to Treasure Supply Card Piles\n");
    int t[3] = {copper, silver, gold};
    for (i = 0; i < 3; i++)
    {
        if (supplyCount(t[i], postGs) == supplyCount(t[i], gs)) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("treasure count = %d, expected = %d\n", supplyCount(t[i], postGs), supplyCount(t[i], gs));
    }
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}


int main() 
{
    int i, j, testCounter, numPlayers, seed;
    int testCount = 20;
    srand(time(NULL));
    struct gameState gs, postGS;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // set up game with random number of players between 2 and MAX
    //int numPlayers = (rand() % (MAX_PLAYERS - 2)) + 2;

    for (testCounter = 0; testCounter < testCount; testCounter++)
    {

        seed = floor(Random() * 20000);
        numPlayers = (rand() % (MAX_PLAYERS - 2)) + 2;
        initializeGame(numPlayers, k, seed, &gs);

        gs.numPlayers = numPlayers;

        // for each player
        for (i = 0; i < numPlayers; i++)
        {
            // randomize size of decks
            // gs.deckCount[i] = floor(Random() * MAX_DECK);
            gs.deckCount[i] = floor(Random() * 20) + 1;
            // randomize cards in deck
            for (j = 0; j < gs.deckCount[i]; j++)
            {
                gs.deck[i][j] = floor(Random() * 26);
            }

            // randomize size of discard pile
            gs.discardCount[i] = floor(Random() * 20);
            // randomize cards in discard
            for (j = 0; j < gs.deckCount[i]; j++)
            {
                gs.discard[i][j] = floor(Random() * 26);
            }

            // randomize size of hand
            gs.handCount[i] = floor(Random() * MAX_HAND);
            // gs->handCount[i] = floor(Random() * 20);
            // randomize cards in hand
            for (j = 0; j < gs.handCount[i]; j++)
            {
                // gs->hand[i][j] = floor(Random() * 26);
                gs.hand[i][j] = floor(rand() % 26);
            }

        }

        gs.whoseTurn = rand() % numPlayers;
        gs.playedCardCount = 20;
        
        for (i = 0; i < gs.playedCardCount; i++)
        {
            gs.playedCards[i] = floor(rand() % 26);
        }

        int thisPlayer = whoseTurn(&gs);
        int randomHandPos = rand() % gs.handCount[thisPlayer];
        gs.hand[whoseTurn(&gs)][randomHandPos] = smithy;

        // set gamestate such that card can be played
        // copy gamestate 
        memcpy(&postGS, &gs, sizeof(struct gameState));
        
        // playSmithy
        int result = playCard(randomHandPos, 0, 0, 0, &postGS);
        printf("TEST 0: Player has played the card successfully\n");
        if (result == 0) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("playCard result = %d, expected = %d\n", result, 0);

        printState(&gs);

        printf("Play Result: %d\n", result);
        checkSmithy(k, &gs, &postGS);
    }

    return 0;
}
