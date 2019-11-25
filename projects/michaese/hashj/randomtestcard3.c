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
			modifiedGame.deckCount[j] = rand() % 11;

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
		
		// Give the player a tribute card
		modifiedGame.hand[currentPlayer][0] = tribute;

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

		// Figure out who the next player is
		int nextPlayer = 0;
		if (currentPlayer == modifiedGame.numPlayers - 1)
		{
			// Set next player
			nextPlayer = 0;
		}
		else
		{
			nextPlayer++;
		}

		int tribute1 = rand() % (26 - 1 + 1) - 1;
		int tribute2 = rand() % (26 - 1 + 1) - 1;
		int tributeRevealedCards[2] = { tribute1, tribute2 };
		cardEffectTribute(&modifiedGame, handPos, currentPlayer, nextPlayer, tributeRevealedCards);
		
		if ((referenceGame.discardCount[nextPlayer] + referenceGame.deckCount[nextPlayer]) <= 1)
		{
			if ((referenceGame.deckCount[nextPlayer] > 0) && (referenceGame.deckCount[nextPlayer] - 1 == modifiedGame.deckCount[nextPlayer]))
			{
				printf("Error decrementing deck count.\n");
			}
			else if ((referenceGame.deckCount[nextPlayer] > 0) && referenceGame.discardCount[nextPlayer] > 0)
			{
				printf("Error decrementing discard count.\n");
			}
		}
		else
		{
			if (referenceGame.deckCount[nextPlayer] == 0)
			{
				if (modifiedGame.deckCount[nextPlayer] != referenceGame.deckCount[nextPlayer] + 1)
				{
					printf("Error incrementing deck count.\n");
				}
			}

			if (modifiedGame.deckCount[nextPlayer] != referenceGame.deckCount[nextPlayer] - 2)
			{
				printf("Error decrementing deck.\n");
			}


			int nextCard = modifiedGame.deck[nextPlayer][modifiedGame.deckCount[nextPlayer] - 1];
			if ((nextCard == estate) || (nextCard == duchy) || (nextCard == province))
			{
				if (modifiedGame.handCount[currentPlayer] != referenceGame.handCount[currentPlayer] + 2)
				{
					printf("Error with adding 2 cards if victory card.\n");
				}
			}
			else if ((nextCard == copper) || (nextCard == silver) || (nextCard == gold))
			{
				if (modifiedGame.coins != referenceGame.coins + 2)
				{
					printf("Error adding coins.\n");
				}
			}
			else
			{
				if (modifiedGame.numActions != referenceGame.numActions + 2)
				{
					printf("Error adding actions.\n");
				}
			}

			nextCard = modifiedGame.deck[nextPlayer][modifiedGame.deckCount[nextPlayer] - 2];
			if ((nextCard == estate) || (nextCard == duchy) || (nextCard == province))
			{
				if (modifiedGame.handCount[currentPlayer] != referenceGame.handCount[currentPlayer] + 2)
				{
					printf("Error with adding 2 cards if victory card.\n");
				}
			}
			else if ((nextCard == copper) || (nextCard == silver) || (nextCard == gold))
			{
				if (modifiedGame.coins != referenceGame.coins + 2)
				{
					printf("Error adding coins.\n");
				}
			}
			else
			{
				if (modifiedGame.numActions != referenceGame.numActions + 2)
				{
					printf("Error adding actions.\n");
				}
			}
		}
		
		memset(&modifiedGame, 23, sizeof(struct gameState));
		memset(&referenceGame, 23, sizeof(struct gameState));
	}

}