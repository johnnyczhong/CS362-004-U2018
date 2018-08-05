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

#define TESTCARD "council room"

// because we're providing random tests for cards
//   we just need to randomize the inputs for the cards
//   if there are any to be had
// this means that we need to stabilize the gamestate
//   such that randomization is restricted to the action
//   of playing the card
// so the question becomes "what actually affects the card being played?"
// in adventurer's case, it's the number of treasure cards in the player's deck
// and the type of treasure cards in the player's deck

int checkCouncilRoom(int* k, struct gameState *gs, struct gameState *postGs)
{

    int i;
    int initialCounter, finalCounter;
    int thisPlayer = whoseTurn(gs);

    // test 2: deck decrease by 4
	printf("TEST 2: Player deck has decreased by 4\n");
    if (postGs->deckCount[thisPlayer] == gs->deckCount[thisPlayer] - 4) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("playCard result = %d, expected = %d\n", postGs->deckCount[thisPlayer], gs->deckCount[thisPlayer] - 1);

    // test 3: hand increased by 3
	printf("TEST 3: Player has 3 more cards in hand\n");
    if (postGs->handCount[thisPlayer] == gs->handCount[thisPlayer] + 3) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("handCount result = %d, expected = %d\n", postGs->handCount[thisPlayer], gs->handCount[thisPlayer] + 3);
    
    // test 4: check that the card is in the played pile
	printf("TEST 4: Player has council_room card in playedCard pile\n");
    initialCounter = 0, finalCounter = 0;
    for (i = 0; i < gs->playedCardCount; i++)
    {
        if (gs->playedCards[i] == council_room) { initialCounter++; };
    }
    for (i = 0; i < postGs->playedCardCount; i++)
    {
        if (postGs->playedCards[i] == council_room) { finalCounter++; };
    }
    if (finalCounter == initialCounter + 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("played count = %d, expected = %d\n", finalCounter, initialCounter + 1);

    // test 5: current player has more buys
	printf("TEST 5: Player has 1 more buy\n");
    if (postGs->numBuys == gs->numBuys + 1) { printf("Test Passed: "); }
    else { printf("Test Failed: "); }
	printf("numActions count = %d, expected = %d\n", postGs->numBuys, gs->numBuys + 1);

	printf("TEST 6: Test that other players draw 1 card, discard unaffected\n");
    // ensure hand, deck, discard counts remain the same for all other players
    for (i = 0; i < gs->numPlayers; i++)
    {
        if (i != whoseTurn(gs))
        {
            if (postGs->deckCount[i] == gs->deckCount[i] - 1) { printf("Test Passed: "); }
            else { printf("Test Failed: "); }
            printf("deck count = %d, expected = %d\n", postGs->deckCount[i], gs->deckCount[i] - 1);
            
            if (postGs->handCount[i] == gs->handCount[i] + 1) { printf("Test Passed: "); }
            else { printf("Test Failed: "); }
            printf("hand count = %d, expected = %d\n", postGs->handCount[i], gs->handCount[i] + 1);
            
            if (postGs->discardCount[i] == gs->discardCount[i]) { printf("Test Passed: "); }
            else { printf("Test Failed: "); }
            printf("discard count = %d, expected = %d\n", postGs->discardCount[i], gs->discardCount[i]);
        }
    }

    printf("TEST 7: No changes to Kingdom Supply Card Piles\n");
    int numKingdomCards = sizeof(k)/sizeof(k[0]);
    for (i = 0; i < numKingdomCards; i++)
    {
        if (supplyCount(k[i], postGs) == supplyCount(k[i], gs)) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("kingdom count = %d, expected = %d\n", supplyCount(k[i], postGs), supplyCount(k[i], gs));
    }

    printf("TEST 8: No Changes to Victory Supply Card Piles\n");
    int v[3] = {estate, duchy, province};
    for (i = 0; i < 3; i++)
    {
        if (supplyCount(v[i], postGs) == supplyCount(v[i], gs)) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("victory count = %d, expected = %d\n", supplyCount(v[i], postGs), supplyCount(v[i], gs));
    }

    printf("TEST 9: No Changes to Treasure Supply Card Piles\n");
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
        gs.hand[whoseTurn(&gs)][randomHandPos] = council_room;

        // set gamestate such that card can be played
        // copy gamestate 
        memcpy(&postGS, &gs, sizeof(struct gameState));
        
        // playCouncilRoom
        int result = playCard(randomHandPos, 0, 0, 0, &postGS);
        printf("TEST 1: Player has played the card successfully\n");
        if (result == 0) { printf("Test Passed: "); }
        else { printf("Test Failed: "); }
        printf("playCard result = %d, expected = %d\n", result, 0);

        printState(&gs);

        printf("Play Result: %d\n", result);
        checkCouncilRoom(k, &gs, &postGS);
    }

    return 0;
}
