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
	
	printf("--------TESTING int drawCard(int player, struct gameState *state);-------------\n\n");
	
	//test draw card when deck is full, deckCount--, handCount++, right card, returns 0
	printf(">>>>> test draw card when deck is full\n");
	int originalDeckCount;
	int originalCard;
	int originalHandCount;
	originalDeckCount = game.deckCount[0];
	originalCard = game.deck[0][5];
	originalHandCount = game.handCount[0];
	drawCard(0, &game);
	printf("Handcount = %d, expected = %d\n", game.handCount[0], originalHandCount+1);
	printf("Deckcount = %d, expected = %d\n", game.deckCount[0], originalDeckCount-1); 
	printf("Card added to hand = %d, expected = %d\n", game.hand[0][5], originalCard); 
	
	//test draw card when deck has one card, handCount++, right card, returns 0
	printf(">>>>> test draw card when deck has one card\n");
	drawCard(0, &game);
	drawCard(0, &game);
	drawCard(0, &game);
	originalDeckCount = game.deckCount[0];
	originalCard = game.deck[0][5];
	originalHandCount = game.handCount[0];
	drawCard(0, &game);
	printf("Handcount = %d, expected = %d\n", game.handCount[0], originalHandCount+1);
	printf("Deckcount = %d, expected = %d\n", game.deckCount[0], originalDeckCount-1); 
	printf("Card added to hand = %d, expected = %d\n", game.hand[0][6], originalCard); 
	
	//test draw card when deck is empty and needs shuffled, handCount++, right card, returns 0
	//move hand cards to discard cards
	int i;
	for (i = 0; i < 10; i++) {
		game.deck[0][i] = game.hand[0][i];
	}
	game.deckCount[0] = 10;
	game.handCount[0] = 0;
	
	printf(">>>>> test draw card when deck has zero cards\n");
	originalDeckCount = game.deckCount[0];
	originalCard = game.deck[0][9];
	originalHandCount = game.handCount[0];
	drawCard(0, &game);
	printf("Handcount = %d, expected = %d\n", game.handCount[0], 1);
	printf("Deckcount = %d, expected = %d\n", game.deckCount[0], 9); 
	
	//test draw card when deck is empty (return -1)
	
	
	//printf("Size of deck before shuffle = %zu, expected = %d\n", sizeof(before)/sizeof(before[0]), 10);
	//assert(before[0] == after[0]); 
	
	printf("\n--------SUCCESS: Testing complete-------------\n");
  
    return 0;
}
 