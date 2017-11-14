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
	
	game.deck[0][5] = 7;  
	game.deck[0][6] = 9;
	game.deck[0][7] = 14;
	game.deck[0][8] = 17;
	game.deck[0][9] = 11;
	
	game.deckCount[0] = 10;
	
	printf("--------TESTING int shuffle(int player, struct gameState *state);-------------\n\n");
	printf("Contents of deck Before Shuffle = ");
	
	int i;
	for (i = 0; i < game.deckCount[0]; i++) {
		printf("%d ", game.deck[0][i]);
		before[i] = game.deck[0][i];
	}
	printf(", expected to != ");
	
	shuffle(0, &game);
	
	for (i = 0; i < game.deckCount[0]; i++) {
		printf("%d ", game.deck[0][i]); 
		after[i] = game.deck[0][i];
	}
	
	printf(" (the contents after shuffle)\n");
	
	printf("Size of deck before shuffle = %zu, expected = %d\n", sizeof(before)/sizeof(before[0]), 10);
	printf("Size of deck after shuffle = %zu, expected = %d\n", sizeof(after)/sizeof(after[0]), 10);
    assert(sizeof(before)/sizeof(before[0]) == sizeof(after)/sizeof(after[0])); // check if the number in deck is same before as after
    
    qsort( before, 10, sizeof(int), compare_int );
    qsort( after, 10, sizeof(int), compare_int );
    
    printf("Contents of deck before shuffle SORTED = ");
    
    for (i = 0; i < 10; i++) {
		printf("%d ", before[i]);
	}
	
	printf(", expected to = ");
	 
	for (i = 0; i < 10; i++) {
		printf("%d ", after[i]);
	}
	
	printf(" (the contents after shuffle SORTED)\n");
	
	//test the when sorted the decks, before and after shuffle, match each other
	assert(before[0] == after[0]); 
	assert(before[1] == after[1]);
	assert(before[2] == after[2]);
	assert(before[3] == after[3]);
	assert(before[4] == after[4]);
	assert(before[5] == after[5]);
	assert(before[6] == after[6]);
	assert(before[7] == after[7]);
	assert(before[8] == after[8]);
	assert(before[9] == after[9]);
	
	printf("\n--------SUCCESS: Testing complete-------------\n");
  
    return 0;
}
 