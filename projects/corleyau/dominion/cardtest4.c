#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "feast"

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

int get5ValueCards(int player, struct gameState *game)
{
	int x, cardVal, total = 0;

	for (x = 0; x < game->discardCount[player]; x++)
	{
		cardVal = getCost(game->discard[player][x]);
		if (cardVal == 5)
			total++;
	}

	return total;
}

int getNumCards(int player, struct gameState *game, int card)
{
	int x, num = 0;

	for (x = 0; x < game->handCount[player]; x++)
	{
		if (game->hand[player][x] == card)
			num++;
	}

	for (x = 0; x < game->deckCount[player]; x++)
	{
		if (game->deck[player][x] == card)
			num++;
	}

	for (x = 0; x < game->discardCount[player]; x++)
	{
		if (game->discard[player][x] == card)
			num++;
	}

	return num;
}

int getGT5ValCards(int player, struct gameState *game)
{
	int x, num = 0, cardVal = 0;

	for (x = 0; x < game->handCount[player]; x++)
	{
		cardVal = getCost(game->hand[player][x]);
		if (cardVal > 5)
			num++;
	}

	for (x = 0; x < game->deckCount[player]; x++)
	{
		cardVal = getCost(game->deck[player][x]);
		if (cardVal > 5)
			num++;
	}

	for (x = 0; x < game->discardCount[player]; x++)
	{
		cardVal = getCost(game->discard[player][x]);
		if (cardVal > 5)
			num++;
	}

	return num;
}

int main() {
    int newCards = 0, discarded = 0;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, newVal5, val5, numFeastCards, newNumFeastCards;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: current player receives a 5 value card --------------
	printf("TEST 1: current player receives a 5 value card\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = duchy;
	cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 1; //1 new card added

	val5 = get5ValueCards(thisPlayer, &G);
	newVal5 = get5ValueCards(thisPlayer, &testG);

	printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + newCards);
	customAssert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + newCards - discarded, "Failed test: discard pile didn't grow by 1");

	printf("discard value 5 cards = %d, expected = %d\n", newVal5, val5 + 1);
	customAssert(newVal5 == (val5 + 1), "Failed test: discard pile didn't grow by one 5 value card");


	// ----------- TEST 2: feast card is trashed after use --------------
	printf("\nTEST 2: feast card is trashed after use\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = duchy;

	//add a feast card to the player's hand
	testG.hand[thisPlayer][testG.handCount[thisPlayer]] = feast;
	testG.handCount[thisPlayer]++;

	//get the number of feast cards before use
	numFeastCards = getNumCards(thisPlayer, &testG, feast);

	cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);

	//get the new number of feast cards
	newNumFeastCards = getNumCards(thisPlayer, &testG, feast);

	printf("number of feast cards = %d, expected = %d\n", newNumFeastCards, numFeastCards - 1);
	customAssert(newNumFeastCards == numFeastCards - 1, "Failed test: number of feast cards didn't decrease by 1");


	// ----------- TEST 3: cannot buy a >5 value card --------------
	printf("\nTEST 3: cannot buy a >5 value card\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	int gt5ValCards, newGT5ValCards;

	//get inital number of 5 value cards
	gt5ValCards = getGT5ValCards(thisPlayer, &testG);

	choice1 = province; //attempting to buy a card that's too expensive
	cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);

	//get new number of 5 value cards
	newGT5ValCards = getGT5ValCards(thisPlayer, &testG);

	printf("num >5 value cards = %d, expected = %d\n", newGT5ValCards, gt5ValCards);
	customAssert(newGT5ValCards == gt5ValCards, "Failed test: number of >5 value cards didn't remain the same");	


	// ----------- TEST 4: cannot buy a card that has 0 supply --------------

	printf("\nTEST 4: cannot buy a card that has 0 supply\n");

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//set supply of duchy to 0
	testG.supplyCount[duchy] = 0;

	choice1 = duchy;
	cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);

	//check numbers of duchy cards
	int numDuchy, newNumDuchy;
	numDuchy = getNumCards(thisPlayer, &G, duchy);
	newNumDuchy = getNumCards(thisPlayer, &testG, duchy);

	printf("num duchy cards = %d, expected = %d\n", newNumDuchy, numDuchy);
	customAssert(newNumDuchy == numDuchy, "Failed test: was able to buy a card with 0 supply");


	if (hasErrors == 0)
		printf("\n >>>>> SUCCESS: %s testing complete <<<<<\n\n", TESTCARD);
	else
		printf("\n >>>>> FAILURE: at least one test failed <<<<<\n\n");


	return 0;
}


