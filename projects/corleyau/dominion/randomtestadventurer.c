#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

void printErrorState(int seed, int player, int expH, int actH, int deckCount, int discardCount)
{
	printf("----------------- Failure Details: ----------------\n");
	printf("Seed: %d\nPlayer: %d\nBefore Hand Count: %d\nAfter Hand Count: %d\nDeck Count: %d\nDiscard Count: %d\n\n", seed, player, expH, actH, deckCount, discardCount);
}

int main()
{

	int n, p, deckCount, discardCount, handCount, seed, numPlayers=2, numErrors;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	srand(time(NULL));

	printf("----------------- Testing Card: adventurer ----------------\n");

	for (n = 0; n < 2000; n++)
	{

		seed = rand() % 10001; //generate a random number for the seed
		initializeGame(numPlayers, k, seed, &G);

		deckCount = rand() % (MAX_DECK + 1);
		discardCount = rand() % (MAX_DECK + 1);
		handCount = rand() % (MAX_HAND + 1);

		p = rand() % 2;
		G.whoseTurn = p;
		G.deckCount[p] = deckCount;
		G.discardCount[p] = discardCount;
		G.handCount[p] = handCount;

		//copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

		if ((G.handCount[p] + 2) != testG.handCount[p])
		{
			printErrorState(seed, p, G.handCount[p], testG.handCount[p], deckCount, discardCount);
			numErrors++;
		}

	}

	printf("Number of errors found: %d\nNumber of tests conducted: 2000\n", numErrors);

	printf("----------------- Testing Complete ----------------\n");

	return 0;
}