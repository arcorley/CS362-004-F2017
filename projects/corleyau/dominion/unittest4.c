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
	int i, numCards, gameOver;

	initializeGame(numPlayers, k, seed, &G);

	printf("\n-------------------- Testing isGameOver Function --------------------\n");

	// -------------------- TEST 1: province supply == 0 --------------------
	printf("TEST 1: province supply == 0\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	numCards = sizeof(testG.supplyCount)/sizeof(testG.supplyCount[0]);

	//set card supplies. province = 0, everything else = 5
	for (i = 0; i < numCards; i++)
	{
		if (i == province)
			testG.supplyCount[i] = 0; //set province count to 0
		else
			testG.supplyCount[i] = 5; //set other cards to 5
	}

	gameOver = isGameOver(&testG);

	printf("Game over: %d, Expected: 1\n", gameOver);
	customAssert(gameOver == 1, "Failed test: gameOver not 1");


	// -------------------- TEST 2: all supplies > 0 --------------------
	printf("\nTEST 2: all supplies > 0\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	numCards = sizeof(testG.supplyCount)/sizeof(testG.supplyCount[0]);

	//set card supplies. all cards > 0
	for (i = 0; i < numCards; i++)
	{
		testG.supplyCount[i] = 5; //set all supplies to > 0
	}

	gameOver = isGameOver(&testG);

	printf("Game over: %d, Expected: 0\n", gameOver);
	customAssert(gameOver == 0, "Failed test: gameOver not 0");


	// -------------------- TEST 3: first 3 supply cards = 0, province > 0 --------------------
	printf("\nTEST 3: first 3 supply cards = 0, province > 0\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	numCards = sizeof(testG.supplyCount)/sizeof(testG.supplyCount[0]);

	//set card supplies. first 3 cards = 0, all others > 0
	for (i = 0; i < numCards; i++)
	{
		if (i < 3)
			testG.supplyCount[i] = 0;
		else
			testG.supplyCount[i] = 5;
	}

	gameOver = isGameOver(&testG);

	printf("Game over: %d, Expected: 1\n", gameOver);
	customAssert(gameOver == 1, "Failed test: gameOver not 1");


	// -------------------- TEST 4: last 3 supply cards = 0, province > 0 --------------------
	printf("\nTEST 4: last 3 supply cards = 0, province > 0\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	numCards = sizeof(testG.supplyCount)/sizeof(testG.supplyCount[0]);

	//set card supplies. last 3 cards = 0, all others > 0
	for (i = 0; i < numCards; i++)
	{
		if (i > (numCards - 4))
			testG.supplyCount[i] = 0;
		else
			testG.supplyCount[i] = 5;
	}

	gameOver = isGameOver(&testG);

	printf("Game over: %d, Expected: 1\n", gameOver);
	customAssert(gameOver == 1, "Failed test: gameOver not 1");

	if (hasErrors == 0)
		printf("\n >>>>> SUCCESS: isGameOver testing complete <<<<<\n\n");
	else
		printf("\n >>>>> FAILURE: at least one test failed <<<<<\n\n");	

	return 0;
}