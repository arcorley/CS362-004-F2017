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
	int card = 0, currentPlayer = 0, numCards, i;

	initializeGame(numPlayers, k, seed, &G);

	printf("\n-------------------- Testing handCard Function --------------------\n");

	// -------------------- TEST 1: Should return the correct value for each card in the player's hand --------------------
	printf("TEST 1: Returned value == game state value at all values of hand position\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = 0;
	numCards = G.deckCount[currentPlayer];//get the number of cards in the player's hand

	for (i = 0; i < numCards; i++) //run the tests
	{
		card = handCard(i, &testG);
		printf("Returned value = %d, expected = %d\n", card, G.hand[currentPlayer][i]);
		customAssert(card == G.hand[currentPlayer][i], "Failed test: Returned value not equal to game state value");
	}


	// -------------------- TEST 2: Game state should not change at all --------------------
	printf("\nTEST 2: Game state should not change at all\n");

	memcpy(&testG, &G, sizeof(struct gameState)); //copy the game state to a test case

	card = handCard(0, &testG); //run the function

	//check if the game state changed
	if (memcmp(&testG, &G, sizeof(struct gameState)) == 0)
		printf("Game states matched\n");
	else
		printf("Game states did not match\n");

	customAssert(memcmp(&testG, &G, sizeof(struct gameState)) == 0, "Failed test: An element of the game state changed");

	// -------------------- TEST 3: Returned value should match game state value after changing currentPlayer --------------------
	printf("\nTEST 3: Returned value should match game state value after changing currentPlayer\n");

	memcpy(&testG, &G, sizeof(struct gameState)); //copy the game state to a test case

	card = handCard(0, &testG); //run the function once
	currentPlayer = 1; //change the value of currentPlayer
	testG.whoseTurn = 1;

	numCards = G.deckCount[currentPlayer];//get the number of cards in the player's hand

	for (i = 0; i < numCards; i++) //run the tests
	{
		card = handCard(i, &testG);
		printf("Returned value = %d, expected = %d\n", card, G.hand[currentPlayer][i]);
		customAssert(card == G.hand[currentPlayer][i], "Failed test: Value didn't match after changing current player");
	}

	if (hasErrors == 0)
		printf("\n >>>>> SUCCESS: handCard testing complete <<<<<\n\n");
	else
		printf("\n >>>>> FAILURE: at least one test failed <<<<<\n\n");

	return 0;
}