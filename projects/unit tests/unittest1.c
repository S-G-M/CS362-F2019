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
    int buys = 0;
    buys = state.numBuys;
 
    // Checks branch 2 of branch 1
    playCard_Baron(&state, currentPlayer);
    if (assertF(buys, state.numBuys) == 1)
    {
        printf("\nDecrementing buys failed, unit test 1 Baron\n")
        exit(1);
    }

    // Test last branch of the if else statement
    state.supplyCount[0] = 10;
    state.supplyCount[1] = 10;
    state.supplyCount[2] = 10;
    int estatesSupply = 0;
    estatesSupply = state.supplyCount[2];
    playCard_Baron(&state, currentPlayer);
    if (assertF(estatesSupply,state.supplyCount[2]) == 1)
    {
        printf("\nDecrementing estates failed, unit test 1 Baron\n")
        exit(1);
    }

    // Tests while branch of if else
    state.handCount[currentPlayer] = 5;
    estatesSupply = state.supplyCount[2];
    playCard_Baron(&state, currentPlayer);
    {
        printf("\nDecrementing estates in while loop failed, unit test 1 Baron\n")
        exit(1);
    }

}