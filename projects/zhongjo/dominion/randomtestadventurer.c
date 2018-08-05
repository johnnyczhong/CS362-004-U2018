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

#define TESTCARD "adventurer"

// because we're providing random tests for cards
//   we just need to randomize the inputs for the cards
//   if there are any to be had
// this means that we need to stabilize the gamestate
//   such that randomization is restricted to the action
//   of playing the card
// so the question becomes "what actually affects the card being played?"
// in adventurer's case, it's the number of treasure cards in the player's deck
// and the type of treasure cards in the player's deck

int checkAdventurer(int* k, struct gameState *gs, struct gameState *postGs)
{

    int i;
    int initialCounter, finalCounter;
    int thisPlayer = whoseTurn(gs);
    // char name[MAX_STRING_LENGTH];

    // check final conditions
	printf("TEST 1: Player %d has same or 0 treasure cards in discard\n", whoseTurn(gs));
    initialCounter = 0, finalCounter = 0;
    for (i = 0; i < gs->discardCount[thisPlayer]; i++)
    {
        if (gs->discard[thisPlayer][i] == copper || gs->discard[thisPlayer][i] == silver || gs->discard[thisPlayer][i] == gold)
        {
            initialCounter++;
            // cardNumToName(gs->discard[thisPlayer][i], name);
            // printf("%-13s\n", name);
        }
        else
        {
            // cardNumToName(gs->discard[thisPlayer][i], name);
            // printf("%-13s\n", name);
        }
    }

    for (i = 0; i < postGs->discardCount[thisPlayer]; i++)
    {
        if (postGs->discard[thisPlayer][i] == copper || postGs->discard[thisPlayer][i] == silver || postGs->discard[thisPlayer][i] == gold)
        {
            finalCounter++;
        }
    }

    if (initialCounter == finalCounter || finalCounter == 0) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("discard result = %d, expected = %d or 0\n", finalCounter, initialCounter);

    // check that the card is in the played pile
    // number of this card before + 1
	printf("TEST 2: Player has adventurer card in playedCard pile\n");
    initialCounter = 0, finalCounter = 0;
    for (i = 0; i < gs->playedCardCount; i++)
    {
        if (gs->playedCards[i] == adventurer) { initialCounter++; };
    }
    for (i = 0; i < postGs->playedCardCount; i++)
    {
        if (postGs->playedCards[i] == adventurer) { finalCounter++; };
    }
    if (finalCounter == initialCounter + 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("played count = %d, expected = %d\n", finalCounter, initialCounter + 1);

    // check that the number of actions is 0
	printf("TEST 3: Player has no remaining actions\n");
	printf("numActions count = %d, expected = %d\n", postGs->numActions, gs->numActions-1);
    assert(postGs->numActions == gs->numActions-1);

	printf("TEST 4: No state changes for other players\n");
    // ensure hand, deck, discard counts remain the same for all other players
    for (i = 0; i < gs->numPlayers; i++)
    {
        if (i != whoseTurn(gs))
        {
            if (gs->deckCount[i] == postGs->deckCount[i]) { printf("Test Passed: "); }
            else { printf("Test Failed: "); }
            printf("deck count = %d, expected = %d\n", gs->deckCount[i], postGs->deckCount[i]);
            
            if (gs->handCount[i] == postGs->handCount[i]) { printf("Test Passed: "); }
            else { printf("Test Failed: "); }
            printf("hand count = %d, expected = %d\n", gs->handCount[i], postGs->handCount[i]);
            
            if (gs->discardCount[i] == postGs->discardCount[i]) { printf("Test Passed: "); }
            else { printf("Test Failed: "); }
            printf("discard count = %d, expected = %d\n", gs->discardCount[i], postGs->discardCount[i]);
        }
    }

    printf("TEST 5: No changes to Kingdom Supply Card Piles\n");
    int numKingdomCards = sizeof(k)/sizeof(k[0]);
    for (i = 0; i < numKingdomCards; i++)
    {
        if (supplyCount(k[i], gs) == supplyCount(k[i], postGs)) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("kingdom count = %d, expected = %d\n", supplyCount(k[i], gs), supplyCount(k[i], postGs));
    }

    printf("TEST 6: No Changes to Victory Supply Card Piles\n");
    int v[3] = {estate, duchy, province};
    for (i = 0; i < 3; i++)
    {
        if (supplyCount(v[i], gs) == supplyCount(v[i], postGs)) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("victory count = %d, expected = %d\n", supplyCount(v[i], gs), supplyCount(v[i], postGs));
    }

    printf("TEST 7: No Changes to Treasure Supply Card Piles\n");
    int t[3] = {copper, silver, gold};
    for (i = 0; i < 3; i++)
    {
        if (supplyCount(t[i], gs) == supplyCount(t[i], postGs)) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("treasure count = %d, expected = %d\n", supplyCount(t[i], gs), supplyCount(t[i], postGs));
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
        gs.hand[whoseTurn(&gs)][randomHandPos] = adventurer;

        // set gamestate such that card can be played
        /*
        gs.phase = 0;
        gs.numActions = 1;
        */
        // copy gamestate 
        memcpy(&postGS, &gs, sizeof(struct gameState));
        
        // playAdventurer
        int result = playCard(randomHandPos, 0, 0, 0, &postGS);

        printf("Play Result: %d\n", result);
        checkAdventurer(k, &gs, &postGS);
    }

    return 0;
}
