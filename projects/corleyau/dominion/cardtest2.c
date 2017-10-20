#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

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

int getNumTCards(int player, struct gameState *game)
{
	int x, numCards = 0, card;

	for (x = 0; x < game->handCount[player]; x++)
	{
		card = game->hand[player][x];

		if (card == copper || card == silver || card == gold)
			numCards++;
	}

	return numCards;
}

int main() {
    int newTreasureCards = 0, origTCardCount, newTCardCount;

    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: current player receives 2 treasure cards --------------
	printf("TEST 1: current player receives 2 treasure cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	newTreasureCards = 2; //2 new cards added

	//get number of treasure cards in each hand
	origTCardCount = getNumTCards(thisPlayer, &G);
	newTCardCount = getNumTCards(thisPlayer, &testG);

	printf("treasure card count = %d, expected = %d\n", newTCardCount, origTCardCount + newTreasureCards);
	customAssert(origTCardCount + newTreasureCards == newTCardCount, "The number of treasure cards didn't grow by 2");


	// ----------- TEST 2: non-treasure cards drawn are discarded (hand only grows by 2) --------------
	printf("\nTEST 2: non-treasure cards drawn are discarded (hand only grows by 2)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	newTreasureCards = 2;

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newTreasureCards);
	customAssert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newTreasureCards, "Failed test: hand count didn't grow by 2");

	// ----------- TEST 3: no state change for other players --------------

	printf("\nTEST 3: no state change for other players\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	//ensure the other player's hand state stayed the same
	printf("other player hand count =  %d, expected = %d\n", testG.handCount[1], G.handCount[1]);
	customAssert(testG.handCount[1] == G.handCount[1], "Failed test: other player's hand count changed");

	//ensure the other player's deck state stayed the same
	printf("other player deck count = %d, expected = %d\n", testG.deckCount[1], G.deckCount[1]);
	customAssert(testG.deckCount[1] == G.deckCount[1], "Failed test: other player's deck count changed");


	// ----------- TEST 4: no state change for victory card pile or kingdom card pile --------------

	printf("\nTEST 4: no state change for victory card pile or kingdom card pile\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	//ensure the victory card pile state stayed the same
	printf("Beginning victory card test:\n");
	printf("estate card count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
	customAssert(testG.supplyCount[estate] == G.supplyCount[estate], "Failed test: estate supply counts don't match");

	printf("duchy card count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
	customAssert(testG.supplyCount[duchy] == G.supplyCount[duchy], "Failed test: duchy supply counts don't match");

	printf("province card count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
	customAssert(testG.supplyCount[province] == G.supplyCount[province], "Failed test: province supply counts don't match");

	//ensure the kingdom card pile state stayed the same
	printf("\nBeginning kingdom card count test:\n");
	for (i = 0; i < 10; i++)
	{
		printf("kingdom card %d count = %d, expected = %d\n", i, testG.supplyCount[k[i]], G.supplyCount[k[i]]);
		customAssert(testG.supplyCount[k[i]] == G.supplyCount[k[i]], "Failed test: kingdom card counts did not match");
	}

	if (hasErrors == 0)
		printf("\n >>>>> SUCCESS: %s testing complete <<<<<\n\n", TESTCARD);
	else
		printf("\n >>>>> FAILURE: at least one test failed <<<<<\n\n");


	return 0;
}


