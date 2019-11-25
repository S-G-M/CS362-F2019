#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"

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

int main()
{
	struct gameState modifiedGame;
	struct gameState referenceGame;
	int numTests = 1000;

	srand(time(0));

	memset(&modifiedGame, 23, sizeof(struct gameState));
	memset(&referenceGame, 23, sizeof(struct gameState));


	for (int i = 0; i < numTests; i++)
	{
		// Randomize a game state
		int choice1 = rand() % 2;
		int choice2 = rand() % 2;
		int estateCheck = 0;
		int handPos = 1;
		modifiedGame.numPlayers = rand() % (MAX_PLAYERS + 1 - 2) + 2;
		int currentPlayer = rand() % modifiedGame.numPlayers;
		modifiedGame.whoseTurn = currentPlayer;
		modifiedGame.coins = rand() % 100;
		modifiedGame.numBuys = 1;
		
		// Build a random game state
		for (int j = 0; j < modifiedGame.numPlayers; j++)
		{
			modifiedGame.handCount[j] = rand() % 11;
			modifiedGame.discardCount[j] = rand() % 11;
			modifiedGame.deckCount[j] = rand() % 100;

			for (int c = 0; c < modifiedGame.handCount[j]; c++)
			{
				modifiedGame.hand[j][c] = rand() % treasure_map + 1;

				// Store if the user gets an estate or not
				if (j = currentPlayer && modifiedGame.hand[j][c] == estate)
				{
					estateCheck = 1;
				}
			}

			for (int de = 0; de < modifiedGame.deckCount[j]; de++)
			{
				modifiedGame.deck[j][de] = rand() % treasure_map + 1;
			}

			for (int di = 0; di < modifiedGame.discardCount[j]; di++)
			{
				modifiedGame.discard[j][di] = rand() % treasure_map + 1;
			}
		}
		
		// Give the player a minion card
		modifiedGame.hand[currentPlayer][1] = minion;

		// 12 estates for 3-4 players, 8 for 2
		if (modifiedGame.numPlayers == 2)
		{
			modifiedGame.supplyCount[estate] = 8;
		}
		else if (modifiedGame.numPlayers > 2)
		{
			modifiedGame.supplyCount[estate] = 12;
		}

		modifiedGame.playedCardCount = 0;

		// Set reference game to be compared against later.
		memcpy(&referenceGame, &modifiedGame, sizeof(struct gameState));
		
		// Choice1 = 1 -> discard estate
		// If no estate in hand, gain one instead
		cardEffectMinion(choice1, choice2, &modifiedGame, handPos, currentPlayer);
		
		if (assertF(modifiedGame.numActions, referenceGame.numActions + 1) != 1)
		{
			printf("Error adding actions.\n");
		}

		if (assertF(modifiedGame.discardCount[currentPlayer], referenceGame.discardCount[currentPlayer] + 1) != 1)
		{
			printf("Error incrementing discard count.\n");
		}

		if (choice1 == 1)
		{
			if (assertF(modifiedGame.coins, referenceGame.coins + 2) != 1)
			{
				printf("Error adding 2 coins.\n");
			}

			if (assertF(modifiedGame.handCount[currentPlayer], referenceGame.handCount[currentPlayer] - 1) != 1)
			{
				printf("Error decrementing hand count.\n");
			}
		}
		else if (choice1 == 0 && choice2 == 1)
		{
			int handCheck = 1;
			for (int k = 0; k < modifiedGame.handCount[currentPlayer]; k++)
			{
				if (modifiedGame.hand[currentPlayer][k] != referenceGame.hand[currentPlayer][k])
				{
					handCheck == 0;
				}
			}

			if (handCheck)
			{
				printf("Error discarding hand.\n");
			}

			if (assertF(modifiedGame.handCount[currentPlayer], 4) != 1)
			{
				printf("Error assigning player 4 new cards.\n");
			}

			for (int o = 0; o < modifiedGame.numPlayers; o++)
			{
				if (referenceGame.handCount[o] >= 5)
				{
					if (modifiedGame.handCount[o] != 4)
					{
						printf("Error assigining other players 4 new cards.\n");
					}
				}
			}
		}
		
		memset(&modifiedGame, 23, sizeof(struct gameState));
		memset(&referenceGame, 23, sizeof(struct gameState));
	}

}