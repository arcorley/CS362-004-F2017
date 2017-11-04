#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

void printErrorState(int seed, int player, int expH, int actH, int deckCount, int handCount)
{
	printf("----------------- Failure Details: ----------------\n");
	printf("Seed: %d\nPlayer: %d\nBefore Discard Count: %d\nAfter Discard Count: %d\nDeck Count: %d\nHand Count: %d\n\n", seed, player, expH, actH, deckCount, handCount);
}

int main()
{

	int n, p, deckCount, discardCount, handCount, result, seed, numPlayers=2, numErrors;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	srand(time(NULL));

	printf("----------------- Testing Card: feast ----------------\n");

	for (n = 0; n < 2000; n++)
	{

		seed = rand() % 10001; //generate a random number for the seed
		initializeGame(numPlayers, k, seed, &G);

		deckCount = rand() % (MAX_DECK + 1);
		discardCount = rand() % (MAX_DECK + 1);
		handCount = rand() % (MAX_HAND + 1);
		choice1 = rand() % 27;
		p = rand() % 2;

		G.whoseTurn = p;
		G.deckCount[p] = deckCount;
		G.discardCount[p] = discardCount;
		G.handCount[p] = handCount;

		//copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		result = cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);

		//if result is 0, discard count should increase by 1, otherwise it shouldn't grow

		if (result == 0)
		{
			if ((G.discardCount[p] + 1) != testG.discardCount[p])
			{
				printf("Expected discard count to grow by 1");
				printErrorState(seed, p, G.discardCount[p], testG.discardCount[p], deckCount, handCount);
				numErrors++;
			}
		}
		else
		{
			if (G.discardCount[p] != testG.discardCount[p])
			{
				printf("Expected discard count to stay the same");
				printErrorState(seed, p, G.discardCount[p], testG.discardCount[p], deckCount, handCount);
				numErrors++;				
			}
		}

	}

	printf("Number of errors found: %d\nNumber of tests conducted: 2000\n", numErrors);

	printf("----------------- Testing Complete ----------------\n");

	return 0;
}