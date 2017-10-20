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
	int seed = 1000;
	struct gameState G, testG;
	int testWhoseTurn;

	initializeGame(numPlayers, k, seed, &G);

	printf("\n-------------------- Testing whoseTurn Function --------------------\n");

	// -------------------- TEST 1: Returned value should match the whoseTurn value stored in the game state --------------------
	printf("TEST 1: Returned value == game state value\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	testWhoseTurn = whoseTurn(&testG);
	printf("Returned value = %d, expected = %d\n", testWhoseTurn, G.whoseTurn);
	customAssert(testWhoseTurn == testG.whoseTurn, "Failed test: whoseTurn did not match original game state");


	// -------------------- TEST 2: Game state should not change at all --------------------
	printf("\nTEST 2: Game state should not change at all\n");

	memcpy(&testG, &G, sizeof(struct gameState)); //copy the game state to a test case

	testWhoseTurn = whoseTurn(&testG); //call the function

	//check if the game state changed
	if (memcmp(&testG, &G, sizeof(struct gameState)) == 0)
		printf("Game states matched\n");
	else
		printf("Game states did not match\n");

	customAssert(memcmp(&testG, &G, sizeof(struct gameState)) == 0, "Failed test: an element of the game state changed");

	// -------------------- TEST 3: Returned value should match game state value after changing whoseTurn --------------------
	printf("\nTEST 3: Returned value should match game state value after changing whoseTurn\n");

	memcpy(&testG, &G, sizeof(struct gameState)); //copy the game state to a test case

	testWhoseTurn = whoseTurn(&testG); //run the function once
	testG.whoseTurn = 1; //change the value of whoseTurn
	testWhoseTurn = whoseTurn(&testG); //call the function again

	//check if results are correct
	printf("Returned value %d, expected = 1\n", testWhoseTurn);
	customAssert(testWhoseTurn == 1, "Failed test: whoseTurn did not match after changing player");

	if (hasErrors == 0)
		printf("\n >>>>> SUCCESS: whoseTurn testing complete <<<<<\n\n");
	else
		printf("\n >>>>> FAILURE: at least one test failed <<<<<\n\n");

	return 0;
}