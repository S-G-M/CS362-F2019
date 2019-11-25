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
	int numTests = 100;

	srand(time(0));

	memset(&modifiedGame, 23, sizeof(struct gameState));
	memset(&referenceGame, 23, sizeof(struct gameState));


	for (int i = 0; i < numTests; i++)
	{
		// Randomize a game state
		int choice1 = rand() % 2;
		int choice2 = rand() % 2;
		int estateCheck = 0;
		int handPos = 0;
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

		// Give the player a baron card
		modifiedGame.hand[currentPlayer][0] = baron;

		// 12 estates for 3-4 players, 8 for 2
		if (modifiedGame.numPlayers == 2)
		{
			modifiedGame.supplyCount[estate] = 8;
		}
		else if (modifiedGame.numPlayers > 2)
		{
			modifiedGame.supplyCount[estate] = 12;
		}

		// Set reference game to be compared against later.
		memcpy(&referenceGame, &modifiedGame, sizeof(struct gameState));

		// Choice1 = 1 -> discard estate
		// If no estate in hand, gain one instead
		cardEffectBaron(choice1, &modifiedGame, currentPlayer);

		if (assertF(modifiedGame.numBuys, referenceGame.numBuys + 1) == -1)
		{
			printf("Error in increasing game buys.\n");
		}

		if (choice1 == 1 && estateCheck == 1)
		{
			// Has an estate, wants to discard and gain 4 coins
			if (assertF(modifiedGame.handCount[currentPlayer], referenceGame.handCount[currentPlayer] - 2) != 1)
			{
				printf("Error, cards not removed from hand.\n");
			}

			if (assertF(modifiedGame.coins, referenceGame.coins + 4) != 1)
			{
				printf("Error, number of coins not added correctly.\n");
			}

			// Discard baron + estate
			if (assertF(modifiedGame.discardCount[currentPlayer], referenceGame.discardCount[currentPlayer] + 2) != 1)
			{
				printf("Error, discard not incremented.\n");
			}
		}
		else if ((choice1 == 1 && estateCheck == 0) || choice1 == 0)
		{
			// Has a Baron, wants to discard, but doesnt have an estate
			if (assertF(modifiedGame.handCount[currentPlayer], referenceGame.handCount[currentPlayer]) != 1)
			{
				// Remove baron card, gain an estate
				printf("Error, card not removed from hand.\n");
			}

			if (assertF(modifiedGame.discardCount[currentPlayer], referenceGame.discardCount[currentPlayer] + 1) != 1)
			{
				printf("Error, discard not incremented.\n");
			}

			if (assertF(modifiedGame.supplyCount[estate], referenceGame.supplyCount[estate] - 1) != 1)
			{
				printf("Error, estate stack not decremented.\n");
			}
		}

		memset(&modifiedGame, 23, sizeof(struct gameState));
		memset(&referenceGame, 23, sizeof(struct gameState));
	}

}