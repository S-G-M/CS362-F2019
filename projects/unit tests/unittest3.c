#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int assertF(int val1, int val2)
{
    if (val1 == val2)
    {
        return 1;
    }
    else
    {
        return -1;
    }  
}

void main(int argc, char** argv)
{
    int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    struct gameState state;

    G.coins = 0;

    printf("\nUnit Test 3: Ambassador Check\n");

    int handPos = 0;
    int currentPlayer = 0;
    int choice1 = 1;
    int choice2 = 0;
    int actions = 0;
    actions = state.numActions;
 

    // Check first if statement branch
    choice2 = 5;
    if(playCard_Ambassador(&state, handPos, currentPlayer, choice1, choice2) == -1)
    {
        printf("\nChoice2 out of bound.\n");
        exit(1);
    }

    // Check second if statement branch
    choice1 = state.handPos;
    choice2 = 1;
    if(playCard_Ambassador(&state, handPos, currentPlayer, choice1, choice2) == -1)
    {
        printf("\nChoice1 out of bound.\n");
        exit(1);
    }

    // Verify supply increase
    int supply;
    supply = state->supplyCount[state->hand[currentPlayer][choice1]];
    playCard_Ambassador(&state, handPos, currentPlayer, choice1, choice2);
    if (state->supplyCount[state->hand[currentPlayer][choice1]] <= supply)
    {
        printf("\nSupply recording error.\n");
        exit(1);
    }

    // Check if discard works properly.
    int discardedCard;
    discardedCard = state.hand[currentPlayer][choice1];
    playCard_Ambassador(&state, handPos, currentPlayer, choice1, choice2);
    if (state.hand[currentPlayer][choice1] == discardedCard)
    {
        printf("\nDiscard error.\n");
        exit(1);
    }
}