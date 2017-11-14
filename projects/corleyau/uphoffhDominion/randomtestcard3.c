#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

void printErrorState(int seed, int player, int deckCount, int discardCount)
{
	printf("----------------- Failure Details: ----------------\n");
	printf("Seed: %d\nPlayer: %d\nDeck Count: %d\nDiscard Count: %d\n", seed, player, deckCount, discardCount);
}

int main()
{

	int n, p, deckCount, discardCount, handCount, seed, numPlayers=2, numErrors;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	srand(time(NULL));

	printf("----------------- Testing Card: steward ----------------\n");

	for (n = 0; n < 2000; n++)
	{

		seed = rand() % 10001; //generate a random number for the seed
		initializeGame(numPlayers, k, seed, &G);

		deckCount = rand() % (MAX_DECK + 1);
		discardCount = rand() % (MAX_DECK + 1);
		handCount = rand() % (MAX_HAND + 1); 
		p = rand() % 2;
		choice1 = (rand() % 3) + 1; //random number between 1 and 3
		choice2 = rand() % G.handCount[p]; //random card in player's hand
		choice3 = rand() % G.handCount[p];

		G.whoseTurn = p;
		G.deckCount[p] = deckCount;
		G.discardCount[p] = discardCount;
		G.handCount[p] = handCount;

		//copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

		//choice1 = 1: plus 2 cards, choice1 = 2: plus 2 coins, choice1 = 3: trash 2 cards
		if (choice1 == 1)
		{
			if ((G.handCount[p] + 2) != testG.handCount[p])
			{
				printf("Expected hand count to increase by 2\n");
				printErrorState(seed, p, deckCount, discardCount);
				printf("Before Hand Count: %d\nAfter Hand Count: %d\n\n", G.handCount[p], testG.handCount[p]);
			}
		}
		else if (choice2 == 2)
		{
			if ((G.coins + 2) != testG.coins)
			{
				printf("Expected coin count to increase by 2\n");
				printErrorState(seed, p, deckCount, discardCount);
				printf("Before Coin Count: %d\nAfter Coin Count: %d\n", G.coins, testG.coins);
			}
		}
		else
		{
			if ((G.handCount[p] - 2) != testG.handCount[p])
			{
				printf("Expected hand count to decrease by 2\n");
				printErrorState(seed, p, deckCount, discardCount);
				printf("Before Hand Count: %d\nAfter Hand Count: %d\n", G.handCount[p], testG.handCount[p]);
			}
		}

	}

	printf("Number of errors found: %d\nNumber of tests conducted: 2000\n", numErrors);

	printf("----------------- Testing Complete ----------------\n");

	return 0;
}