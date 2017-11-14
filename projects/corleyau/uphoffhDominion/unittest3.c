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
	
	printf("--------TESTING int getCost(int cardNumber) -------------\n\n");
   
    int cost;
    
    cost = getCost(0);
 	printf("Cost of curse = %d, expected = %d\n", cost, 0);
 	assert(cost == 0);
 	cost = getCost(1);
 	printf("Cost of estate = %d, expected = %d\n", cost, 2);
 	assert(cost == 2);
 	cost = getCost(2);
 	printf("Cost of duchy = %d, expected = %d\n", cost, 5);
 	assert(cost == 5);
 	cost = getCost(3);
 	printf("Cost of province = %d, expected = %d\n", cost, 8);
 	assert(cost == 8);
 	cost = getCost(4);
 	printf("Cost of copper = %d, expected = %d\n", cost, 0);
 	assert(cost == 0);
 	cost = getCost(5);
 	printf("Cost of silver = %d, expected = %d\n", cost, 3);
 	assert(cost == 3);
 	cost = getCost(6);
 	printf("Cost of gold = %d, expected = %d\n", cost, 6);
 	assert(cost == 6);
 	cost = getCost(7);
 	printf("Cost of adventurer = %d, expected = %d\n", cost, 6);
 	assert(cost == 6);
 	cost = getCost(8);
 	printf("Cost of council_room = %d, expected = %d\n", cost, 5);
 	assert(cost == 5);
 	cost = getCost(9);
 	printf("Cost of feast = %d, expected = %d\n", cost, 4);
 	assert(cost == 4);
 	cost = getCost(10);
 	printf("Cost of gardens = %d, expected = %d\n", cost, 4);
 	assert(cost == 4);
 	cost = getCost(11);
 	printf("Cost of mine = %d, expected = %d\n", cost, 5);
 	assert(cost == 5);
 	cost = getCost(12);
 	printf("Cost of remodel = %d, expected = %d\n", cost, 4);
 	assert(cost == 4);
 	cost = getCost(13);
 	printf("Cost of smithy = %d, expected = %d\n", cost, 4);
 	assert(cost == 4);
 	cost = getCost(14);
 	printf("Cost of village = %d, expected = %d\n", cost, 3);
 	assert(cost == 3);
 	cost = getCost(15);
 	printf("Cost of baron = %d, expected = %d\n", cost, 4);
 	assert(cost == 4);
 	cost = getCost(16);
 	printf("Cost of great_hall = %d, expected = %d\n", cost, 3);
 	assert(cost == 3);
 	cost = getCost(17);
 	printf("Cost of minion = %d, expected = %d\n", cost, 5);
 	assert(cost == 5);
 	cost = getCost(18);
 	printf("Cost of steward = %d, expected = %d\n", cost, 3);
 	assert(cost == 3);
 	cost = getCost(19);
 	printf("Cost of tribute = %d, expected = %d\n", cost, 5);
 	assert(cost == 5);
 	cost = getCost(20);
 	printf("Cost of ambassador = %d, expected = %d\n", cost, 3);
 	assert(cost == 3);
 	cost = getCost(21);
 	printf("Cost of cutpurse = %d, expected = %d\n", cost, 4);
 	assert(cost == 4);
 	cost = getCost(22);
 	printf("Cost of embargo = %d, expected = %d\n", cost, 2);
 	assert(cost == 2);
 	cost = getCost(23);
 	printf("Cost of outpost = %d, expected = %d\n", cost, 5);
 	assert(cost == 5);
 	cost = getCost(24);
 	printf("Cost of salvager = %d, expected = %d\n", cost, 4);
 	assert(cost == 4);
 	cost = getCost(25);
 	printf("Cost of sea_hag = %d, expected = %d\n", cost, 4);
 	assert(cost == 4);
 	cost = getCost(26);
 	printf("Cost of treasure_map = %d, expected = %d\n", cost, 4);
 	assert(cost == 4);
 	
 	
	
	printf("\n--------SUCCESS: Testing complete-------------\n");
  
    return 0;
}
 