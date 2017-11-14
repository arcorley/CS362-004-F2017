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
	
	printf("--------TESTING Smithy card-------------\n\n");
	//If you use this card as your action, you can take 3 cards from your draw pile into your active hand.
	game.whoseTurn = 0;
	game.handCount[0] = 6;
	game.hand[0][5] = 13;
	int handCountBefore = game.handCount[0];
	int playedCardCountBefore = game.playedCardCount;
	
	printf("Handcount before calling smithy = %d, expected = %d\n", handCountBefore, 6);
	printf("Played card count before calling smithy = %d, expected = %d\n", playedCardCountBefore, 0);
	 
	int bonus = 0;
	cardEffect(smithy, 0, 0, 0, &game, 5, &bonus); 
	int handCountAfter = game.handCount[0];
	int playedCardCountAfter = game.playedCardCount; 
	
	printf("Handcount after calling smithy (plus 3 cards, minus the smithy card) = %d, expected = %d\n", handCountAfter, 8);
	printf("Played card count after calling smithy = %d, expected = %d\n", playedCardCountAfter, 1);
	printf("Card added to played cards smithy = %d, expected = %d (number for smithy)\n", game.playedCards[playedCardCountAfter-1], 13);
	
	
	game.whoseTurn = 1;
	int i;
	for (i = 0; i < game.deckCount[1]; i++) {
		game.deck[1][i] = game.discard[1][i];
	}
	game.deckCount[1] = 0;
	game.playedCardCount = 0;
	game.handCount[1] = 6;
	game.hand[1][5] = 13;
	
	printf(">>>>>>Testing with empty deck (need to shuffle)\n");
	handCountBefore = game.handCount[1];
	playedCardCountBefore = game.playedCardCount;
	printf("Handcount before calling smithy = %d, expected = %d\n", handCountBefore, 6);
	printf("Played card count before calling smithy = %d, expected = %d\n", playedCardCountBefore, 0);
	
	bonus = 0;
	cardEffect(smithy, 0, 0, 0, &game, 5, &bonus); 
	handCountAfter = game.handCount[1];
	playedCardCountAfter = game.playedCardCount; 
	
	printf("Handcount after calling smithy (plus 3 cards, minus the smithy card) = %d, expected = %d\n", handCountAfter, 8);
	printf("Played card count after calling smithy = %d, expected = %d\n", playedCardCountAfter, 1);
	printf("Card added to played cards smithy = %d, expected = %d (number for smithy)\n", game.playedCards[playedCardCountAfter-1], 13);

	
	printf("\n--------FAILED: Testing complete-------------\n");
  
    return 0;
}
 