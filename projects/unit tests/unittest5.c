
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
    struct gameState state;

    G.coins = 0;

    printf("\nUnit Test 5: Mine Check\n");

    int handPos = 0;
    int currentPlayer = 0;
    int choice1 = 0;
    int choice2 = gold;

    // Testing cards that are greater than +3 value apart
    state.hand[currentPlayer][choice1] = curse;
    state.hand[currentPlayer][choice2] = gold;

    // This should cause a failure at both the initial card cost check, returning -1
    // And a failure later on where the user picks a card that is at most +3 more valuable
    int test;
    test = playCard_Mine(&state, handPos, currentPlayer, choice1, choice2);
    if(assertF(test, 1))
    {
        printf("Failed Unit Test 5 Mine");
        exit(1);
    }
    else
    {
        printf("Passed Unit Test 5 Mine");
    }

    // Test second if statement in the mine function
    choice2 = -1;
    test = playCard_Mine(&state, handPos, currentPlayer, choice1, choice2);
    if(assertF(assertF(test, 1))
    {
        printf("Failed Testing At Choice2 Value Test");
        exit(1);
    }
    else
    {
        printf("Passed Testing At Choice2 Value Test");
    }
    
}