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
	
	printf("--------TESTING Council Room card-------------\n\n");
	//If you play it as your action, you can draw 4 extra cards from your draw pile. 
	//You also get one extra buy.  
	//All other players get one more card from their draw pile to play with once it is their turn.
	//Bug doesn't consistently give other players an extra card
	
	//Start with player one, test that player 0 doesn't get any cards
	game.whoseTurn = 1;
	game.handCount[1] = 6;
	game.hand[1][5] = 8;
	int handCountBefore = game.handCount[1];
	int playedCardCountBefore = game.playedCardCount;
	int player1HandCountBefore = game.handCount[1];
	int player2HandCountBefore = game.handCount[0];
	int player1NumBuysBefore = game.numBuys;
	
	printf("Player 1 handcount before council room = %d, expected = %d\n", player1HandCountBefore, 6);
	printf("Player 2 handcount before council room = %d, expected = %d\n", player2HandCountBefore, 5);
	printf("Player 1 buy count before council room = %d, expected = %d\n", player1NumBuysBefore, 1);
	
	int bonus = 0;
	cardEffect(council_room, 0, 0, 0, &game, 5, &bonus);
	
	int handCountAfter = game.handCount[1];
	int playedCardCountAfter = game.playedCardCount;
	int player1HandCountAfter = game.handCount[1];
	int player2HandCountAfter = game.handCount[0];
	int player1NumBuysAfter = game.numBuys;
	
	printf("Player 1 handcount after council room = %d, expected = %d\n", player1HandCountAfter, player1HandCountBefore+3);
	printf("Player 0 handcount after council room = %d, expected = %d\n", player2HandCountAfter, player2HandCountBefore+1);
	printf("Player 1 buy count after council room = %d, expected = %d\n", player1NumBuysAfter, 2);
	printf("Card added to played cards coucil room = %d, expected = %d (number for council room)\n", game.playedCards[playedCardCountAfter-1], 8);
	
	//Test when deck needs shuffled. This doesn't work then
	printf(">>>>>>Testing with empty deck (need to shuffle)\n");
	game.whoseTurn = 0;
	int i;
	for (i = 0; i < game.deckCount[1]; i++) {
		game.deck[0][i] = game.discard[0][i];
	}
	game.deckCount[0] = 0;
	game.playedCardCount = 0;
	game.handCount[0] = 6;
	game.hand[0][5] = 8;
	
	handCountBefore = game.handCount[1];
	playedCardCountBefore = game.playedCardCount;
	player1HandCountBefore = game.handCount[0];
	player2HandCountBefore = game.handCount[1];
	player1NumBuysBefore = game.numBuys;
	
	printf("Player 0 handcount after council room = %d, expected = %d\n", player1HandCountAfter, player1HandCountBefore+3);
	printf("Player 1 handcount after council room = %d, expected = %d\n", player2HandCountAfter, player2HandCountBefore+1);
	printf("Player 0 buy count after council room = %d, expected = %d\n", player1NumBuysAfter, 2);
	printf("Card added to played cards coucil room = %d, expected = %d (number for council room)\n", game.playedCards[playedCardCountAfter-1], 8);
	
	
	//printf("Size of deck before shuffle = %zu, expected = %d\n", sizeof(before)/sizeof(before[0]), 10);
	//assert(before[9] == after[9]);
	
	printf("\n--------FAILED: Testing complete-------------\n");
  
    return 0;
}
 