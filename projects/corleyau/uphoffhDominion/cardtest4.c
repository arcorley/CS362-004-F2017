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
	 
	int k[10] = {adventurer, feast, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	
	printf("--------TESTING Mine card -------------\n\n");
	//you can trash (remove a card from your deck to the trash deck) one of your treasure cards and in 
	//return you can get a treasure card that is worth 3 more.
	//BUG - It returns zero instead of -1 when the player doesn’t have a card worth at least as much as 
	//a copper or a card less than gold
	
	game.whoseTurn = 1;
	game.handCount[1] = 6;
	game.hand[1][0] = 1;
	game.hand[1][1] = 1;
	game.hand[1][2] = 1;
	game.hand[1][3] = 4;
	game.hand[1][4] = 4;
	game.hand[1][5] = 4;
	int handCountBefore = game.handCount[1];
	int playedCardCountBefore = game.playedCardCount;
	int player1HandCountBefore = game.handCount[1];
	int player2HandCountBefore = game.handCount[0];
	int player1NumBuysBefore = game.numBuys;
	
	int before[5];
	int after[5];
	int i;
	printf("Player 1 hand cards before mine = ");
	for (i = 0; i < game.handCount[1]; i++) {
		printf("%d ", game.hand[1][i]); 
		before[i] = game.hand[1][i];
	}
	int bonus = 0;
	int returnValue;
	returnValue = cardEffect(mine, 0, 0, 0, &game, 5, &bonus);
	
	printf("! = Player 1 hand cards after mine =");
	for (i = 0; i < game.handCount[1]; i++) {
		printf("%d ", game.hand[1][i]);
		after[i] = game.hand[1][i];
	}
	
	printf("\nReturn value = %d, expected = %d\n", returnValue, -1);
	
	
	printf("\n--------FAILED: Testing complete-------------\n");
  
    return 0;
}
 