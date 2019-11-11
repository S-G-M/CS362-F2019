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
    int nextPlayer= currentPlayer + 1;
    int choice1 = 1;
    int choice2 = 0;
    int actions = 0;
    actions = state.numActions;
 
    // This would catch the bug I introduced changing the deckCount decrement from nextPlayer
    // to currentPlayer
    // Checks branch 2 of the if else statement
    int deckCounter;
    deckCounter = state.deckCount[currentPlayer];
    playCard_Tribute(&state, nextPlayer, currentPlayer);
    if (assertF(deckCounter, state.deckCount[currentPlayer]))
    {
        printf("\nDecrementing failed, unit test 4 Ambassador\n")
        exit(1);
    }

    // Test branch 1 of the first if statement
    // Make sure the deckCount gets decremented properly in this branch
    int deckCounter;
    deckCounter = state.deckCount[nextPlayer];
    state.deckCount[nextPlayer] = 1;
    state.discardCount[nextPlayer] = 0;
    playCard_Tribute(&state, nextPlayer, currentPlayer);
    if(assertF(deckCounter, state.deckCount[nextPlayer]) == -1)
    {
        printf("\nTest Pass, Decrement Successful\n");
    }
    else
    {
        printf("\nDecrementing failed, unit test 4 Ambassador\n");
        exit(1);
    }
    

    // Test branch 3 of branch 1 of the first if statement
    // Make sure the deckCount gets decremented properly in this branch
    int deckCounter;
    deckCounter = state.deckCount[nextPlayer];
    state.deckCount[nextPlayer] = 0;
    state.discardCount[nextPlayer] = 0;
    playCard_Tribute(&state, nextPlayer, currentPlayer);
    if(assertF(deckCounter, state.deckCount[nextPlayer]) == -1)
    {
        printf("\nTest Pass, Decrement Successful\n");
    }
    else
    {
        printf("\nDecrementing failed, unit test 4 Ambassador\n");
        exit(1);
    }
    

    // Test branch 2 of the first if statement, else part
    // Make sure the discard gets decremented properly in this branch
    int discardCounter;
    discardCounter = state.discardCount[nextPlayer];
    state.deckCount[nextPlayer] = 0;
    state.discardCount[nextPlayer] = 3;
    playCard_Tribute(&state, nextPlayer, currentPlayer);
    if(assertF(deckCounter, state.deckCount[nextPlayer]) == -1)
    {
        printf("\nTest Pass, Decrement Successful\n");
    }
    else
    {
        printf("\nDecrementing failed, unit test 4 Ambassador\n");
        exit(1);
    }
}