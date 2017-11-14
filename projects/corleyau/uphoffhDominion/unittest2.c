#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int compare_int( const void* a, const void* b )
{
    if( *(int*)a == *(int*)b ) return 0;
    return *(int*)a < *(int*)b ? -1 : 1;
}
 
int main() { 
	
	int seed = 1000;
	int numPlayers = 2;
	
	struct gameState game;
	
	int before[10];
	int after[10];
	
	int k[10] = {adventurer, feast, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	
	printf("--------TESTING int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);-------------\n\n");
	
	//Test adding to deck, check count and array, test supply went down
	gainCard(7, &game, 1, 0);
	printf("Size of deck after gaining card = %d, expected = %d\n", game.deckCount[0], 6);
	assert(game.deckCount[0] == 6);
	printf("Last card of deck after gaining card = %d, expected = %d\n", game.deck[0][5], 7);
	assert(game.deck[0][5] == 7);
	printf("Supply of card added = %d, expected = %d\n", game.supplyCount[7], 9);
	assert(game.supplyCount[7] == 9);
	
	//Test adding to discard, check count and array, test supply went down
	gainCard(8, &game, 0, 1);
	printf("Size of discard after gaining card = %d, expected = %d\n", game.discardCount[1], 1);
	assert(game.discardCount[1] == 1);
	printf("Last card of discard after gaining card = %d, expected = %d\n", game.discard[1][0], 8);
	assert(game.discard[1][0] == 8);
	printf("Supply of card added = %d, expected = %d\n", game.supplyCount[8], 9);
	assert(game.supplyCount[8] == 9);
	
	//Test adding to hand, check count and array, test supply went down
	gainCard(14, &game, 2, 1);
	printf("Size of hand after gaining card = %d, expected = %d\n", game.handCount[1], 1);
	assert(game.handCount[1] == 1);
	printf("Last card of hand after gaining card = %d, expected = %d\n", game.hand[1][0], 14);
	assert(game.hand[1][0] == 14);
	printf("Supply of card added = %d, expected = %d\n", game.supplyCount[14], 9);
	assert(game.supplyCount[14] == 9);
	
	//Test that is supply is empty, function returnes -1
	game.supplyCount[1] = 0;
	int returnValue = gainCard(1, &game, 2, 1);
	printf("Return value if card supply is empty = %d, expected = %d\n", returnValue, -1);
	assert(returnValue == -1);
	
	printf("\n--------SUCCESS: Testing complete-------------\n");
  
    return 0;
}
 