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
	
	printf("--------TESTING Adventurer card-------------\n\n");
	//If you use this card as your action, you keep drawing from your draw pile until you receive 2 treasure cards (copper, sliver, gold). 
	
	//count and print treasure cards before.
	game.whoseTurn = 0;
	game.deckCount[0] = 10;
	game.deck[0][5] = 4;
	game.deck[0][6] = 5;
	game.deck[0][7] = 6;
	game.deck[0][8] = 4;
	game.deck[0][9] = 6;
	game.handCount[0] = 6;
	game.hand[0][5] = 7;
	
	int treasureCountBefore = 0;
	int i;
	for (i = 0; i < 5; i++) {
		if(game.hand[0][i] == 4 || game.hand[0][i] == 5 || game.hand[0][i] == 6) {
			treasureCountBefore++;
		}
	}
	
	int bonus = 0;
	cardEffect(smithy, 0, 0, 0, &game, 5, &bonus); 
	
	printf("Treasure count before = %d\n", treasureCountBefore);
	
	int treasureCountAfter = 0;
	for (i = 0; i < game.handCount[0]; i++) {
		if(game.hand[0][i] == 4 || game.hand[0][i] == 5 || game.hand[0][i] == 6) {
			treasureCountAfter++;
		}
	}
	
	printf("Treasure count in hand = %d, expected %d (2 more than before)\n", treasureCountAfter, treasureCountBefore+2);
	 
	printf("Played card count after calling adventurer = %d, expected = %d\n", game.playedCardCount, 1);
	printf("Card added to played cards adventurer = %d, expected = %d (number for smithy)\n", game.playedCards[game.playedCardCount-1], 7);
	
	game.whoseTurn = 1;
	
	for (i = 0; i < game.deckCount[1]; i++) {
		game.deck[1][i] = game.discard[1][i];
	}
	game.deckCount[1] = 0;
	game.playedCardCount = 0;
	game.handCount[1] = 6;
	game.hand[1][5] = 7;
	
	printf(">>>>>>Testing with empty deck (need to shuffle)\n");
	
	treasureCountBefore = 0;
	for (i = 0; i < 5; i++) {
		if(game.hand[1][i] == 4 || game.hand[1][i] == 5 || game.hand[1][i] == 6) {
			treasureCountBefore++;
		}
	}
	
	printf("Treasure count before = %d\n", treasureCountBefore);
	
	bonus = 0;
	cardEffect(smithy, 0, 0, 0, &game, 5, &bonus); 
	
	treasureCountAfter = 0;
	for (i = 0; i < game.handCount[0]; i++) {
		if(game.hand[1][i] == 4 || game.hand[1][i] == 5 || game.hand[1][i] == 6) {
			treasureCountAfter++;
		}
	}
	
	printf("Treasure count in hand = %d, expected %d (2 more than before)\n", treasureCountAfter, treasureCountBefore+2);
	 
	printf("Played card count after calling adventurer = %d, expected = %d\n", game.playedCardCount, 1);
	printf("Card added to played cards adventurer = %d, expected = %d (number for smithy)\n", game.playedCards[game.playedCardCount-1], 7);
	
	
	printf("\n--------FAILED: Testing complete-------------\n");
  
    return 0;
}
 