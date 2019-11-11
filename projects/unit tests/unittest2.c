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

    printf("\nUnit Test 1: Mine Check\n");

    int handPos = 0;
    int currentPlayer = 0;
    int choice1 = 1;
    int choice2 = 0;
    int actions = state.numActions;
 

    // Initial function call
    // Choice1 set to 1
    // Covers first branch of if statement
    int coins = G.coins;
    playCard_Minion(&state, handPos, currentPlayer, choice1, choice2);
    if (G.coins != coins + 2 && choice == 1)
    {
        printf("Unit Test 2 Failed");
        exit(1);
    }

    // Make sure the actions part works
    if (state.numActions != actions + 1)
    {
        printf("Actions not recorded properly, test 2 failed");
        exit(1);
    }
    
    choice1 = 0;
    choice2 = 1;
    int discardedCount = state.discardCount[currentPlayer];
    playCard_Minion(&state, handPos, currentPlayer, choice1, choice2);
    if (discardedCount <= state.discardCount[currentPlayer])
    {
        printf("Discard didnt function properly for main player.");
        exit(1);
    }

    // Check if the discards worked for both players in function
    int otherplayerDiscard = state.discardCount[currentPlayer + 1];
    if (otherplayerDiscard <= state.discardCount[currentPlayer + 1])
    {
        printf("Discard didnt function properly for other player.");
        exit(1);
    }
}