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


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}

/*
// produce a valid random state
struct gameState randomizeGameState(struct gameState *gs)
{
    // randomize number of players
    int i, j;
    int numPlayers = (rand() % (MAX_PLAYERS - 2)) + 2;

    gs->numPlayers = numPlayers;

    // for each player
    for (i = 0; i < numPlayers; i++)
    {
        // randomize size of decks
        gs->deckCount[i] = floor(Random() * MAX_DECK);
        // gs->deckCount[i] = floor(Random() * 20);
        // randomize cards in deck
        for (j = 0; j < gs->deckCount[i]; j++)
        {
            gs->deck[i][j] = floor(Random() * 26);
        }

        // randomize size of discard pile
        gs->discardCount[i] = floor(Random() * 20);
        // randomize cards in discard
        for (j = 0; j < gs->deckCount[i]; j++)
        {
            gs->discard[i][j] = floor(Random() * 26);
        }

        // randomize size of hand
        gs->handCount[i] = floor(Random() * MAX_HAND);
        // gs->handCount[i] = floor(Random() * 20);
        // randomize cards in hand
        for (j = 0; j < gs->handCount[i]; j++)
        {
            // gs->hand[i][j] = floor(Random() * 26);
            gs->hand[i][j] = floor(rand() % 26);
        }

    }

    gs->whoseTurn = rand() % numPlayers;
    gs->playedCardCount = 20;
    
    for (i = 0; i < gs->playedCardCount; i++)
    {
        gs->playedCards[i] = floor(rand() % 26);
    }
    printPlayed(whoseTurn(gs), gs);

    printState(gs);
    
    struct gameState resultGS;
	memcpy(gs, &resultGS, sizeof(struct gameState));

    return resultGS;

}
*/

int main() 
{
    int i, j, numPlayers;
    srand(time(NULL));
    struct gameState gs, postGS;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // set up game with random number of players between 2 and MAX
    //int numPlayers = (rand() % (MAX_PLAYERS - 2)) + 2;

    for (i = 0; i < 20; i++)
    {

        numPlayers = (rand() % (MAX_PLAYERS - 2)) + 2;

        gs.numPlayers = numPlayers;

        // for each player
        for (i = 0; i < numPlayers; i++)
        {
            // randomize size of decks
            gs.deckCount[i] = floor(Random() * MAX_DECK);
            // gs->deckCount[i] = floor(Random() * 20);
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
        
        // randomize played cards
        for (i = 0; i < gs.playedCardCount; i++)
        {
            gs.playedCards[i] = floor(rand() % 26);
        }

        int thisPlayer = whoseTurn(gs);
        int randomHandPos = rand() % gs.handCount[thisPlayer];
        gs.hand[whoseTurn(gs)][randomHandPos] = adventurer;

        // set gamestate such that card can be played
        gs.phase = 0;
        gs.numActions = 1;

        // copy gamestate 
        memcpy(&gs, &postGS, sizeof(struct gameState));
        
        // printPlayed(thisPlayer, gs);

        // playAdventurer
        playCard(randomHandPos, 0, 0, 0, &postGS);
        
        checkAdventurer(k, &gs, &postGS);
    }

    return 0;
}
