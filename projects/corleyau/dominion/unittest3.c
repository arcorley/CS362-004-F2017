#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int hasErrors = 0;

void customAssert(int expression, char* failMsg)
{
	if (expression == 0)
	{
		printf("%s\n", failMsg);
		hasErrors++;
	}
	else
		printf("Passed test\n");
}

int main()
{
	int numPlayers = 2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int seed = 10000;
	struct gameState G, testG;
	int currentPlayer = 0, numDiffs = 0, i, status;

	initializeGame(numPlayers, k, seed, &G);

	printf("\n-------------------- Testing shuffle Function --------------------\n");

	// -------------------- TEST 1: Player's deck should change order --------------------
	printf("TEST 1: Player's deck should change order\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	status = shuffle(currentPlayer, &testG);

	for (i = 0; i < testG.deckCount[currentPlayer]; i++)
	{
		if (testG.deck[currentPlayer][i] == G.deck[currentPlayer][i])
		{
			printf("Card in position %d: %d, Value Pre Shuffle: %d. No difference.\n", i, testG.deck[currentPlayer][i], G.deck[currentPlayer][i]);
		}
		else
		{
			printf("Card in position %d: %d, Value Pre Shuffle: %d. Difference found.\n", i, testG.deck[currentPlayer][i], G.deck[currentPlayer][i]);
			numDiffs++;
		}
	}

	customAssert(numDiffs > 0, "Failed test: The player's deck didn't change order");


	// -------------------- TEST 2: Return -1 if there are no cards in deck --------------------
	printf("\nTEST 2: Return -1 if there are no cards in deck\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	testG.deckCount[currentPlayer] = 0; //set the player's deck count to 0

	status = shuffle(currentPlayer, &testG); //run the function

	printf("Returned: %d, Expected: -1\n", status);
	customAssert(status == -1, "Failed test: -1 wasn't returned");


	// -------------------- TEST 3: Player's deck count should remain unchanged --------------------
	printf("\nTEST 3: Player's deck count should remain unchanged\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	status = shuffle(currentPlayer, &testG); //call the function

	printf("New deck count: %d, Expected: %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer]);
	customAssert(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer], "Failed test: Player's deck was changed");	


	if (hasErrors == 0)
		printf("\n >>>>> SUCCESS: shuffle testing complete <<<<<\n\n");
	else
		printf("\n >>>>> FAILURE: at least one test failed <<<<<\n\n");	

	return 0;
}